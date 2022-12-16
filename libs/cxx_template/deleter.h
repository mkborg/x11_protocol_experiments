/**
@file
@brief    'Deleter' template for std::shared_ptr and std::unique_ptr
@details  Copyright (c) 2020 Acronis International GmbH
@author   Mikhail Krivtsov (mikhail.krivtsov@acronis.com)
@since    $Id: $
*/

#pragma once

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
