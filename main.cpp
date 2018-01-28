#include <iostream>
#include "Scanner/Importer.h"
#include "GA/GeneticAlgorithm.h"

int main() {
    DataCenter dataCenter = Importer::import("../Input/videos_worth_spreading.in");
    GeneticAlgorithm *geneticAlgorithm = new GeneticAlgorithm();
    geneticAlgorithm->init(500,dataCenter);
    std::cout << "Hello, World!" << std::endl;

    return 0;
}