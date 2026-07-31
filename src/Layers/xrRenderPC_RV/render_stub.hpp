#pragma once 
#include <log.h>
#include <cstdio>

static inline void render_stub_impl(const char* msg, const char* func, const char * file) {
    if (msg) {
        Msg("%s: %s:%s", msg, file, func);
        fprintf(stdout, "%s: %s:%s\n", msg, file, func);
    } else {
        Msg("Render stub: %s:%s", file, func);
        fprintf(stderr, "Render stub: %s:%s\n", file, func);
    }
}

#define render_stub()  do {render_stub_impl(nullptr, __func__, __FILE__);} while(0);
#define render_stub_unimpl()  do {render_stub_impl("Not full implementation", __func__, __FILE__);} while(0);