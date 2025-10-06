#include "datagram.h"

// Add a datagram to the linked list
void add_datagram(Datagram **head, unsigned long ip, int id)
{
    // Check if datagram already exists
    Datagram *curr = *head;

    while (curr != NULL)
    {
        if (curr->ip == ip && curr->id == id)
        {
            return;
        }
        curr = curr->next;
    }

    // Create a new datagram if it doesn't exist
    Datagram *new_datagram = (Datagram *)malloc(sizeof(Datagram));
    if (!new_datagram)
    {
        fprintf(stderr, "Error: Memory allocation failed in add_datagram.\n");
        return;
    }

    new_datagram->ip = ip;
    new_datagram->id = id;
    new_datagram->fragments = NULL;
    new_datagram->prev = NULL;
    new_datagram->next = NULL;

    // Insert at tail
    if (*head == NULL)
    {
        *head = new_datagram;
    }
    else
    {
        Datagram *tail = *head;
        while (tail->next != NULL)
        {
            tail = tail->next;
        }
        tail->next = new_datagram;
        new_datagram->prev = tail;
    }
    printf("Datagram added with IP %s, ID %d.\n", inet_ntoa(*(struct in_addr *)&ip), id);
}

// Add a fragment to the appropriate datagram
void add_fragment(Datagram **head, unsigned long ip, int id, int frag_offset, bool mf_flag, int length)
{
    // Find datagram
    Datagram *curr = *head;
    while (curr != NULL)
    {
        if (curr->ip == ip && curr->id == id)
        {
            break;
        }
        curr = curr->next;
    }

    if (curr == NULL)
    {
        fprintf(stderr, "Error: Datagram with IP %lu and ID %d not found.\n", ip, id);
        return;
    }

    // Check if fragment already exists
    Fragment *frag_curr = curr->fragments;
    while (frag_curr != NULL)
    {
        if (frag_curr->frag_offset == frag_offset)
        {
            fprintf(stderr, "Duplicate fragment offset %d for Datagram IP %lu, ID %d. Skipping.\n", frag_offset, ip, id);
            return;
        }
        frag_curr = frag_curr->next;
    }

    // Create new fragment (Allocate memory and initialize)
    Fragment *new_fragment = (Fragment *)malloc(sizeof(Fragment));
    if (!new_fragment)
    {
        fprintf(stderr, "Error: Memory allocation failed in add_fragment.\n");
        return;
    }

    new_fragment->frag_offset = frag_offset;
    new_fragment->mf_flag = mf_flag ? 1 : 0;
    new_fragment->length = length;
    new_fragment->prev = NULL;
    new_fragment->next = NULL;

    // Insert fragment in sorted order based on frag_offset
    frag_curr = curr->fragments;
    Fragment *prev = NULL;

    // Find the correct position to insert
    while (frag_curr != NULL && frag_curr->frag_offset < frag_offset)
    {
        prev = frag_curr;
        frag_curr = frag_curr->next;
    }

    new_fragment->next = frag_curr;
    new_fragment->prev = prev;

    // Update the next pointer of the previous fragment
    if (prev != NULL)
    {
        // Inserting in the middle
        prev->next = new_fragment;
    }
    else
    {
        // Inserting at the head
        curr->fragments = new_fragment;
    }

    // Update the next pointer of the previous fragment
    if (frag_curr != NULL)
    {
        frag_curr->prev = new_fragment;
    }
}