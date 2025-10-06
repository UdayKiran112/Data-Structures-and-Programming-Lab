#include "parser.h"

static Datagram *datagram_head = NULL;

void parse_file(FILE *fp)
{
  if (fp == NULL)
  {
    fprintf(stderr, "Error opening file\n");
    return;
  }

  char line[256];

  while (fgets(line, sizeof(line), fp))
  {
    struct in_addr ip_adr;
    int id;
    int frag_offset = 0;  // actual fragment offset
    bool mf_flag = false; // More Fragments flag
    int length = 0;

    int flag = 0;
    char *token = strtok(line, " ");
    while (token != NULL)
    {
      if (flag == 0)
      {
        if (inet_aton(token, &ip_adr) == 0)
        {
          fprintf(stderr, "Invalid IP Address\n");
        }
      }
      else if (flag == 1)
      {
        id = atoi(token);
      }
      else if (flag == 2)
      {
        frag_offset = atoi(token);
      }
      else if (flag == 3)
      {
        mf_flag = (atoi(token) != 0);
      }
      else if (flag == 4)
      {
        length = atoi(token);
      }

      flag++;
      token = strtok(NULL, " ");
    }

    if (flag != 5)
    {
      fprintf(stderr, "Error: Invalid line format\n");
      continue;
    }

    add_datagram(&datagram_head, ip_adr.s_addr, id);
    add_fragment(&datagram_head, ip_adr.s_addr, id, frag_offset, mf_flag, length);
  }
}

void write_output(FILE *fp)
{
  if (fp == NULL)
  {
    fprintf(stderr, "Error opening file for writing\n");
    return;
  }

  Datagram *curr = datagram_head;

  while (curr != NULL)
  {
    Fragment *frag_curr = curr->fragments;
    int exp_offset = 0;
    int total_length = 0;
    int complete = 1;
    const char *error_message = NULL;
    bool has_last_fragment = false;

    while (frag_curr != NULL)
    {
      // Track if last fragment is seen
      if (frag_curr->mf_flag == 0)
        has_last_fragment = true;

      // Skip zero-length fragments for offset calculation, but count MF
      if (frag_curr->length > 0)
      {
        // Missing fragment check
        if (frag_curr->frag_offset > exp_offset)
        {
          complete = 0;
          error_message = "Missing fragments";
          break;
        }

        // Overlapping fragment check
        if (frag_curr->frag_offset < exp_offset)
        {
          complete = 0;
          error_message = "Overlapping fragments";
          break;
        }

        exp_offset = frag_curr->frag_offset + frag_curr->length;
        total_length = exp_offset;
      }

      frag_curr = frag_curr->next;
    }

    // Check if last fragment exists
    if (!has_last_fragment && complete)
    {
      complete = 0;
      error_message = "Incomplete fragments";
    }

    struct in_addr ip_addr;
    ip_addr.s_addr = curr->ip;

    if (complete)
    {
      fprintf(fp, "Datagram %s, ID %d: Complete, Total Length %d\n\n",
              inet_ntoa(ip_addr), curr->id, total_length);
    }
    else
    {
      if (error_message == NULL)
        error_message = "Reason Unknown";

      fprintf(fp, "Datagram %s, ID %d: Incomplete\n",
              inet_ntoa(ip_addr), curr->id);
      fprintf(fp, "Reason: %s\n\n", error_message);
    }

    curr = curr->next;
  }
}
