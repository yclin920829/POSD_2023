#include <gtest/gtest.h>

#include "./folder_test.h"
#include "./file_test.h"
#include "./iterator_test.h"

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
