#include "../src/folder.h"
#include "../src/file.h"
#include "../src/iterator.h"
#include "../src/dfs_iterator.h"

using namespace std;

TEST(IteratorSuite, Ping) {
    ASSERT_TRUE(true);
}

TEST(IteratorSuite, FolderIterator01) {
    
    Folder * folder = new Folder("/Users/user/books/");
    File * file01 = new File("/Users/user/books/001.pdf");
    File * file02 = new File("/Users/user/books/002.pdf");

    folder->add(file01);
    folder->add(file02);

    Iterator* it = folder->createIterator();

    it->first();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ(file01, it->currentItem());

    it->next();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ(file02, it->currentItem());

    it->next();
    ASSERT_TRUE(it->isDone());

    delete it;
}

TEST(IteratorSuite, FolderIterator02) {
    
    Folder * folder01 = new Folder("/Users/user/folder01");
    Folder * folder02 = new Folder("/Users/user/folder02");
    Folder * folder03 = new Folder("/Users/user/folder03");
    Folder * folder04 = new Folder("/Users/user/folder04");

    File * file1_1 = new File("/Users/user/folder01/file1_1.pdf");
    File * file1_2 = new File("/Users/user/folder01/file1_2.pdf");
    File * file1_3 = new File("/Users/user/folder02/file1_3.pdf");

    File * file2_1 = new File("/Users/user/folder02/file2_1.pdf");

    File * file3_1 = new File("/Users/user/folder03/file3_1.pdf");
    File * file3_2 = new File("/Users/user/folder03/file3_2.pdf");
    File * file3_3 = new File("/Users/user/folder03/file3_3.pdf");
    File * file3_4 = new File("/Users/user/folder03/file3_4.pdf");

    File * file4_1 = new File("/Users/user/folder04/file4_1.pdf");
    File * file4_2 = new File("/Users/user/folder04/file4_2.pdf");
    File * file4_3 = new File("/Users/user/folder04/file4_3.pdf");
    File * file4_4 = new File("/Users/user/folder04/file4_4.pdf");

    folder01->add(file1_1);
    folder01->add(file1_2);
    folder01->add(folder02);
    folder01->add(file1_3);

    folder02->add(file2_1);
    folder02->add(folder03);
    folder02->add(folder04);

    folder03->add(file3_1);
    folder03->add(file3_2);
    folder03->add(file3_3);
    folder03->add(file3_4);

    folder04->add(file4_1);
    folder04->add(file4_2);
    folder04->add(file4_3);
    folder04->add(file4_4);

    ASSERT_EQ(12, folder01->numberOfFiles());

    Iterator* it = folder01->createIterator();

    it->first();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ(file1_1, it->currentItem());

    it->next();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ(file1_2, it->currentItem());

    it->next();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ(folder02, it->currentItem());

    it->next();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ(file1_3, it->currentItem());

    it->next();
    ASSERT_TRUE(it->isDone());

    delete it;
}

TEST(IteratorSuite, DFS_iterator) {
    
    Folder * folder01 = new Folder("/Users/user/folder01");
    Folder * folder02 = new Folder("/Users/user/folder02");
    Folder * folder03 = new Folder("/Users/user/folder03");
    Folder * folder04 = new Folder("/Users/user/folder04");

    File * file1_1 = new File("/Users/user/folder01/file1_1.pdf");
    File * file1_2 = new File("/Users/user/folder01/file1_2.pdf");
    File * file1_3 = new File("/Users/user/folder02/file1_3.pdf");

    File * file2_1 = new File("/Users/user/folder02/file2_1.pdf");

    File * file3_1 = new File("/Users/user/folder03/file3_1.pdf");
    File * file3_2 = new File("/Users/user/folder03/file3_2.pdf");
    File * file3_3 = new File("/Users/user/folder03/file3_3.pdf");
    Folder * folder05 = new Folder("/Users/user/folder05");

    File * file4_1 = new File("/Users/user/folder04/file4_1.pdf");
    File * file4_2 = new File("/Users/user/folder04/file4_2.pdf");
    File * file4_3 = new File("/Users/user/folder04/file4_3.pdf");
    File * file4_4 = new File("/Users/user/folder04/file4_4.pdf");

    folder01->add(file1_1);
    folder01->add(file1_2);
    folder01->add(folder02);
    folder01->add(file1_3);

    folder02->add(file2_1);
    folder02->add(folder03);
    folder02->add(folder04);

    folder03->add(file3_1);
    folder03->add(file3_2);
    folder03->add(file3_3);
    folder03->add(folder05);

    folder04->add(file4_1);
    folder04->add(file4_2);
    folder04->add(file4_3);
    folder04->add(file4_4);

    ASSERT_EQ(11, folder01->numberOfFiles());

    Iterator* it = new DfsIterator(folder01);

    // it->first();
    // while (true)
    // {
    //     if (it->isDone())
    //         break;
    //     cout << "item: " << it->currentItem()->name() << endl;
    //     it->next();
    // }

    it->first();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ(file1_1, it->currentItem());

    it->next();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ(file1_2, it->currentItem());

    it->next();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ(folder02, it->currentItem());

    it->next();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ(file2_1, it->currentItem());

    it->next();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ(folder03, it->currentItem());

    it->next();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ(file3_1, it->currentItem());

    it->next();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ(file3_2, it->currentItem());

    it->next();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ(file3_3, it->currentItem());

    it->next();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ(folder05, it->currentItem());

    it->next();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ(folder04, it->currentItem());

    it->next();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ(file4_1, it->currentItem());

    it->next();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ(file4_2, it->currentItem());

    it->next();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ(file4_3, it->currentItem());

    it->next();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ(file4_4, it->currentItem());

    it->next();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ(file1_3, it->currentItem());

    it->next();
    ASSERT_TRUE(it->isDone());

    delete it;

}

