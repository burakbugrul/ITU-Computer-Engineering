/*
 * Muhammed Burak Bugrul
 * 150140015
 * AI - Assignment 1
 * 09.11.2018
 */
#ifndef NODE_HPP
#define NODE_HPP

#include <cstdio>
#include <iostream>
#include <queue>
#include <set>
#include <vector>

using namespace std;

const int N = 7; // Board size
const int D = 4; // Number of ways to move
const int PEGS = 32; // Number of pegs in initial state
const int direction[D][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}}; // 4 ways

const bool board[N][N] = {{0, 0, 1, 1, 1, 0, 0},
                          {0, 0, 1, 1, 1, 0, 0},
                          {1, 1, 1, 1, 1, 1, 1},
                          {1, 1, 1, 1, 1, 1, 1},
                          {1, 1, 1, 1, 1, 1, 1},
                          {0, 0, 1, 1, 1, 0, 0},
                          {0, 0, 1, 1, 1, 0, 0}}; // Valid places in the board

struct Node{

    long long int hash = -1LL; // Hash is for keeping expanded nodes in memory
    bool state[N][N]; // Representation
    int depth = 0; // Number of moves done so far
    int heuristicCost; // Current heuristic cost of the node

    Node(){ // Constructor

        depth = 0;
        hash = -1LL;

        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                state[i][j] = board[i][j];

        state[3][3] = false;
    }

    Node(const bool state_[N][N]){ // Constructor with a specific state

        depth = 0;
        hash = -1LL;

        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                state[i][j] = state_[i][j];
    }

    inline long long int getHash(){ // Hash generate function with a cache

        if (hash != -1LL) // Cache control(Like memoization in dynamic programming)
            return hash;

        int power = 0; // Power of two
        hash = 0LL; // Current hash

        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++, power++)
                hash += (1LL << power) * state[i][j]; // Treating the state as a binary number

        return hash;
    }

    inline vector<Node> getNeighbours(){ // Trying to do every possible movement

        vector<Node> neighbours;

        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                if (board[i][j] && state[i][j])
                    for (int k = 0; k < D; k++){

                        int middleX = i + direction[k][0]; // Peg in the middle
                        int middleY = j + direction[k][1];

                        int destinationX = i + 2 * direction[k][0]; // New place of moved peg
                        int destinationY = j + 2 * direction[k][1];

                        if (0 <= destinationX && destinationX < N &&
                            0 <= destinationY && destinationY < N &&
                            board[destinationX][destinationY] && !state[destinationX][destinationY] &&
                            state[middleX][middleY]){ // Valid move check

                            Node tmp = Node(state); // Createing a new neighbour
                            tmp.state[i][j] = tmp.state[middleX][middleY] = false;
                            tmp.state[destinationX][destinationY] = true;
                            tmp.depth = depth + 1;
                            neighbours.push_back(tmp);
                        }
                    }

        return neighbours;
    }

    inline void heuristic1(){ // Number of holes that can be occupied in next move

        set<pair<int, int> > cnt;

        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                if (board[i][j] && state[i][j])
                    for (int k = 0; k < D; k++){

                        int middleX = i + direction[k][0];
                        int middleY = j + direction[k][1];

                        int destinationX = i + 2 * direction[k][0];
                        int destinationY = j + 2 * direction[k][1];

                        if( 0 <= destinationX && destinationX < N &&
                            0 <= destinationY && destinationY < N &&
                            board[destinationX][destinationY] && !state[destinationX][destinationY] &&
                            state[middleX][middleY] )
                                cnt.insert(pair<int, int>(destinationX, destinationY));
                    }
        
        heuristicCost = (int)cnt.size();
    }

    inline void heuristic2(){ // Number of pegs that can be moved

        int cnt = 0;

        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                if (board[i][j] && state[i][j])
                    for (int k = 0; k < D; k++){

                        int middleX = i + direction[k][0];
                        int middleY = j + direction[k][1];

                        int destinationX = i + 2 * direction[k][0];
                        int destinationY = j + 2 * direction[k][1];

                        if( 0 <= destinationX && destinationX < N &&
                            0 <= destinationY && destinationY < N &&
                            board[destinationX][destinationY] && !state[destinationX][destinationY] &&
                            state[middleX][middleY] ){
                                cnt++;
                                break;
                            }
                    }

        heuristicCost = cnt;
    }

    friend bool operator < ( const Node &a, const Node &b ){ // Compare operator overloading for priority queue
        return a.depth + a.heuristicCost > b.depth + b.heuristicCost; // A* heuristic
    }

    inline void printState(){

        for (int i = 0; i < N; i++, puts(""))
            for (int j = 0; j < N; j++)
                if (!board[i][j])
                    printf("  ");
                else if (state[i][j])
                    printf("* ");
                else
                    printf(". ");

        printf("---------------------------\n");
    }
};

#endif // NODE_HPP