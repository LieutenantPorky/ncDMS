#include "parse_npc.h"
#include "dms_npc.h"
#include "options.h"
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

static int dms_npc_apply_cfg_line(char *line, dms_npc *npc) {
  /* Parse and apply a config option to a dms_npc
   *INPUTS
   *line : a char* containing a line of text to apply as a config option to npc
   *npc : a dms_npc* to modify with the parsed configuration line
   *RETURNS
   * 0 on success, 1 on failure
   * */

  if (!npc) {
    return 1;
  }

  char identifier[STR_SIZE + 1];
  sscanf(line, "%" STR(STR_SIZE) "[^=]%*s", identifier);

  if (!strcasecmp("name", identifier)) {
    char tmp[STR_SIZE + 1];
    sscanf(line, "%*[^=] %*[=] %" STR(STR_SIZE) "[^\n]", tmp);
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

  } else if (!strcasecmp("ac", identifier)) {
    int tmp = 0;
    sscanf(line, "%*[^=] %*[=] %" STR(STR_SIZE) "d", &tmp);
    npc->ac = tmp;

  } else if (!strcasecmp("attributes", identifier)) {
    int attributes[6] = {0};
    sscanf(line, "%*[^=] %*[=] %d , %d , %d , %d , %d , %d", attributes,
           attributes + 1, attributes + 2, attributes + 3, attributes + 4,
           attributes + 5);

    for (int i = 0; i < 6; i++) {
      npc->attributes[i] = attributes[i];
    }
  }

  return 0;
}

dms_npc *dms_npc_from_stream(FILE *restrict stream) {
  /* Parse npc config options from a file stream, and return a newly created npc
   *based on that stream INPUTS: stream - an IO stream to parse configs from
   *OUTPUTS: a newly created dms_npc*
   **/
  dms_npc *npc;
  npc = dms_npc_new();

  char parsedline[STR_SIZE_LONG];
  while (fgets(parsedline, STR_SIZE_LONG, stream)) {
    char *pos_newline = strchr(parsedline, '\n');
    if (pos_newline) {
      *pos_newline = 0;
    }
    dms_npc_apply_cfg_line(parsedline, npc);
  }

  if (DEBUG) {
    printf("parsed NPC: %s\n", npc->name);
  }

  return npc;
}
static int one(const struct dirent *unused) { return 1; }

dms_npc_array *dms_npc_array_from_path(char *restrict filepath) {
  struct dirent **eps;
  int n;
  dms_npc_array *parsed_npc_a = dms_npc_array_new();

  n = scandir(filepath, &eps, one, alphasort);
  if (n >= 0) {
    int cnt;
    for (cnt = 0; cnt < n; ++cnt) {
      printf("filename: %s\n", eps[cnt]->d_name);
      if (eps[cnt]->d_type == DT_REG) {

        char config_path[STR_SIZE_LONG] = {0};
        sprintf(config_path, "%s/%s", filepath, eps[cnt]->d_name);

        printf("full path %s\n", config_path);

        FILE *restrict npc_config_file = fopen(config_path, "r");
        dms_npc *new_npc = dms_npc_from_stream(npc_config_file);
        dms_npc_array_add_element(parsed_npc_a, new_npc);
      }
    }
  } else {
    perror("Couldn't open the directory");
  }

  return parsed_npc_a;
}
