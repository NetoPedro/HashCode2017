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
    std::vector<std::vector<std::string>> population;
    DataCenter dataCenter;
    void init(int generations,DataCenter dataCenter);
    std::vector<std::string> bestSolution ;
    int bestFit ;
    int numberOfRequests = 0;
    std::map<std::vector<std::string>,int> oldPopulationResults;
private:
    float generateInitialPopulation(int populationElementsCount);
    float fitness(std::vector<std::string> chromosome) ;
    void selection();
    void mutation();
    void crossover();
    void findNumberOfRequests();
    int findMaxCacheNumber(std::vector<std::string> parent);
};


#endif //HASHCODE2017_GENETICALGORITHM_H
