#ifndef SRC_MENU_H_
#define SRC_MENU_H_

#include <exception>
#include <functional>
#include <iostream>
#include <vector>

struct MenuItem {
  std::string name = "This is blank menu option";
  std::function<void()> do_work;
};

class Menu {
 private:
  std::string greeting = "It's a dna analyzer.";

  std::vector<MenuItem> items;

  int GetInput() {
    int input;
    std::cin >> input;
    return input;
  }

  void MenuCycle() {
    while (true) {
      std::cout << std::endl
                << "Enter number to choose algorithm or 0 to exit" << std::endl;
      for (size_t i = 0; i < items.size(); i++)
        std::cout << i + 1 << " - " << items[i].name << std::endl;
      std::cout << "0 - exit" << std::endl;

      int choice = GetInput() - 1;

      if (choice == -1) break;
      try {
        items[choice].do_work();
      } catch (const std::exception& e) {
        std::cerr << e.what();
      }

      std::cout << std::endl;
    }
  }

 public:
  static std::string GetUserInput(const std::string& out_message) {
    std::string input;
    std::cout << out_message;
    std::cin >> input;
    return input;
  }

  void AddMenuItem(MenuItem item) { items.push_back(item); }

  void Start() {
    std::cout << greeting << std::endl;
    MenuCycle();
  }
};

#endif  // SRC_MENU_H_
