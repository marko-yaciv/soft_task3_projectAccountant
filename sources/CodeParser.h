//
// Created by Marko on 15.01.2021.
//

#ifndef PROJECTACCOUNTANT_CODEPARSER_H
#define PROJECTACCOUNTANT_CODEPARSER_H

#include <list>
#include <string>
#include <fstream>
#include <iostream>
#include <regex>
#include "InfoKeeper.h"

/*class that parses vector of
 * files and stores their info*/
class CodeParser {
private:
    InfoKeeper* m_keeper;

//function that parses file
    void doParse(std::ifstream& file, const std::string& filePath);
public:
    CodeParser(){};
    explicit CodeParser(InfoKeeper* keeper);

//opens each file and calls to it doParse
    void parseFiles(std::vector<std::string>::iterator begin,
                    std::vector<std::string>::iterator end);
};


#endif //PROJECTACCOUNTANT_CODEPARSER_H
