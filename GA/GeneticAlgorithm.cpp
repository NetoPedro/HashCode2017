//
// Created by Pedro Neto on 19/01/18.
//

#include <zconf.h>
#include "GeneticAlgorithm.h"

#define POPULATION_SIZE 200
#define MUTATION_TAX 0.10
#define SWAP_TAX 0.20

/**
 * Function to start the Genetic Algorithm
 * @param generations Number of generations until stop
 * @param dataCenter DataCenter with the information to run the geneticAlgorithm
 * @param geneSize Size of the Chromosome
 */

void GeneticAlgorithm::init(int generations, DataCenter dataCenter) {
    this->dataCenter = dataCenter ;
    srand (time(NULL));
    findNumberOfRequests();
    this->population = std::vector<std::list<std::string>>(POPULATION_SIZE * 2);
    this->generateInitialPopulation(POPULATION_SIZE);
    for (int i = 0; i < generations; ++i) {
        std::cout << "Geração " << i << std::endl;
     //   std::cout << "Iniciando Cross" << std::endl;
        crossover();
      //  std::cout << "Iniciando Mut" << std::endl;

        mutation();
      //  std::cout << "Iniciando Sel" << std::endl;

        selection();
    }
    std::cout << "Pop Size" << this->population.size() << " "  << std::endl;

    for (std::list<std::string> strings : this->population) {
        for(std::string string : strings){
            std::cout << string << " " ;
        }

        std::cout << std::endl;
        fitness(strings);
    }
    std::cout << "Best : " ;
    for(std::string string : bestSolution){
        std::cout << string << " " ;
    }

    std::cout << std::endl;
    std::cout << "Fitness == " << fitness(bestSolution) * -1 * 1000<< std::endl;

}
/**
 * Function to apply a crossover technique in the population
 * Uses a random mask to cross parents
 * @param geneSize Size of the chromosome
 */
