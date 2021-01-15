//
// Created by Marko on 15.01.2021.
//

#ifndef PROJECTACCOUNTANT_CODEPARSER_H
#define PROJECTACCOUNTANT_CODEPARSER_H


#include <vector>
#include <string>
#include <fstream>
#include <regex>
#include <iostream>
#include <mingw.mutex.h>
#include <mingw.thread.h>


class CodeParser {
private:
    typedef struct {
        unsigned m_numOfBlankLines;
        unsigned m_numOfCodeLines;
        unsigned m_numOfCommentLines;
        unsigned m_numOfAllLines;
    }m_FileInfo;
    std::vector<std::string> m_filesToParse;
    std::mutex m_lock;
    std::ofstream m_out;
private:
    void doParse(std::ifstream& file, const std::string& filePath);
public:
    CodeParser();
    explicit  CodeParser(const std::vector<std::string>& files);
    explicit CodeParser(std::string& file);

    void parseFiles(const std::vector<std::string> &files);
    void saveDataAboutFile(const std::string& filePath, const m_FileInfo& info);
};


#endif //PROJECTACCOUNTANT_CODEPARSER_H
