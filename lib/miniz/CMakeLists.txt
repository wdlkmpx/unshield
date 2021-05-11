set(MINIZ_HEADERS
    "miniz.h"
)

set(MINIZ_SOURCES
    "miniz.c"
)

if(BUILD_STATIC AND MSVC)
    set_msvc_runtime_static()
endif()

add_library(miniz STATIC ${MINIZ_HEADERS} ${MINIZ_SOURCES})

# Linux/Clang-7
# relocation R_X86_64_32S against `.rodata' can not be used when making a shared object;
# recompile with -fPIC
include(CheckCCompilerFlag)
CHECK_C_COMPILER_FLAG("-fPIC" COMPILER_HAS_FPIC)
if (COMPILER_HAS_FPIC)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
endif()
