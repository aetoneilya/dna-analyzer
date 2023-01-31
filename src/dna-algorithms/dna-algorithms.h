#ifndef SRC_DNA_ALGORITHMS_DNA_ALGORITHMS_H_
#define SRC_DNA_ALGORITHMS_DNA_ALGORITHMS_H_

#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

namespace DnaAlgorithm {
static std::map<char, int> kAlphabet = {{'A', 0}, {'C', 1}, {'G', 2}, {'T', 3}};

struct NwSequence {
  int score = 0;
  std::string str1;
  std::string str2;
};

bool CorrectSequence(const std::string &str);

std::vector<size_t> RabinKarpSearch(const std::string &needle,
                                    const std::string &haystack, int q);

NwSequence NwSequenceAlignment(int match_s, int mismatch_s, int gap_s,
                               const std::string &str1,
                               const std::string &str2);

// int MatchStar(const std::string &regexp, size_t r_ind, const std::string
// &text,
//               size_t t_ind);

// int MatchPlus(char ch, const std::string &regexp, size_t r_ind,
//               const std::string &text, size_t t_ind);

// int MatchHere(const std::string &regexp, size_t r_ind, const std::string
// &text,
//               size_t t_ind);

bool RegExpr(const std::string &pattern, const std::string &text);

int KSimilar(const std::string &str1, const std::string &str2);

// bool contains(const std::unordered_map<char, int> &counts, char ch);

std::string MinWindowSubstr(std::string &s, std::string &t);

}  // namespace DnaAlgorithm

#endif  // SRC_DNA_ALGORITHMS_DNA_ALGORITHMS_H_
