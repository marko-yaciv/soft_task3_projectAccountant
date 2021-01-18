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
    std::mutex m_lock;
public:
    //This function uses mutex
    void setInfoAboutFile(FileInfo& info);

    std::list<FileInfo>& getfilesData();

    //provides different types of saving data for derieved classes
    virtual void saveData();

protected:
    std::list<FileInfo> filesData;
};


#endif //PROJECTACCOUNTANT_INFOKEEPER_H
