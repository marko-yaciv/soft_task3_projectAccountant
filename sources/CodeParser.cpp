//
// Created by Marko on 15.01.2021.
//
#include "CodeParser.h"

CodeParser::CodeParser(const std::vector<std::string> &files)
{
    m_filesToParse = files;
    m_out = std::ofstream("out.txt");
}

CodeParser::CodeParser(std::string &file)
{
    m_filesToParse.push_back(file);
    m_out = std::ofstream("out.txt");
}

CodeParser::CodeParser()
{
    m_out = std::ofstream("out.txt");

}

void CodeParser::doParse(std::ifstream &file, const std::string& filePath)
{
    m_FileInfo FileInfo{0};

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
                ++FileInfo.m_numOfCommentLines;
                if(std::regex_match(textLine, codeAfterBlockCommentEnd))
                {
                    ++FileInfo.m_numOfCodeLines;
                }
                isBlockCommentLine = false;
            }
            else
            {
                ++FileInfo.m_numOfCommentLines;
            }
            continue;
        }

        if(std::regex_match(textLine,exprForBlankLine))
        {
            ++FileInfo.m_numOfBlankLines;
        }
        else if(std::regex_search(textLine,commentLine))
        {
            ++FileInfo.m_numOfCommentLines;
            if(std::regex_match(textLine,codeBeforeCommentLine))
            {
                ++FileInfo.m_numOfCodeLines;
            }
        }
        else if(std::regex_search(textLine,std::regex(R"((\/\*))"))) // start of block comment
        {
            ++FileInfo.m_numOfCommentLines;
            if(std::regex_match(textLine,codeBeforeBlockCommentBegin))
            {
                ++FileInfo.m_numOfCodeLines;
            }
            if(!std::regex_search(textLine,std::regex(R"((\*\/))")))
            {
                isBlockCommentLine  = true;
            }
        }
        else
        {
            ++FileInfo.m_numOfCodeLines;
        }
        ++FileInfo.m_numOfAllLines;
    }

    saveDataAboutFile(filePath,FileInfo);
}

void CodeParser::parseFiles(const std::vector<std::string> &files)
{
    std::ifstream fileToAnalyse;

    for(auto&file : files)
    {
        fileToAnalyse = std::ifstream(file);
        if(!fileToAnalyse.is_open())
        {
            std::cout << "Cannot open file " << file << std::endl;
            continue;
        }
        doParse(fileToAnalyse,file);
        fileToAnalyse.close();
    }
}

void CodeParser::saveDataAboutFile(const std::string& filePath, const CodeParser::m_FileInfo &info)
{
    std::lock_guard<std::mutex> lock(m_lock);
    m_out << "File: " << filePath << std::endl
          << "Count of blank lines = " << info.m_numOfBlankLines
          << "\nCount of code lines = " << info.m_numOfCodeLines
          << "\nCount of comment lines = " << info.m_numOfCommentLines
          << "\nTotal count of lines = " << info.m_numOfAllLines << std::endl;
}
