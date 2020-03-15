/*
 Создать структуру для хранения информации об авиабилетах: 3-буквенном 
 коде и наименовании аэропортов вылета и прилета, продолжительности полета 
 и его стоимости. Составить с ее использованием программу поиска оптимальной 
 стратегии перелета из одного аэропорта в другой по критериям оптимизации 
 продолжительности или стоимости авиапутешествия.
 */

#include <stdio.h>

#include "ticket.h"
#include "input.h"
#include "in_out_ticket.h"

int main() {
    FILE* const in_file = stdin;

    int n_tickets = 0;
    printf("Input number of tickets: ");
    if (input_int_number(in_file, &n_tickets) != 0) {
        return 1;
    }

    Ticket** tickets = NULL;
    if (create_tickets(n_tickets, &tickets) != 0) {
        return 1;
    }

    if (fill_tickets(in_file, n_tickets, tickets) != 0) {
        delete_tickets(n_tickets, tickets);
        return 1;
    }

    char* departure = NULL;
    char* arrival = NULL;
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
