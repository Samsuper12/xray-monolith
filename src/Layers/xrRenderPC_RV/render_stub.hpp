#pragma once 
#include <log.h>
#include <cstdio>

static const bool wannaMsg = false;

static inline void render_stub_impl(const char* msg, const char* func, const char * file) {
    if (!wannaMsg) return;

    if (msg) {
        Msg("[RV][STUB]: %s: %s:%s", msg, file, func);
    } else {
        Msg("[RV][STUB]: %s:%s", file, func);
    }
}

#define render_stub()  do {render_stub_impl(nullptr, __func__, __FILE__);} while(0);
#define render_stub_unimpl()  do {render_stub_impl("Not full implementation", __func__, __FILE__);} while(0);