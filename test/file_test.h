#include "../src/file.h"

TEST(FileSuite, Ping) {
    ASSERT_TRUE(true);
}

TEST(FileSuite, File_name) {

    File * file = new File("/Users/user/books/design-pattern.pdf");

    ASSERT_EQ("design-pattern.pdf", file->name());
}

TEST(FileSuite, File_Path) {

    File * file = new File("/Users/user/books/design-pattern.pdf");

    ASSERT_EQ("/Users/user/books/design-pattern.pdf", file->path());
}