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

void GeneticAlgorithm::init(int generations, DataCenter dataCenter,int geneSize) {
    this->dataCenter = dataCenter ;
    std::list<std::string> bestSolution ;
    srand (time(NULL));
    this->generateInitialPopulation(POPULATION_SIZE,geneSize,bestSolution);
    for (int i = 0; i < generations; ++i) {
        crossover(geneSize);
        mutation();
        selection();
    }
}
/**
 * Function to apply a crossover technique in the population
 * Uses a random mask to cross parents
 * @param geneSize Size of the chromosome
 */
void GeneticAlgorithm::crossover(int geneSize) {
    std::list<int> newMembers;
    std::string mask= "" ;

    for (int i = 0; i < geneSize; ++i) {
        int rand = std::rand() % 2 ;
        mask += rand;
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

        std::list<std::string> *descendant1 = new std::list<std::string>() ;
        std::list<std::string>::iterator descandant1Iterator = descendant1->begin();
        for(char gene : mask){
            if(gene == 0){
                descendant1->insert(descandant1Iterator,*parent1Iterator);
            }
            else{
                descendant1->insert(descandant1Iterator,*parent2Iterator);
            }
            parent1Iterator++;
            parent2Iterator++;
            descandant1Iterator++;
        }
        parent1Iterator = parent1.begin();
        parent2Iterator = parent2.begin();
        std::list<std::string> *descendant2 = new std::list<std::string>() ;
        std::list<std::string>::iterator descandant2Iterator = descendant2->begin();
        for(char gene : mask){
            if(gene == 0){
                descendant2->insert(descandant2Iterator,*parent2Iterator);
            }
            else{
                descendant2->insert(descandant2Iterator,*parent1Iterator);
            }
            parent1Iterator++;
            parent2Iterator++;
            descandant2Iterator++;
        }
        descendants->insert(iterator,*descendant1);
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
        if(fitness(parent1) > fitness(parent2)){
            this->population.remove(*it2);
        }
        else{
            this->population.remove(*it1);
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
//TODO
/**
 * Function to calculate the fitness of a Chromosome
 * @param chromosome Chromosome to be analysed
 * @return Returns the fitness value
 */
float GeneticAlgorithm::fitness(std::list<std::string> chromosome) {
    std::list<CacheServer*> caches = this->dataCenter.caches;
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

    //TODO calculate now the cost of the requests for each endpoint
}
//TODO
/**
 * Function to generate the initial population
 * @param populationElementsCount Population size
 * @param geneSize Size of the gene
 * @return returns the best element of the population
 */
float GeneticAlgorithm::generateInitialPopulation(int populationElementsCount, int geneSize, std::list<std::string> bestSolution) {
    return 0 ;
}