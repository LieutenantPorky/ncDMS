#include "windows.h"
#include <curses.h>
#include <ncurses.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

void window_draw_borders(WINDOW *screen) {
  int x;
  int y;
  getmaxyx(screen, y, x);
  for (int i = 0; i < y; i++) {
    mvwaddch(screen, i, 0, '|');
  }
  for (int i = 0; i < y; i++) {
    mvwaddch(screen, i, x - 1, '|');
  }
  for (int i = 0; i < x; i++) {
    mvwaddch(screen, 0, i, '-');
  }
  for (int i = 0; i < x; i++) {
    mvwaddch(screen, y - 1, i, '-');
  }

  mvwaddch(screen, 0, 0, '+');
  mvwaddch(screen, y - 1, 0, '+');
  mvwaddch(screen, 0, x - 1, '+');
  mvwaddch(screen, y - 1, x - 1, '+');
}

static void window_draw_vertical(WINDOW *screen, int iy, int fy, int x) {
  for (int i = iy; i < fy; i++) {
    mvwaddch(screen, i, x, '|');
  }
  mvwaddch(screen, iy, x, '+');
  mvwaddch(screen, fy, x, '+');
}

static void window_draw_horizontal(WINDOW *screen, int ix, int fx, int y) {
  for (int i = ix; i < fx; i++) {
    mvwaddch(screen, y, i, '-');
  }
  mvwaddch(screen, y, ix, '+');
  mvwaddch(screen, y, fx, '+');
}

dms_selection_menu *dms_selection_menu_init(dms_selection_menu *menu,
                                            char *const title,
                                            size_t num_options, int dy, int dx,
                                            int y, int x) {
  if (!menu) {
    return 0;
  }
  *menu =
      (dms_selection_menu){.title = title,
                           .num_options = num_options,
                           .option_labels = malloc(sizeof(char[num_options])),
                           .screen = newwin(dy, dx, y, x)

      };
  return menu;
}

dms_selection_menu *dms_selection_menu_new(char *const title,
                                           size_t num_options, int dy, int dx,
                                           int y, int x) {
  return dms_selection_menu_init(malloc(sizeof(dms_selection_menu)), title,
                                 num_options, dy, dx, y, x);
}

void dms_selection_menu_free(dms_selection_menu *menu) {
  free(menu->option_labels);
  free(menu);
}

void dms_selection_menu_draw(dms_selection_menu *menu) {
  window_draw_borders(menu->screen);
  int x;
  int y;
  getmaxyx(menu->screen, y, x);
  int title_len = strlen(menu->title);

  mvwaddstr(menu->screen, 1, (x - title_len) / 2, menu->title);
  wrefresh(menu->screen);
}
