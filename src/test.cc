#include <gtest/gtest.h>

#include <fstream>

#include "DnaAlgorithms.h"

TEST(lslsdl_test, hellp) {
  const std::vector<size_t> expected_result = {65, 9150};

  std::string needle, haystack;
  std::ifstream haystack_input("tests/HIV-1_AF033819.3.txt");
  haystack_input >> haystack;
  haystack_input.close();

  needle = "AAGCCTCAATAAAGCTT";

  int q = 13;
  std::vector<size_t> res = DnaAlgorithm::RabinKarpSearch(needle, haystack, q);

  for (size_t i = 0; i < expected_result.size() && i < res.size(); i++) {
    EXPECT_EQ(res.at(i), expected_result.at(i));
  }
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
