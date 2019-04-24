//--------------------------------------------------------------------
// Author: Muhammed Burak Bugrul
// ID: 150140015
//--------------------------------------------------------------------

#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define pb push_back
#define SIZE(a) ((int)a.size())

using namespace std;

typedef long long int Lint;

const Lint POWER = 1e2+7;
const Lint MOD = 1e9+7;
const int MAXN = 7;
const int N = 6;

struct Block{
	
	int x,y,length;
	char direction;
	
	Block( int _x=0 , int _y=0 , int _length=0 , int _direction=0 , int _is_target=0 ){
		x = _x; y = _y; length = _length; direction = _direction;
	}
};

struct Node{
	
	Lint hash;
	
	vector<Block> blocks;
	
	Node(){
		hash = -1;
	}
	
	void fill( bool ar[][MAXN] ){ // Filling a look-up table 
		
		for( int i=0 ; i<SIZE(blocks) ; i++ )
			if( blocks[i].direction == 'v' )
				for( int j=0 ; j<blocks[i].length ; j++ )
					ar[blocks[i].x-j][blocks[i].y] = 1;
			else
				for( int j=0 ; j<blocks[i].length ; j++ )
					ar[blocks[i].x][blocks[i].y+j] = 1;
	}
	
	void print(){
		
		for( int i=0 ; i<SIZE(blocks) ; i++ )
			printf("%d %d %d %c\n",blocks[i].x,blocks[i].y,blocks[i].length,blocks[i].direction);
	}
	
	Lint getHash(){
		
		if( hash != -1 ) // If it has calculated before, there is no need to calculate it again
			return hash;
		
		hash = 0;
		Lint power = POWER;
		
		for( int i=SIZE(blocks)-1 ; i>=0 ; i-- ){ // 107 base and modulo 1000000007
			
			hash = ( hash + (blocks[i].length*power)%MOD )%MOD;
			power = (power*POWER)%MOD;
			
			hash = ( hash + (blocks[i].y*power)%MOD )%MOD;
			power = (power*POWER)%MOD;
			
			hash = ( hash + (blocks[i].x*power)%MOD )%MOD;
			power = (power*POWER)%MOD;
		}
		
		return hash;
	}
};

set<Lint> visited_dfs; // Cycle detection for DFS
map<Lint,Node> visited; // Cycle detection and path finding for BFS
queue<Node> Q; // Queue of BFS
stack<Node> S; // Path finding for DFS
int maximum,length; // Calculation holders for DFS

bool dfs( Node node  ){
	
	S.push(node); // Adding node to current path
	visited_dfs.insert(node.getHash()); // Adding hash value to set for cycle detection
	maximum = max(maximum,SIZE(S)); // Maximum number of nodes kept
	
	bool board[MAXN][MAXN]; // Look-up table
	
	if( node.blocks[0].y == N-node.blocks[0].length+1 ){ // Target node control
		
		length = SIZE(S); // Path length
		stack<Node> write;
		
		while( !S.empty() ){
			write.push(S.top());
			S.pop();
		}
		
		while( !write.empty() ){
			write.top().print();
			write.pop();
		}
	
		return true; // We found a path
	}
	
	memset(board,0,sizeof board);
	node.fill(board);
	
	for( int i=0 ; i<SIZE(node.blocks) ; i++ ){
		
		int x = node.blocks[i].x;
		int y = node.blocks[i].y;
		int length = node.blocks[i].length;
		
		if( node.blocks[i].direction == 'v' ){ // Vertical
			
			if( 1 <= x-length && !board[x-length][y] ){
				Node tmp = node;
				tmp.hash = -1;
				tmp.blocks[i].x--; // Creating the new node
				if( visited_dfs.find(tmp.getHash()) == visited_dfs.end() && dfs(tmp) ) // Cycle control and calling dfs
					return true; // We found a path
			}
			if( x+1 <= N && !board[x+1][y] ){
				Node tmp = node;
				tmp.hash = -1;
				tmp.blocks[i].x++;// Creating the new node
				if( visited_dfs.find(tmp.getHash()) == visited_dfs.end() && dfs(tmp) ) // Cycle control and calling dfs
					return true; // We found a path
			}
		}
		else{
		
			if( 1 <= y-1 && !board[x][y-1] ){
				Node tmp = node;
				tmp.hash = -1;
				tmp.blocks[i].y--;// Creating the new node
				if( visited_dfs.find(tmp.getHash()) == visited_dfs.end() && dfs(tmp) ) // Cycle control and calling dfs
					return true; // We found a path
			}
			if(  y+length <= N && !board[x][y+length] ){
				Node tmp = node;
				tmp.hash = -1;
				tmp.blocks[i].y++;// Creating the new node
				if( visited_dfs.find(tmp.getHash()) == visited_dfs.end() && dfs(tmp) ) // Cycle control and calling dfs
					return true; // We found a path
			}
		}
	}
	
	S.pop(); // Keeping path corrently
	return false; // We couldn;t find a path by using this node
}

