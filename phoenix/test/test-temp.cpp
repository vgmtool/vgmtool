#include "phoenix.hpp"
using namespace nall;
using namespace phoenix;

struct Application : Window {
  HorizontalLayout layout;
  ListView listA;
  ListView listB;

  Application() {
    setGeometry({ 256, 256, 640, 400 });

    listA.append("Item");
    listA.append("Item");
    listA.append("Item");
    listA.append("Item");
    listA.append("Item");

    listB.append("Item");
    listB.append("Item");
    listB.append("Item");
    listB.append("Item");
    listB.append("Item");

    append(layout);
    layout.setMargin(5);
    layout.append(listA, ~0, ~0, 5);
    layout.append(listB, ~0, ~0, 0);

    onClose = &OS::quit;

    setVisible();
  }
};

int main() {
  auto application = new Application;
  OS::main();
  delete application;
  return 0;
}
