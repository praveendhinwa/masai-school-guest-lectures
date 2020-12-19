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


// O(n)
int bruteforce(int n) {
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (n % i == 0) {
            ans++;
        }
    }
    return ans;
}

 vector<pair<int, int> > findPrimeFactorisation(int n) {
    // debug(n);
    vector<pair<int, int> > ans;
    // p goes till sqrt(n).
    for (int p = 2; p * p <= n; p++) {
        if (n % p == 0) { // if p divides n. p will always be prime.
            // debug("p", p);
            int e = 0;
            while (n % p == 0) {
                n /= p;
                e++;
            } // Here e denotes the power of p in the prime factorisation representation
            // debug(e);
            // power of 2 in 180 is 2. = 180 = 2^2 * something.
            ans.push_back({p, e});
        }
    }
    if (n > 1) {
        ans.push_back({n, 1});
    }
    return ans;
    // debug(ans);
}


 // Prime factorisation of n.
// n = p1^e1 * p2^e2 * ... 
// 12 = 2^2 * 3^1
// How many divisors it has?
// divisor of 12 will be of form : 2^x * 3^y where 0 <= x <= 2 and 0 <= y <= 1.
// 6 = 2^1 * 3^1 (x = 1 and y = 1)
// How many pairs of (x, y) are there such that 0 <= x <= 2 and 0 <= y <= 1
// (0, 1, 2), (0, 1)
// 3 * 2 = 6.

// n = p1^e1 * p2^e2 * p3^e3
// How many divisors will be there?
// (e1 + 1) * (e2 + 1) * (e3 + 1) ...
/**
 * O(sqrt(n))
 */
int countDivisors(int n) {
    auto primeRepr = findPrimeFactorisation(n);
    // debug(primeRepr);
    int ans = 1;
    for (auto it: primeRepr) {
        ans *= (it.second + 1);
    }
    return ans;
}

/**
 * This kind of recursion is used in many problems.
 * print all strings with some property.
 * print all permutations
 * print all combinations
 */
// Divisor will of form p1^x1 * p2^x2 * ... pk^xk
// d = 1
// index -> 0 (x1 will be go from 0 to e1) .. // d * p1^x1
// index -> 1    // d * p1^x1 * p2^x2
// index -> k + 1 -> d will be a divisor of your number n.
void rec(vector<pair<int, int> > &primeRepr, int index, int d, vector<int> &ans) {
    debug(index, d);
    if (index == primeRepr.size()) {
        ans.push_back(d); // When you reach at the end of the primeRepr array.
    } else {
        int p = primeRepr[index].first;
        int e = primeRepr[index].second;
        // Choose power of p^x where x >= 0 && x <= e
        for (int x = 0; x <= e; x++) {
            // debug(index + 1, d);
            rec(primeRepr, index + 1, d, ans); // d * p^x.
            d *= p;
        }
    }
}

// (index, d)
//                    (0, 1)
//         (1, 1)               (1, 2)          // 2^0 or 2^1 
// (2, 1*)   (2, 3*)        (2, 2*)   (2, 6*)   // 3^0 or 3^1 

// Recusrive function to print all divisors of n.
void printAllDivisors(int n) {
    auto primeRepr = findPrimeFactorisation(n); // p1^e1 * p2^e2 * .... 
    debug(primeRepr);

    vector<int> ans;
    rec(primeRepr, 0, 1, ans);
    debug(ans);
    // rec()
}

// How many number of divisors a number N has?
// Order notation for that?
// O(N^1/3) divisors.
// 10^9 -> 10^3 divisors.

// How many distinct prime divisors can a number N have?
// O(N), O(sqrt(N)), O(log(N))??
// 18 = 2^1 * 3^2 
// How many prime divisors? : 2
// How many divisors: (1 + 1) * (2 + 1) = 2 * 3 = 6.

// How many prime divisors? O(log N) // Easy to prove
// 2*3*5*7*11*13*.. = N
// 2 * 2 * 2 * (k times) <= N
// 2^k <= N
// k = O(log N)

// How many divisors? O(N^1/3) (Fact: remember it) // Hard to prove.

/**
 * Given a number N. Find all divisors of numbers from 1 to N.
 * 
 * Time complexity: O(N log N)
 * N/1 + N/2 + N/3 + N/4 + ... + N/N
 * N * harmonic(N)
 * N * log(N)
 */
void divisor_sieve(int N) {
    vector<vector<int> > divisors(N + 1, vector<int>());
    // divisors[i] -> 
    for (int d = 1; d <= N; d++) { // Iterating over all divisors d numbers from 1 to N.
        for (int i = d; i <= N; i += d) { // Iterate over all multiples of d. (inner loop N/d times)
            divisors[i].push_back(d); 
        }
    }
    for (int i = 1; i <= N; i++) {
        debug(i, divisors[i]);
    }
    // debug(divisors);
}

int main() {    
    divisor_sieve(13);

    // Count the number of divisors of a number n, where n <= 10^9.
    // findPrimeFactorisation(540 * 13 * 17 * 97 * 101);

    // debug(countDivisors(6));

    // printAllDivisors(6);

    // N, find divisors of all numbers from 1 to N.


    return 0;
}