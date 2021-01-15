//
// Created by Marko on 13.01.2021.
//
#include <iostream>
#include "FileAnalyser.h"

FileAnalyser::FileAnalyser(std::vector<std::string>& filesToParse):
                m_countOfBlankLines(0),
                m_countOfCommentLines(0),
                m_countOfCodeLines(0),
                m_countOfAllLines(0),
                m_filesToAnalyse(filesToParse)
{
    m_out = std::ofstream("out.txt");
}
FileAnalyser::FileAnalyser():
        m_countOfBlankLines(0),
        m_countOfCommentLines(0),
        m_countOfCodeLines(0),
        m_countOfAllLines(0)
{
    m_out = std::ofstream("out.txt");
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
unsigned FileAnalyser::getTotalCountOfLines() const
{
    return m_countOfAllLines;
}

void FileAnalyser::startParsing()
{
    auto numOfConcurrency = std::thread::hardware_concurrency();
    auto numOfPackPerThread = m_filesToAnalyse.size() / numOfConcurrency + 1 ;

    std::vector<std::thread> threads(numOfPackPerThread);
    auto begin = m_filesToAnalyse.begin();
    auto end = begin + numOfConcurrency;

    for(auto& th : threads)
    {
        if(end > m_filesToAnalyse.end())
        {
            end = m_filesToAnalyse.end();
        }
        th = std::thread(&FileAnalyser::openAndParse,std::ref(*this),std::vector<std::string>{begin,end});
        begin = end;
        end = begin + numOfConcurrency;
    }

    for(auto& th : threads)
    {
        th.join();
    }
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



void FileAnalyser::openAndParse(const std::vector<std::string>& files)
{
    std::ifstream fileToAnalyse;

    for(auto&file : files)
    {
        fileToAnalyse = std::ifstream(file);
        if(!fileToAnalyse.is_open())
        {
            std::cout << std::string("Cannot open file " + file);
            continue;
        }

        std::lock_guard<std::mutex> lock(m_lock);
        doParse(fileToAnalyse);
        fileToAnalyse.close();

        m_out << "File: " << file << std::endl
              << "Count of blank lines = " << m_countOfBlankLines
              << "\nCount of code lines = " << m_countOfCodeLines
              << "\nCount of comment lines = " << m_countOfCommentLines
              << "\nTotal count of lines = " << m_countOfAllLines << std::endl;
        m_countOfCodeLines = m_countOfCommentLines =
        m_countOfBlankLines = m_countOfAllLines = 0;
    }

}
