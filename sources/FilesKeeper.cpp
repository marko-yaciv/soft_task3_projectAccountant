//
// Created by Marko on 12.01.2021.
//

#include "FilesKeeper.h"
#include <iostream>
#include <utility>
FilesKeeper::FilesKeeper(): m_currentDirectoryPath(""){}

FilesKeeper::FilesKeeper(std::string startDirectory):m_currentDirectoryPath(std::move(startDirectory)){}

FilesKeeper::~FilesKeeper()  = default;

size_t FilesKeeper::getCountOfFiles() const {
    return m_currentDirectoryFilesPaths.size();
}

std::string FilesKeeper::getFilePathAt(size_t index) const {
    return m_currentDirectoryFilesPaths[index];
}

void FilesKeeper::findFiles(){
    for(auto& filePath : fs::recursive_directory_iterator(m_currentDirectoryPath)){
        if(fs::is_regular_file(filePath) /*Add here regex for files extension*/){
            m_currentDirectoryFilesPaths.push_back(filePath.path().string());
        }
    }
}

void FilesKeeper::printFoundedFiles() const {
    for(auto& file : m_currentDirectoryFilesPaths){
        std::cout << file << std::endl;
    }
}

