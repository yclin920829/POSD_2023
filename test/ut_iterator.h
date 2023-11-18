#include <gtest/gtest.h>

TEST(IteratorTest, ping){
    ASSERT_TRUE(true);
}

TEST(IteratorTest, Nomal) {

    JsonObject *jo = new JsonObject;
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

    jo->set("books", books);

    JsonIterator * it = jo->createIterator();

    it->first();
    ASSERT_EQ("books", it->currentKey());
    ASSERT_EQ(books, it->currentValue());
    ASSERT_EQ(books->toString(), it->currentValue()->toString());
    ASSERT_FALSE(it->isDone());

    it->next();
    ASSERT_TRUE(it->isDone());
}

TEST(IteratorTest, StringValue){
    JsonObject *jo = new JsonObject;
    Value * v1 = new StringValue("value1");
    jo->set("key1", v1);
    Value * v2 = new StringValue("value2");
    jo->set("key2", v2);

    JsonIterator * it = jo->createIterator();

    it->first();
    ASSERT_EQ("key1", it->currentKey());
    ASSERT_EQ(v1, it->currentValue());
    ASSERT_FALSE(it->isDone());

    it->next();
    ASSERT_EQ("key2", it->currentKey());
    ASSERT_EQ(v2, it->currentValue());
    ASSERT_FALSE(it->isDone());

    it->next();
    ASSERT_TRUE(it->isDone());
}
