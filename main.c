#include <stdio.h>      // Standard Input/Output functions
#include <stdlib.h>     // Standard library for malloc, free, exit
#include <string.h>     // String handling functions

#define MAX_NAME 50     // Maximum length for applicant's name
#define MAX_STR 100     // Maximum length for address

// Define the structure for a credit card application node
struct node {
    char name[MAX_NAME];              // Applicant's name
    char gender[10];                  // Applicant's gender
    char address[MAX_STR];            // Applicant's address
    char date[15];                    // Date of application (dd/mm/yyyy)
    char time[10];                    // Time of application (hh:mm)
    char ifsc[20];                    // Bank IFSC code
    char acc_no[20];                  // Bank account number
    float balance;                    // Bank account balance
    char service_type[20];            // Type of service requested
    char phone[15];                   // Contact phone number
    char transaction_status[20];      // Status of transaction
    char pan[15];                     // PAN card number
    char aadhar[20];                  // Aadhar card number
    char payment_status[20];          // Payment status (Paid/Unpaid)
    struct node *next;                // Pointer to the next application node
};

// Global pointers to manage the queue
struct node *front = NULL;           // Pointer to the front of the queue
struct node *rear = NULL;            // Pointer to the rear of the queue

// Function declarations
void enqueue();                      // Add a new application to the queue
void dequeue();                      // Process and remove the first application
void peek();                         // Display all pending applications
void searchApplication();            // Search for an application by name
void updateApplication();            // Update an application by name
void deleteApplication();            // Delete an application by name
void inputApplicationDetails(struct node *nn);  // Get details from user
void displayApplication(struct node *temp);     // Display a single application

