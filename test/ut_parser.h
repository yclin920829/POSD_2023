#include <gtest/gtest.h>

#include <iostream>

#include "../src/json_builder.h"
#include "../src/json_parser.h"
#include "../src/json_scanner.h"

TEST(ParserTest, ping){
    ASSERT_TRUE(true);
}

TEST(ParserTest, parser){

    JsonBuilder * builder = new JsonBuilder();
    JsonScanner * scanner = new JsonScanner();
    JsonParser * parser = new JsonParser(scanner, builder);

    std::string input = "{\"keyc\":{\"key1\":\"value1\",\"key2\":\"value2\"}}";
    std::cout<< "input: \n" << input << "\n\n";
    parser->setInput(input);

    parser->parse();

    // std::cout << "---------------test---------------\n";
    // std::cout << parser->getJsonObject()->toString() << "\n";
    ASSERT_EQ("{\n\"keyc\":{\n\"key1\":\"value1\",\n\"key2\":\"value2\"\n}\n}", parser->getJsonObject()->toString());
}
