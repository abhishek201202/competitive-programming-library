---
data:
  attributes: {}
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.8.5/x64/lib/python3.8/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 64, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir).decode()\n  File \"/opt/hostedtoolcache/Python/3.8.5/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/python.py\"\
    , line 84, in bundle\n    raise NotImplementedError\nNotImplementedError\n"
  code: "def extgcd(a, b):\n    if b == 0:\n        return 1, 0\n    else:\n     \
    \   na, nb = extgcd(b, a % b)\n        return nb, na - a//b * nb\ndef modinv(a,\
    \ n):\n    return extgcd(a, n)[0] % n\n"
  dependsOn: []
  extendedDependsOn: []
  extendedRequiredBy: []
  extendedVerifiedWith: []
  isVerificationFile: false
  path: python/extgcd.py
  requiredBy: []
  timestamp: '2017-01-17 21:58:21+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verificationStatusIcon: ':warning:'
  verifiedWith: []
documentation_of: python/extgcd.py
layout: document
redirect_from:
- /library/python/extgcd.py
- /library/python/extgcd.py.html
title: python/extgcd.py
---