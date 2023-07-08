#ifndef PARSE_NPC_H_
#define PARSE_NPC_H_

#include "dms_npc.h"
#include "options.h"
#include <dirent.h>
#include <stdlib.h>
#include <sys/types.h>

dms_npc *dms_npc_from_stream(FILE *restrict stream);

int dms_npc_apply_cfg_line(char *line, dms_npc *npc);

#endif // PARSE_NPC_H_
