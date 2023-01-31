#include <fstream>

#include "dna-algorithms/dna-algorithms.h"
#include "menu.h"

void MenuItemDnaSearch() {
  std::string haystack_path =
      Menu::GetUserInput("Enter path to text file(Haystack):\n");
  std::string needle_path =
      Menu::GetUserInput("Enter path to text file(Needle):\n");

  std::ifstream haystack_input(haystack_path);
  std::ifstream needle_input(needle_path);

  std::string needle, haystack;
  haystack_input >> haystack;
  needle_input >> needle;

  if (!haystack_input.is_open() || haystack_input.fail())
    throw std::invalid_argument("Can't read haystack");

  if (!needle_input.is_open() || needle_input.fail())
    throw std::invalid_argument("Can't read needle");

  if (!DnaAlgorithm::CorrectSequence(needle))
    throw std::invalid_argument(
        "Needle has wrong dna format. Only use alphabet {A, C, G, T } "
        "uppercase");

  if (!DnaAlgorithm::CorrectSequence(haystack))
    throw std::invalid_argument(
        "Haystack has wrong dna format. Only use alphabet {A, C, G, T } "
        "uppercase");

  int q = 13;
  std::vector<size_t> res = DnaAlgorithm::RabinKarpSearch(needle, haystack, q);

  std::cout << "Occurrences in a string:" << std::endl;
  for (auto r : res) std::cout << r << " ";
}

void MenuItemNwSequenceAlignment() {
  std::string input_file_path =
      Menu::GetUserInput("Enter path to text input file:\n");

  std::ifstream input(input_file_path);

  int match_s, mismatch_s, gap_s;
  std::string str1, str2;

  input >> match_s >> mismatch_s >> gap_s >> str1 >> str2;

  if (!input.is_open() || input.fail())
    throw std::invalid_argument("Can't read input file");

  if (!DnaAlgorithm::CorrectSequence(str1) ||
      !DnaAlgorithm::CorrectSequence(str2))
    throw std::invalid_argument(
        "One of strings has wrong dna format. Only use alphabet {A, C, G, T } "
        "uppercase");

  DnaAlgorithm::NwSequence res =
      DnaAlgorithm::NwSequenceAlignment(match_s, mismatch_s, gap_s, str1, str2);

  std::string lines;
  for (size_t i = 0; i < res.str1.size(); i++)
    lines.push_back(res.str1.at(i) == res.str2.at(i) ? '|' : ' ');

  std::cout << "Score and aligned strings: " << std::endl
            << res.score << std::endl
            << res.str1 << std::endl
            << lines << std::endl
            << res.str2;
}

void MenuItemRegExpr() {
  std::string input_file_path =
      Menu::GetUserInput("Enter path to text input file:\n");

  std::string regexp, text;

  std::ifstream input(input_file_path);
  input >> text >> regexp;

  if (!input.is_open() || input.fail())
    throw std::invalid_argument("Can't read input file");

  if (!DnaAlgorithm::CorrectSequence(text))
    throw std::invalid_argument(
        "Text has wrong dna format. Only use alphabet {A, C, G, T } uppercase");

  bool match = DnaAlgorithm::RegExpr(regexp, text);

  std::cout << "Match" << std::endl << (match ? "True" : "False");
}

void MenuItemKSimilar() {
  std::string input_file_path =
      Menu::GetUserInput("Enter path to text input file:\n");

  std::string str1, str2;

  std::ifstream input(input_file_path);
  input >> str1 >> str2;

  if (!input.is_open() || input.fail())
    throw std::invalid_argument("Can't read input file");

  if (!DnaAlgorithm::CorrectSequence(str1) ||
      !DnaAlgorithm::CorrectSequence(str2))
    throw std::invalid_argument(
        "One of strings has wrong dna format. Only use alphabet {A, "
        "C, G, T } "
        "uppercase");

  std::cout << "K = " << std::endl << DnaAlgorithm::KSimilar(str1, str2);
}

void MenuItemMinimumWindow() {
  std::string input_file_path =
      Menu::GetUserInput("Enter path to text input file:\n");

  std::string str1, str2;

  std::ifstream input(input_file_path);
  input >> str1 >> str2;

  if (!input.is_open() || input.fail())
    throw std::invalid_argument("Can't read input file");

  if (!DnaAlgorithm::CorrectSequence(str1) ||
      !DnaAlgorithm::CorrectSequence(str2))
    throw std::invalid_argument(
        "One of strings has wrong dna format. Only use alphabet {A, "
        "C, G, T } "
        "uppercase");

  std::cout << "Minimum window substr" << std::endl
            << DnaAlgorithm::MinWindowSubstr(str1, str2);
}

int main() {
  Menu menu;
  menu.AddMenuItem({"Exact DNA search", MenuItemDnaSearch});
  menu.AddMenuItem(
      {"NW sequence alignment project", MenuItemNwSequenceAlignment});
  menu.AddMenuItem({"Matching regular expressions", MenuItemRegExpr});
  menu.AddMenuItem({"K-similar strings", MenuItemKSimilar});
  menu.AddMenuItem({"Minimum window substring", MenuItemMinimumWindow});

  menu.Start();

  return 0;
}
