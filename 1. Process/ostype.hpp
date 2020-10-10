#include <stdio.h>

enum OS {
    OS_WINDOWS,
    OS_ANDROID,
    OS_LINUX,
    OS_BSD,
    OS_HP_UX,
    OS_AIX,
    OS_IOS,
    OS_OSX,
    OS_SOLARIS,
    OS_UNKNOWN
};

/**
 * Determination a platform of an operation system
 * Fully supported supported only GNU GCC/G++, partially on Clang/LLVM
 */

#if defined(_WIN32)
    #define PLATFORM_NAME "windows" // Windows
    #define PLATFORM_ENUM OS_WINDOWS
#elif defined(_WIN64)
    #define PLATFORM_NAME "windows" // Windows
    #define PLATFORM_ENUM OS_WINDOWS
#elif defined(__CYGWIN__) && !defined(_WIN32)
    #define PLATFORM_NAME "windows" // Windows (Cygwin POSIX under Microsoft Window)
    #define PLATFORM_ENUM OS_WINDOWS
#elif defined(__ANDROID__)
    #define PLATFORM_NAME "android" // Android (implies Linux, so it must come first)
    #define PLATFORM_ENUM OS_ANDROID
#elif defined(__linux__)
    #define PLATFORM_NAME "linux" // Debian, Ubuntu, Gentoo, Fedora, openSUSE, RedHat, Centos and other
    #define PLATFORM_ENUM OS_LINUX
#elif defined(__unix__) || !defined(__APPLE__) && defined(__MACH__)
    #include <sys/param.h>
    #if defined(BSD)
        #define PLATFORM_NAME "bsd" // FreeBSD, NetBSD, OpenBSD, DragonFly BSD
        #define PLATFORM_ENUM OS_BSD
    #endif
#elif defined(__hpux)
    #define PLATFORM_NAME "hp-ux" // HP-UX
    #define PLATFORM_ENUM OS_HP_UX
#elif defined(_AIX)
    #define PLATFORM_NAME "aix" // IBM AIX
    #define PLATFORM_ENUM OS_AIX
#elif defined(__APPLE__) && defined(__MACH__) // Apple OSX and iOS (Darwin)
    #include <TargetConditionals.h>
    #if TARGET_IPHONE_SIMULATOR == 1
        #define PLATFORM_NAME "ios" // Apple iOS
        #define PLATFORM_ENUM OS_IOS
    #elif TARGET_OS_IPHONE == 1
        #define PLATFORM_NAME "ios" // Apple iOS
        #define PLATFORM_ENUM OS_IOS
    #elif TARGET_OS_MAC == 1
        #define PLATFORM_NAME "osx" // Apple OSX
        #define PLATFORM_ENUM OS_OSX
    #endif
#elif defined(__sun) && defined(__SVR4)
    #define PLATFORM_NAME "solaris" // Oracle Solaris, Open Indiana
    #define PLATFORM_ENUM OS_SOLARIS
#else
    #define PLATFORM_NAME NULL
    #define PLATFORM_ENUM OS_UNKNOWN
#endif

// Return a name of platform, if determined, otherwise - an empty string
inline const char *get_platform_name() {
    return (PLATFORM_NAME == NULL) ? "" : PLATFORM_NAME;
}