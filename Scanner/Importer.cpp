//
// Created by Pedro Neto on 15/01/18.
//

#include <fstream>
#include <iostream>
#include <fstream>
#include <string>
#include "../Model/Endpoint.h"
#include "../Model/Video.h"
#include "Importer.h"
#include "../Model/DataCenter.h"


DataCenter Importer::import(std::string filename) {

    std::fstream importer;
    importer.open(filename);
    DataCenter *dataCenter = new DataCenter(); // Initialize the DataCenter to contain all the info of the file
    //Verifies if the file was open
    if (importer.is_open()) {
        std::string elementsCountLine;
        getline(importer,elementsCountLine);
        // Reads the first line of the file
        int videoCount = atoi(elementsCountLine.substr(0, elementsCountLine.find(" ")).c_str());
        elementsCountLine.erase(0, elementsCountLine.find(" ") + 1);
        int endPointsCount = atoi(elementsCountLine.substr(0, elementsCountLine.find(" ")).c_str());
        elementsCountLine.erase(0, elementsCountLine.find(" ") + 1);
        int requestCount = atoi(elementsCountLine.substr(0, elementsCountLine.find(" ")).c_str());
        elementsCountLine.erase(0, elementsCountLine.find(" ") + 1);
        int cacheCount = atoi(elementsCountLine.substr(0, elementsCountLine.find(" ")).c_str());
        elementsCountLine.erase(0, elementsCountLine.find(" ") + 1);
        int cacheSize = atoi(elementsCountLine.c_str());
        //std::list<CacheServer*>::iterator cacheIt = dataCenter->caches.begin();
        dataCenter->caches =  std::vector<CacheServer * >(cacheCount);
        for (int i = 0; i < cacheCount ; ++i) { //Creates Caches using information of the first line
            CacheServer *cacheServer = new CacheServer();
            cacheServer->id = i ;
            cacheServer->maxCapacity = cacheSize;
            dataCenter->caches[i] = cacheServer;  //Store the created cache into the datacenter
        }
        if (videoCount != 0) { // Verifies if there is any video to import
            std::string videoLine;
            getline(importer,videoLine);
            dataCenter->videos = std::vector<Video*>(videoCount);
            for (int i = 0; i < videoCount; ++i) { // Creates objects of the type Video with there size and ID
                Video *video = new Video();
                video->id = i ;
                video->size = atoi(videoLine.substr(0,videoLine.find(" ")).c_str());
                videoLine.erase(0,videoLine.find(" ") + 1);
                dataCenter->videos[i]=video; //Store the created video into the datacenter
            }
        }
        std::list<Endpoint*>::iterator itEndpoints = dataCenter->endpoint.begin();

        for (int i = 0; i < endPointsCount; ++i) { // Creates Endpoints
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

            for (int j = 0; j < endPointConnections; ++j) { //Relate the new Endpoint with cache servers
                std::string  endpointCacheLine    ;
                getline(importer,endpointCacheLine);
                int cacheId = atoi(endpointCacheLine.substr(0,endpointCacheLine.find(" ")).c_str()) ;
                endpointCacheLine.erase(0,endpointCacheLine.find(" ") + 1);
                int cacheLatency = atoi(endpointCacheLine.substr(0,endpointCacheLine.find(" ")).c_str()) ;
                endpoint->cacheLatency.insert(std::pair<int,float>(cacheId,cacheLatency));

            }
            dataCenter->endpoint.insert(itEndpoints, (endpoint)); // Store the created endpoint into the datacenter
        }
        for (int i = 0; i < requestCount; ++i) { // Creates relation beetween videos and endpoints.
            std::string requestString ;
            getline(importer,requestString);
            int videoID = atoi(requestString.substr(0,requestString.find(" ")).c_str());
            requestString.erase(0,requestString.find(" ") +1 );
            int requestEndpoint = atoi(requestString.substr(0,requestString.find(" ")).c_str());
            requestString.erase(0, requestString.find(" ") + 1);
            int quantityOfResquests = atoi(requestString.c_str());
            Endpoint *endpoint = dataCenter->endpointById(requestEndpoint);
            endpoint->requests.insert(std::pair<int,int>(videoID,quantityOfResquests));

        }

        std::cout << "";
    }
    importer.close(); // Close the file
    return *dataCenter;
}