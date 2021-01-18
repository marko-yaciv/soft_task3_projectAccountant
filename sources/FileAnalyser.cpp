//
// Created by Marko on 13.01.2021.
//
#include <iostream>
#include "FileAnalyser.h"

FileAnalyser::FileAnalyser(std::vector<std::string>& filesToParse):
                m_filesToAnalyse(filesToParse)
{

}
FileAnalyser::FileAnalyser()
{

}

void FileAnalyser::startParsing()
{
    auto numOfConcurrency = std::thread::hardware_concurrency();
    auto numOfPackPerThread = m_filesToAnalyse.size() / numOfConcurrency + 1 ;
    std::vector<std::thread> threads(numOfConcurrency);
    auto begin = m_filesToAnalyse.begin();
    auto end = begin + numOfPackPerThread;

    CodeParser parser(this);

    for(auto& th : threads)
    {
        if(end > m_filesToAnalyse.end())
        {
            end = m_filesToAnalyse.end();
        }
        th = std::thread(&CodeParser::parseFiles,std::ref(parser),std::list<std::string>{begin,end});
        begin = end;
        end = begin + numOfPackPerThread;
    }

    for(auto& th : threads)
    {
        th.join();
    }
}

void FileAnalyser::setInfoAboutFile(FileInfo &info)
{
    std::lock_guard<std::mutex> locker(m_lock);
    m_dataAboutFiles.push_back(info);
}

void FileAnalyser::saveDataToJson(const std::string& path)
{
    std::ofstream out(path + "/out.txt");

    for(auto& info : m_dataAboutFiles)
    {
        out << "File: " << info.filePath
        << "\nTotal Lines: " << info.m_numOfAllLines
        << "\nCode Lines: " << info.m_numOfCodeLines
        << "\nBlank Lines: " << info.m_numOfBlankLines
        << "\nComment Lines: " << info.m_numOfCommentLines
        << "\n-----------------------"<< std::endl;
    }
}
