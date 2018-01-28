//
// Created by Pedro Neto on 15/01/18.
//

#include "DataCenter.h"

Endpoint * DataCenter::endpointById(int id ) {


    for (Endpoint *e : this->endpoint){
        if (e->id == id){
            return e ;
        }
    }
    return nullptr;
}

Video * DataCenter::videoById(int id) {
    for(Video *v : this->videos){
        if(v->id  == id){
            return v;
        }
    }
    return nullptr;
}

CacheServer * DataCenter::cacheById(int id){
    for(CacheServer *c : this->caches){
        if(c->id  == id){
            return c;
        }
    }
    return nullptr;
}

long DataCenter::timeAllServerRequests() {
    float toReturn = 0;
    for (Endpoint *endpoint1 : this->endpoint) {
        for (std::pair<int,int> request : endpoint1->requests) {
            toReturn += request.second * endpoint1->serverLatency;
        }
    }
}