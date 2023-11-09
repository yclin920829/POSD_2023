#include <gtest/gtest.h>
#include <iostream>

#include "../src/file.h"
#include "../src/folder.h"
#include "../src/tree_visitor.h"
#include "../src/file_system_scanner.h"
#include "../src/file_system_builder.h"
#include "../src/file_system_parser.h"


#include "../src/node.h"

TEST(FileSystemBuilder, ping){
    ASSERT_TRUE(true);
}

// TEST(FileSystemBuilder, scanner){

//     FileSystemScanner * scanner = new FileSystemScanner();

//     for (scanner->setPath("data/home"); !scanner->isDone(); scanner->nextNode()){
//         std::cout << scanner->currentNodeName() << "  ";
//         if (scanner->isFile()){
//             std::cout << "is a file." << std::endl;
//         }else if (scanner->isFolder()){
//             std::cout << "is a folder." << std::endl;
//         }
//     }
// }

TEST(FileSystemBuilder, parser){

    FileSystemBuilder * builder = new FileSystemBuilder();

    FileSystemParser * parser = new FileSystemParser(builder);
    parser->setPath("data/home");
    parser->parse();


    std::cout << "-----------------------------------------------------------------" << std::endl;

    Folder * root = parser->getRoot();

    cout << root->name() << endl;
    cout << root->numberOfFiles() << endl;

    TreeVisitor * visitor = new TreeVisitor(OrderBy::Name);
    root->accept(visitor);

    // setPath
    // parse
    // getRoot
}

// gerRoot
// buildFile ok
// buildFolder ok
// endFolder


