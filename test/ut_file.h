#pragma once 

#include <gtest/gtest.h>

#include "../src/file.h"

TEST(File, normal) {
    File file01("./folder01/file01.txt");
    ASSERT_EQ("file01.txt", file01.name());
    ASSERT_EQ("./folder01/file01.txt", file01.path());
}

TEST(File, invalid_file) {
    ASSERT_ANY_THROW(File file01("/NOT/EXIST/PATH"));
}

TEST(File, invalid_file_2) {
    ASSERT_ANY_THROW(File file03("./folder01/folder02"));
}