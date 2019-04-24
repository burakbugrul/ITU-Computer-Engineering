#include <cstdio>
#include <cstring>
#include <iostream>
#include <ctime>

using namespace std;

const int MAXN = 2e5;

int z[MAXN];    // Z array, z[i] holds maximum length we can match with prefix of string s starting from ith indice

char s[MAXN];   // Initial string

inline int z_function(string &text, string &pattern) {

    int l = 0, r = 0;                                   // Left and right boundaries of current prefix match
    int result = 0;

    string s = pattern + "#" + text;

    for( int i = 1 ; i < (int)s.size() ; i++ ) {

        z[i] = max(0, min(z[i - l], r - i + 1));        // We can use previously calculated values for new z[i] value, but we can not go beyond right boundary without checking values

        while (i + z[i] < (int)s.size() && s[i + z[i]] == s[z[i]])  // Checking values beyond right boundary in a simple way
            z[i]++;
        
        if( i + z[i] - 1 > r ) {                        // Setting new boundaries
            l = i;
            r = i + z[i] - 1;
        }

        if (z[i] == (int)pattern.size()) {
            return true;
        }
    }
    
    return false;
}

int main(){

    string text, pattern;
    clock_t t;

    cin >> text >> pattern;

    t = clock();

    cerr << z_function(text, pattern) << endl;

    t = clock() - t;

    cout << ((float)t) / CLOCKS_PER_SEC << endl;

    return 0;
}