//
// Created by Marko on 18.01.2021.
//

#ifndef PROJECTACCOUNTANT_UTILS_H
#define PROJECTACCOUNTANT_UTILS_H

#include <iostream>
#include "FilesKeeper.h"
#include "FileAnalyser.h"
#include <chrono>

std::string startProgram()
{
    std::cout << "Enter path ro directory for analysing: " << std::endl;
    std::string path;
    std::cin >> path;
    return path;
}

void findFiles(FilesKeeper& keeper)
{
    try {
        keeper.findFiles();
    }catch (const std::string& ex){
        std::cout << ex << std::endl;
        exit(1);
    }
    std::cout << "Found" << keeper.getCountOfFiles() <<
              " files with such extensions : \".cpp .hpp .h .c\" "<< std::endl;
}

auto clockAndAnalyse(FileAnalyser& analyser)
{
    auto start = std::chrono::high_resolution_clock::now();
    analyser.startParsing();
    auto end = std::chrono::high_resolution_clock::now();
    return end - start;
}
void analyseFiles(FileAnalyser& analyser)
{
    std::cout << "Do you want to clock time? (y/n): ";
    auto c = std::getchar();
    if(c == 'y' || c == 'Y')
    {
        std::cout<< "Processing files..."<<std::endl;
        auto resTime = clockAndAnalyse(analyser);
        std::cout<< "Finished!"<<std::endl;
        std::cout << "Time is: " <<
                  std::chrono::duration_cast<std::chrono::milliseconds>(resTime).count()
                  << std::endl;
    }
    else
    {
        std::cout<< "Processing files..."<<std::endl;
        analyser.startParsing();
        std::cout<< "Finished!"<<std::endl;
    }
}

std::string askPathToSave()
{
    std::string path;
    while(true)
    {
        std::cout << "Where do you want to save data?(path)\n";
        std::cin >> path;
        if(!fs::exists(path) || !fs::is_regular_file(path))
        {
            std::cout << "No such path or file is incorrect\n";
        }
        else
        {
            break;
        }
    }
    return path;
}
void saveData(FileAnalyser& analyser)
{
    std::cout << " Do you want to save results? (y/n): ";
    auto c = std::getchar();
    if(c == 'y' || c == 'Y')
    {
        auto path = askPathToSave();
        std::cout << "Saving info..." << std::endl;
        analyser.saveData(path);
        std::cout << "Results were saved in: " << path << std::endl;
    }
}

#endif //PROJECTACCOUNTANT_UTILS_H
