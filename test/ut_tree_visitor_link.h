#include <iostream>
#include <gtest/gtest.h>

#include "../src/order_by.h"
#include "../src/tree_visitor.h"
#include "../src/iterator_factories.h"

class TreeVisitorTestLink: public ::testing::Test {
protected:
    void SetUp() {

        home = new Folder("structure2/home");

        profile = new File("structure2/home/my_profile");
        home->add(profile);

        hello = new File("structure2/home/hello.txt");
        home->add(hello);

        download = new Folder("structure2/home/Downloads");
        home->add(download);
        funny = new File("structure2/home/Downloads/funny.png");
        download->add(funny);

        document = new Folder("structure2/home/Documents");
        home->add(document);

        note = new File("structure2/home/Documents/note.txt");
        document->add(note);
        hello2 = new File("structure2/home/Documents/hello.txt");
        document->add(hello2);

        programming = new Folder("structure2/home/Documents/programming");
        document->add(programming);
        cpp = new File("structure2/home/Documents/programming/cpp.pub");
        programming->add(cpp);
        oop = new File("structure2/home/Documents/programming/oop.pdf");
        programming->add(oop);
        python = new File("structure2/home/Documents/programming/python.pub");
        programming->add(python);

        ddd = new File("structure2/home/Documents/domain-driven-design.pub");
        document->add(ddd);
        ca = new File("structure2/home/Documents/clean-architecture.pdf");
        document->add(ca);
        ooad = new File("structure2/home/Documents/object-oriented-analysis-and-design.pdf");
        document->add(ooad);
    }
    
    void TearDown() {
        delete home;
        profile = nullptr;
        hello = nullptr;
        download = nullptr;
        funny = nullptr;
        document = nullptr;
        note = nullptr;
        hello2 = nullptr;
        programming = nullptr;
        cpp = nullptr;
        oop = nullptr;
        python = nullptr;
        ddd = nullptr;
        ca = nullptr;
        ooad = nullptr;

        delete homeLink;
        delete profileLink;
        delete helloLink;
        delete downloadLink;
        delete funnyLink;
        delete documentLink;
        delete noteLink;
        delete hello2Link;
        delete programmingLink;
        delete cppLink;
        delete oopLink;
        delete pythonLink;
        delete dddLink;
        delete caLink;
        delete ooadLink;
    }
    
    Node * home;
    Node * profile;
    Node * hello;
    Node * download;
    Node * funny;
    Node * document;
    Node * note;
    Node * hello2;
    Node * programming;
    Node * cpp;
    Node * oop;
    Node * python;
    Node * ddd;
    Node * ca;
    Node * ooad;

    Link * homeLink;
    Link * profileLink;
    Link * helloLink;
    Link * downloadLink;
    Link * funnyLink;
    Link * documentLink;
    Link * noteLink;
    Link * hello2Link;
    Link * programmingLink;
    Link * cppLink;
    Link * oopLink;
    Link * pythonLink;
    Link * dddLink;
    Link * caLink;
    Link * ooadLink;
};

TEST_F(TreeVisitorTestLink, ping) {
    Node * home = new Folder("structure2/home");
    Link * homeLink = new Link("structure2/home", home);

    Node * profile = new File("structure2/home/my_profile2");

    ASSERT_EQ(1, 1);

}

// TEST_F(TreeVisitorTestLink, OrderByName) {
//     string expected = 
//     ".\n"
//     "└── my_profile\n";

//     TreeVisitor * tree = new TreeVisitor(OrderByNameIteratorFactory::instance());
//     homeLink->accept(tree);
//     string result = tree->getTree();

//     ASSERT_EQ(expected, result);

//     delete tree;
// }


// TEST_F(TreeVisitorTest, OrderByNameWithFolderFirst) {
//     string expected = 
//     ".\n"
//     "├── Documents\n"
//     "│   ├── programming\n"
//     "│   │   ├── cpp.pub\n"
//     "│   │   ├── oop.pdf\n"
//     "│   │   └── python.pub\n"
//     "│   ├── clean-architecture.pdf\n"
//     "│   ├── domain-driven-design.pub\n"
//     "│   ├── hello.txt\n"
//     "│   ├── note.txt\n"
//     "│   └── object-oriented-analysis-and-design.pdf\n"
//     "├── Downloads\n"
//     "│   └── funny.png\n"
//     "├── hello.txt\n"
//     "└── my_profile\n";

//     TreeVisitor * tree = new TreeVisitor(OrderByNameWithFolderFirstIteratorFactory::instance());
//     home->accept(tree);
//     string result = tree->getTree();

//     ASSERT_EQ(expected, result);

//     delete tree;
// }

// TEST_F(TreeVisitorTest, OrderByKind) {
//     string expected = 
//     ".\n"
//     "├── my_profile\n"
//     "├── Documents\n"
//     "│   ├── programming\n"
//     "│   │   ├── oop.pdf\n"
//     "│   │   ├── cpp.pub\n"
//     "│   │   └── python.pub\n"
//     "│   ├── clean-architecture.pdf\n"
//     "│   ├── object-oriented-analysis-and-design.pdf\n"
//     "│   ├── domain-driven-design.pub\n"
//     "│   ├── hello.txt\n"
//     "│   └── note.txt\n"
//     "├── Downloads\n"
//     "│   └── funny.png\n"
//     "└── hello.txt\n";

//     TreeVisitor * tree = new TreeVisitor(OrderByKindIteratorFactory::instance());
//     home->accept(tree);
//     string result = tree->getTree();

//     ASSERT_EQ(expected, result);

//     delete tree;
// }