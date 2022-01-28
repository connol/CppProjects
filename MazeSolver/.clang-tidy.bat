# Configuration options for clang-tidy
# CSS Linux machines, Sep 2019: LLVM version 3.8.1
#
# usage: clang-tidy *.cpp -- -std=c++14
#
#
---
# See https://clang.llvm.org/extra/clang-tidy/#using-clang-tidy for all possible checks
Checks: '*,-fuchsia-*,-cppcoreguidelines-pro-bounds-array-to-pointer-decay,-google-readability-braces-around-statements,-google-build-using-namespace,-readability-braces-around-statements,-hicpp-no-array-decay,-modernize-use-trailing-return-type,-hicpp-braces-around-statements,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-llvm-header-guard,-google-global-names-in-headers,-cppcoreguidelines-special-member-functions,-hicpp-special-member-functions,-cppcoreguidelines-owning-memory'

HeaderFilterRegex: '.*'

# Based on LLVM style in https://llvm.org/docs/CodingStandards.html#the-low-level-issues
CheckOptions:
 - { key: readability-identifier-naming.ClassCase,           value: CamelCase  }
 - { key: readability-identifier-naming.StructCase,          value: CamelCase  }
 - { key: readability-identifier-naming.EnumCase,            value: CamelCase  }
 - { key: readability-identifier-naming.VariableCase,        value: CamelCase  }
 - { key: readability-identifier-naming.GlobalConstantCase,  value: UPPER_CASE }
 - { key: readability-identifier-naming.FunctionCase,        value: camelBack  }
 - { key: readability-identifier-naming.PublicMethodCase,    value: camelBack  }
 - { key: readability-identifier-naming.PrivateMethodCase,   value: camelBack  }
 - { key: readability-identifier-naming.PublicMemberCase,    value: CamelCase  } 
...
