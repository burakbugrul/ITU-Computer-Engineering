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

struct AStar{

    int maxNodeCount = 0;
    int totalNodeCount = 1;
    int heuristicChoice;
    priority_queue<Node> PQ;
    set<long long int> visited;
    double t;

    AStar(Node start, int h){
        t = clock();
        heuristicChoice = h;
        PQ.push(start);
        visited.insert(start.getHash());
    }

    inline void run(){

        while( !PQ.empty() ){

            maxNodeCount = max(maxNodeCount, (int)PQ.size()); // Taking the best cost valued node

            Node current = PQ.top();
            PQ.pop();

            visited.insert(current.getHash());

            vector<Node> neighbours = current.getNeighbours();
            totalNodeCount += (int)neighbours.size();

            if ((int)neighbours.size() == 0){

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

            for( Node neighbour : neighbours ){

                neighbour.depth = current.depth + 1;
                
                if( heuristicChoice == 1 )
                    neighbour.heuristic1();
                else
                    neighbour.heuristic2();
                
                PQ.push(neighbour);
            }
        }
    }
};

int main( int argc, char **argv ){

    if( argc != 2 ){
        puts("You should run the code as ./a_star <heuristic choice{1, 2}>");
        return 0;
    }

    Node start;
    AStar a_star(start, argv[1][0] - '0');
    a_star.run();

    return 0;
}