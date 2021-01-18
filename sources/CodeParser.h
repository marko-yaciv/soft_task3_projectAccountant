//
// Created by Marko on 15.01.2021.
//

#ifndef PROJECTACCOUNTANT_CODEPARSER_H
#define PROJECTACCOUNTANT_CODEPARSER_H


#include <list>
#include <string>
#include <fstream>
#include <regex>
#include <iostream>
#include "InfoKeeper.h"

/*class that parses vector of
 * files and stores their info*/
class CodeParser {
private:
    InfoKeeper keeper;

//function that parses file
    void doParse(std::ifstream& file, const std::string& filePath);
public:
    CodeParser();

//opens each file and calls to it doParse
    void parseFiles(const std::list<std::string> &files);

//returns info about files;
    std::list<FileInfo>& getInfo();
};


#endif //PROJECTACCOUNTANT_CODEPARSER_H
