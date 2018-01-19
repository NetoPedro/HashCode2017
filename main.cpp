#include <iostream>
#include "Importer.h"
int main() {
    std::cout << "Hello, World!" << std::endl;
    Importer::import("../ewf.txt");
    return 0;
}