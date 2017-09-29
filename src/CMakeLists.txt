project(src)

set(HEADERS wordCount.h)

set(SOURCES wordCount.cpp)

add_library(src ${HEADERS} ${SOURCES})