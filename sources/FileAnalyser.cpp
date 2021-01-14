//
// Created by Marko on 13.01.2021.
//
#include "FileAnalyser.h"

#include <utility>

FileAnalyser::FileAnalyser(std::string  filePath):
                m_filePath(std::move(filePath)),
                m_countOfBlankLines(0),
                m_countOfCommentLines(0),
                m_countOfCodeLines(0),
                m_countOfAllLines(0)
{

}

unsigned FileAnalyser::getCountOfBlankLines() const
{
    return m_countOfBlankLines;
}

unsigned FileAnalyser::getCountOfCommentLines() const
{
    return m_countOfCommentLines;
}

unsigned FileAnalyser::getCountOfCodeLines() const
{
    return m_countOfCodeLines;
}

void FileAnalyser::analyse()
{
        std::ifstream fileToAnalyse(m_filePath);
        if(!fileToAnalyse.is_open())
        {
            throw std::string("Cannot open file " + m_filePath);
        }

        doParse(fileToAnalyse);

        fileToAnalyse.close();
}

void FileAnalyser::doParse(std::ifstream& file)
{
    std::string textLine;

    std::regex exprForBlankLine("");
    std::regex commentLine(R"(\/\/)");
    std::regex codeBeforeCommentLine(R"(((\w|\s|[;,.=()])+\/\/(\w|\s|[;,.=()])*))");
    std::regex codeBeforeBlockCommentBegin(R"(((\w|\s|[;,.=()])+(\/\*)(\w|\s|[;,.=()])+))");
    std::regex codeAfterBlockCommentEnd(R"(((\w|\s|[;,.=()])+(\*\/)(\w|\s|[;,.=()])+))");

    bool  isBlockCommentLine = false;
    while(std::getline(file, textLine))
    {
        if(isBlockCommentLine)
        {
            if(std::regex_search(textLine, std::regex(R"((\*\/))"))) // end of block comment
            {
                ++m_countOfCommentLines;
                if(std::regex_match(textLine, codeAfterBlockCommentEnd))
                {
                    ++m_countOfCodeLines;
                }
                isBlockCommentLine = false;
            }
            else
            {
                ++m_countOfCommentLines;
            }
            continue;
        }

        if(std::regex_match(textLine,exprForBlankLine))
        {
            ++m_countOfBlankLines;
        }
        else if(std::regex_search(textLine,commentLine))
        {
            ++m_countOfCommentLines;
            if(std::regex_match(textLine,codeBeforeCommentLine))
            {
                ++m_countOfCodeLines;
            }
        }
        else if(std::regex_search(textLine,std::regex(R"((\/\*))"))) // start of block comment
        {
            ++m_countOfCommentLines;
            if(std::regex_match(textLine,codeBeforeBlockCommentBegin))
            {
                ++m_countOfCodeLines;
            }
            if(!std::regex_search(textLine,std::regex(R"((\*\/))")))
            {
                isBlockCommentLine  = true;
            }
        }
        else
        {
            ++m_countOfCodeLines;
        }
        ++m_countOfAllLines;
    }
}


