#include <gtest/gtest.h>

#include <iostream>

TEST(IteratorTest, ping){
    ASSERT_TRUE(true);
}

TEST(IteratorTest, normal){
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