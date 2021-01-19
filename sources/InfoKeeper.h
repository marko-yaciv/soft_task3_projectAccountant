//
// Created by Marko on 17.01.2021.
//

#ifndef PROJECTACCOUNTANT_INFOKEEPER_H
#define PROJECTACCOUNTANT_INFOKEEPER_H

#include <string>
/*Struct contains data about file*/
typedef struct FileInfo{
    unsigned m_numOfBlankLines;
    unsigned m_numOfCodeLines;
    unsigned m_numOfCommentLines;
    unsigned m_numOfAllLines;
    std::string filePath;

    bool operator==(const FileInfo& other) const
    {
        return this->filePath == other.filePath &&
                this->m_numOfAllLines == other.m_numOfAllLines &&
                this->m_numOfCodeLines == other.m_numOfCodeLines &&
                this->m_numOfCommentLines == other.m_numOfCommentLines &&
                this->m_numOfBlankLines == other.m_numOfBlankLines;
    };
}FileInfo;

/*That class wil store
 * data about all files.
 * It uses mutex for safe adding data
 * from threads to vector of FileInfo structures.*/
class InfoKeeper{
public:
    //This function should use mutex
    // if multithreaded file parsing is going
    virtual void setInfoAboutFile(FileInfo& info) = 0;
};


#endif //PROJECTACCOUNTANT_INFOKEEPER_H
