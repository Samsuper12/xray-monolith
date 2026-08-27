#pragma once

#define TRACY_ENABLE
#include <tracy/Tracy.hpp>

#define PROF_THREAD(...)
#define PROF_FRAME() FrameMark
#define PROF_EVENT_N(msg) ZoneScopedN(msg);
#define PROF_EVENT() ZoneScoped;
#define START_PROFILE(msg)                                                     \
  {                                                                            \
    PROF_EVENT_N(msg)
#define STOP_PROFILE }
