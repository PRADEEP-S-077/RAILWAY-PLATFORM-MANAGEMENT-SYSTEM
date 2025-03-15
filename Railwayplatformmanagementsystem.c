#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for a Train Node
typedef struct Train {
    int trainNumber;
    char trainName[50];
    struct Train* next;
} Train;

// Structure for Platform Queue
typedef struct Platform {
    Train* front;
    Train* rear;
} Platform;

// Function to initialize platform queue
void initPlatform(Platform* platform) {
    platform->front = platform->rear = NULL;
}

// Function to add a train to the platform queue
void addTrain(Platform* platform, int number, char name[]) {
    Train* newTrain = (Train*)malloc(sizeof(Train));
    newTrain->trainNumber = number;
    strcpy(newTrain->trainName, name);
    newTrain->next = NULL;

    if (platform->rear == NULL) { // If queue is empty
        platform->front = platform->rear = newTrain;
    } else {
        platform->rear->next = newTrain;
        platform->rear = newTrain;
    }

    printf("Train %d (%s) added to the platform queue.\n", number, name);
}

// Function to remove a train (departure) from the platform queue
void removeTrain(Platform* platform) {
    if (platform->front == NULL) {
        printf("No trains on the platform.\n");
        return;
    }

    Train* temp = platform->front;
    printf("Train %d (%s) is departing...\n", temp->trainNumber, temp->trainName);
    
    platform->front = platform->front->next;
    if (platform->front == NULL) {
        platform->rear = NULL;
    }

    free(temp);
}

// Function to display trains waiting on the platform
void displayTrains(Platform* platform) {
    if (platform->front == NULL) {
        printf("No trains currently on the platform.\n");
        return;
    }

    printf("Trains waiting on the platform:\n");
    Train* temp = platform->front;
    while (temp != NULL) {
        printf("Train %d: %s\n", temp->trainNumber, temp->trainName);
        temp = temp->next;
    }
}

// Main Function
int main() {
    Platform platform;
    initPlatform(&platform);

    int choice, trainNumber;
    char trainName[50];

    while (1) {
        printf("\nRailway Platform Management System\n");
        printf("1. Add Train\n");
        printf("2. Depart Train\n");
        printf("3. Display Trains\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Train Number: ");
                scanf("%d", &trainNumber);
                printf("Enter Train Name: ");
                scanf(" %[^\n]s", trainName);
                addTrain(&platform, trainNumber, trainName);
                break;
            case 2:
                removeTrain(&platform);
                break;
            case 3:
                displayTrains(&platform);
                break;
            case 4:
                printf("Exiting System...\n");
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
