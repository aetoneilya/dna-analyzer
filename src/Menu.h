#include <iostream>
#include <memory>
#include <vector>

struct MenuItem {
  virtual std::string GetName() { return "This is blank menu option"; }
  virtual void Do() { std::cout << "Its doing nothing\n"; };
};

class Menu {
 private:
  std::string greeting = "It's a dna analyzer.";

  std::vector<std::unique_ptr<MenuItem>> items;

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
        std::cout << i + 1 << " - " << items[i]->GetName() << std::endl;

      int choice = GetInput() - 1;

      if (choice == -1) break;
      items[choice]->Do();
    }
  }

 public:
  void Add(std::unique_ptr<MenuItem> item) { items.push_back(std::move(item)); }

  void Start() {
    std::cout << greeting << std::endl;
    MenuCycle();
  }
};
