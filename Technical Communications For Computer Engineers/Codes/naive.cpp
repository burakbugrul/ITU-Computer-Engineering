#include <cstdio>
#include <cstring>
#include <iostream>
#include <ctime>

using namespace std;

inline bool naive_search( string &text, string &pattern ) {

    for( int i=0 ; i <= (int)text.size() - (int)pattern.size() ; i++ ) {

        bool flag = true;

        for( int j=0 ; j < (int)pattern.size() ; j++ )
            if ( text[i + j] != pattern[j] ) {
                flag = false;
                break;
            }
        
        if (flag) {
            return true;
        }
    }

    return false;
}

int main() {

    string text, pattern;
    clock_t t;

    cin >> text >> pattern;

    t = clock();

    cerr << naive_search(text, pattern) << endl;

    t = clock() - t;

    cout << ((float)t) / CLOCKS_PER_SEC << endl;

    return 0;
}