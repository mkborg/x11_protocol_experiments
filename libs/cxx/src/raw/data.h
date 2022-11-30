#pragma once

/// @brief 'raw data' aka 'bytes' storage

#include <string>

#include <stddef.h>     // size_t

namespace cxx {
namespace raw {

class Data
{
private:
  std::string data_;

public:
  inline const void* data() const { return &data_[0]; }
  inline void* data() { return &data_[0]; }
  inline size_t size() const { return data_.size(); }

  inline bool empty() const { return data_.empty(); }

  inline void resize(size_t size, unsigned char filler = 0)
  {
    data_.resize(size, filler);
  }

  Data() = default;
  inline Data(const void* data, size_t size)
    : data_(static_cast<const char*>(data), size) {}
  inline Data(size_t size, unsigned char filler = 0)
    : data_(size, static_cast<std::string::value_type>(filler)) {}
};

} // namespace raw
} // namespace cxx
