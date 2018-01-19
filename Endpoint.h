//
// Created by Pedro Neto on 15/01/18.
//
#include <map>
#include "Video.h"
#include "CacheServer.h"
#ifndef HASHCODE2017_ENDPOINT_H
#define HASHCODE2017_ENDPOINT_H


class Endpoint {
public :int id ;
    std::map<int , float> cacheLatency ;
    std::map<int, int> requests  ;
    float serverLatency ;

};


#endif //HASHCODE2017_ENDPOINT_H
