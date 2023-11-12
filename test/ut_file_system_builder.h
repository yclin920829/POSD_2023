#include <gtest/gtest.h>

#include "../src/file.h"
#include "../src/folder.h"
#include "../src/tree_visitor.h"
#include "../src/file_system_scanner.h"
#include "../src/file_system_builder.h"
#include "../src/file_system_parser.h"

TEST(FileSystemBuilder, ping){
    ASSERT_TRUE(true);
}

TEST(FileSystemBuilder, parser){

    FileSystemBuilder * builder = new FileSystemBuilder();
    FileSystemParser * parser = new FileSystemParser(builder);

    parser->setPath("data/home");
    parser->parse();
    Folder * root = parser->getRoot();

    TreeVisitor * visitor = new TreeVisitor(OrderBy::Name);
    root->accept(visitor);

    string expected;
    expected += ".\n";
    expected += "├── Documents\n";
    expected += "│   ├── clean-architecture.pdf\n";
    expected += "│   ├── domain-driven-design.pub\n";
    expected += "│   ├── hello.txt\n";
    expected += "│   ├── note.txt\n";
    expected += "│   ├── object-oriented-analysis-and-design.pdf\n";
    expected += "│   └── programming\n";
    expected += "│       ├── cpp.pub\n";
    expected += "│       ├── oop.pdf\n";
    expected += "│       └── python.pub\n";
    expected += "├── Downloads\n";
    expected += "│   └── funny.png\n";
    expected += "├── hello.txt\n";
    expected += "└── my_profile\n";

    ASSERT_EQ(expected, visitor->getTree());
}

// TEST(FileSystemBuilder, scanner){

//     FileSystemScanner * scanner = new FileSystemScanner();

//     scanner->setPath("data/home");

//     ASSERT_EQ(scanner->currentNodeName(), "my_profile");
//     ASSERT_TRUE(scanner->isFile());
//     ASSERT_FALSE(scanner->isFolder());
//     ASSERT_FALSE(scanner->isDone());

//     scanner->nextNode();

//     ASSERT_EQ(scanner->currentNodeName(), "Documents");
//     ASSERT_FALSE(scanner->isFile());
//     ASSERT_TRUE(scanner->isFolder());
//     ASSERT_FALSE(scanner->isDone());

//     scanner->nextNode();

//     ASSERT_EQ(scanner->currentNodeName(), "Downloads");
//     ASSERT_FALSE(scanner->isFile());
//     ASSERT_TRUE(scanner->isFolder());
//     ASSERT_FALSE(scanner->isDone());

//     scanner->nextNode();

//     ASSERT_EQ(scanner->currentNodeName(), "hello.txt");
//     ASSERT_TRUE(scanner->isFile());
//     ASSERT_FALSE(scanner->isFolder());
//     ASSERT_FALSE(scanner->isDone());

//     scanner->nextNode();

//     ASSERT_TRUE(scanner->isDone());
// }

TEST(FileSystemBuilder, builder){

    FileSystemBuilder * builder = new FileSystemBuilder();

    builder->buildFolder("data/home");
    ASSERT_EQ(builder->getRoot()->name(), "home");

    builder->buildFile("data/home/my_profile");
    ASSERT_EQ(builder->getRoot()->getChildByName("my_profile")->name(), "my_profile");

    builder->buildFolder("data/home/Documents");
    ASSERT_EQ(builder->getRoot()->name(), "Documents");

    builder->endFolder();
    ASSERT_EQ(builder->getRoot()->name(), "home");

    builder->buildFolder("data/home/Downloads");
    ASSERT_EQ(builder->getRoot()->name(), "Downloads");

    builder->endFolder();
    ASSERT_EQ(builder->getRoot()->name(), "home");

    builder->buildFile("data/home/hello.txt");
    ASSERT_EQ(builder->getRoot()->getChildByName("hello.txt")->name(), "hello.txt");

    builder->endFolder();
    ASSERT_EQ(builder->getRoot()->name(), "home");

    TreeVisitor * visitor = new TreeVisitor(OrderBy::Name);
    builder->getRoot()->accept(visitor);

    string expected;
    expected += ".\n";
    expected += "├── Documents\n";
    expected += "├── Downloads\n";
    expected += "├── hello.txt\n";
    expected += "└── my_profile\n";

    ASSERT_EQ(expected, visitor->getTree());
}