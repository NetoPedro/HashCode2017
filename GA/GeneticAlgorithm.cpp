//
// Created by Pedro Neto on 19/01/18.
//

#include "GeneticAlgorithm.h"

#define POPULATION_SIZE 10
#define MUTATION_TAX 0.15

/**
 * Function to start the Genetic Algorithm
 * @param generations Number of generations until stop
 * @param dataCenter DataCenter with the information to run the geneticAlgorithm
 * @param geneSize Size of the Chromosome
 */

void GeneticAlgorithm::init(int generations, DataCenter dataCenter) {
    this->dataCenter = dataCenter ;
    std::list<std::string> bestSolution ;
    srand (time(NULL));
    this->generateInitialPopulation(POPULATION_SIZE,bestSolution);
    for (int i = 0; i < generations; ++i) {
        crossover();
        mutation();
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
}
/**
 * Function to apply a crossover technique in the population
 * Uses a random mask to cross parents
 * @param geneSize Size of the chromosome
 */
void GeneticAlgorithm::crossover() {
    std::list<int> newMembers;
    std::list<CacheServer*> caches = this->dataCenter.caches;
    for(CacheServer *cacheServer : caches){
        cacheServer->videos.clear();
    }
    int cacheCount = dataCenter.caches.size();
    int point2;
    int point1;
    while (true) {
        point1 = rand() % (cacheCount - 2) + 1;
        point2 = rand() % (cacheCount - 2) + 1 ;

        if (point2 > point1) break;
    }
    std::list<std::list<std::string>> *descendants = new std::list<std::list<std::string>>();
    std::list<std::list<std::string>>::iterator iterator = descendants->begin();
    for (int j = 0; j < POPULATION_SIZE ; j+=2) {
        auto it1 = std::next(this->population.begin(), j);
        std::list<std::string> parent1 = ( std::list<std::string>) *it1;
        auto it2 = std::next(this->population.begin(), j+1);
        std::list<std::string> parent2 = ( std::list<std::string>) *it2;
        std::list<std::string>::iterator parent1Iterator = parent1.begin();
        std::list<std::string>::iterator parent2Iterator = parent2.begin();

        std::list<std::string> descendant1 = *(new std::list<std::string>() );
        std::list<std::string>::iterator descandant1Iterator = descendant1.begin();
        std::list<std::string> *descendant2 = new std::list<std::string>() ;
        std::list<std::string>::iterator descandant2Iterator = descendant2->begin();
        std::list<CacheServer*>::iterator cacheIterator1 = caches.begin();
        int parent1Count = 0;
        int parent2Count = 0;
        int actualCache = 0;
        int freeSpace1 = -1 ;
        for (;;) {
            if(parent1Count == parent1.size() -1) break;

            std::string gene  = *parent1Iterator;
            CacheServer *cacheServer = (CacheServer*) *cacheIterator1;
            if(freeSpace1 == -1) freeSpace1 = cacheServer->maxCapacity;
            Video *video = dataCenter.videoById(atoi(gene.c_str()));
            if(video->size <= freeSpace1){
                descendant1.insert(descendant1.begin(),std::to_string(video->id));
                freeSpace1 = freeSpace1 - video->size;
            }
            else{
                cacheIterator1++ ;
                actualCache++;
                cacheServer = (CacheServer*) *cacheIterator1;
                freeSpace1 = cacheServer->maxCapacity ;
                if(point1 == actualCache ) break;
                descendant1.insert(descendant1.begin(),std::to_string(video->id));
                freeSpace1 = freeSpace1 - video->size ;
            }
            parent1Count++;
            parent1Iterator++;
        }

        std::list<CacheServer*>::iterator cacheIterator2 = caches.begin();
        int actualCache2 = 0;
        int freeSpace2 = -1 ;
        for (;;) {
            if(parent2Count == parent2.size() -1) break;

            std::string gene  = *parent2Iterator;
            CacheServer *cacheServer = (CacheServer*) *cacheIterator2;
            if(freeSpace2 == -1) freeSpace2 = cacheServer->maxCapacity;
            Video *video = dataCenter.videoById(atoi(gene.c_str()));
            if(video->size <= freeSpace2){
                descendant2->insert(descendant2->begin(),std::to_string(video->id));
                freeSpace2 = freeSpace2 - video->size;
            }
            else{
                cacheIterator2++ ;
                actualCache2++;
                cacheServer = (CacheServer*) *cacheIterator2;
                freeSpace2 = cacheServer->maxCapacity ;
                if(point1 == actualCache2 ) break;
                descendant2->insert(descendant2->begin(),std::to_string(video->id));
                freeSpace2 = freeSpace2 - video->size ;
            }
            parent2Count++;
            parent2Iterator++;
        }

        for (;;) {
            if(parent2Count == parent2.size() -1) break;

            std::string gene  = *parent2Iterator;
            CacheServer *cacheServer = (CacheServer*) *cacheIterator2;
            if(freeSpace2 == -1) freeSpace2 = cacheServer->maxCapacity;
            Video *video = dataCenter.videoById(atoi(gene.c_str()));
            if(video->size <= freeSpace2){
                descendant1.insert(descendant1.begin(),std::to_string(video->id));
                freeSpace2 = freeSpace2 - video->size;
            }
            else{
                cacheIterator2++ ;
                actualCache2++;
                cacheServer = (CacheServer*) *cacheIterator2;
                freeSpace2 = cacheServer->maxCapacity ;
                if(point2 == actualCache2 ) break;
                descendant1.insert(descendant1.begin(),std::to_string(video->id));
                freeSpace2 = freeSpace2 - video->size ;
            }
            parent2Count++;
            parent2Iterator++;
        }

        for (;;) {
            if(parent1Count == parent1.size() -1) break;

            std::string gene  = *parent1Iterator;

            CacheServer *cacheServer = (CacheServer*) *cacheIterator1;
            if(freeSpace1 == -1) freeSpace1 = cacheServer->maxCapacity;
            Video *video = dataCenter.videoById(atoi(gene.c_str()));
            if(video->size <= freeSpace1){
                descendant2->insert(descendant2->begin(),std::to_string(video->id));
                freeSpace1 = freeSpace1 - video->size;
            }
            else{
                cacheIterator1++ ;
                actualCache++;
                cacheServer = (CacheServer*) *cacheIterator1;
                freeSpace1 = cacheServer->maxCapacity ;
                if(point2 == actualCache ) break;
                descendant2->insert(descendant2->begin(),std::to_string(video->id));
                freeSpace1 = freeSpace1 - video->size ;
            }
            parent1Count++;
            parent1Iterator++;
        }

        for (;;) {
            if(parent1Count == parent1.size() -1) break;
            std::string gene  = *parent1Iterator;
            CacheServer *cacheServer = (CacheServer*) *cacheIterator1;
            if(freeSpace1 == -1) freeSpace1 = cacheServer->maxCapacity;
            Video *video = dataCenter.videoById(atoi(gene.c_str()));
            if(video->size <= freeSpace1){
                descendant1.insert(descendant1.begin(),std::to_string(video->id));
                freeSpace1 = freeSpace1 - video->size;
            }
            else{
                cacheIterator1++ ;
                actualCache++;
                cacheServer = (CacheServer*) *cacheIterator1;
                freeSpace1 = cacheServer->maxCapacity ;
                descendant1.insert(descendant1.begin(),std::to_string(video->id));
                freeSpace1 = freeSpace1 - video->size ;
            }
            parent1Count++;
            parent1Iterator++;
        }

        for (;;) {
            if(parent2Count == parent2.size() -1) break;

            std::string gene  = *parent2Iterator;

            CacheServer *cacheServer = (CacheServer*) *cacheIterator2;
            if(freeSpace2 == -1) freeSpace2 = cacheServer->maxCapacity;
            Video *video = dataCenter.videoById(atoi(gene.c_str()));
            if(video->size <= freeSpace2){
                descendant2->insert(descendant2->begin(),std::to_string(video->id));
                freeSpace2 = freeSpace2 - video->size;
            }
            else{
                cacheIterator2++ ;
                actualCache2++;
                cacheServer = (CacheServer*) *cacheIterator2;
                freeSpace2 = cacheServer->maxCapacity ;
                descendant2->insert(descendant2->begin(),std::to_string(video->id));
                freeSpace2 = freeSpace2 - video->size ;
            }
            parent2Count++;
            parent2Iterator++;
        }


        descendants->insert(iterator,descendant1);
        descendants->insert(iterator,*descendant2);
    }
    this->population.insert(this->population.end(),descendants->begin(),descendants->end());
}
//Tournament selection
/**
 * Function to apply a selection technique in the population
 * As result the population size will be cut to half of the original size
 * Uses Tournament Selection
 */
void GeneticAlgorithm::selection() {
    for (int j = 0; j < POPULATION_SIZE ; j+=1) {
        auto it1 = std::next(this->population.begin(), j);
        std::list<std::string> parent1 =  *it1;
        auto it2 = std::next(this->population.begin(), j+1);
        std::list<std::string> parent2 = *it2 ;
        if(fitness(parent1) < fitness(parent2)){
            this->population.remove(parent2);
        }
        else{
            this->population.remove(parent1);
        }

    }
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
    std::list<CacheServer*> caches = this->dataCenter.caches;
    for(CacheServer *cacheServer : caches){
        cacheServer->videos.clear();
    }
    std::list<CacheServer*>::iterator cacheIterator = caches.begin();
    int freeSpace = -1 ;
    for (std::string gene : chromosome) {
        CacheServer *cacheServer = (CacheServer*) *cacheIterator;
        if(freeSpace == -1) freeSpace = cacheServer->maxCapacity;
        Video *video = dataCenter.videoById(atoi(gene.c_str()));
        if(video->size <= freeSpace){
            cacheServer->videos.insert(cacheServer->videos.begin(),video);
            freeSpace = freeSpace - video->size;
        }
        else{
            cacheIterator++ ;
            cacheServer = (CacheServer*) *cacheIterator;
            freeSpace = cacheServer->maxCapacity ;
            cacheServer->videos.insert(cacheServer->videos.begin(),video);
            freeSpace = freeSpace - video->size ;
        }
    }
    float fitnessValue  = 0 ;
    for (Endpoint* endpoint : this->dataCenter.endpoint){
        for(std::pair<int,int> request : endpoint->requests){
            int videoId = request.first;
            int latency = 0;
            bool inCache = false ;
            for(std::pair<int,float > cacheConnection : endpoint->cacheLatency){
                int cacheId = cacheConnection.first ;
                CacheServer *cache = this->dataCenter.cacheById(cacheId);
                for(Video *v : cache->videos){
                    if (v->id == videoId){
                        if (!inCache) latency = request.second;
                        else{
                            if (latency > request.second) latency = request.second;
                        }
                        inCache = true;
                        break;
                    }
                }
            }
            if (!inCache) latency = endpoint->serverLatency ;
            fitnessValue += latency * request.second;
        }
    }
    std::cout << "Fitness == " << fitnessValue << std::endl;
    return fitnessValue;
}
//TODO Find the fittest
/**
 * Function to generate the initial population
 * @param populationElementsCount Population size
 * @param geneSize Size of the gene
 * @return returns the best element of the population
 */
float GeneticAlgorithm::generateInitialPopulation(int populationElementsCount, std::list<std::string> bestSolution) {
    int cacheCount = dataCenter.caches.size();
    int videosCount = dataCenter.videos.size();
    std::list<std::list<std::string>>::iterator populationIterator = population.begin();
    srand (time(NULL));
    for (int i = 0; i < populationElementsCount; ++i) {
        std::list<std::string> newMember = *(new std::list<std::string>());
        int actualCache = 0;
        int freeSpace = -1;
        int newNode = 0;
        while(true){
            newNode = rand() % videosCount ;
            Video *video = dataCenter.videoById(newNode);
            std::list<CacheServer*>::iterator caches = dataCenter.caches.begin();
            CacheServer *cacheServer = (CacheServer*) *caches;
            if(freeSpace == -1) freeSpace = cacheServer->maxCapacity;
            if(video->size <= freeSpace){
                cacheServer->videos.insert(cacheServer->videos.begin(),video);
                freeSpace = freeSpace - video->size;
            }
            else{
                caches++ ;
                actualCache++;
                if (actualCache==cacheCount) break;
                cacheServer = (CacheServer*) *caches;
                freeSpace = cacheServer->maxCapacity ;
                cacheServer->videos.insert(cacheServer->videos.begin(),video);
                freeSpace = freeSpace - video->size ;
            }
            newMember.insert((newMember).begin(),std::to_string(newNode));

        }
        this->population.insert(populationIterator,newMember);
        populationIterator++;
    }


}