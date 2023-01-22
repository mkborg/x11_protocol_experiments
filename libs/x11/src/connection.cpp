#include "connection.h"

#include "cxx/raw/data.h"
#include "exceptions/runtime_error.h"
#include "libc/getenv.h"
#include "libc/io/read.h"
#include "libc/io/write.h"
#include "libc/socket/connect.h"
#include "libc/template/socket.h"
#include "logger/debug.h"
//#include "logger/hex_dump.h"
//#include "utils/PREPROCESSOR.h"
#include "x11/connection/config.h"
#include "x11/connection/info.h"
#include "x11/connection/protocol.h"
#include "x11/connection/query.h"
#include "x11/connection/reply.h"
#include "x11/constants.h"
#include "x11/unix_endpoint.h"

/*
    https://datacadamia.com/ssh/x11/display

    hostname:D.S

    where:

    hostname is the name of the computer where the X server runs. An omitted hostname means the localhost.
    D is a sequence number (usually 0). It can be varied if there are multiple displays connected to one computer.
    S is the screen number. A display can actually have multiple screens. Usually there's only one screen though where 0 is the default.

    Examples:

    localhost:4
    example.com:0
    :0.0

    hostname:D.S means screen S on display D of host hostname; the X server for this display is listening at TCP port 6000+D.
    host/unix:D.S means screen S on display D of host host; the X server for this display is listening at UNIX domain socket /tmp/.X11-unix/XD (so it's only reachable from host).
    :D.S is equivalent to host/unix:D.S, where host is the local hostname.
*/
/*
    https://docs.oracle.com/cd/E88353_01/html/E37853/x11-7.html

    From  the  user's perspective, every X server has a display name of the
       form:

              hostname:displaynumber.screennumber
       or
              protocol/hostname:displaynumber.screennumber

       This information is used by the application to determine how it  should
       connect  to  the  server  and which screen it should use by default (on
       displays with multiple monitors):

       protocol
               The protocol specifies the protocol to use  for  communication.
               Exactly  which  protocols  are supported is platform dependent,
               but most commonly supported ones are:

               tcp     TCP over IPv4 or IPv6
               inet    TCP over IPv4 only
               inet6   TCP over IPv6 only
               unix    UNIX Domain Sockets (same host only)
               local   Platform preferred local connection method
               If the  protocol  is  not  specified,  Xlib  uses  whatever  it
               believes is the most efficient transport.

       hostname
               The  hostname  specifies  the  name of the machine to which the
               display is physically connected.  If the hostname is not given,
               a connection to a server on the same machine will be used.

       displaynumber
               The  phrase  "display" is usually used to refer to a collection
               of monitors that share a common set of input devices (keyboard,
               mouse,  tablet, etc.).  Most workstations tend to only have one
               display.  Larger, multi-user systems, however, frequently  have
               several  displays  so  that  more  than one person can be doing
               graphics work at once.  To avoid confusion, each display  on  a
               machine  is assigned a display number (beginning at 0) when the
               X server for that display is started.  The display number  must
               always be given in a display name.

       screennumber
               Some displays share their input devices among two or more moni-
               tors.  These may be configured  as  a  single  logical  screen,
               which  allows  windows to move across screens, or as individual
               screens, each with their own set  of  windows.   If  configured
               such  that each monitor has its own set of windows, each screen
               is assigned a screen number (beginning at 0) when the X  server
               for  that  display  is  started.   If  the screen number is not
               given, screen 0 will be used.
*/
/*
    mk:
        AF_UNIX, SOCK_STREAM, 0
        AF_INET, SOCK_STREAM, 0

    hostname:displaynumber.screennumber
*/

