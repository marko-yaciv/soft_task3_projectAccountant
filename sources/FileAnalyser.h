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
#include "CodeParser.h"
#include "InfoKeeper.h"

/*Implements mulithreaded
 * Analysing of given files
 * and outputing Result info*/
class FileAnalyser: public InfoKeeper {
private:
    std::vector<std::string> m_filesToAnalyse;

public:
    FileAnalyser();
    explicit FileAnalyser(std::vector<std::string>& filesToParse);

//divides total work on threads and starts parsing
    void startParsing();

//function that will save data in json file.
    void saveData() override;
};


#endif //PROJECTACCOUNTANT_FILEANALYSER_H
