#include "main.h"
#include "dms_npc.h"
#include "parse_npc.h"
#include "windows.h"
#include <ncurses.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

  static dms_npc_array *known_npc_a = 0;
  known_npc_a = dms_npc_array_from_path("./data");

  static dms_selection_menu *known_npc_menu;

  if (!DEBUG) {
    init();

    known_npc_menu =
        dms_selection_menu_new("NPC list", known_npc_a->len, 80, 80, 0, 0);
    /* WINDOW *testwin = newwin(60, 80, 0, 0); */
    /* known_npc_menu->screen = testwin; */

    while (true) {
      dms_selection_menu_draw(known_npc_menu);
      /* window_draw_borders(testwin); */
      /* wrefresh(testwin); */
      int ch = getch();
    }
  }
  if (DEBUG) {
    /* dms_npc *goblin = dms_npc_new(); */
    /* dms_npc_apply_cfg_line("name=goblin", goblin); */

    printf("parsed %lu NPCs\n", dms_npc_array_get_length(known_npc_a));
    printf("NPC array size: %lu\n", known_npc_a->maxlen);

    for (size_t i = 0; i < dms_npc_array_get_length(known_npc_a); i++) {
      dms_npc *current = dms_npc_array_get_element(known_npc_a, i);
      printf("%s\n HP %d, AC %d\n", current->name, current->hp, current->ac);
    }

    int dx;
    int dy;
    getmaxyx(known_npc_menu->screen, dy, dx);

    printf("made NPC selection menu with title %s\n, dimensions dy: %d, dx: "
           "%d\n",
           known_npc_menu->title, dy, dx);

    return 1;
  }
}

// Init and finish functions
static void init() {

  (void)signal(SIGINT, finish); /* arrange interrupts to terminate */
  (void)initscr();              /* initialize the curses library */
  /* keypad(stdscr, true); /\* enable keyboard mapping *\/ */
  (void)nonl();   /* tell curses not to do NL->CR/NL on output */
  (void)cbreak(); /* take input chars one at a time, no wait for \n */
  (void)noecho(); /* echo input - in color */

  if (has_colors()) {
    start_color();
  }
  (void)curs_set(0);
}

static void finish(int sig) {
  endwin();
  exit(0);
};
