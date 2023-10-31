#include <iostream>
#include <gtest/gtest.h>

#include "../src/node.h"
#include "../src/folder.h"
#include "../src/file.h"

class OrderByTest: public ::testing::Test {
protected:
    virtual void SetUp() {
        home = new Folder("data/home");

        // node under home
        document = new Folder("data/home/Documents");
        download = new Folder("data/home/Downloads");
        home_hello = new File("data/home/hello.txt");
        profile = new File("data/home/my_profile");

        // node under document
        ca = new File("data/home/Documents/clean-architecture.pdf");
        ddd = new File("data/home/Documents/domain-driven-design.pdf");
        document_hello = new File("data/home/Documents/hello.txt");
        note = new File("data/home/Documents/note.txt");
        ooad = new File("data/home/Documents/object-oriented-analysis-and-design.pdf");
        programming = new Folder("data/home/Documents/programming");

        // node under programming
        cpp = new File("data/home/Documents/programming/cpp.pdf");
        oop = new File("data/home/Documents/programming/oop.pdf");
        python = new File("data/home/Documents/programming/python.pdf");

        // node under download
        funny = new File("data/home/Downloads/funny.png");


        // add
        home->add(profile);
        home->add(document);
        home->add(home_hello);
        home->add(download);
        
        document->add(ca);
        document->add(document_hello);
        document->add(programming);
        document->add(ooad);
        document->add(ddd);
        document->add(note);

        programming->add(oop);
        programming->add(python);
        programming->add(cpp);

        download->add(funny);

    }

    void TearDown() {
        delete home;

        delete document;
        delete download;
        delete home_hello;
        delete profile;

        delete ca;
        delete ddd;
        delete document_hello;
        delete note;
        delete ooad;
        delete programming;

        delete cpp;
        delete oop;
        delete python;

        delete funny;
    }
    
    Node * home;

    Node * document;
    Node * download;
    Node * home_hello;
    Node * profile;

    Node * ca;
    Node * ddd;
    Node * document_hello;
    Node * note;
    Node * ooad;
    Node * programming;

    Node * cpp;
    Node * oop;
    Node * python;

    Node * funny;
    
    
};

TEST_F(OrderByTest, OrderByNormal) {
    
    Iterator * it = home->createIterator(OrderBy::Normal);
    it->first();
    ASSERT_FALSE(it->isDone());
    
    ASSERT_EQ("my_profile", it->currentItem()->name());
    
    it->next();
    ASSERT_EQ("Documents", it->currentItem()->name());

    it->next();
    ASSERT_EQ("hello.txt", it->currentItem()->name());

    it->next();
    ASSERT_EQ("Downloads", it->currentItem()->name());

    it->next();
    ASSERT_TRUE(it->isDone());

}

TEST_F(OrderByTest, OrderByName) {
    
    Iterator * it = home->createIterator(OrderBy::Name);

    for (it->first(); !it->isDone(); it->next()) {
        std::cout << it->currentItem()->name() << std::endl;
    }
    

}





