#include "x11/protocol/request.h"

namespace x11 {
namespace protocol {
namespace request {

GetAtomName::operator ::cxx::raw::Data() const
{
  struct GetAtomNameRequest
  {
    Header header;
    uint32_t atom;
  }
  request = {
    .header = {
      .opcode = (uint8_t) (Id::GetAtomName),
      .unused_1 = 0,
      .size = scaleSize(sizeof(GetAtomNameRequest)),
    },
    .atom = atom_
  };
  return ::cxx::raw::Data(&request, sizeof(request));
}

NoOperation::operator ::cxx::raw::Data() const
{
  static const auto header = Header {
    .opcode = (uint8_t) (Id::NoOperation),
    .unused_1 = 0,
    .size = scaleSize(sizeof(Header))
  };
  return ::cxx::raw::Data(&header, sizeof(header));
}

} // namespace request
} // namespace protocol
} // namespace x11
