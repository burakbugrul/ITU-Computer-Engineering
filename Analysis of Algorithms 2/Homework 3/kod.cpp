/*
 * 
 * Muhammed Burak Bugrul
 * 150140015
 * Ford-Fulkerson algorithm implementation
 * 
 */
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>

#define fi first
#define se second
#define pb push_back
#define SIZE(a) ((int)a.size())

using namespace std;

const int INF = 1e9;
const int MAXN = 1e4;

int N,M,source,sink;
int from[MAXN]; // For tracking the path obtained form BFS
int graph[MAXN][MAXN]; // Graph matrix representation, easy for performing Ford-Fulkerson Algorithm

bool used[MAXN]; // For BFS
bool read[MAXN]; // Assignment control

string name[MAXN]; // Name of nodes in the graph

vector<int> profs,ast_profs,asts; // prof IDs, ast_prof IDs and ast IDs
vector<int> reviewers[MAXN]; // reviewers[i] holds people that read publication i

inline bool bfs(){

    queue<int> q;
    q.push(source); // Starting BFS from source

    memset(used,0,sizeof used); // Clearing used array
    used[source] = true; // We have discovered source node

    while( !q.empty() ){

        int node = q.front();
        q.pop();

        for( int i=0 ; i<=sink ; i++ )
            if( graph[node][i] > 0  && !used[i] ){ // Finding an unvisited neighbour node
                q.push(i);
                from[i] = node;
                used[i] = true;
                if( i == sink )
                    return true; // We found a flow
            }
    }

    return false;
}

int main( int argc, char **argv ){

	ifstream reviewer_file(argv[1]),publication_file(argv[2]);
	ofstream output("output.txt");
	
    reviewer_file >> M;

    for( int i=1 ; i<=M ; i++ ){

        reviewer_file >> name[i] >> graph[source][i]; // Reading name of the reviewer and its reading limit, it will be weight of the edge from source to itself

        if( name[i][0] == 'P' || name[i][0] == 'p' ) // Finding reviever types and saving theri IDs
            profs.pb(i);
        else if( name[i][3] == 'P' || name[i][3] == 'p' )
            ast_profs.pb(i);
        else
            asts.pb(i);
    }

    publication_file >> N;
    sink = N+M+1;

    for( int i=M+1 ; i<sink ; i++ ){

        publication_file >> name[i]; // Reading name of the publication

        if( name[i][0] == 'J' || name[i][0] == 'j' ){

            graph[i][sink] = 2; // Journals should be reviewed by 2 persons

            for( vector<int>::iterator it = profs.begin() ; it != profs.end() ; it++ ) // Prof-Journal edges
                graph[*it][i] = 1;
        }
        else if( name[i][0] == 'C' || name[i][0] == 'c' ){

            graph[i][sink] = 3; // ConfProcs should be reviewed by 3 persons

            for( vector<int>::iterator it = profs.begin() ; it != profs.end() ; it++ ) // Prof-ConfProc edges
                graph[*it][i] = 1;
            for( vector<int>::iterator it = ast_profs.begin() ; it != ast_profs.end() ; it++ ) // AstProf-ConfProc edges
                graph[*it][i] = 1;
        }
        else{

            graph[i][sink] = 2; // WorkProcs should be reviewed by 2 persons

            for( vector<int>::iterator it = profs.begin() ; it != profs.end() ; it++ ) // Prof-WorkProc edges
                graph[*it][i] = 1;
            for( vector<int>::iterator it = ast_profs.begin() ; it != ast_profs.end() ; it++ ) // AstProf-WorkProc edges 
                graph[*it][i] = 1;
            for( vector<int>::iterator it = asts.begin() ; it != asts.end() ; it++ ) // Ast-WorkProc edges
                graph[*it][i] = 1;
        }
    }

    while( bfs() ){ // Performing Ford-Filkerson algorithm on graph with source node 0 and sink node N+M+1

        int reviewer,publication;

        for( int node = sink ; node != source ; node = from[node] ){ // Iterating flow path
            
            if( node > 0 && node <= M ) // Finding reviewer node in the flow path
                reviewer = node;
            if( node > M && node < sink ) // Finding publication node in the flow path
                publication = node;
            
            graph[from[node]][node]--; // Reversing edges by amount of flow(always 1 for this problem)
            graph[node][from[node]]++;
        }

		read[publication] = true; // This publication is reviewed by at least one person
        reviewers[publication].pb(reviewer); // Saving reviewer for this publication
    }

    for( int i=M+1 ; i<sink ; i++ )
        if( !read[i] )
            output << name[i] << " is NOT assigned\n";
        else{
			
			output << name[i] << " is assigned to " << name[reviewers[i][0]];
			
			for( int j=1 ; j<SIZE(reviewers[i]); j++ )
				output << "," << name[reviewers[i][j]];
			
			output << ".\n";
		}

    return 0;
}
