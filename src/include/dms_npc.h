#ifndef DMS_NPC_H_
#define DMS_NPC_H_
#include "main.h"
#include <stdio.h>

enum attribute_names { STR, DEX, CON, INT, WIS, CHA };
enum npc_type { NPC, PLAYER };

typedef struct dms_npc dms_npc;
struct dms_npc {
  char *name;
  enum npc_type type;
  int hp;
  int xp;
  int attributes[6];
  /* size_t numAttacks; */
};

dms_npc *dms_npc_init(dms_npc *);
dms_npc *dms_npc_new();
void dms_npc_destroy(dms_npc *);

typedef struct dms_npc_v dms_npc_v;
struct dms_npc_v {
  dms_npc *element;
  size_t len;
  size_t maxlen;
};

#endif // DMS_NPC_H_
