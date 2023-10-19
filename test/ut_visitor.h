#pragma once

#include <string>
#include <iostream>
#include <gtest/gtest.h>

#include "../src/node.h"
#include "../src/file.h"
#include "../src/folder.h"
#include "../src/find_by_name_visitor.h"
#include "../src/stream_out_visitor.h"

TEST(Visitor, Ping){
    ASSERT_TRUE(true);
}

TEST(Visitor, visit_a_file){

    File * file01 = new File("./folder01/file01.txt");

    FindByNameVisitor * findByNameVisitor = new FindByNameVisitor("file01.txt");

    file01->accept(findByNameVisitor);

    ASSERT_EQ(1, findByNameVisitor->getPaths().size());
    ASSERT_EQ("./folder01/file01.txt", findByNameVisitor->getPaths().front());
    
}

TEST(Visitor, visit_a_folder){

    Folder * folder01 = new Folder("./folder01");

    FindByNameVisitor * findByNameVisitor = new FindByNameVisitor("folder01");

    folder01->accept(findByNameVisitor);

    ASSERT_EQ(1, findByNameVisitor->getPaths().size());
    ASSERT_EQ("./folder01", findByNameVisitor->getPaths().front());
}

TEST(Visitor, visit_a_file_under_a_folder){

    Folder * folder01 = new Folder("./folder01");
    Folder * folder02 = new Folder("./folder01/folder02");
    Folder * folder03 = new Folder("./folder01/folder02/folder03");


    File * file01 = new File("./folder01/file01.txt");
    File * file02 = new File("./folder01/file02.txt");
    File * file03 = new File("./folder01/folder02/file03.txt");
    File * file04 = new File("./folder01/folder02/file04.txt");
    File * file05 = new File("./folder01/folder02/folder03/file05.txt");

    folder01->add(file01);
    folder01->add(file02);
    folder01->add(folder02);
    folder02->add(file03);
    folder02->add(file04);
    folder02->add(folder03);
    folder03->add(file05);

    FindByNameVisitor * findByNameVisitor = new FindByNameVisitor("file03.txt");
    // FindByNameVisitor * findByNameVisitor = new FindByNameVisitor("file05.txt");


    folder01->accept(findByNameVisitor);

    ASSERT_EQ(1, findByNameVisitor->getPaths().size());
    ASSERT_EQ("./folder01/folder02/file03.txt", findByNameVisitor->getPaths().front());
    // ASSERT_EQ("./folder01/folder02/folder03/file05.txt", findByNameVisitor->getPaths().front());
}

TEST(Visitor, stream_out_a_file){

    string path = "./folder01/file01.txt";
    File * file01 = new File(path);

    StreamOutVisitor * streamOutVisitor = new StreamOutVisitor();

    file01->accept(streamOutVisitor);

    // std:: cout << streamOutVisitor->getResult() << std::endl;

    std::string content = "_____________________________________________\n"
                          "./folder01/file01.txt\n"
                          "---------------------------------------------\n"
                          "Hello,\n"
                          "this is file 01\n"
                          "\n"
                          "see you soon\n"
                          "_____________________________________________\n";

    // std::cout << "content:\n" << content << std::endl;

    ASSERT_EQ(content, streamOutVisitor->getResult()); 
}

TEST(Visitor, stream_out_a_folder){

    Folder * folder01 = new Folder("./folder01");
    Folder * folder02 = new Folder("./folder01/folder02");
    Folder * folder03 = new Folder("./folder01/folder02/folder03");
    File * file01 = new File("./folder01/file01.txt");
    File * file02 = new File("./folder01/file02.txt");
    File * file03 = new File("./folder01/folder02/file03.txt");
    File * file04 = new File("./folder01/folder02/file04.txt");
    File * file05 = new File("./folder01/folder02/folder03/file05.txt");

    folder01->add(file01);
    folder01->add(file02);
    folder01->add(folder02);
    folder02->add(file03);
    folder02->add(file04);
    folder02->add(folder03);
    folder03->add(file05);

    // cout << "folder01->numberOfFiles(): " << folder01->numberOfFiles() << endl;

    StreamOutVisitor * streamOutVisitor = new StreamOutVisitor();

    folder01->accept(streamOutVisitor);

    std::string content = "_____________________________________________\n"
                          "./folder01/file01.txt\n"
                          "---------------------------------------------\n"
                          "Hello,\n"
                          "this is file 01\n"
                          "\n"
                          "see you soon\n"
                          "_____________________________________________\n"
                          "\n"
                          "_____________________________________________\n"
                          "./folder01/file02.txt\n"
                          "---------------------------------------------\n"
                          "Hello,\n"
                          "this is file 02\n"
                          "\n"
                          "see you soon\n"
                          "_____________________________________________\n"
                          "\n"
                          "_____________________________________________\n"
                          "./folder01/folder02/file03.txt\n"
                          "---------------------------------------------\n"
                          "Hello,\n"
                          "this is file 03\n"
                          "\n"
                          "see you soon\n"
                          "_____________________________________________\n"
                          "\n"
                          "_____________________________________________\n"
                          "./folder01/folder02/file04.txt\n"
                          "---------------------------------------------\n"
                          "Hello,\n"
                          "this is file 04\n"
                          "\n"
                          "see you soon\n"
                          "_____________________________________________\n"
                          "\n"
                          "_____________________________________________\n"
                          "./folder01/folder02/folder03/file05.txt\n"
                          "---------------------------------------------\n"
                          "Hello,\n"
                          "this is file 05\n"
                          "\n"
                          "see you soon\n"
                          "_____________________________________________\n"
                          "\n";



    // std::cout << "content:\n" << content << std::endl;
    // std:: cout << streamOutVisitor->getResult() << std::endl;



    ASSERT_EQ(content, streamOutVisitor->getResult()); 
}
