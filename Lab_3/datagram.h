#ifndef DATAGRAM_H
#define DATAGRAM_H

#include "fragment.h"

typedef struct Datagram
{
  unsigned long ip;
  int id;
  Fragment *fragments;
  struct Datagram *prev, *next;
} Datagram;

void add_datagram(Datagram **head, unsigned long ip, int id);
void add_fragment(Datagram **head, unsigned long ip, int id, int frag_offset, bool mf_flag, int length);

#endif
