//
// Created by Marko on 19.01.2021.
//
#include <gtest//gtest.h>
#include "../sources/FilesKeeper.h"
#include "../sources/FileAnalyser.h"

TEST(getFiles, invalidDirectoryPath)
{
    FilesKeeper keeper("D:\\Rpogrammming");
    ASSERT_ANY_THROW(keeper.findFiles());
}
TEST(getFiles, isNotDirectory)
{
    FilesKeeper keeper("D:\\Programing\\Clion_work\\test\\main.cpp");
    ASSERT_THROW(keeper.findFiles(),std::string);
}
TEST(getFiles,emptyDirectory)
{
    FilesKeeper keeper("D:\\emptyDir");
    keeper.findFiles();
    EXPECT_EQ(0,keeper.getCountOfFiles());
}

TEST(getFiles,normalTest)
{
    FilesKeeper keeper("D:\\Programing\\QtProjects");
    keeper.findFiles();
    EXPECT_LT(0,keeper.getCountOfFiles());
}


TEST(analyseFiles, noFiles)
{
    std::vector<std::string> files(0);
    FileAnalyser analyser(files);
    EXPECT_THROW(analyser.startParsing(),std::string);
}

TEST(analyseFiles, threadsParsing)
{
    FilesKeeper keeper("D:\\Programing\\QtProjects");
    keeper.findFiles();
    FileAnalyser analyser(keeper.getFiles());
    EXPECT_NO_THROW(analyser.startParsing());
}

TEST(analyseFiles, saveData)
{
    FilesKeeper keeper("D:\\Programing\\QtProjects");
    keeper.findFiles();
    FileAnalyser analyser(keeper.getFiles());
    analyser.startParsing();
    EXPECT_THROW(analyser.saveDataToJson("D:\\Programmming"),std::string);
    EXPECT_NO_THROW(analyser.saveDataToJson("D:\\Programing"));
}

TEST(parseFile, correctParsing)
{
    std::vector<std::string> file{"D:\\Programing\\Code_blocks_work\\test.cpp"};
    FileAnalyser analyser(file);
    analyser.startParsing();

    FileInfo info;
    info.filePath = "D:\\Programing\\Code_blocks_work\\test.cpp";
    info.m_numOfAllLines = 20;
    info.m_numOfBlankLines = 4;
    info.m_numOfCommentLines = 6;
    info.m_numOfCodeLines = 13;

    EXPECT_EQ(info,analyser.getData().front());

}