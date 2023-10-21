#pragma once 

#include <gtest/gtest.h>

#include "../src/file.h"

TEST(File, normal) {
    File hello("./Users/user/home/hello.txt");
    ASSERT_EQ("hello.txt", hello.name());
    ASSERT_EQ("./Users/user/home/hello.txt", hello.path());
}

TEST(File0, my_normal) {
    File file01("./folder01/file01.txt");
    ASSERT_EQ("file01.txt", file01.name());
    ASSERT_EQ("./folder01/file01.txt", file01.path());
}

TEST(File, my_invalid_file) {
    ASSERT_ANY_THROW(File file01("/NOT/EXIST/PATH"));
}

TEST(File, my_invalid_file_2) {
    ASSERT_ANY_THROW(File file03("./folder01/folder02"));
}