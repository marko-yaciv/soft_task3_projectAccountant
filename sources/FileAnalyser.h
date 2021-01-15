//
// Created by Marko on 13.01.2021.
//

#ifndef PROJECTACCOUNTANT_FILEANALYSER_H
#define PROJECTACCOUNTANT_FILEANALYSER_H

#include <string>
#include <fstream>
#include <sstream>
#include <regex>
#include <mingw.thread.h>
#include <mingw.mutex.h>
#include "CodeParser.h"

class FileAnalyser {
private:
    std::vector<std::string> m_filesToAnalyse;

public:
    FileAnalyser();
    explicit FileAnalyser(std::vector<std::string>& filesToParse);
    void startParsing();
};


#endif //PROJECTACCOUNTANT_FILEANALYSER_H
