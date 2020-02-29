#include "ticket.h"

int create_tickets(const int tickets_num, Ticket*** tickets) {
    if (tickets_num < 1) {
        return 1;
    }

    *tickets = malloc(sizeof(Ticket*) * tickets_num);
    if (!(*tickets)) {
        return 1;
    }

    for (int i = 0; i < tickets_num; ++i) {
        Ticket* new_ticket = malloc(sizeof(Ticket));
        if (!new_ticket) {
            delete_tickets(i, *tickets);
            return 1;
        }
        (*tickets)[i] = new_ticket;
    }

    return 0;
}

void delete_tickets(const int tickets_num, Ticket** tickets) {
    for (int i = 0; i < tickets_num; ++i) {
        free(tickets[i]);
    }
    free(tickets);
}


