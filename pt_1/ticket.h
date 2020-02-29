#ifndef ticket_h
#define ticket_h

#include <time.h>
#include <stdlib.h>

typedef struct tm tm;

typedef struct Airport {
    char* name;
    char code[3];
} Airport;

typedef struct Ticket {
    int price;
    tm flight_duration;
    Airport departure_airport;
    Airport arrival_airport;
} Ticket;

int create_tickets(const int tickets_num, Ticket*** tickets);
void delete_tickets(const int tickets_num, Ticket** tickets);

#endif /* ticket_h */
