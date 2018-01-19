//
// Created by Pedro Neto on 15/01/18.
//

#include <fstream>
#include <iostream>
#include <fstream>
#include <string>
#include "Endpoint.h"
#include "Video.h"
#include "Importer.h"
#include "DataCenter.h"


void Importer::import(std::string filename) {

    std::fstream importer;
    importer.open(filename);
    if (importer.is_open()) {
        std::string elementsCountLine;
        getline(importer,elementsCountLine);
        DataCenter *dataCenter = new DataCenter();
        int videoCount = atoi(elementsCountLine.substr(0, elementsCountLine.find(" ")).c_str());
        elementsCountLine.erase(0, elementsCountLine.find(" ") + 1);
        int endPointsCount = atoi(elementsCountLine.substr(0, elementsCountLine.find(" ")).c_str());
        elementsCountLine.erase(0, elementsCountLine.find(" ") + 1);
        int requestCount = atoi(elementsCountLine.substr(0, elementsCountLine.find(" ")).c_str());
        elementsCountLine.erase(0, elementsCountLine.find(" ") + 1);
        int cacheCount = atoi(elementsCountLine.substr(0, elementsCountLine.find(" ")).c_str());
        elementsCountLine.erase(0, elementsCountLine.find(" ") + 1);
        int cacheSize = atoi(elementsCountLine.c_str());
        std::list<CacheServer*>::iterator cacheIt = dataCenter->caches.begin();
        for (int i = 0; i < cacheCount ; ++i) {
            ++cacheIt;
            CacheServer *cacheServer = new CacheServer();
            cacheServer->id = i ;
            cacheServer->maxCapacity = cacheSize;
            dataCenter->caches.insert(cacheIt,cacheServer);
        }
        if (videoCount != 0) {
            std::string videoLine;
            getline(importer,videoLine);
            std::list<Video*>::iterator it = dataCenter->videos.begin();
            for (int i = 0; i < videoCount; ++i) {
                Video *video = new Video();
                video->id = i ;
                video->size = atoi(videoLine.substr(0,videoLine.find(" ")).c_str());
                videoLine.erase(0,videoLine.find(" ") + 1);
               // dataCenter->videos.insert(video,);
                dataCenter->videos.insert(it,video);
                ++it;
            }
        }
        std::list<Endpoint*>::iterator itEndpoints = dataCenter->endpoint.begin();

        for (int i = 0; i < endPointsCount; ++i) {
            int endPointConnections = 0 ;
            ++itEndpoints;
            std::string endPointLine;
            getline(importer,endPointLine);
            int latencyToDataCenter = atoi(endPointLine.substr(0,endPointLine.find(" ")).c_str());
            endPointLine.erase(0,endPointLine.find(" ") + 1);
            endPointConnections = atoi(endPointLine.c_str());
            Endpoint *endpoint = new Endpoint();
            endpoint->id = i ;
            endpoint->serverLatency = latencyToDataCenter ;

            for (int j = 0; j < endPointConnections; ++j) {
                std::string  endpointCacheLine    ;
                getline(importer,endpointCacheLine);
                int cacheId = atoi(endpointCacheLine.substr(0,endpointCacheLine.find(" ")).c_str()) ;
                endpointCacheLine.erase(0,endpointCacheLine.find(" ") + 1);
                int cacheLatency = atoi(endpointCacheLine.substr(0,endpointCacheLine.find(" ")).c_str()) ;
                endpoint->cacheLatency.insert(std::pair<int,float>(cacheId,cacheLatency));
                //Ligar ID à cache
                //Adicionar EndPoints ao datacenter
            }
            dataCenter->endpoint.insert(itEndpoints, (endpoint));
        }
        for (int i = 0; i < requestCount; ++i) {
            std::string requestString ;
            getline(importer,requestString);
            int videoID = atoi(requestString.substr(0,requestString.find(" ")).c_str());
            requestString.erase(0,requestString.find(" ") +1 );
            int requestEndpoint = atoi(requestString.substr(0,requestString.find(" ")).c_str());
            requestString.erase(0, requestString.find(" ") + 1);
            int quantityOfResquests = atoi(requestString.c_str());
           // Request *request = new Request();
            Endpoint *endpoint = dataCenter->endpointById(requestEndpoint);
            endpoint->requests.insert(std::pair<int,int>(videoID,quantityOfResquests));

        }

        std::cout << "";
    }
    importer.close();

}