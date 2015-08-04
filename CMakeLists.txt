CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(kizzy)

INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/include")
ADD_EXECUTABLE(
    kizzy 
    src/application.cpp
    src/applicationmatching.cpp
    src/applications.cpp
    src/configloader.cpp
    src/desktopparser.cpp
    src/directories.cpp
    src/directory.cpp
    src/main.cpp
    src/parsedapplication.cpp
    src/processlauncher.cpp
    src/searcher.cpp
    src/searchresults.cpp
    src/searchstring.cpp
    src/x11view.cpp
)

SET(${CXX_STANDARD_REQUIRED} true)
SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Og")
SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Os -fomit-frame-pointer -march=native -flto -s -fno-exceptions")
SET_PROPERTY(TARGET kizzy PROPERTY CXX_STANDARD 14)
SET_PROPERTY(TARGET kizzy PROPERTY LINK_FLAGS -lX11)
