#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TICKETS 10
#define FILE_NAME "tickets.txt"

typedef struct {
    int ticketId;
    char event[50];
    int isBooked;
} Ticket;

Ticket tickets[MAX_TICKETS];

void saveTickets() {
    FILE *fp = fopen(FILE_NAME, "wb");
    if (!fp) {
        printf("Error saving tickets!\n");
        return;
    }
    fwrite(tickets, sizeof(Ticket), MAX_TICKETS, fp);
    fclose(fp);
}

void loadTickets() {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) {
        // If file doesn't exist, initialize
        for (int i = 0; i < MAX_TICKETS; i++) {
            tickets[i].ticketId = 1000 + i;
            sprintf(tickets[i].event, "Event %d", i + 1);
            tickets[i].isBooked = 0;
        }
        saveTickets();
    } else {
        fread(tickets, sizeof(Ticket), MAX_TICKETS, fp);
        fclose(fp);
    }
}

void viewTickets() {
    printf("\nAvailable Tickets:\n");
    for (int i = 0; i < MAX_TICKETS; i++) {
        if (!tickets[i].isBooked)
            printf("Ticket ID: %d | Event: %s\n", tickets[i].ticketId, tickets[i].event);
    }
}

void bookTicket() {
    int id;
    printf("Enter Ticket ID to book: ");
    scanf("%d", &id);
    for (int i = 0; i < MAX_TICKETS; i++) {
        if (tickets[i].ticketId == id && !tickets[i].isBooked) {
            tickets[i].isBooked = 1;
            saveTickets();
            printf("Ticket booked successfully!\n");
            return;
        }
    }
    printf("Ticket not available!\n");
}

void cancelTicket() {
    int id;
    printf("Enter Ticket ID to cancel: ");
    scanf("%d", &id);
    for (int i = 0; i < MAX_TICKETS; i++) {
        if (tickets[i].ticketId == id && tickets[i].isBooked) {
            tickets[i].isBooked = 0;
            saveTickets();
            printf("Ticket cancelled successfully!\n");
            return;
        }
    }
    printf("No such booked ticket found!\n");
}

int main() {
    int choice;
    loadTickets();

    do {
        printf("\n===== Ticket Booking System =====\n");
        printf("1. View Available Tickets\n");
        printf("2. Book Ticket\n");
        printf("3. Cancel Ticket\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: viewTickets(); break;
            case 2: bookTicket(); break;
            case 3: cancelTicket(); break;
            case 4: printf("Thank you!\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 4);

    return 0;
}