#include <gtest/gtest.h>

#include "../src/file.h"
#include "../src/link.h"
#include "../src/folder.h"

using namespace std;

TEST(Link, LinkToFile) {
    File * file = new File("./structure/file.txt");
    Link * link = new Link("./structure/fileLink.txt", file);

    ASSERT_EQ("fileLink.txt", link->name());
    ASSERT_EQ("./structure/fileLink.txt", link->path());
    ASSERT_EQ(file->numberOfFiles(), link->numberOfFiles());
    ASSERT_EQ(file, link->find("./structure/file.txt"));
    ASSERT_EQ(file, link->getTarget());
    ASSERT_EQ(file->name(), link->getTarget()->name());
    ASSERT_EQ(file->path(), link->getTarget()->path());

    std::list<string> result = link->findByName("file.txt");
    ASSERT_EQ(1, result.size());
    ASSERT_EQ(file->path(), *(result.begin()));

    delete file;
    delete link;
}

TEST(Link, LinkToFolder) {
    Folder * home = new Folder("./structure/home");
    Folder * document = new Folder("./structure/home/Documents");
    File * my_profile = new File("./structure/home/my_profile");
    File * hello = new File("./structure/home/Documents/hello.txt");

    home->add(document);
    home->add(my_profile);
    document->add(hello);

    Link * link = new Link("./structure/homeLink", home);

    ASSERT_EQ("homeLink", link->name());
    ASSERT_EQ("./structure/homeLink", link->path());
    ASSERT_EQ(2, link->numberOfFiles());
    ASSERT_EQ(hello, link->find("./structure/home/Documents/hello.txt"));
    ASSERT_EQ(home, link->getTarget());
    ASSERT_EQ(home->name(), link->getTarget()->name());
    ASSERT_EQ(home->path(), link->getTarget()->path());
    ASSERT_EQ(home->numberOfFiles(), link->getTarget()->numberOfFiles());
   
   std::list<string> result = link->findByName("hello.txt");
    ASSERT_EQ(1, result.size());
    ASSERT_EQ(hello->path(), *(result.begin()));

    delete home;
    delete link;
}