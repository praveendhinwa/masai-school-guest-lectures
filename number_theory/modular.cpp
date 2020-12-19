#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <queue>
#include <deque>
#include <bitset>
#include <iterator>
#include <list>
#include <stack>
#include <map>
#include <set>
#include <functional>
#include <numeric>
#include <utility>
#include <limits>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

using namespace std;

template <typename A, typename B>
string to_string(pair<A, B> p);
 
template <typename A, typename B, typename C>
string to_string(tuple<A, B, C> p);
 
template <typename A, typename B, typename C, typename D>
string to_string(tuple<A, B, C, D> p);
 
string to_string(const string& s) {
  return '"' + s + '"';
}
 
string to_string(const char* s) {
  return to_string((string) s);
}
 
string to_string(bool b) {
  return (b ? "true" : "false");
}
 
string to_string(vector<bool> v) {
  bool first = true;
  string res = "{";
  for (int i = 0; i < static_cast<int>(v.size()); i++) {
    if (!first) {
      res += ", ";
    }
    first = false;
    res += to_string(v[i]);
  }
  res += "}";
  return res;
}
 
template <size_t N>
string to_string(bitset<N> v) {
  string res = "";
  for (size_t i = 0; i < N; i++) {
    res += static_cast<char>('0' + v[i]);
  }
  return res;
}
 
template <typename A>
string to_string(A v) {
  bool first = true;
  string res = "{";
  for (const auto &x : v) {
    if (!first) {
      res += ", ";
    }
    first = false;
    res += to_string(x);
  }
  res += "}";
  return res;
}
 
template <typename A, typename B>
string to_string(pair<A, B> p) {
  return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}
 
template <typename A, typename B, typename C>
string to_string(tuple<A, B, C> p) {
  return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ")";
}
 
template <typename A, typename B, typename C, typename D>
string to_string(tuple<A, B, C, D> p) {
  return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ", " + to_string(get<3>(p)) + ")";
}
 
void debug_out() { cerr << endl; }
 
template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
  cerr << " " << to_string(H);
  debug_out(T...);
}
 
#ifdef LOCAL
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) 42
#endif

/** [0, mod-1]
 * (a + b) % mod = (a % mod + b % mod) % mod
 * (a - b) % mod = (a % mod - b % mod + mod) % mod
 * a * b % mod
 */

// a^b % mod

// Time complexity: O(b)
int modpow(int a, int b, int mod) {
    int res = 1;
    for (int i = 0; i < b; i++) {
        res = res * (long long) a % mod;
    }
    return res;
}

/**
 * I want to computer a^b
 * If b is odd:
 *  a^(b-1) * a
 * Otherwise:
 *  a^(b/2) * a^(b/2)
 */

/***
 * (a, b)
 * (a, b - 1)
 * (a, b/2)
 * (a, b/2 - 1)
 * (a, b)
 */

// In at most two steps, the value of b will be halved.
// 2 * log(b)
// Assumption a > 0.
/**
 * Time complexity: O(log b)
 */
int modpowFaster(int a, int b, int mod) {
    if (b == 0) {
        return 1;
    }
    if (b % 2 == 1) { // b is odd.
        return modpowFaster(a, b - 1, mod) * (long long) a % mod;
    } else { // b is even.
        int res = modpowFaster(a, b / 2, mod);
        return res * (long long) res % mod;
    }
}

int modpowIterative(int a, int b, int mod) {
    //a^b
    // a = 5, b = 6
    // (4 + 2) = (110)
    // 5^6 = 5^(2^2 + 2^1) = 5^(2^2) * 5^(2^1) * 5^(0 * (2^1))

    /***
     * In step 1: 110, a = 5^2, res = 1
     * In step 2: 11, res=5^2, 5^(2^2)
     * In step 3: 1, res = 5^2 * 5^(2^2), a = 5^(2^2) * 5^(2^2)
     */

    // Suppose b is power of 2.
    // 2
    // a^2
    // b = 1
    // res = a^2.

    // (1010) in binary
    // a^(1010)
    // a^(1 * 2^3 + 0 * 2^2 + 1 * 2^1 + 0 * 2^0)
    // a^(2^3) * (a^(2^1)) 

    // 1
    // 10
    // 11
    int res = 1;
    while (b) {
        if (b % 2 == 1) {
            res = res * (long long) a % mod;
        }
        a = a * (long long) a % mod; // a^(2^i) // i steps.
        b /= 2;
    }
    return res;
}

// 1232323232326366464646538364765746466 % 10239
int findRemainder(string s, int mod) {
    // mod -> 10^9 + 7
    long long res = 0;
    for (char ch: s) {
        res *= 10;
        res += (ch - '0');
        res %= mod;
    }
    return res;
}

//
int findModulo(string base, string exponent, int mod) {
    int newBase = findRemainder(base, mod);
    int expo = findRemainder(exponent, mod - 1);
    return modpowIterative(newBase, expo, mod);
}

// Euler function: phi
// Chinese remainder theorem.

// decimal notation.
// "10" -> 10
// "159"
// At step 1: res = 1
// At step 2: res = 15
// At step 3: res = 159
int converToInt(string s) {
    int res = 0;
    for (char ch: s) {
        res *= 10;
        res += (ch - '0');
    }
    return res;
}

int main() {    
    debug(converToInt("15904949"));

    // mod -> prime
    // a^(p-1) = 1 mod p where p is prime. Fermat's theorem.

    // a^x % p // where p is prime.
    // a^(x % (p -1)) % p. // By Fermat's theorem.

    // a^p % p = a

    /**
     * a^p % p
     * // a^(p-1) * a % p
     * // a % p
     * 
     * a^(p+5) % p
     * // (a^(p-1) * a^6) % p
     * a^6 % p
     * // a^((p + 5) % (p-1)) % p
     */

    /**
     * a^17 % 13
     * a^(17%12) % 13
     * (a^(12) * a^5) % 13
     * a^(12) % 13 * a^5 % 12
     * a^5 % 12
     */

    // int p = 97;
    // for (int a = 1; a < p; a++) {
    //     int x = modpowIterative(a, 20000, p);
    //     int y = modpowIterative(a, 20000 % (p - 1), p);

    //     debug(x, y);
    //     assert(x == y);
    //     // cout << endl;    
    // }

/**
 * 
 * 
    * a^20000 % 13
    * 20000 % (13 - 1) = 20000 % 12 = 
    */
    /**
     * x %= (p-1)
     * a^x % p
     */

    // 7 is prime.
    // a^6 % 7 = 1 // a >= and a < p.

    // debug(modpowIterative(10, 1e9, 49));

    // 10^100000
    // a^(10^100000) % mod

    //log(10^100000) = 100000 * log(10) = 10^6 // 
    // 2^100000 * 5^100000
    
    // 

    // <101>
    // 1 * 2^2 + 0 *2^1 + 1 * 2^0
    // (<10>) * 2 + 1
    // 2 * 2 + 1 = 5

    // int mod = 10;
    // int a = 1e9; // 9
    // int b = 1e9; // 10

    // int res = (a * (int64_t) b) % mod;
    // debug(res);
}