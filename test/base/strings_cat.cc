///
#include <bela/__strings/string_cat_internal.hpp>
#include <bela/terminal.hpp>
#include <filesystem>

void u8stringshow() {
  bela::FPrintF(stderr, L"char8_t: %v\n", bela::string_cat<char8_t>(u8"args = 1"));
  bela::FPrintF(stderr, L"char8_t: %v\n", bela::string_cat<char8_t>(u8"args = ", 2));
  bela::FPrintF(stderr, L"char8_t: %v\n", bela::string_cat<char8_t>(u8"args ", u8"= ", 3));
  bela::FPrintF(stderr, L"char8_t: %v\n", bela::string_cat<char8_t>(u8"args ", u8"= ", 3, u8",", 5));
  constexpr char32_t em = 0x1F603; // 😃 U+1F603
  bela::FPrintF(stderr, L"char8_t: %s\n",
                bela::string_cat<char8_t>(u8"Look emoji --> ", em, u8" see: U+", bela::Hex(em)));
  bela::FPrintF(stderr, L"char8_t: %v\n",
                bela::string_cat<char8_t>(u8"Look emoji --> ", em, u8" see: U+", bela::Hex(em), u8" jacksome"));
}

void stringshow() {
  bela::FPrintF(stderr, L"char: %v\n", bela::string_cat<char>(u8"args = 1"));
  bela::FPrintF(stderr, L"char: %v\n", bela::string_cat<char>(u8"args = ", 2));
  bela::FPrintF(stderr, L"char: %v\n", bela::string_cat<char>(u8"args ", u8"= ", 3));
  bela::FPrintF(stderr, L"char: %v\n", bela::string_cat<char>(u8"args ", u8"= ", 3, u8",", 5));
  constexpr char32_t em = 0x1F603; // 😃 U+1F603
  bela::FPrintF(stderr, L"char: %s\n", bela::string_cat<char>(u8"Look emoji --> ", em, u8" see: U+", bela::Hex(em)));
  bela::FPrintF(stderr, L"char: %v\n",
                bela::string_cat<char>(u8"Look emoji --> ", em, " see: U+", bela::Hex(em), u8" jacksome"));
}

void wstringshow() {
  bela::FPrintF(stderr, L"wchar_t: %v\n", bela::string_cat<wchar_t>(L"args = 1"));
  bela::FPrintF(stderr, L"wchar_t: %v\n", bela::string_cat<wchar_t>(L"args = ", 2));
  bela::FPrintF(stderr, L"wchar_t: %v\n", bela::string_cat<wchar_t>(L"args ", L"= ", 3));
  bela::FPrintF(stderr, L"wchar_t: %v\n", bela::string_cat<wchar_t>(L"args ", L"= ", 3, L",", 5));
  constexpr char32_t em = 0x1F603; // 😃 U+1F603
  bela::FPrintF(stderr, L"wchar_t: %s\n",
                bela::string_cat<wchar_t>(L"Look emoji --> ", em, L" see: U+", bela::Hex(em)));
  bela::FPrintF(stderr, L"wchar_t: %v\n",
                bela::string_cat<wchar_t>(L"Look emoji --> ", em, L" see: U+", bela::Hex(em), L" jacksome"));
}

