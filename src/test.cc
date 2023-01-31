#include <gtest/gtest.h>

#include <fstream>

#include "dna-algorithms/dna-algorithms.h"

TEST(Correct_sequence, correct_test_01) {
  std::string str = "GCTA";
  bool res = DnaAlgorithm::CorrectSequence(str);
  EXPECT_TRUE(res);
}

TEST(Correct_sequence, wrong_test_01) {
  std::string str = "GCTAvvvv";
  bool res = DnaAlgorithm::CorrectSequence(str);
  EXPECT_FALSE(res);
}

TEST(RabinKarp, hiv_test_01) {
  const std::vector<size_t> expected_result = {65, 9150};

  std::ifstream haystack_input("tests/part-01-haystack.txt");
  std::string haystack;
  haystack_input >> haystack;

  std::string needle = "AAGCCTCAATAAAGCTT";

  int q = 13;
  std::vector<size_t> res = DnaAlgorithm::RabinKarpSearch(needle, haystack, q);

  EXPECT_EQ(expected_result.size(), res.size());
  for (size_t i = 0; i < expected_result.size(); i++)
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

TEST(NwSequence, nw_sequence_alignment_test_01) {
  int match_s = 1, mismatch_s = -1, gap_s = -2;
  std::string str1 = "GGGCGACACTCCACCATAGA";
  std::string str2 = "GGCGACACCCACCATACAT";

  DnaAlgorithm::NwSequence res =
      DnaAlgorithm::NwSequenceAlignment(match_s, mismatch_s, gap_s, str1, str2);

  EXPECT_EQ(res.score, 10);
  EXPECT_EQ(res.str1, "GGGCGACACTCCACCATAGA-");
  EXPECT_EQ(res.str2, "GG-CGACAC-CCACCATACAT");
}

TEST(NwSequence, empty_test_01) {
  int match_s = 1, mismatch_s = -1, gap_s = -2;
  std::string str1;
  std::string str2;

  DnaAlgorithm::NwSequence res =
      DnaAlgorithm::NwSequenceAlignment(match_s, mismatch_s, gap_s, str1, str2);

  EXPECT_EQ(res.score, 0);
  EXPECT_EQ(res.str1, "");
  EXPECT_EQ(res.str2, "");
}

TEST(RegExpr, regex_test_01) {
  std::string regex = "G?G*AC+A*A.";
  std::string text = "GGCGACACCCACCATACAT";

  bool res = DnaAlgorithm::RegExpr(regex, text);

  EXPECT_EQ(res, true);
}

TEST(RegExpr, regex_test_02) {
  std::string regex = "G?G*AC+A*A.";
  std::string text = "GGCGACACCCACCATACATGGGGGGGGGG";

  bool res = DnaAlgorithm::RegExpr(regex, text);

  EXPECT_EQ(res, false);
}

TEST(RegExpr, empty_test_01) {
  std::string regex;
  std::string text;

  bool res = DnaAlgorithm::RegExpr(regex, text);

  EXPECT_EQ(res, true);
}

TEST(KSimilar, k_similar_test_01) {
  std::string str1 = "GGCGACACC";
  std::string str2 = "AGCCGCGAC";

  int res = DnaAlgorithm::KSimilar(str1, str2);

  EXPECT_EQ(res, 3);
}

TEST(KSimilar, k_similar_test_02) {
  std::string str1 = "GG";
  std::string str2 = "GG";

  int res = DnaAlgorithm::KSimilar(str1, str2);

  EXPECT_EQ(res, 0);
}

TEST(MinWindowSubstr, minimum_window_substr_test_01) {
  std::string str1 = "GGCGACACCCACCATACAT";
  std::string str2 = "TGT";

  std::string res = DnaAlgorithm::MinWindowSubstr(str1, str2);

  EXPECT_EQ(res, "GACACCCACCATACAT");
}

TEST(MinWindowSubstr, empty_test_01) {
  std::string str1;
  std::string str2;

  std::string res = DnaAlgorithm::MinWindowSubstr(str1, str2);

  EXPECT_EQ(res, "");
}

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
