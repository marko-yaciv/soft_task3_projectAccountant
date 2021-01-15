#include <iostream>
#include "FilesKeeper.h"
#include "FileAnalyser.h"
#include <chrono>

int main()
{
    std::cout << "Enter path ro directory for analysing: " << std::endl;
    std::string path;
    std::cin >> path;

/*
 <keeper> will find all files with specified
 extensions starting from root directory <path>
 */
    FilesKeeper keeper(path);
    try {
        keeper.findFiles();
    }catch (const std::string& ex){
        std::cout << ex << std::endl;
        return 1;
    }
    std::cout << "Count of files: " << keeper.getCountOfFiles() << std::endl;

//clock time and analyse vector of files
    FileAnalyser analyser(keeper.getFiles());
    auto start = std::chrono::high_resolution_clock::now();
    analyser.startParsing();
    auto end = std::chrono::high_resolution_clock::now();

//printing result time
    std::cout << "Time is: " <<
    std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
    << std::endl;

    return 0;
}
