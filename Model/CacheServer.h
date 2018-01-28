//
// Created by Pedro Neto on 15/01/18.
//
#include <list>
#include <iostream>
#include "Video.h"
#ifndef HASHCODE2017_CACHESERVER_H
#define HASHCODE2017_CACHESERVER_H


class CacheServer {
public: int id ;
    double maxCapacity ;
    std::list<int> videos ;
};


#endif //HASHCODE2017_CACHESERVER_H
