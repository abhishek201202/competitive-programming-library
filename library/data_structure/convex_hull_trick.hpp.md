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


# :heavy_check_mark: a convex hull trick (非単調, online) <small>(data_structure/convex_hull_trick.hpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c8f6850ec2ec3fb32f203c1f4e3c2fd2">data_structure</a>
* <a href="{{ site.github.repository_url }}/blob/master/data_structure/convex_hull_trick.hpp">View this file on GitHub</a>
    - Last commit date: 2020-01-08 19:16:44+09:00


## 概要

一次関数の集合 $F = \emptyset \subseteq \lbrace \lambda x. ax + b \mid a, b \in \mathbb{Z} \rbrace$ に対し、次が処理可能:

-   直線追加: 与えられた $f = \lambda x. ax + b$ に対し $F \gets F \cup \lbrace f \rbrace$ と均し $O(\log N)$ で更新する
-   最小値取得: 与えられた $x$ に対し $\min _ {f \in F} f(x)$ を $O(\log N)$ で計算する


## Verified with

* :heavy_check_mark: <a href="../../verify/data_structure/convex_hull_trick.line_add_get_min.test.cpp.html">data_structure/convex_hull_trick.line_add_get_min.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
#include <cassert>
#include <climits>
#include <cstdint>
#include <map>
#include <set>
#include <utility>


namespace convex_hull_trick_details {
    /**
     * @note y = ax + b
     */
    struct line_t { int64_t a, b; };
    bool operator < (line_t lhs, line_t rhs) {
        return std::make_pair(- lhs.a, lhs.b) < std::make_pair(- rhs.a, rhs.b);
    }

    struct rational_t { int64_t num, den; };
    bool operator < (rational_t lhs, rational_t rhs) {
        if (lhs.num ==   INT64_MAX or rhs.num == - INT64_MAX) return false;
        if (lhs.num == - INT64_MAX or rhs.num ==   INT64_MAX) return true;
        return (__int128_t)lhs.num * rhs.den < (__int128_t)rhs.num * lhs.den;
    }
}


/*
 * @brief a convex hull trick (非単調, online)
 * @docs data_structure/convex_hull_trick.md
 */
class convex_hull_trick {
    typedef convex_hull_trick_details::line_t line_t;
    typedef convex_hull_trick_details::rational_t rational_t;
    static rational_t make_rational(int64_t num, int64_t den = 1) {
        if (den < 0) { num *= -1; den *= -1; }
        return { num, den };  // NOTE: no reduction
    }

public:
    convex_hull_trick() {
        lines.insert({ + INT64_MAX, 0 });  // sentinels
        lines.insert({ - INT64_MAX, 0 });
        cross.emplace(make_rational(- INT64_MAX), (line_t) { - INT64_MAX, 0 });
    }
    /**
     * @note O(log n)
     */
    void add_line(int64_t a, int64_t b) {
        auto it = lines.insert({ a, b }).first;
        if (not is_required(*prev(it), { a, b }, *next(it))) {
            lines.erase(it);
            return;
        }
        cross.erase(cross_point(*prev(it), *next(it)));
        {  // remove right lines
            auto ju = prev(it);
            while (ju != lines.begin() and not is_required(*prev(ju), *ju, { a, b })) -- ju;
            cross_erase(ju, prev(it));
            it = lines.erase(++ ju, it);
        }
        {  // remove left lines
            auto ju = next(it);
            while(next(ju) != lines.end() and not is_required({ a, b }, *ju, *next(ju))) ++ ju;
            cross_erase(++ it, ju);
            it = prev(lines.erase(it, ju));
        }
        cross.emplace(cross_point(*prev(it), *it), *it);
        cross.emplace(cross_point(*it, *next(it)), *next(it));
        assert (not empty());
    }
    bool empty() const {
        return lines.size() <= 2;
    }
    /**
     * @note O(log n)
     */
    int64_t get_min(int64_t x) const {
        assert (not empty());
        line_t f = prev(cross.lower_bound(make_rational(x)))->second;
        return f.a * x + f.b;
    }

private:
    std::set<line_t> lines;
    std::map<rational_t, line_t> cross;
    template <typename Iterator>
    void cross_erase(Iterator first, Iterator last) {
        for (; first != last; ++ first) {
            cross.erase(cross_point(*first, *next(first)));
        }
    }
    rational_t cross_point(line_t f1, line_t f2) const {
        if (f1.a ==   INT64_MAX) return make_rational(- INT64_MAX);
        if (f2.a == - INT64_MAX) return make_rational(  INT64_MAX);
        return make_rational(f1.b - f2.b, f2.a - f1.a);
    }
    bool is_required(line_t f1, line_t f2, line_t f3) const {
        if (f1.a == f2.a and f1.b <= f2.b) return false;
        if (f1.a == INT64_MAX or f3.a == - INT64_MAX) return true;
        return (__int128_t)(f2.a - f1.a) * (f3.b - f2.b) < (__int128_t)(f2.b - f1.b) * (f3.a - f2.a);
    }
};

