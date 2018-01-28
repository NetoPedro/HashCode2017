//
// Created by Pedro Neto on 15/01/18.
//
#include <unordered_map>
#include "Video.h"
#include "CacheServer.h"
#ifndef HASHCODE2017_ENDPOINT_H
#define HASHCODE2017_ENDPOINT_H


class Endpoint {
public :int id ;
    std::unordered_map<int , float> cacheLatency ;
    std::unordered_map<int, int> requests  ;
    float serverLatency ;

};


#endif //HASHCODE2017_ENDPOINT_H
