#include "../src/folder.h"
#include "../src/file.h"

TEST(FolderSuite, Ping) {
    ASSERT_TRUE(true);
}

TEST(FolderSuite, get_folder_name) {
    Folder * folder01 = new Folder("/Users/user/books");
    ASSERT_EQ("books", folder01->name());
}

TEST(FolderSuite, get_folder_path) {
    Folder * folder = new Folder("/Users/user/books");
    ASSERT_EQ("/Users/user/books", folder->path());
}

TEST(FolderSuite, add_file_to_folder) {

    Folder * folder = new Folder("/Users/user/books");
    File * file01 = new File("/Users/user/books/001.pdf");
    File * file02 = new File("/Users/user/books/002.pdf");
    File * file03 = new File("/Users/user/books/003.pdf");
    File * file04 = new File("/Users/user/books/004.pdf");
    File * file05 = new File("/Users/user/books/005.pdf");

    folder->add(file01);
    folder->add(file02);
    folder->add(file03);
    folder->add(file04);
    folder->add(file05);

    ASSERT_EQ(5, folder->numberOfFiles());
    ASSERT_EQ(file03, folder->getChildByName("003.pdf"));
    ASSERT_EQ(file03, folder->find("/Users/user/books/003.pdf"));

    ASSERT_EQ(nullptr, folder->getChildByName("006.pdf"));
    ASSERT_EQ(nullptr, folder->find("/Users/user/books/006.pdf"));
}

TEST(FolderSuite, add_incorrect_path_file_to_folder) {

    Folder * folder = new Folder("/Users/user/books");
    File * file01 = new File("/Users/user/books/001.pdf");
    File * file02 = new File("/Users/user/books/002.pdf");
    File * file03 = new File("/Users/user/books/003.pdf");
    File * file04 = new File("/Users/user/books/004.pdf");
    File * file05 = new File("/Users/user/books01/005.pdf");

    folder->add(file01);
    folder->add(file02);
    folder->add(file03);
    folder->add(file04);
    ASSERT_ANY_THROW(folder->add(file05));

    ASSERT_EQ(4, folder->numberOfFiles());
    ASSERT_EQ(file03, folder->getChildByName("003.pdf"));
    ASSERT_EQ(file03, folder->find("/Users/user/books/003.pdf"));
}

TEST(FolderSuite, remove_file_from_folder) {

    Folder * folder = new Folder("/Users/user/books");
    File * file01 = new File("/Users/user/books/001.pdf");
    File * file02 = new File("/Users/user/books/002.pdf");
    File * file03 = new File("/Users/user/books/003.pdf");
    File * file04 = new File("/Users/user/books/004.pdf");
    File * file05 = new File("/Users/user/books/005.pdf");

    folder->add(file01);
    folder->add(file02);
    folder->add(file03);
    folder->add(file04);
    folder->add(file05);

    folder -> remove("/Users/user/books/003.pdf");

    ASSERT_EQ(4, folder->numberOfFiles());
    ASSERT_EQ(nullptr, folder->getChildByName("003.pdf"));
    ASSERT_EQ(nullptr, folder->find("/Users/user/books/003.pdf"));
}

TEST(FolderSuite, delete_a_file) {

    Folder * folder = new Folder("/Users/user/books");
    File * file01 = new File("/Users/user/books/001.pdf");
    File * file02 = new File("/Users/user/books/002.pdf");
    File * file03 = new File("/Users/user/books/003.pdf");
    File * file04 = new File("/Users/user/books/004.pdf");
    File * file05 = new File("/Users/user/books/005.pdf");

    folder->add(file01);
    folder->add(file02);
    folder->add(file03);
    folder->add(file04);
    folder->add(file05);


    ASSERT_EQ(5, folder->numberOfFiles());
    ASSERT_EQ(file03, folder->getChildByName("003.pdf"));

    folder -> remove("/Users/user/books/003.pdf");

    ASSERT_EQ(4, folder->numberOfFiles());
    ASSERT_EQ(NULL, folder->getChildByName("003.pdf"));
    ASSERT_EQ(NULL, folder->find("/Users/user/books/003.pdf"));
    ASSERT_EQ(file04, folder->find("/Users/user/books/004.pdf"));
}

