cmake_minimum_required(VERSION 3.10)
project(search_word C)

set(CMAKE_C_STANDARD 99)

add_executable(search_word
    main.c
    search.c
    file_utils.c
)
