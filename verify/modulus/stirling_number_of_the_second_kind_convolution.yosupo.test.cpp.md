---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :heavy_check_mark: modulus/stirling_number_of_the_second_kind_convolution.yosupo.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#06efba23b1f3a9b846a25c6b49f30348">modulus</a>
* <a href="{{ site.github.repository_url }}/blob/master/modulus/stirling_number_of_the_second_kind_convolution.yosupo.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-05-23 00:48:03+09:00


* see: <a href="https://judge.yosupo.jp/problem/stirling_number_of_the_second_kind">https://judge.yosupo.jp/problem/stirling_number_of_the_second_kind</a>


## Depends on

* :heavy_check_mark: <a href="../../library/hack/fastio.hpp.html">hack/fastio.hpp</a>
* :heavy_check_mark: <a href="../../library/modulus/factorial.hpp.html">modulus/factorial.hpp</a>
* :heavy_check_mark: <a href="../../library/modulus/mint.hpp.html">quotient ring / 剰余環 $\mathbb{Z}/n\mathbb{Z}$ <small>(modulus/mint.hpp)</small></a>
* :heavy_check_mark: <a href="../../library/modulus/modinv.hpp.html">modulus/modinv.hpp</a>
* :heavy_check_mark: <a href="../../library/modulus/modpow.hpp.html">modulus/modpow.hpp</a>
* :heavy_check_mark: <a href="../../library/modulus/number_theoretic_transformation.hpp.html">Number Theoretic Transformation (NTT) for Proth primes <small>(modulus/number_theoretic_transformation.hpp)</small></a>
* :heavy_check_mark: <a href="../../library/modulus/number_theoretic_transformation_with_garner.hpp.html">multiprecation on $\mathbb{Z}/n\mathbb{Z}\[x\]$ <small>(modulus/number_theoretic_transformation_with_garner.hpp)</small></a>
* :heavy_check_mark: <a href="../../library/modulus/stirling_number_of_the_second_kind_convolution.hpp.html">the Stirling number of the second kind (for given $N$, compute $S(N, \ast)$ in $O(N \log N)$) <small>(modulus/stirling_number_of_the_second_kind_convolution.hpp)</small></a>
* :heavy_check_mark: <a href="../../library/utils/macros.hpp.html">utils/macros.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/stirling_number_of_the_second_kind"
#include "modulus/stirling_number_of_the_second_kind_convolution.hpp"
#include "hack/fastio.hpp"
#include "utils/macros.hpp"

