#include <gtest/gtest.h>
#include <stdbool.h>

#include "ticket.h"

void fill_ticket(Ticket* ticket) {
    if (!ticket) {
        return;
    }

    strcpy(ticket->dpr_airport.code, "TRT");
    strcpy(ticket->arv_airport.code, "OSL");
    ticket->fl_duration.tm_hour = 12;
    ticket->fl_duration.tm_min = 12;
    ticket->price = 1000;
}

void fill_optimal_ticket(Ticket* ticket) {
    if (!ticket) {
        return;
    }

    strcpy(ticket->dpr_airport.code, "TRT");
    strcpy(ticket->arv_airport.code, "OSL");
    ticket->fl_duration.tm_hour = 10;
    ticket->fl_duration.tm_min = 10;
    ticket->price = 900;
}

// create_tickets

TEST(create_tickets, neg) {
    Ticket** tickets = NULL;

    ASSERT_EQ(create_tickets(-1, &tickets), 1);
    ASSERT_EQ((tickets == NULL), true);
}

TEST(create_tickets, pos) {
    Ticket** tickets = NULL;

    ASSERT_EQ(create_tickets(1, &tickets), 0);
    ASSERT_EQ((tickets != NULL), true);

    delete_tickets(1, tickets);
}


// get_optimal_price_ticket

TEST(get_optimal_price_ticket, neg_tickets) {
    Ticket** tickets = NULL;
    const char* dpr = "TRT";
    const char* arv = "OSL";
    Ticket* ret_val = get_optimal_price_ticket(tickets, 10, dpr, arv);
    
    ASSERT_EQ((ret_val == NULL), true);
}

TEST(get_optimal_price_ticket, neg_n) {
    Ticket** tickets = NULL;
    create_tickets(1, &tickets);
    fill_ticket(tickets[0]);
    const char* dpr = "TRT";
    const char* arv = "OSL";
    Ticket* optimal_ticket = get_optimal_price_ticket(tickets, -1, dpr, arv);
    bool check = (optimal_ticket == NULL);
    delete_tickets(1, tickets);
    
    ASSERT_EQ(check, true);
}

TEST(get_optimal_price_ticket, neg_not_found) {
    Ticket** tickets = NULL;
    create_tickets(1, &tickets);
    fill_ticket(tickets[0]);
    const char* dpr = "OSL";
    const char* arv = "TRT";
    Ticket* optimal_ticket = get_optimal_price_ticket(tickets, -1, dpr, arv);
    bool check = (optimal_ticket == NULL);
    delete_tickets(1, tickets);
    
    ASSERT_EQ(check, true);
}

TEST(get_optimal_price_ticket, neg_wrong_way) {
    Ticket** tickets = NULL;
    create_tickets(1, &tickets);
    fill_ticket(tickets[0]);
    const char* dpr = "TRT";
    Ticket* optimal_ticket = get_optimal_price_ticket(tickets, -1, dpr, dpr);
    bool check = (optimal_ticket == NULL);
    delete_tickets(1, tickets);
    
    ASSERT_EQ(check, true);
}

TEST(get_optimal_price_ticket, pos_one) {
    Ticket** tickets = NULL;
    create_tickets(1, &tickets);
    fill_ticket(tickets[0]);
    const char* dpr = "TRT";
    const char* arv = "OSL";
    Ticket* optimal_ticket = get_optimal_price_ticket(tickets, 1, dpr, arv);
    bool check = (optimal_ticket == tickets[0]);
    delete_tickets(1, tickets);
    
    ASSERT_EQ(check, true);
}

TEST(get_optimal_price_ticket, pos_two) {
    Ticket** tickets = NULL;
    create_tickets(2, &tickets);
    fill_ticket(tickets[0]);
    fill_optimal_ticket(tickets[1]);
    const char* dpr = "TRT";
    const char* arv = "OSL";
    Ticket* optimal_ticket = get_optimal_price_ticket(tickets, 2, dpr, arv);
    bool check = (optimal_ticket == tickets[1]);
    delete_tickets(2, tickets);
    
    ASSERT_EQ(check, true);
}


// get_optimal_duration_ticket

TEST(get_optimal_duration_ticket, neg_tickets) {
    Ticket** tickets = NULL;
    const char* dpr = "TRT";
    const char* arv = "OSL";
    Ticket* ret_val = get_optimal_duration_ticket(tickets, 10, dpr, arv);
    
    ASSERT_EQ((ret_val == NULL), true);
}

TEST(get_optimal_duration_ticket, neg_n) {
    Ticket** tickets = NULL;
    create_tickets(1, &tickets);
    fill_ticket(tickets[0]);
    const char* dpr = "TRT";
    const char* arv = "OSL";
    Ticket* optimal_ticket = get_optimal_duration_ticket(tickets, -1, dpr, arv);
    bool check = (optimal_ticket == NULL);
    delete_tickets(1, tickets);
    
    ASSERT_EQ(check, true);
}

TEST(get_optimal_duration_ticket, neg_not_found) {
    Ticket** tickets = NULL;
    create_tickets(1, &tickets);
    fill_ticket(tickets[0]);
    const char* dpr = "OSL";
    const char* arv = "TRT";
    Ticket* optimal_ticket = get_optimal_duration_ticket(tickets, -1, dpr, arv);
    bool check = (optimal_ticket == NULL);
    delete_tickets(1, tickets);
    
    ASSERT_EQ(check, true);
}

TEST(get_optimal_duration_ticket, neg_wrong_way) {
    Ticket** tickets = NULL;
    create_tickets(1, &tickets);
    fill_ticket(tickets[0]);
    const char* dpr = "TRT";
    Ticket* optimal_ticket = get_optimal_duration_ticket(tickets, -1, dpr, dpr);
    bool check = (optimal_ticket == NULL);
    delete_tickets(1, tickets);
    
    ASSERT_EQ(check, true);
}

TEST(get_optimal_duration_ticket, pos_one) {
    Ticket** tickets = NULL;
    create_tickets(1, &tickets);
    fill_ticket(tickets[0]);
    const char* dpr = "TRT";
    const char* arv = "OSL";
    Ticket* optimal_ticket = get_optimal_duration_ticket(tickets, 1, dpr, arv);
    bool check = (optimal_ticket == tickets[0]);
    delete_tickets(1, tickets);
    
    ASSERT_EQ(check, true);
}

TEST(get_optimal_duration_ticket, pos_two) {
    Ticket** tickets = NULL;
    create_tickets(2, &tickets);
    fill_ticket(tickets[0]);
    fill_optimal_ticket(tickets[1]);
    const char* dpr = "TRT";
    const char* arv = "OSL";
    Ticket* optimal_ticket = get_optimal_duration_ticket(tickets, 2, dpr, arv);
    bool check = (optimal_ticket == tickets[1]);
    delete_tickets(2, tickets);
    
    ASSERT_EQ(check, true);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    
    return RUN_ALL_TESTS();
}