void GeneticAlgorithm::crossover() {
    std::list<int> newMembers;
    std::vector<CacheServer*> caches = this->dataCenter.caches;
    for(CacheServer *cacheServer : caches){
        cacheServer->videos.clear();
    }
    int cacheCount = dataCenter.caches.size();
    int point1;


    //std::vector<std::list<std::string>>::iterator iterator = descendants->begin();
    for (int j = 0; j < POPULATION_SIZE ; j+=2) {
        //auto it1 = std::next(this->population.begin(), j);
        std::list<std::string> parent1 = this->population[j];
       // auto it2 = std::next(this->population.begin(), j+1);
        std::list<std::string> parent2 = this->population[j+1];
        int cacheSize1 = findMaxCacheNumber(parent1) ;
        int cacheSize2 = findMaxCacheNumber(parent2) ;
        if (cacheSize1 > cacheSize2){
            point1 = rand() % (cacheSize2)+1;

        } else{
            point1 = rand() % (cacheSize1)+1;

        }
       // point1 = rand() % (cacheCount - 1) + 1;


        std::list<std::string>::iterator parent1Iterator = parent1.begin();
        std::list<std::string>::iterator parent2Iterator = parent2.begin();

        std::list<std::string> descendant1 = *(new std::list<std::string>() );
        std::list<std::string>::iterator descandant1Iterator = descendant1.begin();
        std::list<std::string> *descendant2 = new std::list<std::string>() ;
        std::list<std::string>::iterator descandant2Iterator = descendant2->begin();
        //std::list<CacheServer*>::iterator cacheIterator1 = caches.begin();
        int parent1Count = 0;
        int parent2Count = 0;
        int actualCache = 0;
        int freeSpace1 = -1 ;
       /* for(std::string string : parent1){
            std::cout << string << " " ;
        }

        std::cout << std::endl;

        for(std::string string : parent2){
            std::cout << string << " " ;
        }

        std::cout << std::endl;*/
        for (;;) {
          //  if(parent1Count == parent1.size() -1) break;

            std::string gene  = *parent1Iterator;
            CacheServer *cacheServer = caches[actualCache];
            if(freeSpace1 == -1) freeSpace1 = cacheServer->maxCapacity;
            Video video = dataCenter.videos[atoi(gene.c_str())];
            if(video.size <= freeSpace1){
                descendant1.insert(descendant1.begin(),std::to_string(video.id));
                freeSpace1 = freeSpace1 - video.size;
            }
            else{
               // cacheIterator1++ ;
                actualCache++;
                cacheServer = caches[actualCache];
                freeSpace1 = cacheServer->maxCapacity ;
                if(point1 == actualCache ) break;
                descendant1.insert(descendant1.begin(),std::to_string(video.id));
                freeSpace1 = freeSpace1 - video.size ;
            }
            parent1Count++;
            parent1Iterator++;
        }

     //   std::list<CacheServer*>::iterator cacheIterator2 = caches.begin();
        int actualCache2 = 0;
        int freeSpace2 = -1 ;
        for (;;) {
        //    if(parent2Count == parent2.size() -1) break;

            std::string gene  = *parent2Iterator;
            CacheServer *cacheServer = caches[actualCache2];
            if(freeSpace2 == -1) freeSpace2 = cacheServer->maxCapacity;
            Video video = dataCenter.videos[atoi(gene.c_str())];
            if(video.size <= freeSpace2){
                descendant2->insert(descendant2->begin(),std::to_string(video.id));
                freeSpace2 = freeSpace2 - video.size;
            }
            else{
                actualCache2++;
                cacheServer = caches[actualCache2];
                freeSpace2 = cacheServer->maxCapacity ;
                if(point1 == actualCache2 ) break;
                descendant2->insert(descendant2->begin(),std::to_string(video.id));
                freeSpace2 = freeSpace2 - video.size ;
            }
            parent2Count++;
            parent2Iterator++;
        }


        for (;;) {
            if(parent1Count == parent1.size() -1) break;
            std::string gene  = *parent1Iterator;
            CacheServer* cacheServer = caches[actualCache];
            if(freeSpace1 == -1) freeSpace1 = cacheServer->maxCapacity;
            Video video = dataCenter.videos[atoi(gene.c_str())];
            if(video.size <= freeSpace1){
                descendant2->insert(descendant2->begin(),std::to_string(video.id));
                freeSpace1 = freeSpace1 - video.size;
            }
            else{
                actualCache++;
                cacheServer = caches[actualCache];
                freeSpace1 = cacheServer->maxCapacity ;
                descendant2->insert(descendant2->begin(),std::to_string(video.id));
                freeSpace1 = freeSpace1 - video.size ;
            }
            parent1Count++;
            parent1Iterator++;
        }

        for (;;) {
            if(parent2Count == parent2.size() -1) break;

            std::string gene  = *parent2Iterator;

            CacheServer *cacheServer = caches[actualCache2];
            if(freeSpace2 == -1) freeSpace2 = cacheServer->maxCapacity;
            Video video = dataCenter.videos[atoi(gene.c_str())];
            if(video.size <= freeSpace2){
                descendant1.insert(descendant1.begin(),std::to_string(video.id));
                freeSpace2 = freeSpace2 - video.size;
            }
            else{
                actualCache2++;
                cacheServer = caches[actualCache];
                freeSpace2 = cacheServer->maxCapacity ;
                descendant1.insert(descendant1.begin(),std::to_string(video.id));
                freeSpace2 = freeSpace2 - video.size ;
            }
            parent2Count++;
            parent2Iterator++;
        }
        int fit1 = fitness(descendant1);
        if((  fit1)<bestFit){
            bestSolution = descendant1;
            bestFit = fit1;
        }
        int fit2 = fitness(*descendant2);
        if(fit2<bestFit){
            bestSolution = *descendant2;
            bestFit = fit2 ;
        }
        (population)[POPULATION_SIZE +  j] = descendant1;
        (population)[POPULATION_SIZE + j+1] = *descendant2;
    }
    //this->population[POPULATION_SIZE + ] = descendants ;
}
//Tournament selection
/**
 * Function to apply a selection technique in the population
 * As result the population size will be cut to half of the original size
 * Uses Tournament Selection
 */
