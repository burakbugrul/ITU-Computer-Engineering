#include <cstdio>
#include <cstring>
#include <iostream>
#include <ctime>
#include <vector>

using namespace std;

inline bool rabin_karp(string const& t, string const& s) {

    const int p = 31; 
    const int m = 1e9 + 9;
    int S = s.size(), T = t.size();

    vector<long long> p_pow(max(S, T)); 
    p_pow[0] = 1; 

    for (int i = 1; i < (int)p_pow.size(); i++) 
        p_pow[i] = (p_pow[i-1] * p) % m;

    vector<long long> h(T + 1, 0); 

    for (int i = 0; i < T; i++)
        h[i+1] = (h[i] + (t[i] - 'a' + 1) * p_pow[i]) % m; 
    
    long long h_s = 0; 

    for (int i = 0; i < S; i++) 
        h_s = (h_s + (s[i] - 'a' + 1) * p_pow[i]) % m; 

    for (int i = 0; i + S - 1 < T; i++) { 

        long long cur_h = (h[i+S] + m - h[i]) % m; 

        if (cur_h == h_s * p_pow[i] % m)
            return true;
    }

    return false;
}

int main() {

    string text, pattern;
    clock_t t;

    cin >> text >> pattern;

    t = clock();

    cerr << rabin_karp(text, pattern) << endl;

    t = clock() - t;

    cout << ((float)t) / CLOCKS_PER_SEC << endl;

    return 0;
}