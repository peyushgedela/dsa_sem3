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

// Structure to represent an airplane
struct Airplane {
    int id;
    int capacity;
    struct Ticket* tickets;
    struct Airplane* next;
};

// Global pointers to the list of airplanes
struct Airplane* airplaneList = NULL;
struct Airplane* currentAirplane = NULL;

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

// Function to create a new airplane with a given capacity
struct Airplane* createAirplane(int id, int capacity) {
    struct Airplane* newAirplane = (struct Airplane*)malloc(sizeof(struct Airplane));
    if (newAirplane) {
        newAirplane->id = id;
        newAirplane->capacity = capacity;
        newAirplane->tickets = NULL;
        newAirplane->next = NULL;
    }
    return newAirplane;
}

// Function to reserve a ticket and add a passenger
void reserveTicket(int ticketId, const char* passengerName) {
    if (currentAirplane == NULL) {
        // No airplanes available, create the first one
        currentAirplane = createAirplane(1, 60);
        airplaneList = currentAirplane;
    }

    struct Ticket* ticket = currentAirplane->tickets;
    while (ticket) {
        if (ticket->id == ticketId) {
            struct Passenger* newPassenger = createPassenger(passengerName);
            if (newPassenger) {
                newPassenger->next = ticket->passengers;
                ticket->passengers = newPassenger;
                printf("Reserved ticket %d for passenger: %s on Airplane %d\n", ticketId, passengerName, currentAirplane->id);
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
            newTicket->next = currentAirplane->tickets;
            currentAirplane->tickets = newTicket;
            printf("Reserved ticket %d for passenger: %s on Airplane %d\n", ticketId, passengerName, currentAirplane->id);
        }
    }

    // Check if the current airplane is filled
    if (currentAirplane->tickets != NULL && currentAirplane->capacity == currentAirplane->tickets->id) {
        // Move to the next airplane
        if (currentAirplane->next == NULL) {
            // Create a new airplane
            currentAirplane->next = createAirplane(currentAirplane->id + 1, 60);
        }
        currentAirplane = currentAirplane->next;
    }
}

// Function to display all passengers for a ticket
void displayPassengers(int ticketId) {
    struct Airplane* airplane = airplaneList;
    while (airplane) {
        struct Ticket* ticket = airplane->tickets;
        while (ticket) {
            if (ticket->id == ticketId) {
                struct Passenger* passenger = ticket->passengers;
                printf("Passengers for ticket %d on Airplane %d:\n", ticketId, airplane->id);
                while (passenger) {
                    printf("%s\n", passenger->name);
                    passenger = passenger->next;
                }
                return;
            }
            ticket = ticket->next;
        }
        airplane = airplane->next;
    }
    printf("Ticket with ID %d not found.\n", ticketId);
}

// Function to cancel a reservation for a passenger
void cancelReservation(int ticketId, const char* passengerName) {
    struct Airplane* airplane = airplaneList;
    while (airplane) {
        struct Ticket* ticket = airplane->tickets;
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
                        printf("Reservation canceled for passenger: %s on Airplane %d\n", passengerName, airplane->id);
                        return;
                    }
                    prevPassenger = passenger;
                    passenger = passenger->next;
                }
            }
            ticket = ticket->next;
        }
        airplane = airplane->next;
    }
    printf("Passenger %s not found on ticket with ID %d.\n", passengerName, ticketId);
}

// Function to display all airplanes, tickets, and passengers
void displayAll() {
    struct Airplane* airplane = airplaneList;
    while (airplane) {
        printf("Airplane ID: %d\n", airplane->id);
        struct Ticket* ticket = airplane->tickets;
        printf("Tickets:\n");
        while (ticket) {
            printf("Ticket ID: %d\n", ticket->id);
            printf("Passengers:\n");
            struct Passenger* passenger = ticket->passengers;
            while (passenger) {
                printf("%s\n", passenger->name);
                passenger = passenger->next;
            }
            ticket = ticket->next;
        }
        printf("\n");
        airplane = airplane->next;
    }
}

int main() {
    while (1) {
        printf("\nAirline Ticket Reservation System\n");
        printf("1. Reserve a Ticket\n");
        printf("2. Cancel Reservation\n");
        printf("3. Display Passengers\n");
        printf("4. Display All\n");
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
            displayAll();
        } else if (choice == 5) {
            break;
        } else {
            printf("Invalid choice. Please enter a valid option.\n");
        }
    }

    // Free allocated memory before exiting the program
    struct Airplane* airplane = airplaneList;
    while (airplane) {
        struct Airplane* tempAirplane = airplane;
        struct Ticket* ticket = airplane->tickets;
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
        airplane = airplane->next;
        free(tempAirplane);
    }

    return 0;
}