int bfs( Node start ){
	
	int cnt = -1; // This will be path length
	Node finish; // For ending path finding loop
	finish.hash = -1;
	
	visited[start.getHash()] = finish;
	Q.push(start); // Start node
	
	while( !Q.empty() ){
		
		bool board[MAXN][MAXN];
		Node current = Q.front(); // Taking a new node from queue
		Q.pop();
		
		if( current.blocks[0].y == N-current.blocks[0].length+1 ){ // Target node control
			
			cnt = 0; // Initializing path length
			Lint cur = current.getHash();
			stack<Node> write;
			write.push(current); // Last node
			
			while( visited[cur].hash != -1 ){
				cnt++;
				write.push(visited[cur]);
				cur = visited[cur].getHash();
			}
			
			while( !write.empty() ){
				write.top().print();
				write.pop();
			}
			
			break;
		}
		
		memset(board,0,sizeof board);
		current.fill(board);
		
		for( int i=0 ; i<SIZE(current.blocks) ; i++ ){
			
			int x = current.blocks[i].x;
			int y = current.blocks[i].y;
			int length = current.blocks[i].length;
			
			if( current.blocks[i].direction == 'v' ){
				
				if( 1 <= x-length && !board[x-length][y] ){
					Node tmp = current;
					tmp.hash = -1;
					tmp.blocks[i].x--; // Creating the new node
					if( visited.find(tmp.getHash()) == visited.end() ){ // Cycle control
						Q.push(tmp);
						visited[tmp.getHash()] = current;
					}
				}
				if( x+1 <= N && !board[x+1][y] ){
					Node tmp = current;
					tmp.hash = -1;
					tmp.blocks[i].x++; // Creating the new node
					if( visited.find(tmp.getHash()) == visited.end() ){ // Cycle control
						Q.push(tmp);
						visited[tmp.getHash()] = current;
					}
				}
			}
			else{
			
				if( 1 <= y-1 && !board[x][y-1] ){
					Node tmp = current;
					tmp.hash = -1;
					tmp.blocks[i].y--; // Creating the new node
					if( visited.find(tmp.getHash()) == visited.end() ){ // Cycle control
						Q.push(tmp);
						visited[tmp.getHash()] = current;
					}
				}
				if(  y+length <= N && !board[x][y+length] ){
					Node tmp = current;
					tmp.hash = -1;
					tmp.blocks[i].y++; // Creating the new node
					if( visited.find(tmp.getHash()) == visited.end() ){ // Cycle control
						Q.push(tmp);
						visited[tmp.getHash()] = current;
					}
				}
			}
		}
	}
	
	return cnt; // Returns path length, if no path found returns -1
}

int main( int argc , char **argv ){
	
	freopen(argv[2],"r",stdin);
	freopen(argv[3],"w",stdout);
	
	Block tmp;
	Node start;
	
	while( scanf("%d%d%d %c",&tmp.x,&tmp.y,&tmp.length,&tmp.direction) != EOF )
		start.blocks.pb(tmp);
	
	if( !strcmp(argv[1],"bfs") ){
		int cnt = bfs(start);
		
		if( cnt == -1 )
			cerr << "There is no way to reach target" << endl;
		else{
			cerr << "A way found" << endl;
			cerr << "Length is: " << cnt << endl;
		}
		cerr << "Maximum number of nodes kept in memory are: " << SIZE(visited) << endl;
		cerr << "Number of nodes found are: " << SIZE(visited) << endl;
	}
	else{
		
		if( !dfs(start) )
			cerr << "There is no way to reach target" << endl;
		else{
			cerr << "A way found" << endl;
			cerr << "Length is: " << length << endl;
		}
		
		cerr << "Maximum number of nodes kept in memory are: " << maximum << endl;
		cerr << "Number of nodes found are: " << SIZE(visited_dfs) << endl;
	}
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}