void GeneticAlgorithm::selection() {
   // std::vector<std::list<std::string>> newPop ;
    //newPop =  std::vector<std::list<std::string>>(POPULATION_SIZE * 2);
    int i = 0 ;
   // std::vector<std::list<std::string>>::iterator popIt = population.begin();
    for (int j = 0; j < POPULATION_SIZE * 2  ; j+=2) {
     //   std::cout << "J = " << j << std::endl;
      //  std::cout << " Pop" << this->population.size() << std::endl;

        //auto it1 = std::next(this->population.begin(), j);
        std::list<std::string> parent1 =  population[j];
    //    auto it2 = std::next(this->population.begin(), j+1);
        std::list<std::string> parent2 = population[j+1] ;
      //  std::cout << "Iniciando Fit1" << std::endl;

        float fitness1 = fitness(parent1);
     //   std::cout << "Terminando Fit1" << std::endl;
     //   std::cout << "Iniciando Fit2" << std::endl;

        float fitness2 = fitness(parent2);
     //   std::cout << "Terminando Fit2" << std::endl;

        if(fitness1 < fitness2){
    //        std::cout << " Removendo Parent2" << std::endl;

            (population)[i] = parent1;
     //       std::cout << " Fim Removendo Parent2" << std::endl;

        }
        else{
   //         std::cout << " Removendo Parent1" << std::endl;
            (population)[i] = parent2;
            //        std::cout << " Fim Removendo Parent1" << std::endl;

        }
        i++;

    }

  //  this->population = newPop;
}
/**
 * Function to apply mutation in the population
 * Uses random values and check if they are greater than the Mutation Tax defined
 */
void GeneticAlgorithm::mutation() {
    for (std::list<std::string> chromosome  : this->population) {
        int rand = std::rand();
        if (rand <= MUTATION_TAX){
            int randomGeneValue = std::rand() * (dataCenter.videos.size()-1);
            int randomGene = std::rand() * (chromosome.size()-1);
            std::list<std::string>::iterator iterator = chromosome.begin();
            std::advance(iterator,randomGene);
            *iterator = std::to_string(randomGeneValue);
        }

    }
}
/**
 * Function to calculate the fitness of a Chromosome
 * @param chromosome Chromosome to be analysed
 * @return Returns the fitness value
 */
float GeneticAlgorithm::fitness(std::list<std::string> chromosome) {
    std::map<std::list<std::string>,int>::iterator iterator = oldPopulationResults.find( chromosome );
    if(iterator != oldPopulationResults.end())
        return iterator->second;
   /* if (oldPopulationResults.count(chromosome)){
        return oldPopulationResults[chromosome];
    } */



        std::vector<CacheServer *> caches = this->dataCenter.caches;
        for (CacheServer *cacheServer : caches) {
            cacheServer->videos.clear();
        }
        int actualCache = 0;
        int freeSpace = -1;
        for (std::string gene : chromosome) {
            CacheServer *cacheServer = caches[actualCache];
            if (freeSpace == -1) freeSpace = cacheServer->maxCapacity;
            Video video = dataCenter.videos[atoi(gene.c_str())];
            if (video.size <= freeSpace) {
                cacheServer->videos.insert(cacheServer->videos.begin(), video.id);
                //  caches[actualCache] = cacheServer;
                freeSpace = freeSpace - video.size;
            } else {
                actualCache++;
                cacheServer = caches[actualCache];
                freeSpace = cacheServer->maxCapacity;
                cacheServer->videos.insert(cacheServer->videos.begin(), video.id);
                //caches[actualCache] = cacheServer;
                freeSpace = freeSpace - video.size;
            }
        }
        float fitnessValue = 0;
        for (Endpoint endpoint : this->dataCenter.endpoint) {
            for (std::pair<int, int> request : endpoint.requests) {
                int videoId = request.first;
                int latency = 0;
                bool inCache = false;
                for (std::pair<int, float> cacheConnection : endpoint.cacheLatency) {
                    int cacheId = cacheConnection.first;
                    CacheServer *cache = caches[cacheId];
                    for (int vId : cache->videos) {
                        if (vId == videoId) {
                            if (!inCache) latency = endpoint.serverLatency - endpoint.cacheLatency[cache->id];
                            else {
                                if (latency + endpoint.serverLatency > request.second) latency =
                                                                                               endpoint.serverLatency -
                                                                                               endpoint.cacheLatency[cache->id];
                            }
                            inCache = true;
                            break;
                        }
                    }
                }
                if (!inCache) latency = 0;
                fitnessValue += latency * request.second;
            }
        }
        fitnessValue = fitnessValue / numberOfRequests;
        //   std::cout << "Fitness == " << fitnessValue * 1000<< std::endl;
        oldPopulationResults[chromosome] = fitnessValue * -1;
        return fitnessValue * -1;

}
//TODO Find the fittest
/**
 * Function to generate the initial population
 * @param populationElementsCount Population size
 * @param geneSize Size of the gene
 * @return returns the best element of the population
 */
