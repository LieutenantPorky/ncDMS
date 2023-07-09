#ifndef PARSE_NPC_H_
#define PARSE_NPC_H_

#include "dms_npc.h"
#include "options.h"
#include <dirent.h>
#include <stdlib.h>
#include <sys/types.h>

dms_npc *dms_npc_from_stream(FILE *restrict stream);
dms_npc_array *dms_npc_array_from_path(char *restrict filepath);

#endif // PARSE_NPC_H_
