#include <gtest/gtest.h>

#include "./parser_test.h"
#include "./db_test.h"

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}