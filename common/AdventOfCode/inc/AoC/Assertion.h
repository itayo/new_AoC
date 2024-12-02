#ifndef ADVENTOFCODE_ASSERTION_H
#define ADVENTOFCODE_ASSERTION_H

#include <iostream>

namespace Assert {
#define TestOrExitBase(assert, cond, file, line) \
{                                               \
  if(!assert) {                                    \
  std::cout << "\nAssertion failed " << "at " << file << "#" << line << " condition = (" << cond << ")" << std::endl; \
  std::terminate();                                   \
  }                                                   \
}

#define ExitOnAssertFail(assert) \
{                            \
TestOrExitBase(assert,#assert,__FILE__,__LINE__); \
}

#define ExitIfReached() \
{                            \
TestOrExitBase(false,"Should not reach",__FILE__,__LINE__); \
}

#define ExitIfReachedWithMessage(s) \
{                            \
TestOrExitBase(false,"Should not reach!!! " + s,__FILE__,__LINE__); \
}
}

#endif //ADVENTOFCODE_ASSERTION_H