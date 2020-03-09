#ifndef in_out_ticket_h
#define in_out_ticket_h

#include <stdio.h>
#include <string.h>

#include "ticket.h"
#include "input.h"

int fill_tickets(FILE* const in_file, const size_t n_tickets,
                 Ticket** tickets);

void print_ticket_data(const Ticket* ticket);

#endif /* in_out_ticket_h */
