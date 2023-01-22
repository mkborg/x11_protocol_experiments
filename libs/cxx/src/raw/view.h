#pragma once

/*
    This is 'raw view' for 'raw data' aka 'bytes'.

    Probably It shall be named 'DataView' (or 'RawDataView'). Alternatively
    both 'RawData' and 'RawView' can be moved into 'raw' namespace as 'Data'
    and 'View'.

    Internally it holds only pointer to actual data stored elsewhere and size
    of 'visible' part of that data.

    It is somehow similar to 'std::string_view' or 'boost::asio::buffer'
    ('const_buffer' and 'mutable_buffer')
*/

//#include "misc/byte.h"

//#include <string>

#include <string.h> // memcmp()

namespace cxx {
namespace raw {
namespace base {

// 'void', 'char' or 'byte' (aka 'unsigned char')
// 'T' is internally stored type ('char' or 'byte')
// 'P' is externally visible [pointed] type ('P*' i.e. 'void*' or 'T*')
template <typename T, typename P = T>
class View
{
private:
  T* data_;
  size_t size_;

  //explicit inline static operator P*(T* t) { return reinterpret_cast<P*>(t); }
  //explicit inline static operator T*(P* p) { return reinterpret_cast<T*>(p); }

public:
  inline const P* data() const { return data_; }
  inline P* data() { return data_; }
  inline size_t size() const { return size_; }

  inline bool empty() const { return !size(); }

  /*
    ...[......]....... available
    ......[.......]... requested
    ......[...]....... returned
  */
  View subView(size_t pos = 0, size_t count = -1) const
  {
    auto available_size = size();
    if (pos > available_size) {
      pos = available_size;
    }
    auto remainig_size = available_size - pos;
    if (count > remainig_size) {
      count = remainig_size;
    }
    return View(data() + pos, count);
  }

  int compare(const View& v) const
  {
    auto size1(size());
    auto size2(v.size());
    auto common_size = (size1 < size2) ? size1 : size2;
    auto r(memcmp(data(), v.data(), common_size));
    return (r) ? r : (size1 - size2);
  }

  ~View() = default;

  View(const View& o) = default;
  View(View&& o) = default;

  View& operator=(const View& o) = default;
  View& operator=(View&& o) = default;

  View(P* data, size_t size)
    : data_( static_cast<T*>(data) )
    , size_(size)
  {
  }

  // Moves the start of the view forward by n characters. 
  void remove_prefix( size_t n )
  {
    data_ += n;
    size_ -= n;
  }

#if 0
  // Moves the end of the view back by n characters. 
  void remove_suffix( size_t n );
#endif
};

} // namespace base
} // namespace raw
} // namespace cxx
