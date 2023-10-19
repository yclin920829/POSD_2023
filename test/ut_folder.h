#pragma once 

#include <string>
#include <iostream>
#include <gtest/gtest.h>

#include "../src/file.h"
#include "../src/folder.h"

using namespace std;

TEST(Folder, normal) {
    Folder folder02("./folder01/folder02");

    ASSERT_EQ("folder02", folder02.name());
    ASSERT_EQ("./folder01/folder02", folder02.path());
}

TEST(Folder, add_file) {
    Folder folder01("./folder01");
    File file01("./folder01/file01.txt");
    folder01.add(&file01);

    ASSERT_EQ("file01.txt", folder01.getChildByName("file01.txt")->name());
}

TEST(Folder, add_incorrect_path_file_to_folder) {
    Folder folder01("./folder01");
    File file01("./folder01/folder02/file03.txt");

    ASSERT_ANY_THROW(folder01.add(&file01));
}

TEST(Folder, add_folder) {
    Folder folder01("./folder01");
    Folder folder02("./folder01/folder02");

    folder01.add(&folder02);

    ASSERT_EQ("folder02", folder01.getChildByName("folder02")->name());
}

TEST(Folder, invalid_folder) {
    ASSERT_ANY_THROW(Folder folder01("/NOT/EXIST/PATH"));
}

TEST(Folder, invalid_folder_2) {
    ASSERT_ANY_THROW(Folder folder01("./folder01/file01.txt"));
}