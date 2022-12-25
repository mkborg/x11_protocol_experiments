#pragma once

/// @brief    'Deleter' template for std::shared_ptr and std::unique_ptr

namespace Template {

template <typename T, void(*deleter)(T*)>
struct Deleter
{
  inline void operator()(T* p)
  {
    deleter(p);
  }
};

} // namespace Template
