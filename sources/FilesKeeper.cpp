//
// Created by Marko on 12.01.2021.
//

#include "FilesKeeper.h"
#include <iostream>
#include <utility>
FilesKeeper::FilesKeeper(): m_rootDirectoryPath(""){}

FilesKeeper::FilesKeeper(std::string startDirectory): m_rootDirectoryPath(std::move(startDirectory)){}

FilesKeeper::~FilesKeeper()  = default;

size_t FilesKeeper::getCountOfFiles() const
{
    return m_currentDirectoryFilesPaths.size();
}

std::string FilesKeeper::getFilePathAt(size_t index) const
{
    return m_currentDirectoryFilesPaths[index];
}

void FilesKeeper::findFiles()
{
    if (fs::exists(m_rootDirectoryPath) ||
        fs::is_directory(m_rootDirectoryPath))
    {
        throw std::string(m_rootDirectoryPath +
        " isn't directory or doesn't exists");
    }
    std::regex extensions(".*\\.[hc](pp)?");

    for(auto& filePath : fs::recursive_directory_iterator(m_rootDirectoryPath))
    {
        if (fs::is_regular_file(filePath) &&
            std::regex_match(filePath.path().string(),extensions))
        {
            m_currentDirectoryFilesPaths.push_back(filePath.path().string());
        }
    }
}

void FilesKeeper::printFoundedFiles() const
{
    for(auto& file : m_currentDirectoryFilesPaths)
    {
        std::cout << file << std::endl;
    }
}

