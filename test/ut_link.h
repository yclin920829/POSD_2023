#include <gtest/gtest.h>

#include "../src/file.h"
#include "../src/link.h"
#include "../src/folder.h"

using namespace std;

// TODO: add more tests
TEST(Link, LinkToFile) {
    File * file = new File("./structure/file.txt");
    Link * link = new Link("link", file);
    ASSERT_EQ(1, link->numberOfFiles());
    ASSERT_EQ(file, link->getTarget());
    ASSERT_EQ(file, link->find("./structure/file.txt"));
    ASSERT_EQ(nullptr, link->find("not_exist"));
}
