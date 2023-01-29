#ifndef SRC_DNAALGORITHMS_H_
#define SRC_DNAALGORITHMS_H_

#include <algorithm>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

namespace DnaAlgorithm {
static std::map<char, int> kAlphabet = {{'A', 0}, {'C', 1}, {'G', 2}, {'T', 3}};

bool CorrectSequence(const std::string &str) {
  for (size_t i = 0; i < str.size(); i++)
    if (!kAlphabet.count(str[i])) return false;
  return true;
}

std::vector<size_t> RabinKarpSearch(const std::string &needle,
                                    const std::string &haystack, int q) {
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
  std::string str1;
  std::string str2;
};

NwSequence NwSequenceAlignment(int match_s, int mismatch_s, int gap_s,
                               const std::string &str1,
                               const std::string &str2) {
  // backtrack matrix
  //  l - left
  //  u - up
  //  d - left right diagonal
  //  else none
  std::vector<std::vector<char>> backtrack_matrix(
      str1.size() + 1, std::vector<char>(str2.size() + 1, 'n'));

  std::vector<std::vector<int>> matrix(str1.size() + 1,
                                       std::vector<int>(str2.size() + 1));
  matrix[0][0] = 0;
  for (int i = 0; i < (int)str1.size() + 1; i++) {
    matrix[i][0] = i * gap_s;
    backtrack_matrix[i][0] = 'u';
  }
  for (int i = 0; i < (int)str2.size() + 1; i++) {
    matrix[0][i] = i * gap_s;
    backtrack_matrix[0][i] = 'l';
  }

  // fill matrix
  for (int i = 1; i < (int)str1.size() + 1; i++)
    for (int j = 1; j < (int)str2.size() + 1; j++) {
      int diagonal = str1[i - 1] == str2[j - 1]
                         ? matrix[i - 1][j - 1] + match_s
                         : matrix[i - 1][j - 1] + mismatch_s;
      int up = matrix[i - 1][j] + gap_s;
      int left = matrix[i][j - 1] + gap_s;

      if (up >= left && up >= diagonal) {
        matrix[i][j] = up;
        backtrack_matrix[i][j] = 'u';
      } else if (diagonal >= up && diagonal >= left) {
        matrix[i][j] = diagonal;
        backtrack_matrix[i][j] = 'd';
      } else if (left >= up && left >= diagonal) {
        matrix[i][j] = left;
        backtrack_matrix[i][j] = 'l';
      }
    }

  //   for (int i = 0; i < (int)str1.size() + 1; i++) {
  //     for (int j = 0; j < (int)str2.size() + 1; j++) {
  //       std::cout << matrix[i][j] << " ";
  //     }
  //     std::cout << std::endl;
  //   }
  //   for (int i = 0; i < (int)str1.size() + 1; i++) {
  //     for (int j = 0; j < (int)str2.size() + 1; j++) {
  //       std::cout << backtrack_matrix[i][j] << " ";
  //     }
  //     std::cout << std::endl;
  //   }

  NwSequence nw_res;
  int res_len = std::max((int)str1.size(), (int)str2.size());
  nw_res.str1.reserve(res_len);
  nw_res.str2.reserve(res_len);
  nw_res.score = matrix.back().back();

  int i = (int)str1.size();
  int j = (int)str2.size();
  while (i != 0 || j != 0) {
    char move = backtrack_matrix[i][j];
    if (move == 'd') {
      nw_res.str1.insert(0, 1, str1[i - 1]);
      nw_res.str2.insert(0, 1, str2[j - 1]);
      i -= 1;
      j -= 1;
    } else if (move == 'u') {
      nw_res.str1.insert(0, 1, str1[i - 1]);
      nw_res.str2.insert(0, 1, '-');
      i -= 1;
    } else if (move == 'l') {
      nw_res.str1.insert(0, 1, '-');
      nw_res.str2.insert(0, 1, str2[j - 1]);
      j -= 1;
    }
  }

  return nw_res;
}

int MatchHere(const std::string &regexp, int r_ind, const std::string &text,
              int t_ind);

int MatchStar(const std::string &regexp, int r_ind, const std::string &text,
              int t_ind) {
  do {
    if (MatchHere(regexp, r_ind, text, t_ind)) return 1;
  } while (t_ind++ < text.size());
  return 0;
}

int MatchHere(const std::string &regexp, int r_ind, const std::string &text,
              int t_ind) {
  if (regexp.size() == r_ind) return text.size() == t_ind;
  if (regexp[r_ind] == '*') return MatchStar(regexp, r_ind + 1, text, t_ind);
  if (regexp[r_ind] == '.' || regexp[r_ind] == text[t_ind])
    return MatchHere(regexp, r_ind + 1, text, t_ind + 1);

  return 0;
}

bool RegExpr(const std::string &pattern, const std::string &text) {
  return MatchHere(pattern, 0, text, 0);
}

// /* match: search for regexp anywhere in text */
// int match(char *regexp, char *text) {
//   if (regexp[0] == '^') return matchhere(regexp + 1, text);
//   do { /* must look even if string is empty */
//     if (matchhere(regexp, text)) return 1;
//   } while (*text++ != '\0');
//   return 0;
// }

// /* matchhere: search for regexp at beginning of text */
// int matchhere(char *regexp, char *text) {
//   if (regexp[0] == '\0') return 1;
//   if (regexp[1] == '*') return matchstar(regexp[0], regexp + 2, text);
//   if (regexp[0] == '$' && regexp[1] == '\0') return *text == '\0';
//   if (*text != '\0' && (regexp[0] == '.' || regexp[0] == *text))
//     return matchhere(regexp + 1, text + 1);
//   return 0;
// }

// /* matchstar: search for c*regexp at beginning of text */
// int matchstar(int c, char *regexp, char *text) {
//   do { /* a * matches zero or more instances */
//     if (matchhere(regexp, text)) return 1;
//   } while (*text != '\0' && (*text++ == c || c == '.'));
//   return 0;
// }

}  // namespace DnaAlgorithm

#endif  // SRC_DNAALGORITHMS_H_
