#include <gtest/gtest.h>

#include <iostream>
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

    // std::cout << "---------------test---------------\n";
    // std::cout << visitor->getResult();

}