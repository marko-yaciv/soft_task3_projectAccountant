//
// Created by Marko on 12.01.2021.
//

#ifndef PROJECTACCOUNTANT_FILEKEEPER_H
#define PROJECTACCOUNTANT_FILEKEEPER_H

#include <string>
#include <fstream>
#include <experimental/filesystem>
#include <regex>
#include <vector>

#include <mingw.mutex.h>

namespace fs = std::experimental::filesystem;
class FilesKeeper
{
private:
    std::string m_rootDirectoryPath;
    std::vector<std::string> m_currentDirectoryFilesPaths;


public:
    FilesKeeper();
    ~FilesKeeper();
    explicit FilesKeeper(std::string  startDirectory);

    void findFiles();
    [[nodiscard]] size_t getCountOfFiles() const;
    [[nodiscard]] std::string getFilePathAt(size_t index) const;
    [[nodiscard]] std::vector<std::string>& getFiles();
    void printFoundedFiles() const;
};


#endif //PROJECTACCOUNTANT_FILEKEEPER_H
