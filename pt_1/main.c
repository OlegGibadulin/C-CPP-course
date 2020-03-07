/*
 Создать структуру для хранения информации об авиабилетах: 3-буквенном 
 коде и наименовании аэропортов вылета и прилета, продолжительности полета 
 и его стоимости. Составить с ее использованием программу поиска оптимальной 
 стратегии перелета из одного аэропорта в другой по критериям оптимизации 
 продолжительности или стоимости авиапутешествия.
 */

#include <stdio.h>
#include <string.h>

#include "ticket.h"
#include "input.h"

int fill_tickets(FILE* const in_file, const size_t n_tickets,
                 Ticket** tickets);

void print_ticket_data(const Ticket* ticket);

int main() {
    FILE* const in_file = stdin;

    int n_tickets;
    printf("Input number of tickets: ");
    if (input_int_number(in_file, &n_tickets) != 0) {
        return 1;
    }

    Ticket** tickets;
    if (create_tickets(n_tickets, &tickets) != 0) {
        return 1;
    }

    if (fill_tickets(in_file, n_tickets, tickets) != 0) {
        delete_tickets(n_tickets, tickets);
        return 1;
    }

    char* departure;
    char* arrival;
    printf("Input code of departure airport: ");
    if (!(departure = input_string(in_file))) {
        delete_tickets(n_tickets, tickets);
        return 1;
    }
    printf("Input code of arrival airport: ");
    if (!(arrival = input_string(in_file))) {
        delete_tickets(n_tickets, tickets);
        return 1;
    }

    Ticket* optimal_ticket = get_optimal_price_ticket(tickets, n_tickets, departure, arrival);
    if (!optimal_ticket) {
        delete_tickets(n_tickets, tickets);
        printf("There are not tickets from %s to %s\n", departure, arrival);
        return 1;
    }
    printf("Optimal ticket by price\n");
    print_ticket_data(optimal_ticket);

    optimal_ticket = get_optimal_duration_ticket(tickets, n_tickets, departure, arrival);
    if (!optimal_ticket) {
        delete_tickets(n_tickets, tickets);
        printf("There are not tickets from %s to %s\n", departure, arrival);
        return 1;
    }
    printf("Optimal ticket by flight duration\n");
    print_ticket_data(optimal_ticket);
    

    delete_tickets(n_tickets, tickets);
    free(departure);
    free(arrival);
    
    return 0;
}


int fill_tickets(FILE* const in_file, const size_t n_tickets,
                 Ticket** tickets) {
    printf("Input tickets data\n\n");
    
    char* str;
    int num;
    tm time;
    for (size_t i = 0; i < n_tickets; ++i) {
        Ticket* cur_ticket = tickets[i];
        Airport* arv_airport = &cur_ticket->arv_airport;
        Airport* dpr_airport = &cur_ticket->dpr_airport;

        printf("Ticket %lu\n", i + 1);
        printf("Input name of departure airport: ");
        if (!(str = input_string(in_file))) {
            return 1;
        }
        dpr_airport->name = str;

        printf("Input code of departure airport: ");
        if (!(str = input_string(in_file)) || strlen(str) != 3) {
            return 1;
        }
        strcpy(dpr_airport->code, str);
        free(str);
        
        printf("Input name of arrival airport: ");
        if (!(str = input_string(in_file))) {
            return 1;
        }
        arv_airport->name = str;

        printf("Input code of arrival airport: ");
        if (!(str = input_string(in_file)) || strlen(str) != 3) {
            return 1;
        }
        strcpy(arv_airport->code, str);
        free(str);

        printf("Input flight duration: ");
        if (input_hours_and_minutes(in_file, &time) != 0) {
            return 1;
        }
        cur_ticket->fl_duration = time;

        printf("Input ticket price: ");
        if (input_int_number(in_file, &num) != 0) {
            return 1;
        }
        cur_ticket->price = num;

        printf("\n");
    }
    
    return 0;
}

void print_ticket_data(const Ticket* ticket) {
    if (!ticket) {
        return;
    }

    printf("Ticket %s-%s\n", ticket->dpr_airport.code,
                             ticket->arv_airport.code);
    printf("%s - %s\n", ticket->dpr_airport.name,
                      ticket->arv_airport.name);

    if (ticket->fl_duration.tm_min != 0) {
        printf("Flight duration: %d:%d\n", ticket->fl_duration.tm_hour,
                                     ticket->fl_duration.tm_min);
    } else {
        printf("Flight duration: %d:0%d\n", ticket->fl_duration.tm_hour,
                                     ticket->fl_duration.tm_min);
    }

    printf("Price: %d\n\n", ticket->price);
}

