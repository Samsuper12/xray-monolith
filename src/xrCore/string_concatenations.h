#ifndef STRING_CONCATENATIONS_H
#define STRING_CONCATENATIONS_H

#include "_types_own.h"
#include "_stl_extensions.h"

class shared_str;

#ifndef _EDITOR

char * XRCORE_API strconcat(int dest_sz, char* dest, const char* S1, const char* S2);
char * XRCORE_API strconcat(int dest_sz, char* dest, const char* S1, const char* S2, const char* S3);
char * XRCORE_API strconcat(int dest_sz, char* dest, const char* S1, const char* S2, const char* S3, const char* S4);
char * XRCORE_API strconcat(int dest_sz, char* dest, const char* S1, const char* S2, const char* S3, const char* S4,
                           const char* S5);
char * XRCORE_API strconcat(int dest_sz, char* dest, const char* S1, const char* S2, const char* S3, const char* S4,
                           const char* S5, const char* S6);

#else // _EDITOR
// obsolete: should be deleted as soon borland work correctly with new strconcats
inline char* strconcat(int dest_sz, char* dest, const char* S1, const char* S2)
{
    return xr_strcat(xr_strcpy(dest, dest_sz, S1), dest_sz, S2);
}

// dest = S1+S2+S3
inline char* strconcat(int dest_sz, char* dest, const char* S1, const char* S2, const char* S3)
{
    return xr_strcat(xr_strcat(xr_strcpy(dest, dest_sz, S1), dest_sz, S2), dest_sz, S3);
}

// dest = S1+S2+S3+S4
inline char* strconcat(int dest_sz, char* dest, const char* S1, const char* S2, const char* S3, const char* S4)
{
    return xr_strcat(xr_strcat(xr_strcat(xr_strcpy(dest, dest_sz, S1), dest_sz, S2), dest_sz, S3), dest_sz, S4);
}

// dest = S1+S2+S3+S4+S5
inline char* strconcat(int dest_sz, char* dest, const char* S1, const char* S2, const char* S3, const char* S4, const char* S5)
{
    return xr_strcat(xr_strcat(xr_strcat(xr_strcat(xr_strcpy(dest, dest_sz, S1), dest_sz, S2), dest_sz, S3), dest_sz, S4), dest_sz, S5);
}

// dest = S1+S2+S3+S4+S5+S6
inline char* strconcat(int dest_sz, char* dest, const char* S1, const char* S2, const char* S3, const char* S4, const char* S5, const char* S6)
{
    return xr_strcat(xr_strcat(xr_strcat(xr_strcat(xr_strcat(xr_strcpy(dest, dest_sz, S1), dest_sz, S2), dest_sz, S3), dest_sz, S4), dest_sz, S5), dest_sz, S6);
}

#endif

// warning: do not comment this macro, as stack overflow check is very light
// (consumes ~1% performance of STRCONCAT macro)
#ifndef _EDITOR
#define STRCONCAT_STACKOVERFLOW_CHECK

#ifdef STRCONCAT_STACKOVERFLOW_CHECK

#define STRCONCAT(dest, ...) \
 do { \
 xray::core::detail::string_tupples STRCONCAT_tupples_unique_identifier(__VA_ARGS__); \
 u32 STRCONCAT_buffer_size = STRCONCAT_tupples_unique_identifier.size(); \
 xray::core::detail::check_stack_overflow(STRCONCAT_buffer_size); \
 (dest) = (char *)alloca(STRCONCAT_buffer_size); \
 STRCONCAT_tupples_unique_identifier.concat (dest); \
  } while (0)

#else //#ifdef STRCONCAT_STACKOVERFLOW_CHECK

#define STRCONCAT(dest, ...) \
 do { \
 xray::core::detail::string_tupples STRCONCAT_tupples_unique_identifier(__VA_ARGS__); \
 (dest) = (char *)alloca(STRCONCAT_tupples_unique_identifier.size()); \
 STRCONCAT_tupples_unique_identifier.concat (dest); \
  } while (0)

#endif //#ifdef STRCONCAT_STACKOVERFLOW_CHECK

#endif //_EDITOR
#include "xrstring.h"
#include "string_concatenations_inline.h"

// Giperion XRay Oxygen - ultimate version of strconcat
template<typename StringReceiverType, typename... ArgList>
char* xr_strconcat(StringReceiverType& receiver, ArgList... args)
{
	static_assert(std::is_array< StringReceiverType>::value); // must be array...
	static_assert(std::is_same<typename std::remove_extent< StringReceiverType>::type, char>::value); // ... of chars

	char* pStrCursor = &receiver[0];
	char* pStrEnd = &receiver[0] + sizeof(StringReceiverType);
	int dummy[] = { _strconcatSingle(pStrCursor, pStrEnd, args)... };
	(void)dummy;

	*pStrCursor = '\0';
	return &receiver[0];
}

int XRCORE_API _strconcatSingle(char*& destPtr, char* pDestEnd, const char* Str);


#endif // #ifndef STRING_CONCATENATIONS_H