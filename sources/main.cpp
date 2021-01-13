#include <iostream>
#include "FilesKeeper.h"
int main() {
    FilesKeeper keeper(R"(D:\Programing\QtProjects)");
    keeper.findFiles();
    keeper.printFoundedFiles();
    std::cout << "Count of files: " << keeper.getCountOfFiles() << std::endl;
    return 0;
}
