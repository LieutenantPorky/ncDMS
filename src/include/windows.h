#ifndef WINDOWS_H_
#define WINDOWS_H_

#include "dms_npc.h"
#include <ncurses.h>
#include <stddef.h>

typedef void process_input(char);
typedef struct dms_state_manager dms_state_manager;
struct dms_state_manager {
  process_input *process_input;
  dms_npc_array *loaded_npc_a;
};

typedef struct dms_selection_menu dms_selection_menu;
struct dms_selection_menu {
  char *title;
  WINDOW *screen;
  size_t num_options;
  size_t current_option;
  char **option_labels;
};

dms_selection_menu *dms_selection_menu_init(dms_selection_menu *menu,
                                            char *const title,
                                            size_t num_options, int dy, int dx,
                                            int y, int x);

dms_selection_menu *dms_selection_menu_new(char *const title,
                                           size_t num_options, int dy, int dx,
                                           int y, int x);

void dms_selection_menu_destroy(dms_selection_menu *menu);

void dms_selection_menu_draw(dms_selection_menu *menu);
int dms_selection_menu_process_input(dms_selection_menu *menu, char ch);
size_t dms_selection_menu_get_selected(dms_selection_menu *menu);

void window_draw_borders(WINDOW *screen);
#endif // WINDOWS_H_
