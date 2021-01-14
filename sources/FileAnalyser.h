//
// Created by Marko on 13.01.2021.
//

#ifndef PROJECTACCOUNTANT_FILEANALYSER_H
#define PROJECTACCOUNTANT_FILEANALYSER_H

#include <string>
#include <fstream>
#include <sstream>
#include <regex>
class FileAnalyser {
private:
    const std::string m_filePath;

    unsigned m_countOfBlankLines;
    unsigned m_countOfCommentLines;
    unsigned m_countOfCodeLines;
    unsigned m_countOfAllLines;

    void doParse(std::ifstream& file);

public:
    explicit FileAnalyser(std::string filePath);
    void analyse();

    [[nodiscard]] unsigned getCountOfBlankLines() const;
    [[nodiscard]] unsigned getCountOfCommentLines() const;
    [[nodiscard]] unsigned getCountOfCodeLines() const;
};


#endif //PROJECTACCOUNTANT_FILEANALYSER_H
