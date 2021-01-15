#include <iostream>
#include "FilesKeeper.h"
#include "FileAnalyser.h"
#include <chrono>

int main()
{
    FilesKeeper keeper("D:\\Programing\\boost_1_75_0\\tools");
    try {
        keeper.findFiles();
    }catch (const std::string& ex){
        std::cout << ex << std::endl;
        return 1;
    }
    std::cout << "Count of files: " << keeper.getCountOfFiles() << std::endl;

    FileAnalyser analyser(keeper.getFiles());

    auto start = std::chrono::high_resolution_clock::now();
    analyser.startParsing();
    //analyser.openAndParse(keeper.getFiles());
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time is: " << std::chrono::duration_cast<std::chrono::milliseconds>(end  - start).count() << std::endl;
    return 0;
}
