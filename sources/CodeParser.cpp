//
// Created by Marko on 15.01.2021.
//
#include "CodeParser.h"

CodeParser::CodeParser(InfoKeeper* keeper): m_keeper(keeper)
{

}

void CodeParser::doParse(std::ifstream &file, const std::string& filePath)
{
    FileInfo fileData{0};
    fileData.filePath = filePath;

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
                ++fileData.m_numOfCommentLines;
                if(std::regex_match(textLine, codeAfterBlockCommentEnd))
                {
                    ++fileData.m_numOfCodeLines;
                }
                isBlockCommentLine = false;
            }
            else
            {
                ++fileData.m_numOfCommentLines;
            }
            continue;
        }

        if(std::regex_match(textLine,exprForBlankLine))
        {
            ++fileData.m_numOfBlankLines;
        }
        else if(std::regex_search(textLine,commentLine))
        {
            ++fileData.m_numOfCommentLines;
            if(std::regex_match(textLine,codeBeforeCommentLine))
            {
                ++fileData.m_numOfCodeLines;
            }
        }
        else if(std::regex_search(textLine,std::regex(R"((\/\*))"))) // start of block comment
        {
            ++fileData.m_numOfCommentLines;
            if(std::regex_match(textLine,codeBeforeBlockCommentBegin))
            {
                ++fileData.m_numOfCodeLines;
            }
            if(!std::regex_search(textLine,std::regex(R"((\*\/))")))
            {
                isBlockCommentLine  = true;
            }
        }
        else
        {
            ++fileData.m_numOfCodeLines;
        }
        ++fileData.m_numOfAllLines;
    }

    m_keeper->setInfoAboutFile(fileData);
}

void CodeParser::parseFiles(const std::list<std::string> &files)
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

/*std::list<FileInfo>& CodeParser::getInfo()
{
    return keeper.getfilesData();
}*/
