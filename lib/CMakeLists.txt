project(libunshield C)

add_subdirectory(convert_utf)

find_package(ZLIB)
if(NOT ZLIB_FOUND)
add_subdirectory(zlib)
endif()

set(LIBUNSHIELD_HEADERS
    "internal.h"
    "libunshield.h"
    "log.h"
    "cabfile.h"
)

set(LIBUNSHIELD_SOURCES
    "component.c"
    "directory.c"
    "file.c"
    "file_group.c"
    "helper.c"
    "libunshield.c"
    "log.c"
)

if(BUILD_STATIC)
    add_library(${PROJECT_NAME} STATIC ${LIBUNSHIELD_HEADERS} ${LIBUNSHIELD_SOURCES})
else()
    add_library(${PROJECT_NAME} SHARED ${LIBUNSHIELD_HEADERS} ${LIBUNSHIELD_SOURCES})
endif()

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC convert_utf)

if(ZLIB_FOUND)
    target_link_libraries(${PROJECT_NAME} PUBLIC ZLIB::ZLIB)
else()
    target_link_libraries(${PROJECT_NAME} PUBLIC zlib)
endif()

set_target_properties(libunshield PROPERTIES PREFIX "")

install(TARGETS libunshield RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES libunshield.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
