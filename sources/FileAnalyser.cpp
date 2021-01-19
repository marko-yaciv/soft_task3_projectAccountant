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
int FileAnalyser::calculateNumOfConcurrency()
{
    auto maxHardwareThreadsNumber = std::thread::hardware_concurrency();
    int sizeOfData = m_filesToAnalyse.size();

    if(sizeOfData >= maxHardwareThreadsNumber)
    {
        return maxHardwareThreadsNumber;
    }
    return sizeOfData;
}

void FileAnalyser::startParsing()
{
    if(m_filesToAnalyse.empty())
    {
        throw std::string("Threre are nothing to parse");
    }
    auto numOfConcurrency = calculateNumOfConcurrency();
    CodeParser parser(this);
#ifndef USE_THREAD_POOL
    auto numOfPackPerThread = m_filesToAnalyse.size() / numOfConcurrency + 1;
    auto begin = m_filesToAnalyse.begin();
    auto end = begin + numOfPackPerThread;
    std::vector<std::thread> threads(numOfConcurrency);

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
#else
    boost::asio::thread_pool pool(numOfConcurrency);
    for(auto& file : m_filesToAnalyse)
    {
        boost::asio::post(pool,[&file, &parser]
        {
            parser.parseFiles(std::list<std::string>{file});
        });
    }
    pool.join();
#endif
}

void FileAnalyser::setInfoAboutFile(FileInfo &info)
{
    std::lock_guard<std::mutex> locker(m_lock);
    m_dataAboutFiles.push_back(info);
}

void FileAnalyser::saveDataToJson(const std::string& path)
{
    std::ofstream file(path + "/result.json");
    if(!file.is_open())
    {
        throw std::string("Canot open file. Check please path validity");
    }
    for(auto& info : m_dataAboutFiles)
    {
        std::stringstream ss;
        boost::property_tree::ptree pt;
        pt.put("FileName", info.filePath);
        pt.put("Info.NumberOfLines", info.m_numOfAllLines);
        pt.put("Info.NumberOfBlankLines", info.m_numOfBlankLines);
        pt.put("Info.NumberOfCodeLines", info.m_numOfCodeLines);
        pt.put("Info.NumberOfCmmentLines", info.m_numOfCommentLines);

        boost::property_tree::json_parser::write_json(ss,pt);
        file << ss.str();
    }

}

std::list<FileInfo> FileAnalyser::getData() const {
    return m_dataAboutFiles;
}

