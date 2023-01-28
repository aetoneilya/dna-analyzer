#ifndef SRC_DNAALGORITHMS_H_
#define SRC_DNAALGORITHMS_H_

#include <algorithm>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

namespace DnaAlgorithm {
static std::map<char, int> kAlphabet = {{'A', 0}, {'C', 1}, {'G', 2}, {'T', 3}};

bool CorrectSequence(const std::string& str) {
  for (size_t i = 0; i < str.size(); i++)
    if (!kAlphabet.count(str[i])) return false;
  return true;
}

std::vector<size_t> RabinKarpSearch(const std::string& needle,
                                    const std::string& haystack, int q) {
  if (!CorrectSequence(needle))
    throw std::invalid_argument(
        "Needle has wrong dna format. Use only letters: A, C, G, T. in "
        "uppercase");

  if (!CorrectSequence(haystack))
    throw std::invalid_argument(
        "Haystack has wrong dna format. Use only letters: A, C, G, T. in "
        "uppercase");

  if (needle.size() > haystack.size())
    throw std::invalid_argument(
        "Haystack size must be bigger than needle size");

  std::vector<size_t> result;
  int haystack_hash = 0;
  int needle_hash = 0;
  int h = 1;
  int alphabet_size = (int)kAlphabet.size();

  for (size_t i = 0; i < needle.size() - 1; i++) h = (h * alphabet_size) % q;

  for (size_t i = 0; i < needle.size(); i++) {
    haystack_hash =
        (alphabet_size * haystack_hash + kAlphabet[haystack[i]]) % q;
    needle_hash = (alphabet_size * needle_hash + kAlphabet[needle[i]]) % q;
  }

  for (size_t i = 0; i <= haystack.size() - needle.size(); i++) {
    if (haystack_hash == needle_hash &&
        haystack.compare(i, needle.size(), needle) == 0) {
      result.push_back(i);
    }

    haystack_hash =
        (alphabet_size * (haystack_hash - kAlphabet[haystack[i]] * h) +
         kAlphabet[haystack[i + needle.size()]]) %
        q;

    if (haystack_hash < 0) haystack_hash = (haystack_hash + q);
  }

  return result;
}

struct NwSequence {
  int score = 0;
  std::string str;
};

void NwSequenceAlignment(int match_s, int mismatch_s, int gap_s,
                         const std::string& str1, const std::string& str2) {
  std::vector<std::vector<int>> matrix(str1.size() + 1,
                                       std::vector<int>(str2.size() + 1));
  matrix[0][0] = 0;
  for (int i = 0; i < (int)str1.size() + 1; i++) matrix[i][0] = i * gap_s;
  for (int i = 0; i < (int)str2.size() + 1; i++) matrix[0][i] = i * gap_s;

  // fill matrix
  for (int i = 1; i < (int)str1.size() + 1; i++)
    for (int j = 1; j < (int)str2.size() + 1; j++) {
      int diagonal = str1[i - 1] == str2[i - 1]
                         ? matrix[i - 1][j - 1] + match_s
                         : matrix[i - 1][j - 1] + mismatch_s;
      int up = matrix[i - 1][j] + gap_s;
      int left = matrix[i][j - 1] + gap_s;

      matrix[i][j] = std::max({diagonal, up, left});
    }
}

}  // namespace DnaAlgorithm

#endif  // SRC_DNAALGORITHMS_H_
