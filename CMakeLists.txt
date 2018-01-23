cmake_minimum_required(VERSION 3.9)
project(HashCode2017)

set(CMAKE_CXX_STANDARD 14)

add_executable(HashCode2017 main.cpp Model/Endpoint.cpp Model/Endpoint.h Model/CacheServer.cpp Model/CacheServer.h Model/Video.cpp Model/Video.h Scanner/Importer.cpp Scanner/Importer.h Model/DataCenter.cpp Model/DataCenter.h GA/GeneticAlgorithm.cpp GA/GeneticAlgorithm.h)