TEST(FolderSuite, delete_a_folder) {
    Folder * folder01 = new Folder("/Users/user/books01");
    Folder * folder02 = new Folder("/Users/user/books01/books02");
    
    File * file01 = new File("/Users/user/books01/001.pdf");
    File * file02 = new File("/Users/user/books01/002.pdf");
    File * file03 = new File("/Users/user/books01/003.pdf");
    File * file04 = new File("/Users/user/books01/004.pdf");
    File * file05 = new File("/Users/user/books01/005.pdf");
    
    File * file06 = new File("/Users/user/books01/books02/006.pdf");
    File * file07 = new File("/Users/user/books01/books02/007.pdf");
    File * file08 = new File("/Users/user/books01/books02/008.pdf");
    File * file09 = new File("/Users/user/books01/books02/009.pdf");
    File * file10 = new File("/Users/user/books01/books02/010.pdf");

    folder01->add(file01);
    folder01->add(file02);
    folder01->add(file03);
    folder01->add(file04);
    folder01->add(file05);

    folder02->add(file06);
    folder02->add(file07);
    folder02->add(file08);
    folder02->add(file09);
    folder02->add(file10);

    folder01->add(folder02);

    ASSERT_EQ(10, folder01->numberOfFiles());

    ASSERT_EQ(file08, folder01->find("/Users/user/books01/books02/008.pdf"));
    folder01->remove("/Users/user/books01/books02");
    ASSERT_EQ(nullptr, folder01->find("/Users/user/books01/books02/008.pdf"));
}

TEST(FolderSuite, get_child_by_name) {

    Folder * folder = new Folder("/Users/user/books");
    File * file01 = new File("/Users/user/books/001.pdf");
    File * file02 = new File("/Users/user/books/002.pdf");
    File * file03 = new File("/Users/user/books/003.pdf");
    File * file04 = new File("/Users/user/books/004.pdf");
    File * file05 = new File("/Users/user/books/005.pdf");

    folder->add(file01);
    folder->add(file02);
    folder->add(file03);
    folder->add(file04);
    folder->add(file05);

    ASSERT_EQ(file03, folder->getChildByName("003.pdf"));

}

TEST(FolderSuite, find_path_one_layer_folder) {

    Folder * folder01 = new Folder("/Users/user/books01");
    Folder * folder02 = new Folder("/Users/user/books01/books02");
    
    File * file01 = new File("/Users/user/books01/001.pdf");
    File * file02 = new File("/Users/user/books01/002.pdf");
    File * file03 = new File("/Users/user/books01/003.pdf");
    File * file04 = new File("/Users/user/books01/004.pdf");
    File * file05 = new File("/Users/user/books01/005.pdf");
    
    File * file06 = new File("/Users/user/books01/books02/006.pdf");
    File * file07 = new File("/Users/user/books01/books02/007.pdf");
    File * file08 = new File("/Users/user/books01/books02/008.pdf");
    File * file09 = new File("/Users/user/books01/books02/009.pdf");
    File * file10 = new File("/Users/user/books01/books02/010.pdf");

    folder01->add(file01);
    folder01->add(file02);
    folder01->add(file03);
    folder01->add(file04);
    folder01->add(file05);

    folder02->add(file06);
    folder02->add(file07);
    folder02->add(file08);
    folder02->add(file09);
    folder02->add(file10);

    folder01->add(folder02);

    ASSERT_EQ(file03, folder01->find("/Users/user/books01/003.pdf"));
    ASSERT_EQ(file08, folder01->find("/Users/user/books01/books02/008.pdf"));
    ASSERT_EQ(file06, folder01->find("/Users/user/books01/books02/006.pdf"));

}

TEST(FolderSuite, numbers_of_files_two_layer_folder) {

    Folder * folder01 = new Folder("/Users/user/books01");
    Folder * folder02 = new Folder("/Users/user/books01/books02");
    
    File * file01 = new File("/Users/user/books01/001.pdf");
    File * file02 = new File("/Users/user/books01/002.pdf");
    File * file03 = new File("/Users/user/books01/003.pdf");
    File * file04 = new File("/Users/user/books01/004.pdf");
    File * file05 = new File("/Users/user/books01/005.pdf");
    
    File * file06 = new File("/Users/user/books01/books02/006.pdf");
    File * file07 = new File("/Users/user/books01/books02/007.pdf");
    File * file08 = new File("/Users/user/books01/books02/008.pdf");
    File * file09 = new File("/Users/user/books01/books02/009.pdf");
    File * file10 = new File("/Users/user/books01/books02/010.pdf");

    folder01->add(file01);
    folder01->add(file02);
    folder01->add(file03);
    folder01->add(file04);
    folder01->add(file05);

    folder02->add(file06);
    folder02->add(file07);
    folder02->add(file08);
    folder02->add(file09);
    folder02->add(file10);

    folder01->add(folder02);

    ASSERT_EQ(5, folder02->numberOfFiles());    
    ASSERT_EQ(5, folder02->numberOfFiles());
    ASSERT_EQ(10, folder01->numberOfFiles());
    
}
