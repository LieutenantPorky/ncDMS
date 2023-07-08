#include "parse_npc.h"
#include "dms_npc.h"
#include "options.h"
#include <stdio.h>
#include <string.h>
#include <strings.h>

int dms_npc_apply_cfg_line(char *line, dms_npc *npc) {

  if (!npc) {
    return 1;
  }

  char identifier[STR_SIZE + 1];
  sscanf(line, "%" STR(STR_SIZE) "[^=]%*s", identifier);

  if (!strcasecmp("name", identifier)) {
    char tmp[STR_SIZE + 1];
    sscanf(line, "%*[^=] %*[=] %" STR(STR_SIZE) "s", tmp);
    strcpy(npc->name, tmp);

  } else if (!strcasecmp("type", identifier)) {
    char tmp[STR_SIZE + 1];
    sscanf(line, "%*[^=] %*[=] %" STR(STR_SIZE) "s", tmp);

    if (!strcasecmp(tmp, "npc")) {
      npc->type = NPC;
    } else {
      npc->type = PLAYER;
    }

  } else if (!strcasecmp("hp", identifier)) {
    int tmp = 0;
    sscanf(line, "%*[^=] %*[=] %" STR(STR_SIZE) "d", &tmp);
    npc->hp = tmp;

  } else if (!strcasecmp("xp", identifier)) {
    int tmp = 0;
    sscanf(line, "%*[^=] %*[=] %" STR(STR_SIZE) "d", &tmp);
    npc->xp = tmp;
  }

  return 0;
}
