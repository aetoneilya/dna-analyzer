#include <fstream>

#include "DnaAlgorithms.h"
#include "Menu.h"

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
  void Do() override { std::cout << "I am working"; }
};

struct MenuItemRegExpr : public MenuItem {
  std::string GetName() override { return "Matching regular expressions"; }
  void Do() override { std::cout << "I am working"; }
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
