---
data:
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
  bundledCode: "#line 2 \"monoids/min.hpp\"\n#include <algorithm>\n#include <limits>\n\
    \ntemplate <class T>\nstruct min_monoid {\n    typedef T value_type;\n    value_type\
    \ unit() const { return std::numeric_limits<T>::max(); }\n    value_type mult(value_type\
    \ a, value_type b) const { return std::min(a, b); }\n};\n"
  code: "#pragma once\n#include <algorithm>\n#include <limits>\n\ntemplate <class\
    \ T>\nstruct min_monoid {\n    typedef T value_type;\n    value_type unit() const\
    \ { return std::numeric_limits<T>::max(); }\n    value_type mult(value_type a,\
    \ value_type b) const { return std::min(a, b); }\n};\n"
  dependsOn: []
  extendedDependsOn: []
  extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: string/longest_common_prefix.hpp
    title: "Longest Common Prefix / \u6700\u9577\u5171\u901A\u63A5\u982D\u8F9E (\u63A5\
      \u5C3E\u8F9E\u914D\u5217, \u524D\u51E6\u7406 $O(N (\\log N)^2)$ + $O(1)$)"
  - icon: ':heavy_check_mark:'
    path: utils/left_to_right_maxima.hpp
    title: "Length of Left-to-right Maxima (\u524D\u51E6\u7406 $O(n \\log n)$ + $O(1)$)"
  - icon: ':heavy_check_mark:'
    path: monoids/plus_min_action.hpp
    title: monoids/plus_min_action.hpp
  extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: string/longest_common_prefix.yosupo.test.cpp
    title: string/longest_common_prefix.yosupo.test.cpp
  - icon: ':heavy_check_mark:'
    path: data_structure/sparse_table.yosupo.test.cpp
    title: data_structure/sparse_table.yosupo.test.cpp
  - icon: ':heavy_check_mark:'
    path: data_structure/lazy_propagation_segment_tree.range_min_range_add.test.cpp
    title: data_structure/lazy_propagation_segment_tree.range_min_range_add.test.cpp
  - icon: ':heavy_check_mark:'
    path: graph/cartesian_tree.yukicoder-1031.test.cpp
    title: graph/cartesian_tree.yukicoder-1031.test.cpp
  isVerificationFile: false
  path: monoids/min.hpp
  requiredBy:
  - string/longest_common_prefix.hpp
  - utils/left_to_right_maxima.hpp
  - monoids/plus_min_action.hpp
  timestamp: '2019-12-27 19:16:13+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verificationStatusIcon: ':heavy_check_mark:'
  verifiedWith:
  - string/longest_common_prefix.yosupo.test.cpp
  - data_structure/sparse_table.yosupo.test.cpp
  - data_structure/lazy_propagation_segment_tree.range_min_range_add.test.cpp
  - graph/cartesian_tree.yukicoder-1031.test.cpp
documentation_of: monoids/min.hpp
layout: document
redirect_from:
- /library/monoids/min.hpp
- /library/monoids/min.hpp.html
title: monoids/min.hpp
---