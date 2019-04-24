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

struct DFS{

    set<long long int> visited;
    int nodeCount = 1;
    int maxNodeCount = 0;
    int totalNodeCount = 1;
    double t;

    bool _run( Node current ){

        vector<Node> neighbours = current.getNeighbours();
        nodeCount += (int)neighbours.size();
        totalNodeCount += (int)neighbours.size();
        maxNodeCount = max(maxNodeCount, nodeCount);

        if( (int)neighbours.size() == 0 ){
            printf("A final state has been found!\n");
            printf("Number of moves: %d\n", current.depth);
            printf("Maximum number of nodes kept in the memory: %d\n", maxNodeCount);
            printf("Number of generated nodes: %d\n", totalNodeCount);
            printf("Number of nodes expanded: %d\n", (int)visited.size());
            printf("Number of pegs in the final state: %d\n", PEGS - current.depth);
            printf("Final state:\n\n");
            current.printState();
            return true;
        }

        for (Node neighbour : neighbours){

            visited.insert(neighbour.getHash()); // Depth first iteration
            
            if( _run(neighbour) )
                return true;
        }

        nodeCount -= (int)neighbours.size();
        return false;
    }

    inline void run( Node start ){
        t = clock();
        _run(start);
        t = clock() - t;
        printf("Run time of algorithm took: %lf seconds\n\n", t / CLOCKS_PER_SEC);
    }
};

int main(){

    Node start;
    DFS dfs;
    dfs.run(start);

    return 0;
}