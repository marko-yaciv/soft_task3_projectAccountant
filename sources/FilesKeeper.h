//
// Created by Marko on 12.01.2021.
//

#ifndef PROJECTACCOUNTANT_FILEKEEPER_H
#define PROJECTACCOUNTANT_FILEKEEPER_H

#include <boost/filesystem.hpp>
#include <string>
#include <fstream>
#include <regex>
#include <list>

/*This class finds al files in given root directory
 * and keeps them in list*/
class FilesKeeper
{
private:
    std::string m_rootDirectoryPath;
    std::vector<std::string> m_currentDirectoryFilesPaths;

public:
    FilesKeeper();
    ~FilesKeeper();
    explicit FilesKeeper(std::string  startDirectory);

/*This function will find all files with scpecified regex
     * using recursive_directory iterator*/
    void findFiles();

    [[nodiscard]] size_t getCountOfFiles() const;
    [[nodiscard]] std::vector<std::string>& getFiles();
    void printFoundedFiles() const;
};

#endif //PROJECTACCOUNTANT_FILEKEEPER_H
