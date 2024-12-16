cmake_minimum_required(VERSION 3.14)

# Nazwa projektu i ustawienie języka
project(cpp-project LANGUAGES CXX)

# Ustawienie wersji C++
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Znajdź wszystkie pliki źródłowe
file(GLOB_RECURSE SRC_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")

# Dodaj Raylib do projektu
find_package(raylib REQUIRED)

# Tworzenie pliku wykonywalnego
add_executable(cpp-project ${SRC_FILES})

# Dołączenie katalogu z nagłówkami
target_include_directories(cpp-project PUBLIC "${CMAKE_SOURCE_DIR}/include")

# Linkowanie z biblioteką Raylib
target_link_libraries(cpp-project raylib)

# Wymagane zależności dla systemu Linux
if (UNIX AND NOT APPLE)
    target_link_libraries(cpp-project m pthread dl rt X11)
endif()



# cmake_minimum_required(VERSION 3.14)
# project(cpp-project CXX)

# file(GLOB_RECURSE SRC_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")
# add_executable(cpp-project ${SRC_FILES})
# target_include_directories(cpp-project PUBLIC "${CMAKE_SOURCE_DIR}/include")
# set_target_properties(cpp-project PROPERTIES CXX_STANDARD 23)
