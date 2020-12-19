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

/**
 * Basic definitions:
 * integers: <Today's lecture's focus>
 * -infinity  -2, -1, 0, 1, 2, ... ..., infinity
 * real numbrs:
 * -infinity, -1.5, -0.5, 0, 0.5, 0, 1.0, 2.5555555555, 4/3, ... infinity. 
 * /

/**
 * A divisor of a number n is some number x that divides n perfectly.
 * 
 * Does number 3 divide 9? Yes, 3 is a divisor of 9.
 * Does number 4 divide 9 perfectly (remainder should be zero)? Remainder: 1
 * // No, 4 is not a divisor. 
 * 
 * Write down all divisors of 9.
 * 1? Yes
 * 2? No
 * 3? Yes
 * 6? No
 * 7?
 * 9? Yes
 * 
 * Divisors: 1, 3, 9 
 * 
 * Write down divisors of 10?
 * 1, 2, 5, 10
 * /

/**
 *  GCD (Greatest Common Divisor)
 *  gcd of two numbers a, b is the largest number x that is the divisor of both a and b.
 * 
 * 6, 9
 * 1? Yes
 * 2? (Yes, No) -> divisor
 * 3? Yes
 * 
 * What's the greatest divisor of 6 and 9? 3.
 * 
 * gcd of 20, 30?
 * 5
 * 10
 * gcd of (20, 30) = 10
 * 
 * gcd of 20, 30, 50
 * 10
 */

/**
 * Time complexity: min(a, b)
 */
int gcd_by_definition(int a, int b) {
    for (int x = min(a, b); x >= 1; x--) {
        if (a % x == 0 && b % x == 0) {
            return x;
        }
    }
    assert(false);
}

/**
 * Suppose a >= b.
 * Identity:
 * gcd(a, b) = gcd(a - b, b)
 * Example: gcd(20, 30) = gcd(20, 10) = gcd(10, 10) = 10
 * gcd(1, n) = 1.
 * gcd(0, n) = n
 * 
 * Time complexity: O(min(a, b)) again.
 */
int gcd_by_subtractive_identity(int a, int b) {
    // debug(a, b);
    if (a < b) {
        swap(a, b);
    }
    // a >= b.
    if (b == 0) { // Base case. // Due to property that gcd(0, n) = n.
        return a;
    }
    return gcd_by_subtractive_identity(a - b, b); // Using identity: gcd(a, b) = gcd(a - b, b)
}

/**
 * How to make this faster.
 * gcd(105, 10)
 * gcd(95, 10)
 * gcd(85, 10)
 * 75
 * 65
 * 
 * 
 * 25
 * 15
 * gcd(5, 10)
 * 
 * gcd(105, 10) -> gcd(105 % 10, 10) -> gcd(5, 10)
 * 
 * Identity (Property):
 * // a >= b
 * gcd(a, b) = gcd(a % b, b)
 * 
 * gcd(10^9, 1) = gcd(0, 1) = 1
 * 
 * Time complexity: O(log(max(a, b)))
 */
int gcd_final(int a, int b) {
    // debug(a, b);
    if (a < b) {
        swap(a, b);
    }
    // a >= b.
    if (b == 0) { // Base case. // Due to property that gcd(0, n) = n.
        return a;
    }
    return gcd_final(a % b, b); // Using identity: gcd(a, b) = gcd(a % b, b)
}

/**
 * a, b, a >= b Step 0 max(a, b) = 30
 * a % b, b, Step 1
 * () Step 2 max(a, b) = 15
 * 
 * Fact: In two steps, the value of max(a, b) will become less than half of its original.
 * Prove this fact.
 * 10^9
 * 10^9/2
 * 10^9/4
 * ..
 * 
 * 
 * log(10^9) * 2 // max(a, b) = 1
 */


// Gcd of three numbers.

int main() {
    //gcd(a, b, c)
    // gcd(gcd(a, b), c);

    vector<int> a;

    int g = 0;
    for (int x: a) {
        g = gcd(g, x);
    }

    // g of the entire array a.


    // int T = 100000;

    // while (T--) {
    //     int a = 1; 
    //     // rand() % (int) 1e9 + 1;
    //     int b = rand() % (int) 1e5 + 1;

    //     // debug(a, b);
    //     debug(gcd_by_subtractive_identity(a, b));
    // }

    // gcd_final(1, 1000);
    // debug(gcd_final(20, 30));
    // debug(gcd_final(1, 30));
    // debug(gcd_final(30, 30));
    // debug(gcd_final(34, 153));

    // int a = 1e9; // 10^9
    // int b = 1e9 - 1;
    // debug(gcd(a, b));
    
    return 0;
}