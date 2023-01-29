#include <fstream>

#include "Menu.h"
#include "dna-algorithms/DnaAlgorithms.h"

struct MenuItemDnaSearch : public MenuItem {
  std::string GetName() override { return "Exact DNA search"; }
  void Do() override {
    std::string needle_path, haystack_path;
    std::cout << "Enter path to text(Haystack): " << std::endl;
    std::cin >> haystack_path;
    std::cout << "Enter path to text(Needle): " << std::endl;
    std::cin >> needle_path;

    std::string needle, haystack;
    std::ifstream haystack_input(haystack_path);
    std::ifstream needle_input(needle_path);

    haystack_input >> haystack;
    needle_input >> needle;

    haystack_input.close();
    needle_input.close();

    try {
      int q = 13;
      std::vector<size_t> res =
          DnaAlgorithm::RabinKarpSearch(needle, haystack, q);

      std::cout << "Occurrences in a string:\n";
      for (auto r : res) {
        std::cout << r << " ";
      }
      std::cout << std::endl;
    } catch (const std::exception& e) {
      std::cerr << "Error: " << e.what() << '\n';
    }
  }
};

struct MenuItemNwSequenceAlignment : public MenuItem {
  std::string GetName() override { return "NW sequence alignment"; }
  void Do() override {
    int match_s = 1;
    int mismatch_s = -1;
    int gap_s = -2;

    std::string str1 = "GGGCGACACTCCACCATAGA";
    std::string str2 = "GGCGACACCCACCATACAT";
    // std::string str1 = "GAAC";
    // std::string str2 = "CAAGAC";

    DnaAlgorithm::NwSequence res = DnaAlgorithm::NwSequenceAlignment(
        match_s, mismatch_s, gap_s, str1, str2);

    std::cout << "Score: " << res.score << std::endl;

    std::cout << res.str1 << std::endl;
    for (int i = 0; i < res.str1.size(); i++) {
      if (res.str1.at(i) == res.str2.at(i))
        std::cout << '|';
      else
        std::cout << " ";
    }
    std::cout << std::endl << res.str2 << std::endl;
  }
};

struct MenuItemRegExpr : public MenuItem {
  std::string GetName() override { return "Matching regular expressions"; }
  void Do() override {
    std::string regexp, text;
    std::cout << "enter regexp:\n";
    std::cin >> regexp;
    std::cout << "enter text\n";
    std::cin >> text;

    std::cout << DnaAlgorithm::RegExpr(regexp, text);
  }
};

struct MenuItemKSimilar : public MenuItem {
  std::string GetName() override { return "K-similar strings"; }
  void Do() override { std::cout << "I am working"; }
};

struct MenuItemMinimumSubstr : public MenuItem {
  std::string GetName() override { return "Minimum window substring"; }
  void Do() override { std::cout << "I am working"; }
};

int main() {
  Menu menu;
  menu.AddMenuItem(std::make_unique<MenuItemDnaSearch>());
  menu.AddMenuItem(std::make_unique<MenuItemNwSequenceAlignment>());
  menu.AddMenuItem(std::make_unique<MenuItemRegExpr>());
  menu.AddMenuItem(std::make_unique<MenuItemKSimilar>());
  menu.AddMenuItem(std::make_unique<MenuItemMinimumSubstr>());
  menu.Start();

  return 0;
}
