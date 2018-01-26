//
// Created by Pedro Neto on 26/01/18.
//
#include "../GA/GeneticAlgorithm.h"
#ifndef HASHCODE2017_GENETICALGORITHMTEST_H
#define HASHCODE2017_GENETICALGORITHMTEST_H


class GeneticAlgorithmTest : GeneticAlgorithm {
public:
    bool fitnessTest();
    bool selectionTest();
    bool crossoverTest();
    bool mutationTest();
};


#endif //HASHCODE2017_GENETICALGORITHMTEST_H
