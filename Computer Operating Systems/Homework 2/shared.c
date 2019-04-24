#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <signal.h>

#define MOD 50
#define SIGNAL 12
#define KEYSEM ftok(strcat(get_current_dir_name(),argv[0]),1)
#define KEYSEM2 ftok(strcat(get_current_dir_name(),argv[0]),2)
#define KEYSHM ftok(strcat(get_current_dir_name(),argv[0]),3)

void sem_signal( int semid, int val ){
	
	struct sembuf semaphore;
	semaphore.sem_num = 0;
	semaphore.sem_op = val;
	semaphore.sem_flg = 1;
	
	semop(semid,&semaphore,1);
}

void sem_wait( int semid, int val ){
	
	struct sembuf semaphore;
	semaphore.sem_num = 0;
	semaphore.sem_op = (-1*val);
	semaphore.sem_flg = 1;
	
	semop(semid,&semaphore,1);
}

void mysignal( int signum ){
}

void mysigset( int num ){
	
	struct sigaction mysigaction;
	mysigaction.sa_handler = (void *) mysignal;
	mysigaction.sa_flags = 0;
	sigaction(num,&mysigaction,NULL);
}

int main( int argc, char **argv ){
	
	mysigset(SIGNAL);
	srand(time(NULL));
	
	int shmid = 0;
	int *globalcp = NULL;
	int cnt;
	int termSem = 0, lock = 0;
	int f;
	int child[2];
	int i, myOrder = 0;
	int n,M;
	
	for( i=0 ; i<2 ; i++ ){
		
		f = fork();
		
		if( f == -1 ){
			printf("Fork hatasi olustu\n");
			exit(1);
		}
		
		if( f == 0 )
			break;
		
		child[i] = f;
	}
	
	if( f != 0 ){
		
		printf("A dizisinin eleman sayisini giriniz(n): ");
		fflush(stdout);
		scanf("%d",&n);
		
		termSem = semget(KEYSEM2,1,0700|IPC_CREAT);
		semctl(termSem,0,SETVAL,0);
		
		lock = semget(KEYSEM,1,0700|IPC_CREAT);
		semctl(lock,0,SETVAL,1);
		
		shmid = shmget(KEYSHM,sizeof(int)*(n*3+5),0700|IPC_CREAT);
		globalcp = (int *)shmat(shmid,0,0);
		
		for( i=0 ; i<n ; i++ )
			globalcp[i+4] = rand()%MOD;
		
		printf("A dizisi: ");
		
		for( i=0 ; i<n ; i++ )
			printf("%d ",globalcp[i+4]);
		
		puts("");
		
		printf("A dizsinin baslangic adresi %u\n",(globalcp+4));
		printf("M sayisini giriniz: ");
		fflush(stdout);
		scanf("%d",&M);
		globalcp[0] = n;
		globalcp[1] = M;
		shmdt(globalcp);
		sleep(2);
		
		for( i=0 ; i<2 ; i++ )
			kill(child[i],SIGNAL);
		
		sleep(2);
		sem_wait(termSem,2);
		semctl(termSem,0,IPC_RMID,0);
		semctl(lock,0,IPC_RMID,0);
		shmctl(shmid,IPC_RMID,0);
		
		exit(0);
	}
	else{
		
		myOrder = i;
		pause();
		lock = semget(KEYSEM,1,0);
		termSem = semget(KEYSEM2,1,0);
		
		shmid = shmget(KEYSHM,sizeof(int)*(n*3+5),0);
		globalcp = (int *) shmat(shmid,0,0);
		globalcp[myOrder+2] = 0; // x ve y sayilari
		
		sem_wait(lock,1);
		
		n = globalcp[0];
		M = globalcp[1];
		//~ printf("%d %d-------\n",n,M);
		
		for( i=4 ; i<n+4 ; i++ ){
			//~ printf("%d-\n",globalcp[i]);
			if( ( myOrder == 0 && globalcp[i] <= M ) || ( myOrder == 1 && globalcp[i] > M ) )
				globalcp[myOrder+2]++;
			}
		
		printf("Cocuk %d: eleman sayisi: %d\n",myOrder+1,globalcp[myOrder+2]);
		
		if( myOrder == 0 ){
			
			cnt = 0;
			
			for( i=4 ; i<n+4 ; i++ )
				if( globalcp[i] <= M ){
					globalcp[n+4+cnt] = globalcp[i];
					cnt++;
				}
			
			printf("Cocuk 1: B dizisinin baslangic adresi: %u\n",(int)(globalcp+n+4));
			printf("Cocuk 1: B dizisi: ");
			fflush(stdout);
			
			for( i=0 ; i<globalcp[myOrder+2] ; i++ )
				printf("%d ",globalcp[n+4+i]);
			
			puts("");
		}
		else{
			
			cnt = 0;
			
			for( i=4 ; i<n+4 ; i++ )
				if( globalcp[i] > M ){
					globalcp[n+4+globalcp[2]+cnt] = globalcp[i];
					cnt++;
				}
			
			printf("Cocuk 1: C dizisinin baslangic adresi: %u\n",globalcp+n+globalcp[2]+4);
			printf("Cocuk 2: C dizisi: ");
			fflush(stdout);
			
			for( i=0 ; i<globalcp[myOrder+2] ; i++ )
				printf("%d ",globalcp[n+4+globalcp[2]+i]);
			
			puts("");
		}
		
		sem_signal(lock,1);
		sleep(1);
		
		shmdt(globalcp);
		sem_signal(termSem,1);
		exit(0);
	}
	
	return 0;
}
