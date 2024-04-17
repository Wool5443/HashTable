cmake_minimum_required(VERSION 3.5)
set(projectName "HashTable")

project(${projectName} CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

set(CMAKE_CXX_FLAGS_DEBUG "-march=native -mavx512f -Wno-switch -Wno-conversion -Wno-unused-variable -Wno-pointer-arith -g -D _DEBUG -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wchar-subscripts -Wconditionally-supported -Wctor-dtor-privacy -Wempty-body -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Winit-self -Wredundant-decls -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -pie -fPIE -Werror=vla -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr")
set(CMAKE_CXX_FLAGS_RELEASE "-march=native -mavx512f -O3 -g -DNDEBUG")

set(SOURCES 
    "LinkedList/Utils/Utils.cpp"
    "LinkedList/Utils/Utils.hpp"
    "LinkedList/src/LinkedList.cpp"
    "LinkedList/src/PrettyDumpList.cpp"
    "LinkedList/headers/LinkedList.hpp"
    "LinkedList/headers/PrettyDumpList.hpp"
    "LinkedList/headers/ListSettings.ini"
    "String/headers/String.hpp"
    "String/headers/StringSettings.hpp"
    "String/src/String.cpp"
    "src/main.cpp"
    "src/HashTable.cpp"
    "src/DumpHashTable.cpp"
    "src/FileLoader.cpp"
    "src/Hash.cpp"
    "src/Testing.cpp"
    "src/StrcmpAVX512.cpp"
    "headers/HashTable.hpp"
    "headers/DumpHashTable.hpp"
    "headers/HashTableSettings.hpp"
    "headers/FileLoader.hpp"
    "headers/Hash.hpp"
    "headers/Testing.hpp"
    "headers/StrcmpAVX512.hpp"
)

file(MAKE_DIRECTORY "log/LinkedList/")
file(MAKE_DIRECTORY "log/LinkedList/txt")
file(MAKE_DIRECTORY "log/LinkedList/dot")
file(MAKE_DIRECTORY "log/LinkedList/img")
file(MAKE_DIRECTORY "Containers/")
file(MAKE_DIRECTORY "Results/")

include_directories(headers LinkedList/headers LinkedList/Utils String/headers)

add_executable(${projectName} ${SOURCES})

target_link_libraries(${projectName})
