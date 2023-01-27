#include "Menu.h"

struct MenuItemDnaSearch : public MenuItem {
  std::string GetName() { return "Exact DNA search"; }
  void Do() { std::cout << "I am working"; }
};

struct MenuItemNwSequenceAlignment : public MenuItem {
  std::string GetName() { return "NW sequence alignment"; }
  void Do() { std::cout << "I am working"; }
};

struct MenuItemRegExpr : public MenuItem {
  std::string GetName() { return "Matching regular expressions"; }
  void Do() { std::cout << "I am working"; }
};

struct MenuItemKSimilar : public MenuItem {
  std::string GetName() { return "K-similar strings"; }
  void Do() { std::cout << "I am working"; }
};

struct MenuItemMinimumSubstr : public MenuItem {
  std::string GetName() { return "Minimum window substring"; }
  void Do() { std::cout << "I am working"; }
};

int main() {
  Menu menu;
  menu.Add(std::make_unique<MenuItemDnaSearch>());
  menu.Add(std::make_unique<MenuItemNwSequenceAlignment>());
  menu.Add(std::make_unique<MenuItemRegExpr>());
  menu.Add(std::make_unique<MenuItemKSimilar>());
  menu.Add(std::make_unique<MenuItemMinimumSubstr>());
  menu.Start();

  return 0;
}