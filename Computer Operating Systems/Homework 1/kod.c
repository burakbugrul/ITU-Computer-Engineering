#include <stdio.h>
#include <unistd.h>

int main(){
	
	int i = 1;
	int sonuc = 0;
	
	for( i=1 ; i<=3 ; i++ ){
		
		sonuc = fork();
		
		if( sonuc == 0 ){
			printf("Cocuk proses %d. \n",i);
			break;
		}
		else
			printf("Anne proses (i=%d). \n",i);
	}
	
	return 0;
}
