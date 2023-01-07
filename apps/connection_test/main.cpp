#include "cxx/raw/data.h"
#include "libc/io/read.h"
#include "libc/io/write.h"
#include "logger/debug.h"
//#include "logger/debug_level.h"
#include "logger/hex_dump.h"
#include "x11/connection.h"
#include "x11/protocol/error.h"
#include "x11/protocol/event.h"
#include "x11/protocol/request.h"
#include "x11/protocol/reply.h"

// Looks like 'NoOperation' does not produce 'reply'
static void tryNoOperation(const ::x11::Connection& connection)
{
  const auto request = ::x11::protocol::request::NoOperation().operator ::cxx::raw::Data();
  ::libc::io::cxx::write_exact(connection.get(), request.data(), request.size());
  DPRINTF("request '%s()' sent", "NoOperation");
/*
  auto reply = ::cxx::raw::Data(32);
  const auto readed_size = ::libc::io::cxx::read(connection.get(), reply.data(), reply.size());
  DPRINTF("readed_size=%zu", readed_size);
  DHEX(reply.data(), readed_size);
*/
}

static void tryGetAtomName(const ::x11::Connection& connection, uint32_t atom)
{
  const auto request = ::x11::protocol::request::GetAtomName(atom).operator ::cxx::raw::Data();
  ::libc::io::cxx::write_exact(connection.get(), request.data(), request.size());
  DPRINTF("request '%s(%u)' sent", "GetAtomName", atom);

  auto reply = ::cxx::raw::Data(0x1000);
  const auto readed_size = ::libc::io::cxx::read(connection.get(), reply.data(), reply.size());
  DPRINTF("readed_size=%zu", readed_size);
  if (sizeof(::x11::protocol::reply::Header) <= readed_size) {
    const auto replyHeader = static_cast<const ::x11::protocol::reply::Header*>(reply.data());
    DPRINTF("replyHeader: status=%u/'%s' size=%u/%u",
        replyHeader->status,
        ::x11::protocol::event::toString( (::x11::protocol::event::Id) (replyHeader->status) ),
        replyHeader->size, replyHeader->size * 4);
    if (::x11::protocol::event::Id::Error == (::x11::protocol::event::Id) (replyHeader->status)) {
      const auto errorHeader = static_cast<const ::x11::protocol::error::Header*>(reply.data());
      DPRINTF("error_code=%u/'%s' sequence_number=%u bad=0x%X/%u major_opcode=%u/'%s' minor_opcode=%u",
          errorHeader->error_code,
          ::x11::protocol::error::toString( (::x11::protocol::error::Id) (errorHeader->error_code) ),
          errorHeader->sequence_number,
          errorHeader->bad,
          errorHeader->bad,
          errorHeader->major_opcode,
          ::x11::protocol::request::toString( (::x11::protocol::request::Id) (errorHeader->major_opcode)),
          errorHeader->minor_opcode
      );
    }
  }
  DHEX(reply.data(), readed_size);
}

int main()
{
  ++debug_level;
  ::x11::Connection connection;
  tryNoOperation(connection);
  tryGetAtomName(connection, 0);
  tryGetAtomName(connection, 1);

  return 0;
}