int main() {
    int choice;  // Variable to store user choice

    // Infinite loop to show the menu repeatedly
    while (1) {
        // Displaying the menu
        printf("\n===== Credit Card Application Menu =====\n");
        printf("1. Apply for Service\n");
        printf("2. View All Applications\n");
        printf("3. Process Next Application\n");
        printf("4. Search Application\n");
        printf("5. Update Application\n");
        printf("6. Delete Application\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);     // Take user input
        getchar();                // Clear the newline from input buffer

        // Switch based on user choice
        switch (choice) {
            case 1: enqueue(); break;         // Add new application
            case 2: peek(); break;            // View all applications
            case 3: dequeue(); break;         // Process the first application
            case 4: searchApplication(); break; // Search application by name
            case 5: updateApplication(); break; // Update application by name
            case 6: deleteApplication(); break; // Delete application by name
            case 7:                              // Exit program
                printf("Thank you for using the Application System.\n");
                exit(0);                         // Exit with success code
            default:
                printf("Invalid choice. Try again.\n");  // Invalid input
        }
    }
    return 0;  // Exit from main (not reached due to infinite loop)
}

// Function to add an application to the queue
void enqueue() {
    struct node *nn = (struct node *)malloc(sizeof(struct node));  // Allocate memory
    if (nn == NULL) {
        printf("Memory allocation failed.\n");  // Handle memory failure
        return;
    }
    inputApplicationDetails(nn);  // Get details from user
    nn->next = NULL;              // Next is NULL as this will be the last node

    if (rear == NULL) {           // If queue is empty
        front = rear = nn;        // New node is both front and rear
    } else {
        rear->next = nn;          // Link the new node after rear
        rear = nn;                // Update rear to point to new node
    }
    printf("Application submitted successfully for %s.\n", nn->name);  // Confirmation
}

// Function to remove and process the front application
void dequeue() {
    if (front == NULL) {
        printf("No applications to process.\n");  // Queue is empty
        return;
    }
    struct node *temp = front;           // Temporarily hold the front node
    printf("\n--- Processed Application ---\n");
    displayApplication(temp);            // Display the application
    front = front->next;                 // Move front to next node
    if (front == NULL) rear = NULL;      // If queue is empty, rear is NULL too
    free(temp);                          // Free memory of processed node
}

// Function to display all applications in the queue
void peek() {
    if (front == NULL) {
        printf("No pending applications.\n");  // Queue is empty
        return;
    }
    struct node *temp = front;          // Start from front
    printf("\n--- Pending Applications ---\n");
    while (temp != NULL) {              // Traverse through queue
        displayApplication(temp);       // Show each application
        temp = temp->next;              // Move to next node
    }
}

// Function to display a single application
void displayApplication(struct node *temp) {
    printf("\nName: %s | Gender: %s | Phone: %s\n", temp->name, temp->gender, temp->phone);
    printf("Address: %s\n", temp->address);
    printf("Date: %s | Time: %s\n", temp->date, temp->time);
    printf("IFSC: %s | Account No: %s | Balance: %.2f\n", temp->ifsc, temp->acc_no, temp->balance);
    printf("Service: %s | PAN: %s | Aadhar: %s\n", temp->service_type, temp->pan, temp->aadhar);
    printf("Transaction: %s | Payment: %s\n", temp->transaction_status, temp->payment_status);
}

// Function to get application details from user
void inputApplicationDetails(struct node *nn) {
    printf("Enter Name: ");
    fgets(nn->name, MAX_NAME, stdin);
    nn->name[strcspn(nn->name, "\n")] = '\0';  // Remove newline

    printf("Enter Gender: ");
    fgets(nn->gender, sizeof(nn->gender), stdin);
    nn->gender[strcspn(nn->gender, "\n")] = '\0';

    printf("Enter Address: ");
    fgets(nn->address, sizeof(nn->address), stdin);
    nn->address[strcspn(nn->address, "\n")] = '\0';

    printf("Enter Date (dd/mm/yyyy): ");
    fgets(nn->date, sizeof(nn->date), stdin);
    nn->date[strcspn(nn->date, "\n")] = '\0';

    printf("Enter Time (hh:mm): ");
    fgets(nn->time, sizeof(nn->time), stdin);
    nn->time[strcspn(nn->time, "\n")] = '\0';

    printf("Enter IFSC Code: ");
    fgets(nn->ifsc, sizeof(nn->ifsc), stdin);
    nn->ifsc[strcspn(nn->ifsc, "\n")] = '\0';

    printf("Enter Account Number: ");
    fgets(nn->acc_no, sizeof(nn->acc_no), stdin);
    nn->acc_no[strcspn(nn->acc_no, "\n")] = '\0';

    printf("Enter Balance: ");
    scanf("%f", &nn->balance);    // Read float
    getchar();                    // Clear newline

    printf("Enter Service Type: ");
    fgets(nn->service_type, sizeof(nn->service_type), stdin);
    nn->service_type[strcspn(nn->service_type, "\n")] = '\0';

    printf("Enter Phone Number: ");
    fgets(nn->phone, sizeof(nn->phone), stdin);
    nn->phone[strcspn(nn->phone, "\n")] = '\0';

    printf("Enter Transaction Status: ");
    fgets(nn->transaction_status, sizeof(nn->transaction_status), stdin);
    nn->transaction_status[strcspn(nn->transaction_status, "\n")] = '\0';

    printf("Enter PAN Number: ");
    fgets(nn->pan, sizeof(nn->pan), stdin);
    nn->pan[strcspn(nn->pan, "\n")] = '\0';

    printf("Enter Aadhar Number: ");
    fgets(nn->aadhar, sizeof(nn->aadhar), stdin);
    nn->aadhar[strcspn(nn->aadhar, "\n")] = '\0';

    printf("Enter Payment Status (Paid/Unpaid): ");
    fgets(nn->payment_status, sizeof(nn->payment_status), stdin);
    nn->payment_status[strcspn(nn->payment_status, "\n")] = '\0';
}

// Function to search an application by name
void searchApplication() {
    if (front == NULL) {
        printf("No applications to search.\n");
        return;
    }
    char searchName[MAX_NAME];
    printf("Enter name to search: ");
    fgets(searchName, MAX_NAME, stdin);
    searchName[strcspn(searchName, "\n")] = '\0';

    struct node *temp = front;
    int found = 0;
    while (temp != NULL) {
        if (strcmp(temp->name, searchName) == 0) {
            printf("\n--- Application Found ---\n");
            displayApplication(temp);
            found = 1;
            break;
        }
        temp = temp->next;
    }
    if (!found)
        printf("Application not found.\n");
}

// Function to update an application by name
void updateApplication() {
    if (front == NULL) {
        printf("No applications to update.\n");
        return;
    }
    char updateName[MAX_NAME];
    printf("Enter name to update: ");
    fgets(updateName, MAX_NAME, stdin);
    updateName[strcspn(updateName, "\n")] = '\0';

    struct node *temp = front;
    int found = 0;
    while (temp != NULL) {
        if (strcmp(temp->name, updateName) == 0) {
            printf("\n--- Updating Application ---\n");
            inputApplicationDetails(temp);
            printf("Application updated.\n");
            found = 1;
            break;
        }
        temp = temp->next;
    }
    if (!found)
        printf("Application not found.\n");
}

// Function to delete an application by name
void deleteApplication() {
    if (front == NULL) {
        printf("No applications to delete.\n");
        return;
    }
    char deleteName[MAX_NAME];
    printf("Enter name to delete: ");
    fgets(deleteName, MAX_NAME, stdin);
    deleteName[strcspn(deleteName, "\n")] = '\0';

    struct node *temp = front, *prev = NULL;
    while (temp != NULL) {
        if (strcmp(temp->name, deleteName) == 0) {
            if (temp == front) {
                front = front->next;
                if (front == NULL) rear = NULL;
            } else {
                prev->next = temp->next;
                if (temp == rear) rear = prev;
            }
            free(temp);
            printf("Application deleted.\n");
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("Application not found.\n");
}