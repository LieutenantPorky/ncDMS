#ifndef DMS_NPC_H_
#define DMS_NPC_H_
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

enum attribute_names { STR, DEX, CON, INT, WIS, CHA };
enum npc_type { NPC, PLAYER };

typedef struct dms_npc dms_npc;
struct dms_npc {
  char *name;
  enum npc_type type;
  int hp;
  int xp;
  int ac;
  int attributes[6];
  /* size_t numAttacks; */
};

dms_npc *dms_npc_init(dms_npc *);
dms_npc *dms_npc_new();
void dms_npc_destroy(dms_npc *);
dms_npc *dms_npc_v_init(size_t size, dms_npc vector[size]);
dms_npc *dms_npc_v_new(size_t size);

typedef struct dms_npc_array dms_npc_array;
struct dms_npc_array {
  dms_npc *element;
  size_t len;
  size_t maxlen;
};

dms_npc_array *dms_npc_array_init(dms_npc_array *npc_a);
dms_npc_array *dms_npc_array_new();
dms_npc *dms_npc_array_get_element(dms_npc_array *npc_a, size_t position);
int dms_npc_array_add_element(dms_npc_array *npc_a, dms_npc *element);
size_t dms_npc_array_get_length(dms_npc_array *npc_a);
void dms_npc_array_destroy(dms_npc_array *);

#endif // DMS_NPC_H_
