/*
 * Muhammed Burak Bugrul
 * 150140015
 * AI - Assignment 1
 * 09.11.2018
 */
#include <cstdio>
#include <iostream>
#include <queue>
#include <set>
#include <vector>
#include <cmath>
#include <ctime>

#include "node.hpp"

using namespace std;

struct BFS{

    int maxNodeCount = 0;
    int totalNodeCount = 1;
    double t;
    queue<Node> Q;
    set<long long int> visited;

    BFS( Node start ){
        t = clock();
        Q.push(start);
        visited.insert(start.getHash());
    }

    inline void run(){

        while( !Q.empty() ){

            maxNodeCount = max(maxNodeCount, (int)Q.size());

            Node current = Q.front(); // Breadth first iteration
            Q.pop();

            visited.insert(current.getHash());

            vector<Node> neighbours = current.getNeighbours();
            totalNodeCount += (int)neighbours.size();

            if( (int)neighbours.size() == 0 ){

                printf("A final state has been found!\n");
                printf("Number of moves: %d\n", current.depth);
                printf("Maximum number of nodes kept in the memory: %d\n", maxNodeCount);
                printf("Number of generated nodes: %d\n", totalNodeCount);
                printf("Number of nodes expanded: %d\n", (int)visited.size());
                printf("Number of pegs in the final state: %d\n", PEGS - current.depth);
                printf("Final state:\n\n");
                current.printState();
                t = clock() - t;
                printf("Run time of algorithm took: %lf seconds\n\n", t / CLOCKS_PER_SEC);
                return;
            }

            for( Node neighbour : neighbours )
                Q.push(neighbour);
        }
    }

};

int main(){

    Node start;
    BFS bfs(start);
    bfs.run();

    return 0;
}