///
#include <bela/stdwriter.hpp>
#include <bela/endian.hpp>

int wmain() {
  int val = 2;
  auto x = bela::Swapbe(val);
  bela::FPrintF(stderr,L"%d\n",x);
  return 0;
}