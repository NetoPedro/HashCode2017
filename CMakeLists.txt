cmake_minimum_required(VERSION 3.9)
project(HashCode2017)

set(CMAKE_CXX_STANDARD 14)

add_executable(HashCode2017 main.cpp Endpoint.cpp Endpoint.h CacheServer.cpp CacheServer.h Video.cpp Video.h Importer.cpp Importer.h DataCenter.cpp DataCenter.h)