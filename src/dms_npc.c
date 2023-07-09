#include "dms_npc.h"
#include "options.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

dms_npc *dms_npc_init(dms_npc *npc) {
  if (!npc) {
    printf("did not init npc\n");
    return 0;
  }
  *npc = (dms_npc){.name = calloc(STR_SIZE, sizeof(char))};
  return npc;
}
dms_npc *dms_npc_new() { return dms_npc_init(malloc(sizeof(dms_npc))); }
void dms_npc_destroy(dms_npc *npc) { free(npc); }
dms_npc *dms_npc_v_init(size_t size, dms_npc vector[size]) {
  if (!vector) {
    return 0;
  }
  for (int i = 0; i < size; i++) {
    dms_npc_init(vector + i);
  }
  return vector;
}
dms_npc *dms_npc_v_new(size_t size) {
  return dms_npc_v_init(size, malloc(sizeof(dms_npc[size])));
}

dms_npc_array *dms_npc_array_init(dms_npc_array *npc_a) {
  *npc_a = (dms_npc_array){
      .element = dms_npc_new(),
      .len = 0,
      .maxlen = 1,
  };
  return npc_a;
}

dms_npc_array *dms_npc_array_new() {
  return dms_npc_array_init(malloc(sizeof(dms_npc_array)));
}

dms_npc *dms_npc_array_get_element(dms_npc_array *npc_a, size_t position) {
  if (position < npc_a->len) {
    return npc_a->element + position;
  }
  return 0;
}

int dms_npc_array_add_element(dms_npc_array *npc_a, dms_npc *element) {
  if (npc_a->len < npc_a->maxlen) {
    npc_a->element[npc_a->len] = *element;
    npc_a->len++;
    return 0;
  }
  dms_npc *nelement = 0;
  nelement = realloc(npc_a->element, sizeof(dms_npc[2 * npc_a->maxlen]));
  if (nelement) {
    npc_a->element = nelement;
    npc_a->maxlen *= 2;
    npc_a->element[npc_a->len] = *element;
    npc_a->len++;
    return 0;
  }
  return 1;
}

size_t dms_npc_array_get_length(dms_npc_array *npc_a) {
  if (npc_a) {
    return npc_a->len;
  }
  return 0;
}

void dms_npc_array_destroy(dms_npc_array *npc_a) {
  if (npc_a) {
    dms_npc_destroy(npc_a->element);
    free(npc_a);
  }
}
