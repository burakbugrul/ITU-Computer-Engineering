#include <cstdio>
#include <cstring>
#include <iostream>
#include <ctime>

using namespace std;

inline bool kmp( string &text, string &pattern ) {

    int next[(int)pattern.size() + 1];
    int result = 0;

    memset(next, 0, sizeof next);

    for( int i=1 ; i < (int)pattern.size() ; i++ ) {

        int j = next[i + 1];

        while( j > 0 && pattern[i] != pattern[j] )
            j = next[j];
        
        if( j > 0 || pattern[i] == pattern[j] )
            next[i + 1] = j + 1;
    }

    for( int i=0, j=0 ; i < (int)text.size() ; i++ ) {

        if( text[i] == pattern[j] ) {

            j++;

            if( j == (int)pattern.size() ) {
                return true;
            }
        } else if( j > 0 ) {
            j = next[j];
            i--;
        }
    }

    return false;
}

int main() {

    string text, pattern;
    clock_t t;

    cin >> text >> pattern;

    t = clock();

    cerr << kmp(text, pattern) << endl;

    t = clock() - t;

    cout << ((float)t) / CLOCKS_PER_SEC << endl;

    return 0;
}