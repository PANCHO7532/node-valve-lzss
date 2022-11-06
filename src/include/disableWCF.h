/*
 * /====================================================================\
 * | Valve LZSS wrapper                                                 |
 * | Copyright (c) PANCHO7532 [pancho7532@p7com.net] 2022               |
 * |====================================================================|
 * |-> Purpose: Disable GCC/G++ unstable function cast warning          |
 * \====================================================================/
 * See: https://github.com/nodejs/nan/issues/807 for more info.
 */
#if defined(__GNUC__) && __GNUC__ >= 8
#define DISABLE_WCAST_FUNCTION_TYPE _Pragma("GCC diagnostic push") _Pragma("GCC diagnostic ignored \"-Wcast-function-type\"")
#define DISABLE_WCAST_FUNCTION_TYPE_END _Pragma("GCC diagnostic pop")
#else
#define DISABLE_WCAST_FUNCTION_TYPE
#define DISABLE_WCAST_FUNCTION_TYPE_END
#endif