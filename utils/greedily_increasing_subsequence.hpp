#pragma once
#include <stack>
#include <tuple>
#include <utility>
#include <vector>
#include "utils/macros.hpp"
#include "data_structure/sparse_table.hpp"
#include "monoids/min.hpp"

/**
 * @brief Length of Greedily Increasing Subsequences (前処理 $O(n \log n)$ + $O(1)$)
 * @description computes the lengths of the greedily increasing subsubsequence for the given interval
 * @note the greedily increasing subsubsequence for a sequence $a$ means the subsubsequence of the elements $a_i$ which satisfy $\forall j \lt i. a_j \lt a_i$.
 */
class greedily_increasing_subsequence {
    std::vector<int> depth;
    sparse_table<min_monoid<int> > table;

public:
    greedily_increasing_subsequence() = default;

    int operator () (int l, int r) const {
        assert (0 <= l and l <= r and r <= (int)depth.size());
        if (l == r) return 0;
        return depth[l] - table.range_get(l, r) + 1;
    }

private:
    greedily_increasing_subsequence(const std::vector<int> & depth_)
            : depth(depth_), table(ALL(depth_)) {
    }

public:
    /**
     * @note this is just a constructor, but is needed to specify template arguments.
     */
    template <class T, class Comparator = std::less<T>, class RandomAccessIterator>
    static greedily_increasing_subsequence construct(RandomAccessIterator first, RandomAccessIterator last, const Comparator & cmp = Comparator()) {
        int n = std::distance(first, last);

        // make a forest
        std::vector<int> parent(n, -1);
        std::stack<int> stk;
        REP (i, n) {
            while (not stk.empty() and cmp(*(first + stk.top()), *(first + i))) {
                parent[stk.top()] = i;
                stk.pop();
            }
            stk.push(i);
        }

        // calculate depths
        std::vector<int> depth(n);
        REP_R (i, n) {
            if (parent[i] != -1) {
                depth[i] = depth[parent[i]] + 1;
            }
        }

        return greedily_increasing_subsequence(depth);
    }
};
