#include <gtest/gtest.h>

#include "../src/beautify_visitor.h"

TEST(VisitorTest, ping){
    ASSERT_TRUE(true);
}

TEST(VisitorTest, normal) {
    JsonObject *example = new JsonObject;
    JsonObject *books = new JsonObject;
    JsonObject *clean_code = new JsonObject;
    JsonObject *design_pattern = new JsonObject;
    Value * v1 = new StringValue("Robert C. Martin");
    clean_code->set("author", v1);
    Value * v2 = new StringValue("Clean Code");
    clean_code->set("name", v2);
    Value * v3 = new StringValue("Erich Gamma, Richard Helm, Ralph Johnson, John Vlissides");
    design_pattern->set("author", v3);
    Value * v4 = new StringValue("Design Patterns Elements of Reusable Object-Oriented Software");
    design_pattern->set("name", v4);

    books->set("clean code", clean_code);
    books->set("design pattern", design_pattern);

    example->set("books", books);

    BeautifyVisitor * visitor = new BeautifyVisitor();

    example->accept(visitor);
}

TEST(VisitorTest, BeautifyVisitor) {
    std::string expect = "{\n    \"desc\": \"Product\",\n    \"id\": \"10\",\n    \"isDeleted\": \"false\"\n}";

    JsonObject *example = new JsonObject;
    Value * v1 = new StringValue("Product");
    example->set("desc", v1);
    Value * v2 = new StringValue("10");
    example->set("id", v2);
    Value * v3 = new StringValue("false");
    example->set("isDeleted", v3);

    BeautifyVisitor * visitor = new BeautifyVisitor();
    
    example->accept(visitor);

    ASSERT_EQ(expect, visitor->getResult());
}

TEST(VisitorTest, BeautifyVisitorWithComposed) {
    std::string expect = "{\n    \"books\": {\n        \"clean code\": {\n            \"author\": \"Robert C. Martin\",\n            \"name\": \"Clean Code\"\n        },\n        \"design patterns\": {\n            \"author\": \"Erich Gamma, Richard Helm, Ralph Johnson, and John Vlissides\",\n            \"name\": \"Design Patterns: Elements of Reusable Object-Oriented Software\"\n        }\n    }\n}";

    JsonObject *example = new JsonObject;
    JsonObject *books = new JsonObject;
    JsonObject *clean_code = new JsonObject;
    JsonObject *design_pattern = new JsonObject;
    Value * v1 = new StringValue("Robert C. Martin");
    clean_code->set("author", v1);
    Value * v2 = new StringValue("Clean Code");
    clean_code->set("name", v2);
    Value * v3 = new StringValue("Erich Gamma, Richard Helm, Ralph Johnson, and John Vlissides");
    design_pattern->set("author", v3);
    Value * v4 = new StringValue("Design Patterns: Elements of Reusable Object-Oriented Software");
    design_pattern->set("name", v4);

    books->set("clean code", clean_code);
    books->set("design patterns", design_pattern);

    example->set("books", books);

    BeautifyVisitor * visitor = new BeautifyVisitor();

    example->accept(visitor);

    ASSERT_EQ(expect, visitor->getResult());
}