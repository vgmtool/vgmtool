static void ListView_activate(ListView *self) {
  if(self->onActivate) self->onActivate();
}

static void ListView_change(ListView *self) {
  if(self->state.selected == false || self->state.selection != self->selection()) {
    self->state.selected = true;
    self->state.selection = self->selection();
    if(self->onChange) self->onChange();
  }
}

static void ListView_toggle(GtkCellRendererToggle *cell, gchar *path_string, ListView *self) {
  unsigned row = decimal(path_string);
  self->setChecked(row, !self->checked(row));
  if(self->onToggle) self->onToggle(row);
}

void pListView::append(const lstring &text) {
  GtkTreeIter iter;
  gtk_list_store_append(store, &iter);
  for(unsigned n = 0; n < text.size(); n++) gtk_list_store_set(store, &iter, 1 + n, (const char*)text[n], -1);
}

void pListView::autoSizeColumns() {
  gtk_tree_view_columns_autosize(GTK_TREE_VIEW(subWidget));
}

bool pListView::checked(unsigned row) {
  GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(subWidget));
  GtkTreeIter iter;
  bool state;
  if(gtk_tree_model_get_iter_from_string(model, &iter, string(row)) == false) return false;
  gtk_tree_model_get(model, &iter, 0, &state, -1);
  return state;
}

void pListView::modify(unsigned row, const lstring &text) {
  GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(subWidget));
  GtkTreeIter iter;
  gtk_tree_model_get_iter_from_string(model, &iter, string(row));
  for(unsigned n = 0; n < text.size(); n++) gtk_list_store_set(store, &iter, 1 + n, (const char*)text[n], -1);
}

void pListView::reset() {
  listView.state.selected = false;
  listView.state.selection = 0;
  gtk_list_store_clear(GTK_LIST_STORE(store));
  gtk_tree_view_set_model(GTK_TREE_VIEW(subWidget), GTK_TREE_MODEL(store));
  //reset gtk_scrolled_window scrollbar position to 0,0 (top-left), as ListView is now empty
  gtk_scrolled_window_set_hadjustment(GTK_SCROLLED_WINDOW(gtkWidget), 0);
  gtk_scrolled_window_set_vadjustment(GTK_SCROLLED_WINDOW(gtkWidget), 0);
}

bool pListView::selected() {
  GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(subWidget));
  return gtk_tree_selection_get_selected(selection, 0, 0);
}

unsigned pListView::selection() {
  GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(subWidget));
  GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(subWidget));
  GtkTreeIter iter;
  if(gtk_tree_selection_get_selected(selection, 0, &iter) == false) return listView.state.selection;
  char *path = gtk_tree_model_get_string_from_iter(model, &iter);
  unsigned row = decimal(path);
  g_free(path);
  return row;
}

void pListView::setCheckable(bool checkable) {
  gtk_tree_view_column_set_visible(column[0].column, checkable);
}

void pListView::setChecked(unsigned row, bool checked) {
  GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(subWidget));
  GtkTreeIter iter;
  gtk_tree_model_get_iter_from_string(model, &iter, string(row));
  gtk_list_store_set(GTK_LIST_STORE(model), &iter, 0, checked, -1);
}

void pListView::setHeaderText(const lstring &text) {
  destructor();
  constructor();
}

void pListView::setHeaderVisible(bool visible) {
  gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(subWidget), visible);
}

void pListView::setSelected(bool selected) {
  if(selected == false) {
    GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(subWidget));
    gtk_tree_selection_unselect_all(selection);
  } else {
    setSelection(listView.state.selection);
  }
}

void pListView::setSelection(unsigned row) {
  GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(subWidget));
  GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(subWidget));
  gtk_tree_selection_unselect_all(selection);
  GtkTreeIter iter;
  if(gtk_tree_model_get_iter_from_string(model, &iter, string(row)) == false) return;
  gtk_tree_selection_select_iter(selection, &iter);

  //scroll window to selected item
  char *path = gtk_tree_model_get_string_from_iter(model, &iter);
  GtkTreePath *treePath = gtk_tree_path_new_from_string(path);
  gtk_tree_view_scroll_to_cell(GTK_TREE_VIEW(subWidget), treePath, nullptr, true, 0.5, 0.0);
  gtk_tree_path_free(treePath);
  g_free(path);
}

