//
// Created by Pedro Neto on 19/01/18.
//

#ifndef HASHCODE2017_GENETICALGORITHM_H
#define HASHCODE2017_GENETICALGORITHM_H


#include <list>
#include <map>
#include <iostream>
#include "DataCenter.h"

class GeneticAlgorithm {
public:
    std::list<std::map<int,std::list<int>>> population;
    void init(int generations,DataCenter dataCenter);
private:
    float generateInitialPopulation(int populationElementsCount);
    float fitness() ;
    void selection();
    void mutation();
    void crossover();
};


#endif //HASHCODE2017_GENETICALGORITHM_H
