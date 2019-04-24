#include <cstdio>
#include <iostream>
#include <vector>

#define GREEDY 0
#define DFS 1
#define HORIZONTAL 0
#define VERTICAL 1

using namespace std;

inline bool is_equal( double a, double b ){

    if( a < b )
        swap(a, b);
    
    if( a - b < 1e-4 )
        return true;
    
    return false;
}

struct Block{

    bool direction; // 0 for horizontal, 1 for vertical
    double x, y;    // Lower left corner
    double length;

    inline void read( double _length ){
        
        int dir;
        length = _length;

        scanf("%d%lf%lf", &dir, &x, &y);
        direction = dir;
    }

    inline double is_center_supported_by(Block &b){ // Checking if center point is supported or not

        if( direction == VERTICAL )
            return false;
        
        double begin_x = b.x;
        double end_x = begin_x + (b.direction == HORIZONTAL ? length : (double)1);

        if (begin_x <= x + length / (double)2 && x + length / (double)2 <= end_x )
            return true;
        
        return false;
    }

    inline double support_count(Block &b){ // Getting supported length

        double begin_x = b.x;
        double end_x = begin_x + (b.direction == HORIZONTAL ? length : 1);

        double sum_begin_x = max(begin_x, x);
        double sum_end_x = min(end_x, x + (direction == HORIZONTAL ? length : 1));

        return max((double)0, sum_end_x - sum_begin_x);
    }

    inline double get_top(){ // Getting top point

        if( direction == VERTICAL )
            return y + length;
        else
            return y + (double)1;
    }

    friend bool operator < (const Block &a, const Block &b){ // For sorting
        return a.y < b.y;
    }
};

struct Construction{

    int N;                      // Number of blocks
    int X, Y;                   // Maximum coordinate values in the input set
    int algorithm;              // Search algorithm

    bool is_found = false;

    double length;

    vector<Block> blocks;       // Blocks to be placed
    vector<bool> used;          // Visited array for dfs
    vector<int> stack;          // Stack for dfs
    vector<int> result_order;   // Block id orders for placement

    inline void read(){

        scanf("%d%lf", &N, &length);

        blocks.resize(N);
        used.resize(N, false);
        stack.resize(N);
        result_order.resize(N);

        for( int i=0 ; i<N ; i++ )
            blocks[i].read(length);
    }

    inline bool dfs( int depth=0 ){

        if( depth == N )
            return is_found = true;

        for( int i=0 ; i<N ; i++ )
            if( !used[i] ){
                    if( blocks[i].y == 0 ){

                        used[i] = true;
                        stack[depth] = i;
                        
                        if( dfs(depth + 1) )
                            return true;
                        
                        used[i] = false;
                    }
                    else{

                        double cur = 0;
                        bool flag = false;

                        for( int j=0 ; j<depth ; j++ )
                            if( is_equal(blocks[stack[j]].get_top(), blocks[i].y )){

                                if ( blocks[i].direction == HORIZONTAL && blocks[i].is_center_supported_by(blocks[stack[j]])){
                                    flag = true;
                                    break;
                                }

                                else
                                    cur += blocks[i].support_count(blocks[stack[j]]);
                            }

                        if ((blocks[i].direction == HORIZONTAL && (flag || cur >= (length * (double)2 / (double)3))) ||
                            (blocks[i].direction == VERTICAL && is_equal(cur, (double)1))){

                            used[i] = true;
                            stack[depth] = i;

                            if (dfs(depth + 1))
                                return true;

                            used[i] = false;
                        }
                    }
                }
            
        return false;
    }

    inline bool greedy(){

    }

    inline void set_algorithm( int _algorithm ){

        if (-1 < _algorithm && _algorithm < 2)
            algorithm = _algorithm;
        else
            algorithm = GREEDY; // GREEDY will be set in case of an invalid input
    }

    inline void search(){

        if (algorithm == GREEDY)
            greedy();
        else if(algorithm == DFS)
            dfs();

    }

    inline void print_result(){

        if( algorithm == DFS ){

            if( !is_found ){
                puts("There is no valid solution");
                cerr << "There is no valid solution" << endl;
                return;
            }

            printf("%d %lf\n", N, length);
            for( int i=0 ; i<N ; i++ )
                printf("%d %d %lf %lf\n", stack[i], blocks[stack[i]].direction, blocks[stack[i]].x, blocks[stack[i]].y);
        }
        else{}
    }

};

int main( int argc, char **argv ){

    if( argc != 2 ){
        puts("Usage is:\n./blocks <algorithm number>");
        return 0;
    }

    Construction construction;

    construction.read();
    construction.set_algorithm(argv[1][0] - '0');
    construction.search();
    construction.print_result();

    return 0;
}