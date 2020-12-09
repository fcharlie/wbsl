//
#ifndef HAZEL_ELF_HPP
#define HAZEL_ELF_HPP
#include "hazel.hpp"
#include <bela/endian.hpp>
#include "elf.h"

namespace hazel::elf {

constexpr int COMPRESS_ZLIB = 1;            /* ZLIB compression. */
constexpr int COMPRESS_LOOS = 0x60000000;   /* First OS-specific. */
constexpr int COMPRESS_HIOS = 0x6fffffff;   /* Last OS-specific. */
constexpr int COMPRESS_LOPROC = 0x70000000; /* First processor-specific type. */
constexpr int COMPRESS_HIPROC = 0x7fffffff; /* Last processor-specific type. */

// ELF64 file header.
struct FileHeader {
  uint8_t Class;
  uint8_t Data;
  uint8_t Version;
  uint8_t OSABI;
  uint8_t ABIVersion;
  uint8_t LSB;
  uint16_t Type;    /* File type. */
  uint16_t Machine; /* Machine architecture. */
  uint64_t Entry;   /* Entry point. */
};

struct ProgHeader {
  int Type;
  int Flags;
  uint64_t Off;
  uint64_t Vaddr;
  uint64_t Paddr;
  uint64_t Filesz;
  uint64_t Memsz;
  uint64_t Align;
};

struct Symbol {
  std::string Name;
  std::string Version;
  std::string Library;
  uint64_t Value;
  uint64_t Size;
  int SectionIndex;
  uint8_t Info;
  uint8_t Other;
};

struct Section {
  std::string Name;
  uint32_t Type{0};
  uint64_t Flags{0};
  uint64_t Addr{0};
  uint64_t Offset{0};
  uint64_t Size{0};
  uint32_t Link{0};
  uint32_t Info{0};
  uint64_t Addralign{0};
  uint64_t Entsize{0};
  uint64_t FileSize{0};
  int64_t compressionOffset{0};
  int compressionType{0};
  uint32_t nameIndex;
};

class File {
private:
  bool ParseFile(bela::error_code &ec);
  bool PositionAt(uint64_t pos, bela::error_code &ec) const {
    auto li = *reinterpret_cast<LARGE_INTEGER *>(&pos);
    LARGE_INTEGER oli{0};
    if (SetFilePointerEx(fd, li, &oli, SEEK_SET) != TRUE) {
      ec = bela::make_system_error_code(L"SetFilePointerEx: ");
      return false;
    }
    return true;
  }
  bool Read(void *buffer, size_t len, size_t &outlen, bela::error_code &ec) const {
    DWORD dwSize = {0};
    if (ReadFile(fd, buffer, static_cast<DWORD>(len), &dwSize, nullptr) != TRUE) {
      ec = bela::make_system_error_code(L"ReadFile: ");
      return false;
    }
    outlen = static_cast<size_t>(len);
    return true;
  }
  bool ReadAt(void *buffer, size_t len, uint64_t pos, size_t &outlen, bela::error_code &ec) {
    if (!PositionAt(pos, ec)) {
      return false;
    }
    return Read(buffer, len, outlen, ec);
  }
  bool ReadAt(bela::Buffer &b, size_t len, uint64_t pos, bela::error_code &ec) const {
    if (len > b.capacity()) {
      b.grow(bela::align_length(len));
    }
    if (!PositionAt(pos, ec)) {
      return false;
    }
    return Read(b.data(), len, b.size(), ec);
  }
  void Free() {
    if (needClosed && fd != INVALID_HANDLE_VALUE) {
      CloseHandle(fd);
      fd = INVALID_HANDLE_VALUE;
    }
  }
  void MoveFrom(File &&r) {
    Free();
    fd = r.fd;
    r.fd = INVALID_HANDLE_VALUE;
    r.needClosed = false;
    size = r.size;
    sections = std::move(r.sections);
    progs = std::move(r.progs);
    memcpy(&fh, &r.fh, sizeof(fh));
  }

  template <typename T> T SwapByte(T t) {
    if (en == bela::endian::Endian::native) {
      return t;
    }
    return bela::bswap(t);
  }
  const Section *SectionByType(uint32_t st) const {
    for (const auto &s : sections) {
      if (s.Type == st) {
        return &s;
      }
    }
    return nullptr;
  }
  bool getSymbols64(uint32_t st, std::vector<Symbol> &syms, bela::Buffer &buffer, bela::error_code &ec);
  bool getSymbols32(uint32_t st, std::vector<Symbol> &syms, bela::Buffer &buffer, bela::error_code &ec);

public:
  File() = default;
  File(const File &) = delete;
  File &operator=(const File &) = delete;
  ~File() { Free(); }
  // NewFile resolve pe file
  bool NewFile(std::wstring_view p, bela::error_code &ec);
  bool NewFile(HANDLE fd_, int64_t sz, bela::error_code &ec);
  int64_t Size() const { return size; }
  const auto &Sections() const { return sections; }
  const auto &Progs() const { return progs; }
  bool DynString(int tag, std::vector<std::string> &sv, bela::error_code &ec);
  bool Importeds(std::vector<std::string> &libs, bela::error_code &ec) { return DynString(DT_NEEDED, libs, ec); }

private:
  HANDLE fd{INVALID_HANDLE_VALUE};
  int64_t size{bela::SizeUnInitialized};
  bela::endian::Endian en{bela::endian::Endian::native};
  FileHeader fh;
  std::vector<Section> sections;
  std::vector<ProgHeader> progs;
  bool is64bit{false};
  bool needClosed{false};
};
} // namespace hazel::elf

#endif