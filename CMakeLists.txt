cmake_minimum_required(VERSION 3.9)
project(Program2)

set(CMAKE_CXX_STANDARD 11)

add_executable(Program2
        Autograder/json.hpp
        createteams.cxx
        teamdata.cpp
        teamdata.h
        json.hpp
        priorityqueue.cpp
        priorityqueue.h
        )