void pListView::constructor() {
  gtkWidget = 0;
  subWidget = 0;

  gtkWidget = gtk_scrolled_window_new(0, 0);
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(gtkWidget), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
  gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(gtkWidget), GTK_SHADOW_ETCHED_IN);

  lstring headerText;
  headerText.append("");  //checkbox column
  for(auto &headerItem : listView.state.headerText) headerText.append(headerItem);
  if(headerText.size() == 1) headerText.append("");

  GType *v = (GType*)malloc(headerText.size() * sizeof(GType));
  for(unsigned n = 0; n < headerText.size(); n++) v[n] = (n == 0 ? G_TYPE_BOOLEAN : G_TYPE_STRING);
  store = gtk_list_store_newv(headerText.size(), v);
  free(v);

  subWidget = gtk_tree_view_new_with_model(GTK_TREE_MODEL(store));
  gtk_container_add(GTK_CONTAINER(gtkWidget), subWidget);
  g_object_unref(G_OBJECT(store));

  for(unsigned n = 0; n < headerText.size(); n++) {
    if(n == 0) {
      column[n].renderer = gtk_cell_renderer_toggle_new();
      column[n].column = gtk_tree_view_column_new_with_attributes("", column[n].renderer, "active", n, (void*)0);
      gtk_tree_view_column_set_resizable(column[n].column, false);
      gtk_tree_view_column_set_visible(column[n].column, false);
      g_signal_connect(column[n].renderer, "toggled", G_CALLBACK(ListView_toggle), (gpointer)&listView);
    } else {
      column[n].renderer = gtk_cell_renderer_text_new();
      column[n].column = gtk_tree_view_column_new_with_attributes("", column[n].renderer, "text", n, (void*)0);
      gtk_tree_view_column_set_resizable(column[n].column, true);
    }
    column[n].label = gtk_label_new(headerText[n]);
    gtk_tree_view_column_set_widget(GTK_TREE_VIEW_COLUMN(column[n].column), column[n].label);
    gtk_tree_view_append_column(GTK_TREE_VIEW(subWidget), column[n].column);
    gtk_widget_show(column[n].label);
  }

  gtk_tree_view_set_rules_hint(GTK_TREE_VIEW(subWidget), headerText.size() >= 3);  //two or more columns + checkbox column
  gtk_tree_view_set_search_column(GTK_TREE_VIEW(subWidget), 1);

  g_signal_connect_swapped(G_OBJECT(subWidget), "cursor-changed", G_CALLBACK(ListView_change), (gpointer)&listView);
  g_signal_connect_swapped(G_OBJECT(subWidget), "row-activated", G_CALLBACK(ListView_activate), (gpointer)&listView);

  gtk_widget_show(subWidget);

  setHeaderVisible(listView.state.headerVisible);
  setCheckable(listView.state.checkable);
  for(auto &text : listView.state.text) append(text);
  for(unsigned n = 0; n < listView.state.checked.size(); n++) setChecked(n, listView.state.checked[n]);
  if(listView.state.selected) setSelection(listView.state.selection);
  autoSizeColumns();
}

void pListView::destructor() {
  gtk_widget_destroy(subWidget);
  gtk_widget_destroy(gtkWidget);
}

void pListView::orphan() {
  destructor();
  constructor();
}

void pListView::setFocused() {
  gtk_widget_grab_focus(subWidget);
}

void pListView::setFont(const string &font) {
  pFont::setFont(gtkWidget, font);
  for(unsigned n = 0; n < 1 + listView.state.headerText.size(); n++) {
    pFont::setFont(column[n].label, font);
  }
}
