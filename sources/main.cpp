#include <iostream>
#include "FilesKeeper.h"
#include "FileAnalyser.h"
int main()
{
    /*FilesKeeper keeper(R"(D:\Programing\QtProjects)");
    keeper.findFiles();
    keeper.printFoundedFiles();
    std::cout << "Count of files: " << keeper.getCountOfFiles() << std::endl;*/
    FileAnalyser analyser(R"(D:\Programing\QtProjects\2course\kursova\learn-system\studentdialog.h)");
    analyser.analyse();
    std::cout
    << "Count of blank lines = " << analyser.getCountOfBlankLines()
    << "\nCount of code lines = " << analyser.getCountOfCodeLines()
    << "\nCount of comment lines = " << analyser.getCountOfCommentLines()
    << std::endl;

    return 0;
}
