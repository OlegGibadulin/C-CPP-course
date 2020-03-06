#ifndef ticket_h
#define ticket_h

#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>

#define CHUNK_SIZE 20

typedef struct tm tm;

typedef struct Airport {
    char* name;
    char code[3];
} Airport;

typedef struct Ticket {
    int price;
    tm fl_duration;
    Airport dpr_airport;
    Airport arv_airport;
} Ticket;

int create_tickets(const size_t n_tickets, Ticket*** tickets);
void delete_tickets(const size_t n_tickets, Ticket** tickets);

Ticket* get_optimal_price_ticket(Ticket** tickets, const size_t n_tickets,
                                const char* dpr_code, const char* arv_code);

Ticket* get_optimal_duration_ticket(Ticket** tickets, const size_t n_tickets,
                                const char* dpr_code, const char* arv_code);

#endif /* ticket_h */
