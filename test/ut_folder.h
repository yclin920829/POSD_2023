#pragma once 

#include <string>
#include <gtest/gtest.h>

#include "../src/file.h"
#include "../src/folder.h"

using namespace std;

TEST(Folder, normal) {
    Folder home("./Users/user/home");

    ASSERT_EQ("home", home.name());
    ASSERT_EQ("./Users/user/home", home.path());
}

TEST(Folder, add_file) {
    Folder home("./Users/user/home");
    File hello("./Users/user/home/hello.txt");
    home.add(&hello);

    ASSERT_EQ("hello.txt", home.getChildByName("hello.txt")->name());
}

TEST(Folder, add_incorrect_path_file_to_folder) {
    Folder home("./Users/user/home");
    File hello("./Users/user/home/Documents/hello.txt");
    ASSERT_ANY_THROW(home.add(&hello));
}

TEST(Folder, add_folder) {
    Folder home("./Users/user/home");
    Folder document("./Users/user/home/Documents");

    home.add(&document);

    ASSERT_EQ("Documents", home.getChildByName("Documents")->name());
}

TEST(Folder, my_normal) {
    Folder folder02("./folder01/folder02");

    ASSERT_EQ("folder02", folder02.name());
    ASSERT_EQ("./folder01/folder02", folder02.path());
}

TEST(Folder, my_add_file) {
    Folder folder01("./folder01");
    File file01("./folder01/file01.txt");
    folder01.add(&file01);

    ASSERT_EQ("file01.txt", folder01.getChildByName("file01.txt")->name());
}

TEST(Folder, my_add_incorrect_path_file_to_folder) {
    Folder folder01("./folder01");
    File file01("./folder01/folder02/file03.txt");

    ASSERT_ANY_THROW(folder01.add(&file01));
}

TEST(Folder, my_add_folder) {
    Folder folder01("./folder01");
    Folder folder02("./folder01/folder02");

    folder01.add(&folder02);

    ASSERT_EQ("folder02", folder01.getChildByName("folder02")->name());
}

TEST(Folder, my_invalid_folder) {
    ASSERT_ANY_THROW(Folder folder01("/NOT/EXIST/PATH"));
}

TEST(Folder, my_invalid_folder_2) {
    ASSERT_ANY_THROW(Folder folder01("./folder01/file01.txt"));
}