TEST(IteratorSuite, BFS_iterator) {
    
    Folder * folder01 = new Folder("/Users/user/folder01");
    Folder * folder02 = new Folder("/Users/user/folder02");
    Folder * folder03 = new Folder("/Users/user/folder03");
    Folder * folder04 = new Folder("/Users/user/folder04");

    File * file1_1 = new File("/Users/user/folder01/file1_1.pdf");
    File * file1_2 = new File("/Users/user/folder01/file1_2.pdf");
    File * file1_3 = new File("/Users/user/folder02/file1_3.pdf");

    File * file2_1 = new File("/Users/user/folder02/file2_1.pdf");

    File * file3_1 = new File("/Users/user/folder03/file3_1.pdf");
    File * file3_2 = new File("/Users/user/folder03/file3_2.pdf");
    File * file3_3 = new File("/Users/user/folder03/file3_3.pdf");
    Folder * folder05 = new Folder("/Users/user/folder05");

    File * file4_1 = new File("/Users/user/folder04/file4_1.pdf");
    File * file4_2 = new File("/Users/user/folder04/file4_2.pdf");
    File * file4_3 = new File("/Users/user/folder04/file4_3.pdf");
    File * file4_4 = new File("/Users/user/folder04/file4_4.pdf");

    folder01->add(file1_1);
    folder01->add(file1_2);
    folder01->add(folder02);
    folder01->add(file1_3);

    folder02->add(file2_1);
    folder02->add(folder03);
    folder02->add(folder04);

    folder03->add(file3_1);
    folder03->add(file3_2);
    folder03->add(file3_3);
    folder03->add(folder05);

    folder04->add(file4_1);
    folder04->add(file4_2);
    folder04->add(file4_3);
    folder04->add(file4_4);

    ASSERT_EQ(11, folder01->numberOfFiles());

    Iterator* it = new BfsIterator(folder01);

    // it->first();
    // while (true)
    // {
    //     if (it->isDone())
    //         break;
    //     cout << "item: " << it->currentItem()->name() << endl;
    //     it->next();
    // }

    it->first();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ(file1_1, it->currentItem());

    it->next();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ(file1_2, it->currentItem());

    it->next();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ(folder02, it->currentItem());

    it->next();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ(file1_3, it->currentItem());

    it->next();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ(file2_1, it->currentItem());

    it->next();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ(folder03, it->currentItem());

    it->next();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ(folder04, it->currentItem());

    it->next();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ(file3_1, it->currentItem());

    it->next();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ(file3_2, it->currentItem());

    it->next();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ(file3_3, it->currentItem());

    it->next();
    ASSERT_FALSE(it->isDone()); 
    ASSERT_EQ(folder05, it->currentItem());

    it->next();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ(file4_1, it->currentItem());
    
    it->next();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ(file4_2, it->currentItem());

    it->next();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ(file4_3, it->currentItem());

    it->next();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ(file4_4, it->currentItem());

    it->next();
    ASSERT_TRUE(it->isDone());

    delete it;

}





