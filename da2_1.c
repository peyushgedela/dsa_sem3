#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a passenger
struct Passenger {
    char name[100];
    struct Passenger* next;
};

// Structure to represent a ticket
struct Ticket {
    int id;
    struct Passenger* passengers;
    struct Ticket* next;
};

// Global pointer to the list of tickets
struct Ticket* ticketList = NULL;

// Function to create a new passenger node
struct Passenger* createPassenger(const char* name) {
    struct Passenger* newPassenger = (struct Passenger*)malloc(sizeof(struct Passenger));
    if (newPassenger) {
        strcpy(newPassenger->name, name);
        newPassenger->next = NULL;
    }
    return newPassenger;
}

// Function to create a new ticket node with an empty passenger list
struct Ticket* createTicket(int id) {
    struct Ticket* newTicket = (struct Ticket*)malloc(sizeof(struct Ticket));
    if (newTicket) {
        newTicket->id = id;
        newTicket->passengers = NULL; // Initialize with an empty list of passengers
        newTicket->next = NULL;
    }
    return newTicket;
}

// Function to reserve a ticket and add a passenger
void reserveTicket(int ticketId, const char* passengerName) {
    struct Ticket* ticket = ticketList;
    while (ticket) {
        if (ticket->id == ticketId) {
            struct Passenger* newPassenger = createPassenger(passengerName);
            if (newPassenger) {
                newPassenger->next = ticket->passengers;
                ticket->passengers = newPassenger;
                printf("Reserved ticket %d for passenger: %s\n", ticketId, passengerName);
                return;
            }
        }
        ticket = ticket->next;
    }

    // If the ticket does not exist, create a new ticket
    struct Ticket* newTicket = createTicket(ticketId);
    if (newTicket) {
        struct Passenger* newPassenger = createPassenger(passengerName);
        if (newPassenger) {
            newTicket->passengers = newPassenger;
            newTicket->next = ticketList;
            ticketList = newTicket;
            printf("Reserved ticket %d for passenger: %s\n", ticketId, passengerName);
        }
    }
}

// Function to display all passengers for a ticket
void displayPassengers(int ticketId) {
    struct Ticket* ticket = ticketList;
    while (ticket) {
        if (ticket->id == ticketId) {
            struct Passenger* passenger = ticket->passengers;
            printf("Passengers for ticket %d:\n", ticketId);
            while (passenger) {
                printf("%s\n", passenger->name);
                passenger = passenger->next;
            }
            return;
        }
        ticket = ticket->next;
    }
    printf("Ticket with ID %d not found.\n", ticketId);
}

// Function to cancel a reservation for a passenger
void cancelReservation(int ticketId, const char* passengerName) {
    struct Ticket* ticket = ticketList;
    while (ticket) {
        if (ticket->id == ticketId) {
            struct Passenger* prevPassenger = NULL;
            struct Passenger* passenger = ticket->passengers;
            while (passenger) {
                if (strcmp(passenger->name, passengerName) == 0) {
                    if (prevPassenger) {
                        prevPassenger->next = passenger->next;
                    } else {
                        ticket->passengers = passenger->next;
                    }
                    free(passenger);
                    printf("Reservation canceled for passenger: %s\n", passengerName);
                    return;
                }
                prevPassenger = passenger;
                passenger = passenger->next;
            }
        }
        ticket = ticket->next;
    }
    printf("Passenger %s not found on ticket with ID %d.\n", passengerName, ticketId);
}

// Function to display all tickets and their passengers
void displayAllTickets() {
    struct Ticket* ticket = ticketList;
    while (ticket) {
        printf("Ticket ID: %d\n", ticket->id);
        struct Passenger* passenger = ticket->passengers;
        printf("Passengers:\n");
        while (passenger) {
            printf("%s\n", passenger->name);
            passenger = passenger->next;
        }
        printf("\n");
        ticket = ticket->next;
    }
}

int main() {
    while (1) {
        printf("\nAirline Ticket Reservation System\n");
        printf("1. Reserve a Ticket\n");
        printf("2. Cancel Reservation\n");
        printf("3. Display Passengers\n");
        printf("4. Display All Tickets\n");
        printf("5. Exit\n");

        int choice;
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            int ticketId;
            char name[100];
            printf("Enter Ticket ID: ");
            scanf("%d", &ticketId);
            printf("Enter Passenger Name: ");
            scanf("%s", name);
            reserveTicket(ticketId, name);
        } else if (choice == 2) {
            int ticketId;
            char name[100];
            printf("Enter Ticket ID: ");
            scanf("%d", &ticketId);
            printf("Enter Passenger Name: ");
            scanf("%s", name);
            cancelReservation(ticketId, name);
        } else if (choice == 3) {
            int ticketId;
            printf("Enter Ticket ID: ");
            scanf("%d", &ticketId);
            displayPassengers(ticketId);
        } else if (choice == 4) {
            displayAllTickets();
        } else if (choice == 5) {
            break;
        } else {
            printf("Invalid choice. Please enter a valid option.\n");
        }
    }

    // Free allocated memory before exiting the program
    struct Ticket* ticket = ticketList;
    while (ticket) {
        struct Ticket* tempTicket = ticket;
        struct Passenger* passenger = ticket->passengers;
        while (passenger) {
            struct Passenger* tempPassenger = passenger;
            passenger = passenger->next;
            free(tempPassenger);
        }
        ticket = ticket->next;
        free(tempTicket);
    }

    return 0;
}