float GeneticAlgorithm::generateInitialPopulation(int populationElementsCount) {
    int cacheCount = dataCenter.caches.size();
    int videosCount = dataCenter.videos.size();
    //std::list<std::list<std::string>>::iterator populationIterator = population.begin();
    srand (time(NULL));
    int bestSolutionFitness = 0;
    for (int i = 0; i < populationElementsCount; ++i) {
        std::list<std::string> newMember = *(new std::list<std::string>());
        int actualCache = 0;
        int freeSpace = -1;
        int newNode = 0;
        while(true){
            newNode = rand() % videosCount ;
            Video video = dataCenter.videos[newNode];
            std::vector<CacheServer*> caches = dataCenter.caches;
            CacheServer* cacheServer = caches[actualCache];
            if(freeSpace == -1) freeSpace = cacheServer->maxCapacity;
            if(video.size <= freeSpace){
                cacheServer->videos.insert(cacheServer->videos.begin(),video.id);
                freeSpace = freeSpace - video.size;
            }
            else{
                actualCache++;
                if (actualCache==cacheCount) break;
                cacheServer = caches[actualCache];
                freeSpace = cacheServer->maxCapacity ;
                cacheServer->videos.insert(cacheServer->videos.begin(),video.id);
                freeSpace = freeSpace - video.size ;
            }

            newMember.insert((newMember).begin(),std::to_string(newNode));

        }
        if (i == 0) {bestSolution = newMember;
        bestFit = fitness(newMember);}
        else{
            if(fitness(newMember)<bestFit){
                bestSolution = newMember;
                bestFit = fitness(newMember);
            }
        }
        this->population[i] = newMember;
        //populationIterator++;
    }


}


int GeneticAlgorithm::findMaxCacheNumber(std::list<std::string> parent) {
    int freeSpace1 = -1;
    int parent1Count = 0;
    int actualCache = 0;
    std::list<std::string>::iterator parentIterator = parent.begin();
    std::vector<CacheServer *> caches = this->dataCenter.caches;
    for (;;) {
        if(parent1Count == parent.size() -1) break;
        std::string gene  = *parentIterator;
        CacheServer *cacheServer = caches[actualCache];
        if(freeSpace1 == -1) freeSpace1 = cacheServer->maxCapacity;
        Video video = dataCenter.videos[atoi(gene.c_str())];
        if(video.size <= freeSpace1){
            freeSpace1 = freeSpace1 - video.size;
        }
        else{
            actualCache++;
            cacheServer = caches[actualCache];
            freeSpace1 = cacheServer->maxCapacity ;
            freeSpace1 = freeSpace1 - video.size ;
        }
        parent1Count++;
        parentIterator++;
    }
    return actualCache;
}

void GeneticAlgorithm::findNumberOfRequests(){
    for (Endpoint endpoint : this->dataCenter.endpoint){
        for(std::pair<int,int> request : endpoint.requests){
            numberOfRequests += request.second;
        }
    }
}