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
    //
    std::list<std::list<std::string>> population;
    DataCenter dataCenter;
    void init(int generations,DataCenter dataCenter,int geneSize);
private:
    float generateInitialPopulation(int populationElementsCount,int geneSize);
    float fitness(std::list<std::string> chromosome) ;
    void selection();
    void mutation();
    void crossover(int geneSize);
};


#endif //HASHCODE2017_GENETICALGORITHM_H
