#include <gtest/gtest.h>

#include <iostream>

#include "../src/json_builder.h"
#include "../src/json_parser.h"
#include "../src/json_scanner.h"
#include "../src/beautify_visitor.h"

TEST(ParserTest, ping){
    ASSERT_TRUE(true);
}

TEST(ParserTest, parser){

    JsonBuilder * builder = new JsonBuilder();
    JsonScanner * scanner = new JsonScanner();
    JsonParser * parser = new JsonParser(scanner, builder);

    std::string input = "{\"keyc\":{\"key1\":\"value1\",\"key2\":\"value2\"}}";
    // std::cout<< "input: \n" << input << "\n\n";
    parser->setInput(input);

    parser->parse();

    // std::cout << "---------------test---------------\n";
    // std::cout << parser->getJsonObject()->toString() << "\n";
    ASSERT_EQ("{\n\"keyc\":{\n\"key1\":\"value1\",\n\"key2\":\"value2\"\n}\n}", parser->getJsonObject()->toString());
}

TEST(ParserTest, WithBeautify){

    JsonBuilder * builder = new JsonBuilder();
    JsonScanner * scanner = new JsonScanner();
    JsonParser * parser = new JsonParser(scanner, builder);

    std::string input = "{\"books\": {\"clean code\": {\"author\": \"Robert C. Martin\",\"name\": \"Clean Code\"},\"design patterns\": {\"author\": \"Erich Gamma, Richard Helm, Ralph Johnson, and John Vlissides\",\"name\": \"Design Patterns: Elements of Reusable Object-Oriented Software\"}}}";

    parser->setInput(input);

    parser->parse();

    std::string expected = "{\n    \"books\": {\n        \"clean code\": {\n            \"author\": \"Robert C. Martin\",\n            \"name\": \"Clean Code\"\n        },\n        \"design patterns\": {\n            \"author\": \"Erich Gamma, Richard Helm, Ralph Johnson, and John Vlissides\",\n            \"name\": \"Design Patterns: Elements of Reusable Object-Oriented Software\"\n        }\n    }\n}";
    std::string my_jenkins_code = "{\n    \"design patterns\": {\n        \"author\": \"Erich Gamma, Richard Helm, Ralph Johnson, and John Vlissides\",\n        \"clean code\": {\n            \"author\": \"Robert C. Martin\",\n            \"name\": \"Clean Code\"\n        },\n        \"name\": \"Design Patterns: Elements of Reusable Object-Oriented Software\"\n    }\n}";

    BeautifyVisitor * visitor = new BeautifyVisitor();
    parser->getJsonObject()->accept(visitor);

    std::cout << "---------------input---------------\n";
    std::cout << input << "\n";
    std::cout << "---------------expected---------------\n";
    std::cout << expected << "\n";
    std::cout << "---------------my_jenkins_code---------------\n";
    std::cout << my_jenkins_code << "\n";
    std::cout << "---------------my_code_withBeauty---------------\n";
    std::cout << visitor->getResult() << "\n";
    std::cout << "---------------my_code_toString---------------\n";
    std::cout << parser->getJsonObject()->toString() << "\n";
    std::cout << "\n";

    ASSERT_EQ(expected, visitor->getResult());
}