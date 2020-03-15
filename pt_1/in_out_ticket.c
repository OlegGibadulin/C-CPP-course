#include "in_out_ticket.h"

int fill_tickets(FILE* const in_file, const size_t n_tickets,
                 Ticket** tickets) {
    if (!in_file || !tickets) {
        return 1;
    }
    
    printf("Input tickets data\n\n");
    
    char* str = NULL;
    int num = 0;
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
