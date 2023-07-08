#include "dms_npc.h"

dms_npc *dms_npc_init(dms_npc *npc) {
  if (!npc) {
    return 0;
  }
  npc = (dms_npc *){0};
  return npc;
}

dms_npc *dms_npc_new() { return dms_npc_init(malloc(sizeof(dms_npc))); }
void dms_npc_destroy(dms_npc *npc) { free(npc); }