struct inverted_convex_hull_trick {
    convex_hull_trick data;
    void add_line(int64_t a, int64_t b) { data.add_line(- a, - b); }
    int64_t get_max(int64_t x) { return - data.get_min(x); }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "data_structure/convex_hull_trick.hpp"
#include <cassert>
#include <climits>
#include <cstdint>
#include <map>
#include <set>
#include <utility>


namespace convex_hull_trick_details {
    /**
     * @note y = ax + b
     */
    struct line_t { int64_t a, b; };
    bool operator < (line_t lhs, line_t rhs) {
        return std::make_pair(- lhs.a, lhs.b) < std::make_pair(- rhs.a, rhs.b);
    }

    struct rational_t { int64_t num, den; };
    bool operator < (rational_t lhs, rational_t rhs) {
        if (lhs.num ==   INT64_MAX or rhs.num == - INT64_MAX) return false;
        if (lhs.num == - INT64_MAX or rhs.num ==   INT64_MAX) return true;
        return (__int128_t)lhs.num * rhs.den < (__int128_t)rhs.num * lhs.den;
    }
}


/*
 * @brief a convex hull trick (非単調, online)
 * @docs data_structure/convex_hull_trick.md
 */
class convex_hull_trick {
    typedef convex_hull_trick_details::line_t line_t;
    typedef convex_hull_trick_details::rational_t rational_t;
    static rational_t make_rational(int64_t num, int64_t den = 1) {
        if (den < 0) { num *= -1; den *= -1; }
        return { num, den };  // NOTE: no reduction
    }

public:
    convex_hull_trick() {
        lines.insert({ + INT64_MAX, 0 });  // sentinels
        lines.insert({ - INT64_MAX, 0 });
        cross.emplace(make_rational(- INT64_MAX), (line_t) { - INT64_MAX, 0 });
    }
    /**
     * @note O(log n)
     */
    void add_line(int64_t a, int64_t b) {
        auto it = lines.insert({ a, b }).first;
        if (not is_required(*prev(it), { a, b }, *next(it))) {
            lines.erase(it);
            return;
        }
        cross.erase(cross_point(*prev(it), *next(it)));
        {  // remove right lines
            auto ju = prev(it);
            while (ju != lines.begin() and not is_required(*prev(ju), *ju, { a, b })) -- ju;
            cross_erase(ju, prev(it));
            it = lines.erase(++ ju, it);
        }
        {  // remove left lines
            auto ju = next(it);
            while(next(ju) != lines.end() and not is_required({ a, b }, *ju, *next(ju))) ++ ju;
            cross_erase(++ it, ju);
            it = prev(lines.erase(it, ju));
        }
        cross.emplace(cross_point(*prev(it), *it), *it);
        cross.emplace(cross_point(*it, *next(it)), *next(it));
        assert (not empty());
    }
    bool empty() const {
        return lines.size() <= 2;
    }
    /**
     * @note O(log n)
     */
    int64_t get_min(int64_t x) const {
        assert (not empty());
        line_t f = prev(cross.lower_bound(make_rational(x)))->second;
        return f.a * x + f.b;
    }

private:
    std::set<line_t> lines;
    std::map<rational_t, line_t> cross;
    template <typename Iterator>
    void cross_erase(Iterator first, Iterator last) {
        for (; first != last; ++ first) {
            cross.erase(cross_point(*first, *next(first)));
        }
    }
    rational_t cross_point(line_t f1, line_t f2) const {
        if (f1.a ==   INT64_MAX) return make_rational(- INT64_MAX);
        if (f2.a == - INT64_MAX) return make_rational(  INT64_MAX);
        return make_rational(f1.b - f2.b, f2.a - f1.a);
    }
    bool is_required(line_t f1, line_t f2, line_t f3) const {
        if (f1.a == f2.a and f1.b <= f2.b) return false;
        if (f1.a == INT64_MAX or f3.a == - INT64_MAX) return true;
        return (__int128_t)(f2.a - f1.a) * (f3.b - f2.b) < (__int128_t)(f2.b - f1.b) * (f3.a - f2.a);
    }
};

struct inverted_convex_hull_trick {
    convex_hull_trick data;
    void add_line(int64_t a, int64_t b) { data.add_line(- a, - b); }
    int64_t get_max(int64_t x) { return - data.get_min(x); }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>
