#include "main.h"
#include "dms_npc.h"
#include "parse_npc.h"
#include <stddef.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

  if (!DEBUG) {
    init();
  }
  if (DEBUG) {
    /* dms_npc *goblin = dms_npc_new(); */
    /* dms_npc_apply_cfg_line("name=goblin", goblin); */

    dms_npc_array *known_npc_a = dms_npc_array_from_path("./data");
    printf("parsed %lu NPCs\n", dms_npc_array_get_length(known_npc_a));
    printf("NPC array size: %lu\n", known_npc_a->maxlen);

    for (size_t i = 0; i < dms_npc_array_get_length(known_npc_a); i++) {
      dms_npc *current = dms_npc_array_get_element(known_npc_a, i);
      printf("%s\n HP %d, AC %d\n", current->name, current->hp, current->ac);
    }

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
