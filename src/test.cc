#include <gtest/gtest.h>

#include <fstream>

#include "dna-algorithms/dna-algorithms.h"

TEST(RabinKarp, hiv_test_01) {
  const std::vector<size_t> expected_result = {65, 9150};

  std::string needle, haystack;
  std::ifstream haystack_input("tests/HIV-1_AF033819.3.txt");
  haystack_input >> haystack;
  haystack_input.close();

  needle = "AAGCCTCAATAAAGCTT";

  int q = 13;
  std::vector<size_t> res = DnaAlgorithm::RabinKarpSearch(needle, haystack, q);

  for (size_t i = 0; i < expected_result.size() && i < res.size(); i++)
    EXPECT_EQ(res.at(i), expected_result.at(i));
}

TEST(RabinKarp, empty_test_01) {
  std::string needle, haystack;
  std::ifstream haystack_input("tests/HIV-1_AF033819.3.txt");
  haystack_input >> haystack;
  haystack_input.close();

  int q = 13;
  std::vector<size_t> res = DnaAlgorithm::RabinKarpSearch(needle, haystack, q);

  EXPECT_EQ(res.size(), 0);
}

TEST(RabinKarp, empty_test_02) {
  std::string needle;
  std::string haystack;

  int q = 13;
  std::vector<size_t> res = DnaAlgorithm::RabinKarpSearch(needle, haystack, q);

  EXPECT_EQ(res.size(), 0);
}

TEST(RabinKarp, nw_sequence_alignment_test_01) {
  int match_s = 1, mismatch_s = -1, gap_s = -2;
  std::string str1 = "GGGCGACACTCCACCATAGA";
  std::string str2 = "GGCGACACCCACCATACAT";

  DnaAlgorithm::NwSequence res =
      DnaAlgorithm::NwSequenceAlignment(match_s, mismatch_s, gap_s, str1, str2);

  EXPECT_EQ(res.score, 10);
  EXPECT_EQ(res.str1, "GGGCGACACTCCACCATAGA-");
  EXPECT_EQ(res.str2, "GG-CGACAC-CCACCATACAT");
}

TEST(RabinKarp, regex_test_01) {
  std::string regex = "G?G*AC+A*A.";
  std::string text = "GGCGACACCCACCATACAT";

  bool res = DnaAlgorithm::RegExpr(regex, text);

  EXPECT_EQ(res, true);
}

TEST(RabinKarp, k_similar_test_01) {
  std::string str1 = "GGCGACACC";
  std::string str2 = "AGCCGCGAC";

  int res = DnaAlgorithm::KSimilar(str1, str2);

  EXPECT_EQ(res, 3);
}

TEST(RabinKarp, minimum_window_substr_test_01) {
  std::string str1 = "GGCGACACCCACCATACAT";
  std::string str2 = "TGT";

  std::string res = DnaAlgorithm::MinWindowSubstr(str1, str2);

  EXPECT_EQ(res, "GACACCCACCATACAT");
}

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
