#pragma once

#include <string>
#include <iostream>

#include "../src/node.h"
#include "../src/file.h"
#include "../src/folder.h"
#include "../src/find_by_name_visitor.h"

TEST(Visitor, Ping){
    ASSERT_TRUE(true);
}

TEST(Visitor, visit_a_file){
    cout << "\n";
    
    File * file01 = new File("/Folder01/File01");

    FindByNameVisitor * findByNameVisitor = new FindByNameVisitor("File01");

    file01->accept(findByNameVisitor);

    ASSERT_EQ(1, findByNameVisitor->getPaths().size());
    ASSERT_EQ("/Folder01/File01", findByNameVisitor->getPaths().front());

    // delete file01;
    // delete findByNameVisitor;

    cout << "\n";
}

TEST(Visitor, visit_a_folder){
    cout << "\n";

    Folder * folder01 = new Folder("/Folder01");

    FindByNameVisitor * findByNameVisitor = new FindByNameVisitor("Folder01");

    folder01->accept(findByNameVisitor);

    ASSERT_EQ(1, findByNameVisitor->getPaths().size());
    ASSERT_EQ("/Folder01", findByNameVisitor->getPaths().front());

    cout << "\n";
}

TEST(Visitor, visit_a_file_under_a_folder){
    Folder * folder01 = new Folder("/Folder01");

    File * file01 = new File("/Folder01/File01");
    File * file02 = new File("/Folder01/File02");
    File * file03 = new File("/Folder01/File03");
    File * file04 = new File("/Folder01/File04");
    File * file05 = new File("/Folder01/File05");

    folder01->add(file01);
    folder01->add(file02);
    folder01->add(file03);
    folder01->add(file04);
    folder01->add(file05);

    FindByNameVisitor * findByNameVisitor = new FindByNameVisitor("File03");

    folder01->accept(findByNameVisitor);

    ASSERT_EQ(1, findByNameVisitor->getPaths().size());
    ASSERT_EQ("/Folder01/File03", findByNameVisitor->getPaths().front());

    ASSERT_TRUE(true);
}