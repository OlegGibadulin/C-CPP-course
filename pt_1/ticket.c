#include "ticket.h"

int create_tickets(const size_t n_tickets, Ticket*** tickets) {
    if (n_tickets < 1) {
        return 1;
    }

    *tickets = malloc(sizeof(Ticket*) * n_tickets);
    if (!(*tickets)) {
        return 1;
    }

    for (size_t i = 0; i < n_tickets; ++i) {
        Ticket* new_ticket = malloc(sizeof(Ticket));
        if (!new_ticket) {
            delete_tickets(i, *tickets);
            return 1;
        }
        (*tickets)[i] = new_ticket;
    }

    return 0;
}

void delete_tickets(const size_t n_tickets, Ticket** tickets) {
    for (size_t i = 0; i < n_tickets; ++i) {
        free(tickets[i]);
    }
    free(tickets);
}

Ticket* get_optimal_price_ticket(Ticket** tickets, const size_t n_tickets,
                                const char* dpr_code, const char* arv_code) {
    if (!tickets || n_tickets < 1) {
        return NULL;
    }

    size_t i_min;
    int min_price = INT_MAX;

    for (size_t i = 0; i < n_tickets; ++i) {
        if (strcmp(tickets[i]->dpr_airport.code, dpr_code) == 0 &&
            strcmp(tickets[i]->arv_airport.code, arv_code) == 0) {
            if (tickets[i]->price < min_price) {
                i_min = i;
                min_price = tickets[i]->price;
            }
        }
    }

    return tickets[i_min];
}

Ticket* get_optimal_duration_ticket(Ticket** tickets, const size_t n_tickets,
                                const char* dpr_code, const char* arv_code) {
    if (!tickets || n_tickets < 1) {
        return NULL;
    }

    size_t i_min;
    tm min_dur;
    min_dur.tm_hour = 0;
    min_dur.tm_min = 0;

    for (size_t i = 0; i < n_tickets; ++i) {
        if (strcmp(tickets[i]->dpr_airport.code, dpr_code) == 0 &&
            strcmp(tickets[i]->arv_airport.code, arv_code) == 0) {
            if ((tickets[i]->fl_duration.tm_hour < min_dur.tm_hour &&
                tickets[i]->fl_duration.tm_min < min_dur.tm_min) || i == 0) {
                i_min = i;
                min_dur = tickets[i]->fl_duration;
            }

        }
    }

    return tickets[i_min];
}