namespace x11 {

static ::libc::base::Socket connect(const std::string& display)
{
  DPRINTF("display='%s'", display.c_str());
  const auto connectionConfig = ::x11::connection::Config(display);

#if 0
  const auto raw_protocol_id = ::x11::connection::raw::toProtocol(connectionConfig.protocol().c_str());
  DPRINTF("raw_protocol_id=%u/'%s'", unsigned(raw_protocol_id), ::x11::connection::raw::toString(raw_protocol_id));

  const auto cxx_optionalProtocol = ::x11::connection::cxx::toOptionalProtocol(connectionConfig.protocol().c_str());
  DPRINTF("cxx_optionalProtocol={%i,%u/'%s'}", (bool)(cxx_optionalProtocol), unsigned(*cxx_optionalProtocol),
      ::x11::connection::raw::toString(*cxx_optionalProtocol));

  const auto optionalProtocol = ::x11::connection::toOptionalProtocol(connectionConfig.protocol().c_str());
  DPRINTF("optionalProtocol={%i,%u/'%s'}", (bool)(optionalProtocol), unsigned(*optionalProtocol),
      ::x11::connection::raw::toString(*optionalProtocol));

  const auto cxx_protocol = ::x11::connection::cxx::Protocol(connectionConfig.protocol().c_str());
  const auto cxx_raw_protocol_id = static_cast<::x11::connection::raw::Protocol_storage_type>(cxx_protocol);
  DPRINTF("cxx_raw_protocol_id=%u/'%s'", unsigned(cxx_raw_protocol_id),
      ::x11::connection::raw::toString(static_cast<::x11::connection::raw::Protocol>(cxx_protocol)));
#endif

  const auto endPoint = ::x11::unix::EndPoint(connectionConfig.display());
  const auto endPoint_socketPath = endPoint.socketPath();
  DPRINTF("endPoint_socketPath='%s'", endPoint_socketPath.c_str());

  ::libc::Unix::StreamSocket socket;
  ::libc::socket::cxx::connect(socket.get(), static_cast<const sockaddr*>(endPoint), endPoint.size());
  DPRINTF("connected");
  return std::move(socket);
}

//static ::x11::connection::Info connect(const ::libc::base::Socket& socket)
static ::cxx::raw::Data getInfoImage(const ::libc::base::Socket& socket)
{
  static const
  ::x11::connection::query::Header queryHeader = { 'l', 0, 11, 0, 0, 0, 0 };
  ::libc::io::cxx::write_exact(socket.get(), &queryHeader, sizeof(queryHeader));

  ::x11::connection::reply::Header replyHeader;
  ::libc::io::cxx::read_exact(socket.get(), &replyHeader, sizeof(replyHeader));
  const auto data_size = replyHeader.data_size * sizeof(uint32_t);
  DPRINTF("id=%u reason_size=%u major=%u minor=%u data_size=%u*4=%zu",
      replyHeader.id,
      replyHeader.reason_size,
      replyHeader.protocol_major_version, replyHeader.protocol_minor_version,
      replyHeader.data_size, data_size);

  auto extraData = ::cxx::raw::Data(data_size);
  if (data_size) {
    ::libc::io::cxx::read_exact(socket.get(), extraData.data(), extraData.size());
    //DHEX(extraData.data(), readed_size);
  }

  const auto replyId = static_cast<::x11::connection::reply::Id>(replyHeader.id);
  if (::x11::connection::reply::Id::Failed == replyId) {

    const auto reason = std::string( static_cast<const char*>(extraData.data()), replyHeader.reason_size);
    throw RUNTIME_ERROR_PRINTF("Unexpected connection reply id=%u reason='%s'",
        replyHeader.id, ::x11::connection::reply::toString(replyId), reason.c_str());

  } else if (::x11::connection::reply::Id::Success == replyId) {

    if (extraData.size() < sizeof(::x11::connection::Info)) {
      throw RUNTIME_ERROR_PRINTF("'connection::reply' is too short ('info' underflow)");
    }
    return extraData;
/*
    const auto info = static_cast<const ::x11::connection::Info*>(extraData.data());
    DPRINTF("release_number=%u resource_id_base=0x%X/%u resource_id_mask=0x%X/%u",
        info->release_number,
        info->resource_id_base, info->resource_id_base,
        info->resource_id_mask, info->resource_id_mask);
    DPRINTF("motion_buffer_size=%u vendor_size=%u request_maximum_size=%u screens_count=%u formats_count=%u",
        info->motion_buffer_size,
        info->vendor_size,
        info->request_maximum_size,
        info->screens_count,
        info->formats_count);
    DPRINTF("image_byte_order=%u bitmap_format_bit_order=%u",
        info->image_byte_order, info->bitmap_format_bit_order);
    DPRINTF("bitmap_format_scanline_unit=%u bitmap_format_scanline_pad=%u",
        info->bitmap_format_scanline_unit, info->bitmap_format_scanline_pad);
    DPRINTF("min_keycode=%u max_keycode=%u",
        info->min_keycode, info->max_keycode);

    const auto storage4vendor = extraData.size() - sizeof(::x11::connection::Info);
    if (storage4vendor < info->vendor_size) {
      throw RUNTIME_ERROR_PRINTF("'connection::reply' is too short ('%s' underflow)", "vendor");
    }
    const auto vendor_data = static_cast<const char*>(extraData.data()) + sizeof(::x11::connection::Info);
    const auto vendor = std::string(vendor_data, info->vendor_size);
    DPRINTF("vendor='%s'", vendor.c_str());

    const auto vendor_storage_size = (info->vendor_size + 3) & ~3;
    DPRINTF("vendor_storage_size=%u", vendor_storage_size);

    const auto storage4formats = storage4vendor - vendor_storage_size;
    const auto formats_storage_size = sizeof(::x11::connection::Format) * info->formats_count;
    if (storage4formats < formats_storage_size) {
      throw RUNTIME_ERROR_PRINTF("'connection::reply' is too short ('%s' underflow)", "formats");
    }
    const auto vendor_data_end = vendor_data + vendor_storage_size;
    const auto formats = reinterpret_cast<const ::x11::connection::Format*>(vendor_data_end);
    for (unsigned i = 0; i < info->formats_count; ++i) {
      DPRINTF("format[%u] depth=%u bits_per_pixel=%u scanline_pad=%u", i,
          formats[i].depth, formats[i].bits_per_pixel, formats[i].scanline_pad);
    }

    const auto storage4screens = storage4formats - formats_storage_size;
    const auto screens_storage_size = sizeof(::x11::connection::Screen) * info->screens_count;
    if (storage4screens < screens_storage_size) {
      throw RUNTIME_ERROR_PRINTF("'connection::reply' is too short ('%s' underflow)", "screens");
    }
    const auto formats_data_end = vendor_data_end + formats_storage_size;
    const auto screens = reinterpret_cast<const ::x11::connection::Screen*>(formats_data_end);
    for (unsigned i = 0; i < info->screens_count; ++i) {
      DPRINTF("screen[%u] root_window=%u default_colormap=%u white_pixel=0x%X/%u black_pixel=0x%X/%u", i,
          screens[i].root_window,
          screens[i].default_colormap,
          screens[i].white_pixel, screens[i].white_pixel,
          screens[i].black_pixel, screens[i].black_pixel);
    }

    // FIXME: parse 'connection info'
*/
  } else if (::x11::connection::reply::Id::Authenticate == replyId) {
    // Warning: 'reason_size' is not specified in 'Authenticate' documentation
    const auto reason = std::string( static_cast<const char*>(extraData.data()), replyHeader.reason_size);
    throw RUNTIME_ERROR_PRINTF("Unexpected connection reply id=%u reason='%s'",
        replyHeader.id, ::x11::connection::reply::toString(replyId), reason.c_str());
  } else {
    throw RUNTIME_ERROR_PRINTF("Unexpected connection reply id=%u",
        replyHeader.id, ::x11::connection::reply::toString(replyId));
  }
}

Connection::Connection(::libc::base::Socket&& socket)
  : ::libc::base::Socket( std::move(socket) )
  , ::x11::connection::Info(
      ::x11::getInfoImage( *static_cast<const ::libc::base::Socket*>(this) )
  )
{
}

Connection::Connection(const std::string& display)
  : Connection(::x11::connect(display))
{
}

Connection::Connection()
  : Connection(::libc::cxx::getenv(::x11::constants::environment::DISPLAY))
{
}

} // namespace x11
