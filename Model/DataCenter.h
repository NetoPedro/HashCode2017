//
// Created by Pedro Neto on 15/01/18.
//
#include <list>
#include <vector>
#include <iostream>
#include "Video.h"
#include "CacheServer.h"
#include "Endpoint.h"

#ifndef HASHCODE2017_DATACENTER_H
#define HASHCODE2017_DATACENTER_H


class DataCenter {
public :
    std::vector<CacheServer*> caches ;
    std::vector<Endpoint> endpoint ;
    std::vector<Video> videos ;

    long timeAllServerRequests();
};


#endif //HASHCODE2017_DATACENTER_H
