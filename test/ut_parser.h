#include <gtest/gtest.h>

#include "../src/json_builder.h"
#include "../src/json_parser.h"
#include "../src/json_scanner.h"
#include "../src/beautify_visitor.h"

TEST(ParserTest, ping){
    ASSERT_TRUE(true);
}

TEST(ParserTest, ParseObject){

    JsonBuilder * builder = new JsonBuilder();
    JsonScanner * scanner = new JsonScanner();
    JsonParser * parser = new JsonParser(scanner, builder);

    std::string input = "{\"keyc\":{\"key1\":\"value1\",\"key2\":\"value2\"}}";
    std::string expected = "{\n\"keyc\":{\n\"key1\":\"value1\",\n\"key2\":\"value2\"\n}\n}";

    parser->setInput(input);
    parser->parse();

    ASSERT_EQ(expected, parser->getJsonObject()->toString());
}

TEST(ParserTest, ParseObjectWithSpaces){
    
    JsonBuilder * builder = new JsonBuilder();
    JsonScanner * scanner = new JsonScanner();
    JsonParser * parser = new JsonParser(scanner, builder);

    std::string input = "{       \"keyc\" : {       \"key1\"     :     \"value1\"           , \"key2\" :         \"value2\"     }         }";
    std::string expected = "{\n\"keyc\":{\n\"key1\":\"value1\",\n\"key2\":\"value2\"\n}\n}";
    
    parser->setInput(input);
    parser->parse();

    ASSERT_EQ("{\n\"keyc\":{\n\"key1\":\"value1\",\n\"key2\":\"value2\"\n}\n}", parser->getJsonObject()->toString());
}

TEST(ParserTest, ParseObjectWithinner){
        
    JsonBuilder * builder = new JsonBuilder();
    JsonScanner * scanner = new JsonScanner();
    JsonParser * parser = new JsonParser(scanner, builder);

    std::string input = "{\"books\": {\"clean code\": {\"author\": \"Robert C. Martin\",\"name\": \"Clean Code\"},\"design patterns\": {\"author\": \"Erich Gamma, Richard Helm, Ralph Johnson, and John Vlissides\",\"name\": \"Design Patterns Elements of Reusable Object-Oriented Software\"}}}";
    std::string expected = "{\n\"books\":{\n\"clean code\":{\n\"author\":\"Robert C. Martin\",\n\"name\":\"Clean Code\"\n},\n\"design patterns\":{\n\"author\":\"Erich Gamma, Richard Helm, Ralph Johnson, and John Vlissides\",\n\"name\":\"Design Patterns Elements of Reusable Object-Oriented Software\"\n}\n}\n}";
    
    parser->setInput(input);
    parser->parse();

    ASSERT_EQ(expected, parser->getJsonObject()->toString());
}

TEST(ParserTest, WithBeautify){

    JsonBuilder * builder = new JsonBuilder();
    JsonScanner * scanner = new JsonScanner();
    JsonParser * parser = new JsonParser(scanner, builder);

    std::string input = "{\"books\": {\"clean code\": {\"author\": \"Robert C. Martin\",\"name\": \"Clean Code\"},\"design patterns\": {\"author\": \"Erich Gamma, Richard Helm, Ralph Johnson, and John Vlissides\",\"name\": \"Design Patterns Elements of Reusable Object-Oriented Software\"}}}";
    std::string expected = "{\n    \"books\": {\n        \"clean code\": {\n            \"author\": \"Robert C. Martin\",\n            \"name\": \"Clean Code\"\n        },\n        \"design patterns\": {\n            \"author\": \"Erich Gamma, Richard Helm, Ralph Johnson, and John Vlissides\",\n            \"name\": \"Design Patterns Elements of Reusable Object-Oriented Software\"\n        }\n    }\n}";
    
    parser->setInput(input);
    parser->parse();

    BeautifyVisitor * visitor = new BeautifyVisitor();
    parser->getJsonObject()->accept(visitor);

    ASSERT_EQ(expected, visitor->getResult());
}
