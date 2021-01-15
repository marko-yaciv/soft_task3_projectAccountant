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
class FileAnalyser {
private:
    std::ofstream m_out;
    std::mutex m_lock;
    std::vector<std::string> m_filesToAnalyse;
    unsigned m_countOfBlankLines;
    unsigned m_countOfCommentLines;
    unsigned m_countOfCodeLines;
    unsigned m_countOfAllLines;

    void doParse(std::ifstream& file);
public:
    void openAndParse(const std::vector<std::string>& files);
    FileAnalyser();
    explicit FileAnalyser(std::vector<std::string>& filesToParse);
    void startParsing();

    [[nodiscard]] unsigned getCountOfBlankLines() const;
    [[nodiscard]] unsigned getCountOfCommentLines() const;
    [[nodiscard]] unsigned getCountOfCodeLines() const;
    [[nodiscard]] unsigned getTotalCountOfLines() const;

};


#endif //PROJECTACCOUNTANT_FILEANALYSER_H
