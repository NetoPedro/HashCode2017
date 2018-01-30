//
// Created by Pedro Neto on 19/01/18.
//

#ifndef HASHCODE2017_GENETICALGORITHM_H
#define HASHCODE2017_GENETICALGORITHM_H


#include <list>
#include <map>
#include <iostream>
#include "../Model/DataCenter.h"

class GeneticAlgorithm {
public:
    //
    std::vector<std::list<std::string>> population;
    DataCenter dataCenter;
    void init(int generations,DataCenter dataCenter);
    std::list<std::string> bestSolution ;
    int bestFit ;
    int numberOfRequests = 0;

private:
    float generateInitialPopulation(int populationElementsCount);
    float fitness(std::list<std::string> chromosome) ;
    void selection();
    void mutation();
    void crossover();
    void findNumberOfRequests();
    int findMaxCacheNumber(std::list<std::string> parent);
};


#endif //HASHCODE2017_GENETICALGORITHM_H
