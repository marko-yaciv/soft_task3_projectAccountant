#include <iostream>
#include "FilesKeeper.h"
int main() {
    FilesKeeper keeper(R"(D:\Programing\QtProjects\1_course)");
    keeper.findFiles();
    keeper.printFoundedFiles();
    return 0;
}
