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
 * Prime number: 
 * A number is prime number if it has no divisor other than 1 and n.
 * 
 * Trivial divisors would be 1 and the number itself.
 * If a number has non trivial divisor, it won't be a prime number.
 * e.g. 10 is not a prime because it has two non trivial divisors 2, 5
 * 1 and 10 -> trivial divisors
 *
 * 1 -> not a prime number.
 * 2 -> prime (1, 2)
 * 3 -> prime (1, 3)
 * 4 -> not (2)
 * 5 -> prime (1, 5)
 * 6 -> not a prime (2)
 */

/**
 * Time complexity: O(n)
 */
int isPrimeBasic(int n) {
    if (n == 1) {
        return false;
    }
    // iterate over all non trivial divisors.
    for (int i = 2; i <= n - 1; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

/**
 * Observation:
 *  If a number is not a prime, then there will be a divisor <= sqrt(n)
 * 
 * Proof:
 *  Suppose a number n is not prime.
 *  Then take any non trivial divisor d.
 *  If d <= sqrt(n):
 *      My property is satisfied. I am done.
 *  Else if d > sqrt(n):
 *      (n/d) is also a divisor of n.
 *      n/(n/d) = d.
 *      You can see that the number n/d can't be greater than sqrt(n)
 *      So divisor n/d satisfies your property. 
 *      d * n/d = n
 * 
 * 51 <= sqrt(51) = 7.
 * 51 = 3 * 17
 * 
 * divisor d
 * Take any divisord divides n
 * if d <= sqrt(n) -> I am done
 * Otherwise (n/d) is also a divisor of n.
 * 
 * Prove:
 * n = p * q (p > 1 and  and q > 1)
 * 
 * Time complexity: O(sqrt(n))
 * // n = 10^9
 */
int isPrimeSecondVersion(int n) {
    if (n <= 1) {
        return false;
    }
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

/**
 * Sieve of Erastothenes:
 * 
 * 1- 2 3 4- 5 6- 7 8- 9- 10-
 * 11 12- 13 14- 15- 16- 17 18- 19 20- 21-
 * 
 * 
 * Understand this algorithm as follows.
 * Let us say you have a sieve which originally contains all numbers (e.g. 2 to 21).
 * Find the smallest number. You are guaranteed that this smallest number is a prime.
 * Remove all the numbers that are multiple of 2 from the sieve except 2.
 *  (4, 6, 8, 10, 12, 14, 16, 18, 20)
 * // Find the next smallest number that you didn't pick
 * // 3
 * // remove all multiples of 3 except 3. (6, 9, 12, 15, 18, 21)
 * //  Now remaining numbers are : 2, 3, 5, 7, 11, 13, 17, 19
 * // Next smallest number 5 -> 
 * // Cross all multiples of 5 except 5, 10, 15, 20
 * 
 * // In the end, whatever is remaining in your sieve is just the prime numbers.
 */

/**
 * Time complexity: N log N
 */

/**
 * Which one is faster?
 * 
 * Time complexity = N/1 + N/2 + N/3 + .... + N/N
 * In fact: sum of N/p where p is prime.
 * 
 * Time complexity = N/1 + N/2 + N/3 + .... + N/N
 * TC = N (1 + 1/2 + 1/3 + 1/4 + 1/5 + .... + 1/N)
 * Harmonic series sum <= O(log N)
 * TC = N * harmonic_sum(N)
 * TC = N * log N.
 * 
 * Proof:
 * harmonic_sum(N) <= integration (1/x) dx where limits are from 1 to N.
 * ln(X) limits 1 to N
 * ln(N) - ln(1) = ln(N)
 * 
 * harmonic_sum(N) <= ln(N)
 * 
 * ln and log
 * ln is called natural log, its base is e. 2.71......
 */

void sieve(int N) {
    // Check whether is a number is prime or not for numbers 1 to N.
    vector<bool> isPrime(N + 1);
    for (int i = 2; i <= N; i++) {
        isPrime[i] = true;
    }

    // i * 1, i * 2, i * 3, ,,,, i * N/i, i * (N/i+1) > N 
    for (int i = 2; i <= N; i++) {
        if (isPrime[i]) {
            // For a given i, N/i multiples
            // cout << endl;
            // cout << "the smallest prime number in the sieve that is not consided yet " << i << endl;
            // // debug("i);
            // Going over multiples of i.
            // cout << "multiples of i" << endl;
            for (int j = i + i; j <= N; j += i) { // Will run at max N/i steps.
                // cout << j << " ";
                isPrime[j] = false;
            }
            // cout << endl;
        }
    }

    // Now, isPrime[i] = true, those numbers are prime.
    int cnt = 0;
    for (int i = 0; i <= N; i++) {
        if (isPrime[i]) {
            cnt++;
            // debug(i);
        }
    }
    debug(cnt);
}

double harmonic(int n) {
    double ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += 1 / (double) i;
    }
    return ans;
}

int main() {    
    // Find all prime numbers from 1 to 10^7.
    // 10^7 * sqrt(10^7) = 3 * 10^10 -> won't run in time.

    debug(harmonic(1e9));

    // int MAX = 3e7;
    // sieve(MAX);

    // sieve(20);

    // int cnt = 0;
    // for (int n = 1; n <= MAX; n++) {
    //     if (isPrimeSecondVersion(n)) {
    //         cnt++;
    //     }
    // }

    // debug(cnt);

    // for (int n = 1; n <= 10; n++) {
    //    debug(n, isPrimeSecondVersion(n));
    // }
    
    return 0;
}