constexpr int MOD = 998244353;
int main() {
    int n = in<int>();
    auto f = stirling_number_of_the_second_kind_convolution<MOD>(n);
    REP (k, n + 1) {
        out<int>(f[k].value);
        out<char>(k < n ? ' ' : '\n');
    }
    return 0;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "modulus/stirling_number_of_the_second_kind_convolution.yosupo.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/stirling_number_of_the_second_kind"
#line 2 "modulus/stirling_number_of_the_second_kind_convolution.hpp"
#include <cassert>
#include <vector>
#line 2 "modulus/mint.hpp"
#include <algorithm>
#line 4 "modulus/mint.hpp"
#include <iostream>
#line 3 "modulus/modpow.hpp"

inline int32_t modpow(uint_fast64_t x, uint64_t k, int32_t MOD) {
    assert (/* 0 <= x and */ x < (uint_fast64_t)MOD);
    uint_fast64_t y = 1;
    for (; k; k >>= 1) {
        if (k & 1) (y *= x) %= MOD;
        (x *= x) %= MOD;
    }
    assert (/* 0 <= y and */ y < (uint_fast64_t)MOD);
    return y;
}
#line 4 "modulus/modinv.hpp"

inline int32_t modinv_nocheck(int32_t value, int32_t MOD) {
    assert (0 <= value and value < MOD);
    if (value == 0) return -1;
    int64_t a = value, b = MOD;
    int64_t x = 0, y = 1;
    for (int64_t u = 1, v = 0; a; ) {
        int64_t q = b / a;
        x -= q * u; std::swap(x, u);
        y -= q * v; std::swap(y, v);
        b -= q * a; std::swap(b, a);
    }
    if (not (value * x + MOD * y == b and b == 1)) return -1;
    if (x < 0) x += MOD;
    assert (0 <= x and x < MOD);
    return x;
}

inline int32_t modinv(int32_t x, int32_t MOD) {
    int32_t y = modinv_nocheck(x, MOD);
    assert (y != -1);
    return y;
}
#line 7 "modulus/mint.hpp"


/**
 * @brief quotient ring / 剰余環 $\mathbb{Z}/n\mathbb{Z}$
 */
template <int32_t MOD>
struct mint {
    int32_t value;
    mint() : value() {}
    mint(int64_t value_) : value(value_ < 0 ? value_ % MOD + MOD : value_ >= MOD ? value_ % MOD : value_) {}
    mint(int32_t value_, std::nullptr_t) : value(value_) {}
    explicit operator bool() const { return value; }
    inline mint<MOD> operator + (mint<MOD> other) const { return mint<MOD>(*this) += other; }
    inline mint<MOD> operator - (mint<MOD> other) const { return mint<MOD>(*this) -= other; }
    inline mint<MOD> operator * (mint<MOD> other) const { return mint<MOD>(*this) *= other; }
    inline mint<MOD> & operator += (mint<MOD> other) { this->value += other.value; if (this->value >= MOD) this->value -= MOD; return *this; }
    inline mint<MOD> & operator -= (mint<MOD> other) { this->value -= other.value; if (this->value <    0) this->value += MOD; return *this; }
    inline mint<MOD> & operator *= (mint<MOD> other) { this->value = (uint_fast64_t)this->value * other.value % MOD; return *this; }
    inline mint<MOD> operator - () const { return mint<MOD>(this->value ? MOD - this->value : 0, nullptr); }
    inline mint<MOD> pow(uint64_t k) const { return mint<MOD>(modpow(value, k, MOD), nullptr); }
    inline mint<MOD> inv() const { return mint<MOD>(modinv(value, MOD), nullptr); }
    inline mint<MOD> operator /  (mint<MOD> other) const { return *this *  other.inv(); }
    inline mint<MOD> operator /= (mint<MOD> other)       { return *this *= other.inv(); }
    inline bool operator == (mint<MOD> other) const { return value == other.value; }
    inline bool operator != (mint<MOD> other) const { return value != other.value; }
};
template <int32_t MOD> mint<MOD> operator * (int64_t value, mint<MOD> n) { return mint<MOD>(value) * n; }
template <int32_t MOD> std::istream & operator >> (std::istream & in, mint<MOD> & n) { int64_t value; in >> value; n = value; return in; }
template <int32_t MOD> std::ostream & operator << (std::ostream & out, mint<MOD> n) { return out << n.value; }
#line 4 "modulus/factorial.hpp"

template <int32_t MOD>
mint<MOD> fact(int n) {
    static std::vector<mint<MOD> > memo(1, 1);
    while (n >= memo.size()) {
        memo.push_back(memo.back() * mint<MOD>(memo.size()));
    }
    return memo[n];
}
template <int32_t MOD>
mint<MOD> inv_fact(int n) {
    static std::vector<mint<MOD> > memo;
    if (memo.size() <= n) {
        int l = memo.size();
        int r = n * 1.3 + 100;
        memo.resize(r);
        memo[r - 1] = fact<MOD>(r - 1).inv();
        for (int i = r - 2; i >= l; -- i) {
            memo[i] = memo[i + 1] * (i + 1);
        }
    }
    return memo[n];
}
#line 4 "modulus/number_theoretic_transformation_with_garner.hpp"
#include <cstdint>
#include <tuple>
#line 2 "utils/macros.hpp"
#define REP(i, n) for (int i = 0; (i) < (int)(n); ++ (i))
#define REP3(i, m, n) for (int i = (m); (i) < (int)(n); ++ (i))
#define REP_R(i, n) for (int i = (int)(n) - 1; (i) >= 0; -- (i))
#define REP3R(i, m, n) for (int i = (int)(n) - 1; (i) >= (int)(m); -- (i))
#define ALL(x) std::begin(x), std::end(x)
#line 9 "modulus/number_theoretic_transformation.hpp"

template <int32_t PRIME> struct proth_prime {};
template <> struct proth_prime<1224736769> { static constexpr int a =             73, b = 24, g =  3; };
template <> struct proth_prime<1053818881> { static constexpr int a =     3 * 5 * 67, b = 20, g =  7; };
template <> struct proth_prime<1051721729> { static constexpr int a =        17 * 59, b = 20, g =  6; };
template <> struct proth_prime<1045430273> { static constexpr int a =            997, b = 20, g =  3; };
template <> struct proth_prime<1012924417> { static constexpr int a =     3 * 7 * 23, b = 21, g =  5; };
template <> struct proth_prime<1007681537> { static constexpr int a =        31 * 31, b = 20, g =  3; };
template <> struct proth_prime<1004535809> { static constexpr int a =            479, b = 21, g =  3; };
template <> struct proth_prime< 998244353> { static constexpr int a =         7 * 17, b = 23, g =  3; };
template <> struct proth_prime< 985661441> { static constexpr int a =         5 * 47, b = 22, g =  3; };
template <> struct proth_prime< 976224257> { static constexpr int a =     7 * 7 * 19, b = 20, g =  3; };
template <> struct proth_prime< 975175681> { static constexpr int a =     3 * 5 * 31, b = 21, g = 17; };
template <> struct proth_prime< 962592769> { static constexpr int a = 3 * 3 * 3 * 17, b = 21, g =  7; };
template <> struct proth_prime< 950009857> { static constexpr int a =        4 * 151, b = 21, g =  7; };
template <> struct proth_prime< 943718401> { static constexpr int a =  3 * 3 * 5 * 5, b = 22, g =  7; };
template <> struct proth_prime< 935329793> { static constexpr int a =            223, b = 22, g =  3; };
template <> struct proth_prime< 924844033> { static constexpr int a =  3 * 3 * 7 * 7, b = 21, g =  5; };
template <> struct proth_prime< 469762049> { static constexpr int a =              7, b = 26, g =  3; };
template <> struct proth_prime< 167772161> { static constexpr int a =              5, b = 25, g =  3; };

struct is_proth_prime_impl {
    template <int32_t PRIME, class T> static auto check(T *) -> decltype(proth_prime<PRIME>::g, std::true_type());
    template <int32_t PRIME, class T> static auto check(...) -> std::false_type;
};
template <int32_t PRIME>
struct is_proth_prime : decltype(is_proth_prime_impl::check<PRIME, std::nullptr_t>(nullptr)) {
};

/**
 * @brief Number Theoretic Transformation (NTT) for Proth primes
 * @note O(N log N)
 * @note radix-2, decimation-in-frequency, Cooley-Tukey
 * @note cache std::polar (~ 2x faster)
 */
template <int32_t PRIME>
void ntt_inplace(std::vector<mint<PRIME> > & a, bool inverse) {
    const int n = a.size();
    const int log2_n = __builtin_ctz(n);
    assert (n == 1 << log2_n);
    assert (log2_n <= proth_prime<PRIME>::b);

    // prepare rotors
    std::vector<mint<PRIME> > ep, iep;
    while ((int)ep.size() <= log2_n) {
        ep.push_back(mint<PRIME>(proth_prime<PRIME>::g).pow(mint<PRIME>(-1).value / (1 << ep.size())));
        iep.push_back(ep.back().inv());
    }

    // divide and conquer
    std::vector<mint<PRIME> > b(n);
    REP3 (i, 1, log2_n + 1) {
        int w = 1 << (log2_n - i);
        mint<PRIME> base = (inverse ? iep : ep)[i];
        mint<PRIME> now = 1;
        for (int y = 0; y < n / 2; y += w) {
            REP (x, w) {
                auto l = a[y << 1 | x];
                auto r = now * a[y << 1 | x | w];
                b[y | x] = l + r;
                b[y | x | n >> 1] = l - r;
            }
            now *= base;
        }
        std::swap(a, b);
    }

    // div by n if inverse
    if (inverse) {
        auto n_inv = mint<PRIME>(n).inv();
        REP (i, n) {
            a[i] *= n_inv;
        }
    }
}

/**
 * @brief multiprecation on $\mathbb{F}_p[x]$ for Proth primes
 * @note O(N log N)
 * @note (f \ast g)(i) = \sum_{0 \le j \lt i + 1} f(j) g(i - j)
 */
template <int32_t PRIME>
typename std::enable_if<is_proth_prime<PRIME>::value, std::vector<mint<PRIME> > >::type ntt_convolution(const std::vector<mint<PRIME> > & a_, const std::vector<mint<PRIME> > & b_) {
    if (a_.size() <= 32 or b_.size() <= 32) {
        std::vector<mint<PRIME> > c(a_.size() + b_.size() - 1);
        REP (i, a_.size()) REP (j, b_.size()) c[i + j] += a_[i] * b_[j];
        return c;
    }
    int m = a_.size() + b_.size() - 1;
    int n = (m == 1 ? 1 : 1 << (32 - __builtin_clz(m - 1)));
    auto a = a_;
    auto b = b_;
    a.resize(n);
    b.resize(n);
    ntt_inplace(a, false);
    ntt_inplace(b, false);
    REP (i, n) {
        a[i] *= b[i];
    }
    ntt_inplace(a, true);
    a.resize(m);
    return a;
}
#line 10 "modulus/number_theoretic_transformation_with_garner.hpp"

template <int32_t MOD, int32_t MOD1, int32_t MOD2, int32_t MOD3>
mint<MOD> garner_algorithm_template(mint<MOD1> a1, mint<MOD2> a2, mint<MOD3> a3) {
    static const auto r12 = mint<MOD2>(MOD1).inv();
    static const auto r13 = mint<MOD3>(MOD1).inv();
    static const auto r23 = mint<MOD3>(MOD2).inv();
    a2 = (a2 - a1.value) * r12;
    a3 = (a3 - a1.value) * r13;
    a3 = (a3 - a2.value) * r23;
    return mint<MOD>(a1.value) + a2.value * mint<MOD>(MOD1) + a3.value * (mint<MOD>(MOD1) * mint<MOD>(MOD2));
}

/**
 * @brief multiprecation on $\mathbb{Z}/n\mathbb{Z}[x]$
 */
template <int32_t MOD>
typename std::enable_if<not is_proth_prime<MOD>::value, std::vector<mint<MOD> > >::type ntt_convolution(const std::vector<mint<MOD> > & a, const std::vector<mint<MOD> > & b) {
    if (a.size() <= 32 or b.size() <= 32) {
        std::vector<mint<MOD> > c(a.size() + b.size() - 1);
        REP (i, a.size()) REP (j, b.size()) c[i + j] += a[i] * b[j];
        return c;
    }
    constexpr int PRIMES[3] = { 1004535809, 998244353, 985661441 };
    std::vector<mint<PRIMES[0]> > x0(a.size());
    std::vector<mint<PRIMES[1]> > x1(a.size());
    std::vector<mint<PRIMES[2]> > x2(a.size());
    REP (i, a.size()) {
        x0[i] = a[i].value;
        x1[i] = a[i].value;
        x2[i] = a[i].value;
    }
    std::vector<mint<PRIMES[0]> > y0(b.size());
    std::vector<mint<PRIMES[1]> > y1(b.size());
    std::vector<mint<PRIMES[2]> > y2(b.size());
    REP (j, b.size()) {
        y0[j] = b[j].value;
        y1[j] = b[j].value;
        y2[j] = b[j].value;
    }
    std::vector<mint<PRIMES[0]> > z0 = ntt_convolution<PRIMES[0]>(x0, y0);
    std::vector<mint<PRIMES[1]> > z1 = ntt_convolution<PRIMES[1]>(x1, y1);
    std::vector<mint<PRIMES[2]> > z2 = ntt_convolution<PRIMES[2]>(x2, y2);
    std::vector<mint<MOD> > c(z0.size());
    REP (k, z0.size()) {
        c[k] = garner_algorithm_template<MOD>(z0[k], z1[k], z2[k]);
    }
    return c;
}
#line 7 "modulus/stirling_number_of_the_second_kind_convolution.hpp"

/**
 * @brief the Stirling number of the second kind (for given $N$, compute $S(N, \ast)$ in $O(N \log N)$)
 * @see https://min-25.hatenablog.com/entry/2015/04/07/160154
 */
template <int MOD>
std::vector<mint<MOD> > stirling_number_of_the_second_kind_convolution(int n) {
    assert (0 <= n);
    std::vector<mint<MOD> > a(n + 1);
    std::vector<mint<MOD> > b(n + 1);
    REP (i, n + 1) {
        a[i] = mint<MOD>(i).pow(n) * inv_fact<MOD>(i);
        b[i] = (i % 2 == 0 ? 1 : -1) * inv_fact<MOD>(i);
    }
    auto c = ntt_convolution(a, b);
    c.resize(n + 1);
    return c;
}
#line 3 "hack/fastio.hpp"
#include <cstdio>
#include <string>
#include <type_traits>

template <class Char, std::enable_if_t<std::is_same_v<Char, char>, int> = 0>
inline Char in() { return getchar_unlocked(); }
template <class String, std::enable_if_t<std::is_same_v<String, std::string>, int> = 0>
inline std::string in() {
    char c; do { c = getchar_unlocked(); } while (isspace(c));
    std::string s;
    do { s.push_back(c); } while (not isspace(c = getchar_unlocked()));
    return s;
}
template <class Integer, std::enable_if_t<std::is_integral_v<Integer>, int> = 0>
inline Integer in() {
    char c; do { c = getchar_unlocked(); } while (isspace(c));
    if (std::is_signed<Integer>::value and c == '-') return -in<Integer>();
    Integer n = 0;
    do { n = n * 10 + c - '0'; } while (not isspace(c = getchar_unlocked()));
    return n;
}

template <class Char, std::enable_if_t<std::is_same_v<Char, char>, int> = 0>
inline void out(char c) { putchar_unlocked(c); }
template <class String, std::enable_if_t<std::is_same_v<String, std::string>, int> = 0>
inline void out(const std::string & s) { for (char c : s) putchar_unlocked(c); }
template <class Integer, std::enable_if_t<std::is_integral_v<Integer>, int> = 0>
inline void out(Integer n) {
    char s[20];
    int i = 0;
    if (std::is_signed<Integer>::value and n < 0) { putchar_unlocked('-'); n *= -1; }
    do { s[i ++] = n % 10; n /= 10; } while (n);
    while (i) putchar_unlocked(s[-- i] + '0');
}
#line 5 "modulus/stirling_number_of_the_second_kind_convolution.yosupo.test.cpp"

constexpr int MOD = 998244353;
int main() {
    int n = in<int>();
    auto f = stirling_number_of_the_second_kind_convolution<MOD>(n);
    REP (k, n + 1) {
        out<int>(f[k].value);
        out<char>(k < n ? ' ' : '\n');
    }
    return 0;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>
