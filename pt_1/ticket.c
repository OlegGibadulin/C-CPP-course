#include "ticket.h"

Ticket* create_ticket() {
    Ticket* new_ticket = (Ticket*) malloc(sizeof(Ticket));
    new_ticket->price = 0;
    new_ticket->arv_airport.name = NULL;
    new_ticket->dpr_airport.name = NULL;

    return new_ticket;
}

int create_tickets(const int n_tickets, Ticket*** tickets) {
    if (n_tickets < 1) {
        return 1;
    }

    *tickets = (Ticket**) malloc(sizeof(Ticket*) * n_tickets);
    if (!(*tickets)) {
        return 1;
    }

    for (size_t i = 0; i < n_tickets; ++i) {
        Ticket* new_ticket = create_ticket();
        if (!new_ticket) {
            delete_tickets(i, *tickets);
            return 1;
        }
        (*tickets)[i] = new_ticket;
    }

    return 0;
}

void delete_tickets(const int n_tickets, Ticket** tickets) {
    if (!tickets) {
        return;
    }

    for (size_t i = 0; i < n_tickets; ++i) {
        if (tickets[i]) {
            if (tickets[i]->arv_airport.name) {
                free(tickets[i]->arv_airport.name);
            }
            if (tickets[i]->dpr_airport.name) {
                free(tickets[i]->dpr_airport.name);
            }
            free(tickets[i]);
        }
    }
    free(tickets);
}

Ticket* get_optimal_price_ticket(Ticket** tickets, const int n_tickets,
                                const char* dpr_code, const char* arv_code) {
    if (!tickets || n_tickets < 1) {
        return NULL;
    }

    int i_min = -1;
    int min_price = INT_MAX;

    for (int i = 0; i < n_tickets; ++i) {
        if (strcmp(tickets[i]->dpr_airport.code, dpr_code) == 0 &&
            strcmp(tickets[i]->arv_airport.code, arv_code) == 0) {
            if (tickets[i]->price < min_price) {
                i_min = i;
                min_price = tickets[i]->price;
            }
        }
    }
    
    if (i_min == -1) {
        return NULL;
    }

    return tickets[i_min];
}

Ticket* get_optimal_duration_ticket(Ticket** tickets, const int n_tickets,
                                const char* dpr_code, const char* arv_code) {
    if (!tickets || n_tickets < 1) {
        return NULL;
    }

    int i_min = -1;
    tm min_dur;
    min_dur.tm_hour = 0;
    min_dur.tm_min = 0;

    for (int i = 0; i < n_tickets; ++i) {
        if (strcmp(tickets[i]->dpr_airport.code, dpr_code) == 0 &&
            strcmp(tickets[i]->arv_airport.code, arv_code) == 0) {
            if ((tickets[i]->fl_duration.tm_hour < min_dur.tm_hour &&
                tickets[i]->fl_duration.tm_min < min_dur.tm_min) || i == 0) {
                i_min = i;
                min_dur = tickets[i]->fl_duration;
            }

        }
    }
    
    if (i_min == -1) {
        return NULL;
    }

    return tickets[i_min];
}

