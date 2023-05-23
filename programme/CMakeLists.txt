cmake_minimum_required(VERSION 3.0)
project(monExecutable)

add_compile_options(-Wall)

set(SRCS0
    structure.cpp
    score.cpp autre.cpp
    )
    
set(SRCS1
    algo.cpp
    main.cpp
    )

#set(SRCS2
#    algo2.cpp
#    main2.cpp
#    )

set(HEADERS0
    structure.h
    score.h autre.h
    common.h
    )

set(HEADERS1
    algo.h
    )

#set(HEADERS2
#    algo2.h
#    )

add_executable(${PROJECT_NAME} ${SRCS0} ${SRCS1} ${HEADERS0} ${HEADERS1})