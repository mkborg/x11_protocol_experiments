#include "x11/protocol/event.h"

#include "utils/PREPROCESSOR.h"

namespace x11 {
namespace protocol {
namespace event {

static char const * const names[] =
{
  "Error"			, // 0
  "SuccessReply"		, // 1

  "KeyPressEvent"		, // 2
  "KeyReleaseEvent"		, // 3
  "ButtonPressEvent"		, // 4
  "ButtonReleaseEvent"		, // 5
  "MotionNotifyEvent"		, // 6
  "EnterNotifyEvent"		, // 7
  "LeaveNotifyEvent"		, // 8
  "FocusInEvent"		, // 9
  "FocusOutEvent"		, // 10
  "KeymapNotifyEvent"		, // 11
  "ExposeEvent"			, // 12
  "GraphicsExposureEvent"	, // 13
  "NoExposureEvent"		, // 14
  "VisibilityNotifyEvent"	, // 15
  "CreateNotifyEvent"		, // 16
  "DestroyNotifyEvent"		, // 17
  "UnmapNotifyEvent"		, // 18
  "MapNotifyEvent"		, // 19
  "MapRequestEvent"		, // 20
  "ReparentNotifyEvent"		, // 21
  "ConfigureNotifyEvent"	, // 22
  "ConfigureRequestEvent"	, // 23
  "GravityNotifyEvent"		, // 24
  "ResizeRequestEvent"		, // 25
  "CirculateNotifyEvent"	, // 26
  "CirculateRequestEvent"	, // 27
  "PropertyNotifyEvent"		, // 28
  "SelectionClearEvent"		, // 29
  "SelectionRequestEvent"	, // 30
  "SelectionNotifyEvent"	, // 31
  "ColormapNotifyEvent"		, // 32
  "ClientMessageEvent"		, // 33
  "MappingNotifyEvent"		, // 34
};

char const * toString(Id id)
{
  return
      (unsigned(id) < ARRAY_SIZE(names))
          ? names[unsigned(id)]
          : "?";
}

} // namespace event
} // namespace protocol
} // namespace x11
