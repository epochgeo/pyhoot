
#ifndef __LIB_EXPORTS_H__
#define __LIB_EXPORTS_H__

#ifdef BUILD_STATIC_LIB
# define LIB_EXPORT
#elif (defined BUILD_DYN_LIB)
# if (defined __WIN32__) || (defined _WIN32) || defined(__CYGWIN__)
#  ifdef __GNUC__    
#   define LIB_EXPORT  __cdecl __attribute__((dllexport))
#  else
#   define LIB_EXPORT  __cdecl __declspec(dllexport)
#  endif
# else
#  define LIB_EXPORT  __attribute__ ((visibility ("default")))
# endif
#else
# if (defined __WIN32__) || (defined _WIN32) || defined(__CYGWIN__)
#  ifdef __GNUC__
#   define LIB_EXPORT  __cdecl
#  else
#   define LIB_EXPORT  __declspec(dllexport)
#  endif
# else
#  define LIB_EXPORT
# endif
#endif

#endif