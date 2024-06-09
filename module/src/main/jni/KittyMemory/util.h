#ifndef UTILS
#define UTILS

#include <jni.h>
#include <unistd.h>
#include <cstdio>
#include <cstring>
#include <string>
#include <cstdlib>
#include "Log.h"
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <locale>
#include <codecvt>
#include <unistd.h>
#include <sys/uio.h>
#include <sys/mman.h>
#include <inttypes.h>
#include <sys/system_properties.h>
#include <stdio.h>
#include <string.h>

typedef unsigned long DWORD;
static uintptr_t libBase;

bool libLoaded = false;



char* basename(char* path) {
  char* last_slash = strrchr(path, '/');
  if (last_slash == NULL) {
   return path;
  } else {
   return last_slash + 1;
  }
 }

DWORD findLibrary(const char *library) {
    DWORD result = 0;
    char line[512];

    FILE *f = fopen("/proc/self/maps", "rt");

    if (!f) return result;

    while (fgets(line, sizeof line, f)) {
        uintptr_t tmpBase;
        uintptr_t tmpEnd;
        char tmpName[256];
        char tmpPerms[4]; 
        if (sscanf(line, "%" PRIXPTR "-%" PRIXPTR "%s %*s %*s %*s %s", &tmpBase, &tmpEnd, tmpPerms, tmpName) > 0) {
            if (!strcmp(basename(tmpName), library) && strstr(tmpPerms, "xp") != NULL) {
                result = (DWORD)tmpBase;
                break;
            }
        }
    }
    fclose(f);
    return result;
}

DWORD getAbsoluteAddress(const char *libraryName, DWORD relativeAddr) {
    libBase = findLibrary(libraryName);
    if (libBase == 0)
        return 0;
    return (reinterpret_cast<DWORD>(libBase + relativeAddr));
}


jboolean isGameLibLoaded(JNIEnv *env, jobject thiz) {
    return libLoaded;
}

bool isLibraryLoaded(const char *libraryName) {
    //libLoaded = true;
    char line[512] = {0};
    FILE *fp = fopen(OBFUSCATE("/proc/self/maps"), OBFUSCATE("rt"));
    if (fp != NULL) {
        while (fgets(line, sizeof(line), fp)) {
            std::string a = line;
            if (strstr(line, libraryName)) {
                libLoaded = true;
                return true;
            }
        }
        fclose(fp);
    }
    return false;
}

uintptr_t string2Offset(const char *c) {
    int base = 16;
    // See if this function catches all possibilities.
    // If it doesn't, the function would have to be amended
    // whenever you add a combination of architecture and
    // compiler that is not yet addressed.
    static_assert(sizeof(uintptr_t) == sizeof(unsigned long)
                  || sizeof(uintptr_t) == sizeof(unsigned long long),
                  "Please add string to handle conversion for this architecture.");

    // Now choose the correct function ...
    if (sizeof(uintptr_t) == sizeof(unsigned long)) {
        return strtoul(c, nullptr, base);
    }

    // All other options exhausted, sizeof(uintptr_t) == sizeof(unsigned long long))
    return strtoull(c, nullptr, base);
}

#include <iostream>
#include <cstring>

uintptr_t obfuscateMD5(const char *md5String) {
    // Your obfuscation logic here, for example, a simple XOR operation
    const char key = 'A';
    size_t length = strlen(md5String);
    char obfuscatedMD5[length + 1];

    for (size_t i = 0; i < length; ++i) {
        obfuscatedMD5[i] = md5String[i] ^ key;
    }

    obfuscatedMD5[length] = '\0';

    // Convert the obfuscated string to uintptr_t using your existing function
    return string2Offset(obfuscatedMD5);
}

int main() {
    const char *originalMD5 = "your_original_md5_here";
    uintptr_t obfuscatedValue = obfuscateMD5(originalMD5);

    // Use the obfuscatedValue as needed in your code
    std::cout << "Obfuscated Value: " << obfuscatedValue << std::endl;

    return 0;
}


#endif
