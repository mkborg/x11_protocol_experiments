#pragma once

#include "libc/base/endpoint.h"

namespace libc {
namespace Template {

template<typename T>
class EndPoint
  : public base::EndPoint
{
public:
  explicit inline EndPoint()
    : base::EndPoint(sizeof(T))
  {
  }
  explicit inline EndPoint(const T& a)
    : base::EndPoint(static_cast<void*>(&a), sizeof(a))
  {
  }
  EndPoint(const EndPoint&) = default;
  EndPoint(EndPoint&&) = default;
};

} // namespace Template
} // namespace libc
