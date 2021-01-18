//
// Created by Marko on 17.01.2021.
//

#include "InfoKeeper.h"

void InfoKeeper::setInfoAboutFile(FileInfo &info)
{
    std::lock_guard<std::mutex> lock(m_lock);
    filesData.push_back(info);
}

void InfoKeeper::saveData()
{

}

std::list<FileInfo>& InfoKeeper::getfilesData(){
    return filesData;
}
