/*
 * /====================================================================\
 * | Valve LZSS wrapper                                                 |
 * | Copyright (c) PANCHO7532 [pancho7532@p7com.net] 2022               |
 * |====================================================================|
 * |-> Purpose: Valve typedefs                                          |
 * \====================================================================/
 * Most of the code here is extracted from: https://github.com/SteamRE/open-steamworks
 * Probably placeholder until I re-structure this into something more readable.
 */
#ifdef __GNUC__
typedef unsigned int errno_t;

#ifdef _S4N_
typedef unsigned int size_t;
#define NULL 0
#endif
#endif

#ifdef _WIN32
#define STEAM_CALL __cdecl
#else
#define STEAM_CALL
#endif

#if defined(__x86_64__) || defined(_WIN64)
#define X64BITS
#endif

typedef unsigned char uint8;
typedef signed char int8;

#if defined( _MSV_VER )

typedef __int16 int16;
typedef unsigned __int16 uint16;
typedef __int32 int32;
typedef unsigned __int32 uint32;
typedef __int64 int64;
typedef unsigned __int64 uint64;

#ifdef X64BITS
typedef __int64 intp;				// intp is an integer that can accomodate a pointer
typedef unsigned __int64 uintp;		// (ie, sizeof(intp) >= sizeof(int) && sizeof(intp) >= sizeof(void *)
#else
typedef __int32 intp;
typedef unsigned __int32 uintp;
#endif

#else // _MSV_VER

typedef unsigned char uint8;

typedef unsigned short uint16;
typedef signed short int16;

typedef unsigned int uint32;
typedef signed int int32;

typedef unsigned int uint;

typedef unsigned long long uint64;
typedef long long int64;
#ifdef X64BITS
typedef long long intp;
typedef unsigned long long uintp;
#else
typedef int intp;
typedef unsigned int uintp;
#endif

#endif // else _MSV_VER