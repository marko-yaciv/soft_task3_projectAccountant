#include "utils.h"

int main()
{
    auto path  = startProgram();
    std::cout << "Walking throw directories..."<< std::endl;

    FilesKeeper keeper(path);
    findFiles(keeper);

    FileAnalyser analyser(keeper.getFiles());
    analyseFiles(analyser);
    saveData(analyser);
    return 0;
}