int wmain(int argc, wchar_t **argv) {
  std::error_code ec;
  constexpr char32_t blueheart = U'💙';
  auto arg0 = std::filesystem::absolute(argv[0], ec);
  bela::basic_alphanum<wchar_t> was[] = {(std::numeric_limits<uint64_t>::max)(),
                                         (std::numeric_limits<uint64_t>::min)(),
                                         (std::numeric_limits<int64_t>::max)(),
                                         (std::numeric_limits<int64_t>::min)(),
                                         (std::numeric_limits<uint32_t>::max)(),
                                         (std::numeric_limits<uint32_t>::min)(),
                                         (std::numeric_limits<int32_t>::max)(),
                                         (std::numeric_limits<int32_t>::min)(),
                                         (std::numeric_limits<uint16_t>::max)(),
                                         (std::numeric_limits<uint16_t>::min)(),
                                         (std::numeric_limits<int16_t>::max)(),
                                         (std::numeric_limits<int16_t>::min)(),
                                         1,
                                         1.2f,
                                         L"hello world",
                                         u"hello world",
                                         u'\u00a9',
                                         L'我',
                                         L"这是一段简单的文字",
                                         blueheart,
                                         arg0,
                                         bela::Hex((std::numeric_limits<int32_t>::max)(), bela::kZeroPad20),
                                         bela::Hex((std::numeric_limits<int32_t>::min)(), bela::kZeroPad20),
                                         bela::Dec((std::numeric_limits<int32_t>::max)(), bela::kZeroPad20),
                                         bela::Dec((std::numeric_limits<int32_t>::min)(), bela::kZeroPad20)};
  for (const auto &a : was) {
    bela::FPrintF(stderr, L"wchar_t: %v\n", a.Piece());
  }
  bela::basic_alphanum<char16_t> uas[] = {(std::numeric_limits<uint64_t>::max)(),
                                          (std::numeric_limits<uint64_t>::min)(),
                                          (std::numeric_limits<int64_t>::max)(),
                                          (std::numeric_limits<int64_t>::min)(),
                                          (std::numeric_limits<uint32_t>::max)(),
                                          (std::numeric_limits<uint32_t>::min)(),
                                          (std::numeric_limits<int32_t>::max)(),
                                          (std::numeric_limits<int32_t>::min)(),
                                          (std::numeric_limits<uint16_t>::max)(),
                                          (std::numeric_limits<uint16_t>::min)(),
                                          (std::numeric_limits<int16_t>::max)(),
                                          (std::numeric_limits<int16_t>::min)(),
                                          1,
                                          1.2f,
                                          L"hello world",
                                          u"hello world",
                                          u'\u00a9',
                                          L'我',
                                          L"这是一段简单的文字",
                                          blueheart,
                                          arg0,
                                          bela::Hex((std::numeric_limits<int32_t>::max)(), bela::kZeroPad20),
                                          bela::Hex((std::numeric_limits<int32_t>::min)(), bela::kZeroPad20),
                                          bela::Dec((std::numeric_limits<int32_t>::max)(), bela::kZeroPad20),
                                          bela::Dec((std::numeric_limits<int32_t>::min)(), bela::kZeroPad20)};
  for (const auto &a : uas) {
    bela::FPrintF(stderr, L"char16_t: %v\n", a.Piece());
  }
  bela::basic_alphanum<char8_t> u8as[] = {(std::numeric_limits<uint64_t>::max)(),
                                          (std::numeric_limits<uint64_t>::min)(),
                                          (std::numeric_limits<int64_t>::max)(),
                                          (std::numeric_limits<int64_t>::min)(),
                                          (std::numeric_limits<uint32_t>::max)(),
                                          (std::numeric_limits<uint32_t>::min)(),
                                          (std::numeric_limits<int32_t>::max)(),
                                          (std::numeric_limits<int32_t>::min)(),
                                          (std::numeric_limits<uint16_t>::max)(),
                                          (std::numeric_limits<uint16_t>::min)(),
                                          (std::numeric_limits<int16_t>::max)(),
                                          (std::numeric_limits<int16_t>::min)(),
                                          1,
                                          1.2f,
                                          u8"hello world",
                                          "hello world",
                                          u8'U',
                                          'x',
                                          U'我',
                                          u8"这是一段简单的文字",
                                          blueheart,
                                          bela::Hex((std::numeric_limits<int32_t>::max)(), bela::kZeroPad20),
                                          bela::Hex((std::numeric_limits<int32_t>::min)(), bela::kZeroPad20),
                                          bela::Dec((std::numeric_limits<int32_t>::max)(), bela::kZeroPad20),
                                          bela::Dec((std::numeric_limits<int32_t>::min)(), bela::kZeroPad20)};
  for (const auto &a : u8as) {
    bela::FPrintF(stderr, L"char8_t: %v\n", a.Piece());
  }
  bela::basic_alphanum<char> cas[] = {(std::numeric_limits<uint64_t>::max)(),
                                      (std::numeric_limits<uint64_t>::min)(),
                                      (std::numeric_limits<int64_t>::max)(),
                                      (std::numeric_limits<int64_t>::min)(),
                                      (std::numeric_limits<uint32_t>::max)(),
                                      (std::numeric_limits<uint32_t>::min)(),
                                      (std::numeric_limits<int32_t>::max)(),
                                      (std::numeric_limits<int32_t>::min)(),
                                      (std::numeric_limits<uint16_t>::max)(),
                                      (std::numeric_limits<uint16_t>::min)(),
                                      (std::numeric_limits<int16_t>::max)(),
                                      (std::numeric_limits<int16_t>::min)(),
                                      1,
                                      1.97821741f,
                                      u8"hello world",
                                      "hello world",
                                      u8'U',
                                      'x',
                                      U'我',
                                      "这是一段简单的文字",
                                      blueheart,
                                      bela::Hex((std::numeric_limits<int32_t>::max)(), bela::kZeroPad20),
                                      bela::Hex((std::numeric_limits<int32_t>::min)(), bela::kZeroPad20),
                                      bela::Dec((std::numeric_limits<int32_t>::max)(), bela::kZeroPad20),
                                      bela::Dec((std::numeric_limits<int32_t>::min)(), bela::kZeroPad20)};
  for (const auto &a : cas) {
    bela::FPrintF(stderr, L"char: %v\n", a.Piece());
  }
  u8stringshow();
  stringshow();
  wstringshow();
  return 0;
}