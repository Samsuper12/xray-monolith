
#include <build_config_defines.h>
#include <LocatorAPI.h>

#include "log.h"
#include "os_clipboard.h"
#include "xrCore.h"
#include "xrDebug.h"
#include "xrsharedmem.h"

#include <boost/stacktrace.hpp>
#include <fmt/base.h>
#include <cstdlib>
#include <exception>

xrDebug Debug;

namespace crash_saving
{
    void (*save_impl)() = nullptr;
	BOOL enabled = TRUE;

    void save()
    {
        if (enabled && save_impl != nullptr)
        {
            (*save_impl)();
        }
    }
}

LPCSTR xrDebug::error2string(long code)
{
	Msg("error2string: %ld", code);
}

void xrDebug::do_exit(const std::string& message) {
	Msg("%s", message.c_str());
	fmt::print("Exit. Reason: {}\nStacktrace:{}", message, boost::stacktrace::to_string(boost::stacktrace::stacktrace()));
	std::abort();
}

void xrDebug::error(long hr, const char* expr, const char* file, int line, const char* function, bool& ignore_always)
{
	backend(expr, error2string(hr), 0, 0, file, line, function, ignore_always);
}

void xrDebug::error(long hr, const char* expr, const char* e2, const char* file, int line, const char* function,
                    bool& ignore_always)
{
	backend(expr, error2string(hr), e2, 0, file, line, function, ignore_always);
}

void xrDebug::fail(const char* e1, const char* file, int line, const char* function, bool& ignore_always)
{
	backend(e1, "assertion failed", 0, 0, file, line, function, ignore_always);
}

void xrDebug::fail(const char* e1, const std::string& e2, const char* file, int line, const char* function,
                   bool& ignore_always)
{
	backend(e1, e2.c_str(), 0, 0, file, line, function, ignore_always);
}

void xrDebug::fail(const char* e1, const char* e2, const char* file, int line, const char* function,
                   bool& ignore_always)
{
	backend(e1, e2, 0, 0, file, line, function, ignore_always);
}

void xrDebug::fail(const char* e1, const char* e2, const char* e3, const char* file, int line, const char* function,
                   bool& ignore_always)
{
	backend(e1, e2, e3, 0, file, line, function, ignore_always);
}

void xrDebug::fail(const char* e1, const char* e2, const char* e3, const char* e4, const char* file, int line,
                   const char* function, bool& ignore_always)
{
	backend(e1, e2, e3, e4, file, line, function, ignore_always);
}

void __cdecl xrDebug::fatal(const char* file, int line, const char* function, const char* F, ...)
{
	string1024 buffer;

	va_list p;
	va_start(p, F);
	vsprintf(buffer, F, p);
	va_end(p);

	bool ignore_always = true;

	backend(nullptr, "fatal error", buffer, 0, file, line, function, ignore_always);
}

void xrDebug::backend(const char* expression, const char* description, const char* argument0, const char* argument1,
                      const char* file, int line, const char* function, bool& ignore_always)
{
	static xrCriticalSection CS;

	CS.Enter();

	string4096 assertion_info;
	gather_info(expression, description, argument0, argument1, file, line, function, assertion_info,
	            sizeof(assertion_info));

	FlushLog();
	fmt::print("Stacktrace:\r\n{}\n{}\n", assertion_info, boost::stacktrace::to_string(boost::stacktrace::stacktrace()));

	CS.Leave();
	std::abort();
}

void xrDebug::gather_info(const char* expression, const char* description, const char* argument0, const char* argument1,
                          const char* file, int line, const char* function, char * assertion_info,
                          u32 const assertion_info_size)
{
	if (!expression)
		expression = "<no expression>";
	char * buffer_base = assertion_info;
	char * buffer = assertion_info;
	int assertion_size = (int)assertion_info_size;
	LPCSTR endline = "\n";
	LPCSTR prefix = "[error]";
	bool extended_description = (description && !argument0 && strchr(description, '\n'));
	for (int i = 0; i < 2; ++i) {
		if (!i)
			buffer += xr_sprintf(buffer, assertion_size - u32(buffer - buffer_base), "%sFATAL ERROR%s%s", endline,
			                     endline, endline);
		buffer += xr_sprintf(buffer, assertion_size - u32(buffer - buffer_base), "%sExpression    : %s%s", prefix,
		                     expression, endline);
		buffer += xr_sprintf(buffer, assertion_size - u32(buffer - buffer_base), "%sFunction      : %s%s", prefix,
		                     function, endline);
		buffer += xr_sprintf(buffer, assertion_size - u32(buffer - buffer_base), "%sFile          : %s%s", prefix, file,
		                     endline);
		buffer += xr_sprintf(buffer, assertion_size - u32(buffer - buffer_base), "%sLine          : %d%s", prefix, line,
		                     endline);

		if (extended_description) {
			buffer += xr_sprintf(buffer, assertion_size - u32(buffer - buffer_base), "%s%s%s", endline, description,
			                     endline);
			if (argument0) {
				if (argument1) {
					buffer += xr_sprintf(buffer, assertion_size - u32(buffer - buffer_base), "%s%s", argument0,
					                     endline);
					buffer += xr_sprintf(buffer, assertion_size - u32(buffer - buffer_base), "%s%s", argument1,
					                     endline);
				}
				else
					buffer += xr_sprintf(buffer, assertion_size - u32(buffer - buffer_base), "%s%s", argument0,
					                     endline);
			}
		}
		else {
			buffer += xr_sprintf(buffer, assertion_size - u32(buffer - buffer_base), "%sDescription   : %s%s", prefix,
			                     description, endline);
			if (argument0) {
				if (argument1) {
					buffer += xr_sprintf(buffer, assertion_size - u32(buffer - buffer_base), "%sArgument 0    : %s%s",
					                     prefix, argument0, endline);
					buffer += xr_sprintf(buffer, assertion_size - u32(buffer - buffer_base), "%sArgument 1    : %s%s",
					                     prefix, argument1, endline);
				}
				else
					buffer += xr_sprintf(buffer, assertion_size - u32(buffer - buffer_base), "%sArguments     : %s%s",
					                     prefix, argument0, endline);
			}
		}

		buffer += xr_sprintf(buffer, assertion_size - u32(buffer - buffer_base), "%s", endline);
		if (!i) {
			Msg("%s", assertion_info);
			FlushLog();
			buffer = assertion_info;
			endline = "\r\n";
			prefix = "";
		}
	}
}