//
// Created by Marko on 12.01.2021.
//

#include "FilesKeeper.h"
#include <iostream>
#include <utility>
FilesKeeper::FilesKeeper():
m_rootDirectoryPath("")
{

}

FilesKeeper::FilesKeeper(std::string startDirectory):
m_rootDirectoryPath(std::move(startDirectory))
{

}

FilesKeeper::~FilesKeeper()  = default;

size_t FilesKeeper::getCountOfFiles() const
{
    return m_currentDirectoryFilesPaths.size();
}

void FilesKeeper::findFiles()
{
    if (!boost::filesystem::exists(m_rootDirectoryPath) ||
        !boost::filesystem::is_directory(m_rootDirectoryPath))
    {
        throw std::string(m_rootDirectoryPath +
        " isn't directory or doesn't exist\n");
    }
    std::regex extensions(".*\\.[hc](pp)?");

    for(auto& filePath : boost::filesystem::recursive_directory_iterator(m_rootDirectoryPath))
    {
        if (boost::filesystem::is_regular_file(filePath) &&
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



std::vector<std::string>& FilesKeeper::getFiles()
{
    return m_currentDirectoryFilesPaths;
}

