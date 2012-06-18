#include "phoenix.hpp"
using namespace nall;
using namespace phoenix;

struct Application : Window {
  VerticalLayout layout;
  ListView listView;
  ComboBox comboView;
  Button button;
  Menu file;
  Menu submenu;
  Item quit;

  Application() {
    setTitle("Main Window");
    setGeometry({128, 128, 640, 480});

    file.setText("File");
    submenu.setText("Submenu");
    submenu.setImage(image("folder.png"));
    quit.setText("Quit");
    quit.setImage(image("image.png"));

  //submenu.setImage();
  //quit.setImage();

    setMenuVisible();
    append(file);
    file.append(submenu);
    file.append(quit);

    listView.setHeaderText("Column 1", "Column 2", "Column 3");
    listView.setHeaderVisible();
    listView.setCheckable();
    listView.append("A", "B", "C");
    listView.append("D", "E", "F");
    listView.append("G", "H", "I");

    listView.setImage(0, 0, image("image.png"));
    listView.setImage(1, 0, image("folder.png"));
    listView.setImage(2, 2, image("folder.png"));
  //listView.setImage(0, 0);
  //listView.setImage(1, 0);

    button.setText("Hello");
    button.setImage(image("image.png"));
  //button.setImage();

    append(layout);
    layout.setMargin(5);
    layout.append(listView, {~0, ~0}, 5);
    layout.append(comboView, {~0, 0}, 5);
    layout.append(button, {~0, 0});

    comboView.append("item1", "item2*", "item3", "item4", "item5", "item6", "item7", "item8");

    button.onActivate = [&] {
      DialogWindow::fileOpen(*this, "c:/users/byuu/desktop", "All files (*)");
      listView.remove(1);
      comboView.modify(1, "item2");
      comboView.remove(2);
    };

    setVisible();
    onClose = &OS::quit;
  }
} *application = nullptr;

int main() {
  application = new Application;
  OS::main();
  return 0;
}
