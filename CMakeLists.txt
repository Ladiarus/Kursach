cmake_minimum_required(VERSION 3.21)
project(Kursach)

set(CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")

add_executable(Kursach main.cpp Account.cpp Account.h Core.cpp Core.h Menues.cpp Menues.h MySpace.cpp MySpace.h DB_accounts.cpp DB_accounts.h Hash/sha256.cpp Hash/sha256.h Hash/Hash.cpp Hash/Hash.h main.h globals.h globals.cpp Student.cpp Student.h DB_students.cpp DB_students.h)
