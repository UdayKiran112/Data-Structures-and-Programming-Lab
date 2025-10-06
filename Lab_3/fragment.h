#ifndef FRAGMENT_H
#define FRAGMENT_H

#include "parser.h"

typedef struct Fragment
{
    int frag_offset;
    bool mf_flag;
    int length;
    struct Fragment *prev, *next;
} Fragment;

#endif
