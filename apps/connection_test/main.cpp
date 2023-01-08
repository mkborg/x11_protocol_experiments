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

  // 'error' and 'event' always have size of 32 bytes.
  // 'reply' always have header with 32 bytes size.
  // 'reply' may have 'additional data' with size specified in 'header'.
  auto eventData = ::cxx::raw::Data(sizeof(::x11::protocol::event::Base));
  ::libc::io::cxx::read_exact(connection.get(), eventData.data(), eventData.size());
  const auto eventBase = static_cast<const ::x11::protocol::event::Base*>(eventData.data());
  const auto eventId = static_cast<::x11::protocol::event::Id>(eventBase->id);
  DPRINTF("eventData: id=%u/'%s' sendEvent=%u",
      eventBase->id, ::x11::protocol::event::toString(eventId),
      eventBase->sendEvent);
  DHEX(eventData.data(), eventData.size());

  if (::x11::protocol::event::Id::Error == eventId) {
    const auto errorHeader = static_cast<const ::x11::protocol::error::Header*>(eventData.data());
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
  } else if (::x11::protocol::event::Id::SuccessReply == eventId) {
    const auto replyBase = static_cast<const ::x11::protocol::reply::Base*>(eventData.data());
    const auto extraData_size = replyBase->size * 4;
    DPRINTF("replyBase: status=%u/'%s' sequence_number=%u size=%u/%u",
        replyBase->status,
        ::x11::protocol::event::toString( (::x11::protocol::event::Id) (replyBase->status) ),
        replyBase->sequence_number,
        replyBase->size, extraData_size);
    if (extraData_size) {
      auto extraData = ::cxx::raw::Data(extraData_size);
#if 1
      ::libc::io::cxx::read_exact(connection.get(), extraData.data(), extraData.size());
#else
      const auto readed = ::libc::io::cxx::read(connection.get(), extraData.data(), extraData.size());
      DPRINTF("readed=%zu", readed);
#endif
      // TODO: decode extra data
      DHEX(extraData.data(), extraData.size());
    }
  } else {
    // TODO: decode event
    DHEX(eventData.data(), eventData.size());
  }
}

int main()
{
  ++debug_level;

  ::x11::Connection connection;

  tryNoOperation(connection);
  for (uint32_t atom = 0; atom < 4; ++atom) {
    tryGetAtomName(connection, atom);
  }

  return 0;
}
