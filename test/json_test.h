#include "../src/json_object.h"
#include "../src/string_value.h"

TEST(JSonSuite, OneKeyStringValue) {
    JsonObject *jo = new JsonObject;
    Value * v1 = new StringValue("value1");
    jo->set("key1", v1);
    ASSERT_EQ(v1, jo->getValue("key1"));
    ASSERT_EQ("{\n\"key1\":\"value1\"\n}", jo->toString());

}

TEST(JSonSuite, TwoKeyStringValue) {
    JsonObject *jo = new JsonObject;
    Value * v1 = new StringValue("value1");
    jo->set("key1", v1);
    Value * v2 = new StringValue("value2");
    jo->set("key2", v2);
    ASSERT_EQ("\"value1\"", jo->getValue("key1")->toString());
    ASSERT_EQ("\"value2\"", jo->getValue("key2")->toString());
    ASSERT_EQ("{\n\"key1\":\"value1\",\n\"key2\":\"value2\"\n}", jo->toString());

}

TEST(JSonSuite, Composite) {
    JsonObject *jo = new JsonObject;
    Value * v1 = new StringValue("value1");
    jo->set("key1", v1);
    Value * v2 = new StringValue("value2");
    jo->set("key2", v2);

    JsonObject *j_composite = new JsonObject;
    j_composite->set("keyc", jo);
    ASSERT_EQ(jo, j_composite->getValue("keyc"));
    ASSERT_EQ("{\n\"keyc\":{\n\"key1\":\"value1\",\n\"key2\":\"value2\"\n}\n}", j_composite->toString());
}

// {
//     "books": {
//         "clean code": {
//             "author": "Robert C. Martin",
//             "name": "Clean Code"
//         },
//         "design pattern": {
//             "author": "Erich Gamma, Richard Helm, Ralph Johnson, John Vlissides",
//             "name": "Design Patterns Elements of Reusable Object-Oriented Software"
//         }
//     }
// }

// TEST(JSonSuite, example){
//     JsonObject *example = new JsonObject;
//     JsonObject *books = new JsonObject;
//     JsonObject *clean_code = new JsonObject;
//     JsonObject *design_pattern = new JsonObject;
//     Value * v1 = new StringValue("Robert C. Martin");
//     clean_code->set("author", v1);
//     Value * v2 = new StringValue("Clean Code");
//     clean_code->set("name", v2);
//     Value * v3 = new StringValue("Erich Gamma, Richard Helm, Ralph Johnson, John Vlissides");
//     design_pattern->set("author", v3);
//     Value * v4 = new StringValue("Design Patterns Elements of Reusable Object-Oriented Software");
//     design_pattern->set("name", v4);

//     books->set("clean code", clean_code);
//     books->set("design pattern", design_pattern);

//     example->set("books", books);

//     std::cout << example->toString() << "\n";
// }

