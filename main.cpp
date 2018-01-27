#include <iostream>
#include "Scanner/Importer.h"
#include "GA/GeneticAlgorithm.h"

int main() {
    DataCenter dataCenter = Importer::import("../Input/ewf.txt");
    GeneticAlgorithm *geneticAlgorithm = new GeneticAlgorithm();
    geneticAlgorithm->init(1,dataCenter);
    std::cout << "Hello, World!" << std::endl;

    return 0;
}