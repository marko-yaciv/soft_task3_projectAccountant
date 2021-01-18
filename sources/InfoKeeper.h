//
// Created by Marko on 17.01.2021.
//

#ifndef PROJECTACCOUNTANT_INFOKEEPER_H
#define PROJECTACCOUNTANT_INFOKEEPER_H

#include <mingw.thread.h>
#include <mingw.mutex.h>
#include <list>
#include <string>

/*Struct contains data about file*/
typedef struct {
    unsigned m_numOfBlankLines;
    unsigned m_numOfCodeLines;
    unsigned m_numOfCommentLines;
    unsigned m_numOfAllLines;
    std::string filePath;
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
