//
// Created by Marko on 13.01.2021.
//

#ifndef PROJECTACCOUNTANT_FILEANALYSER_H
#define PROJECTACCOUNTANT_FILEANALYSER_H
#define BOOST_BIND_GLOBAL_PLACEHOLDERS
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <sstream>
#include <boost/thread.hpp>
#include <thread>
#include "CodeParser.h"
#include "InfoKeeper.h"
//#define USE_THREAD_POOL

#ifdef USE_THREAD_POOL
    #include <boost/asio/thread_pool.hpp>
    #include <boost/asio.hpp>
#endif

/*Implements mulithreaded
 * Analysing of given files
 * and Saves Result info*/

class FileAnalyser: public InfoKeeper {
private:
    std::vector<std::string>& m_filesToAnalyse;
    std::list<FileInfo> m_dataAboutFiles;
    std::mutex m_lock;

    // overrided function to get info about files when processing
    void setInfoAboutFile(FileInfo& info) override;
    int calculateNumOfConcurrency();
public:

    explicit FileAnalyser(std::vector<std::string>& filesToParse);

//divides total work on threads and starts parsing
    void startParsing();
    [[nodiscard]] std::list<FileInfo> getData() const;
//function that will save data in json file.
    void saveDataToJson(const std::string& path);
};


#endif //PROJECTACCOUNTANT_FILEANALYSER_H
