#include "main.h"

int main(int argc, char *argv[]) {

  if (!DEBUG) {
    init();
  }
  if (DEBUG) {
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
