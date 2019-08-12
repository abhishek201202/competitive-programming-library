#include "number/fast_fourier_transformation.hpp"

#include <cassert>
#include <random>
#include <vector>
#include "utils/macros.hpp"
using namespace std;

#include <iostream>
int main() {
    vector<int> f { 1, 2, 3 };
    vector<int> g { 10, 20, 30 };
    vector<int> h = convolution(f, g);
    assert (h[0] == 1 * 10);
    assert (h[1] == 1 * 20 + 2 * 10);
    assert (h[2] == 1 * 30 + 2 * 20 + 3 * 10);
    assert (h[3] ==          2 * 30 + 3 * 20);
    assert (h[4] ==                   3 * 30);

    default_random_engine gen;
    REP (iteration, 1000) {
        int n = uniform_int_distribution<int>(1, iteration + 1)(gen);
        int m = uniform_int_distribution<int>(1, iteration + 1)(gen);
        vector<int64_t> f(n);
        REP (i, n) {
            f[i] = uniform_int_distribution<int64_t>(- 1000000, 1000000)(gen);
        }
        vector<int64_t> g(m);
        REP (j, m) {
            g[j] = uniform_int_distribution<int64_t>(- 1000000, 1000000)(gen);
        }
        vector<int64_t> h(n + m - 1);
        REP (i, n) REP (j, m) {
            h[i + j] += f[i] * g[j];
        }
        assert (h == convolution(f, g));
    }
    return 0;
}
