#include "../src/folder.h"

TEST(FolderSuite, Ping) {
    ASSERT_TRUE(true);
}

TEST(FolderSuite, Folder_name) {

    Folder * folder01 = new Folder("/Users/user/books");
    // Folder * folder02 = new Folder("/Users/user/books/");

    ASSERT_EQ("books", folder01->name());
    // ASSERT_EQ("books", folder02->name());
}

TEST(FolderSuite, Folder_Path) {

    Folder * folder = new Folder("/Users/user/books/");

    ASSERT_EQ("/Users/user/books/", folder->path());
}
