//
// Created by Pedro Neto on 15/01/18.
//
#include <list>
#include <iostream>
#include "Video.h"
#include "CacheServer.h"
#include "Endpoint.h"

#ifndef HASHCODE2017_DATACENTER_H
#define HASHCODE2017_DATACENTER_H


class DataCenter {
public :
    std::list<CacheServer*> caches ;
    std::list<Endpoint*> endpoint ;
    std::list<Video*> videos ;
    Endpoint * endpointById(int id );
    Video * videoById(int id );
};


#endif //HASHCODE2017_DATACENTER_H
