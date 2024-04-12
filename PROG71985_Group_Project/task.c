#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include "task.h"
#include <time.h>

#define FILENAME "todo_data.txt"
#define MAX_SEARCH 100


void save_data(TASK tasks[], int task_count) {      //save to file function
    FILE* fp = fopen(FILENAME, "w");                //open file in write mode, file pointer as fp
    if (fp == NULL) {                               //if fp NULL, exit with error message
        fprintf(stderr, "Error opening file for writing\n");
        return;
    }
    for (int i = 0; i < task_count; i++) {
       
        const char* timeToWrite = (tasks[i].notificationTime[0] != '\0') ? tasks[i].notificationTime : "-";  //write data of tasks to file
        fprintf(fp, "%d,%s,%s\n", tasks[i].task_number, tasks[i].description, timeToWrite);                  
    }
    fclose(fp);                                                                                               //close file  
}


void load_data(TASK tasks[], int* task_count) {                           //load file function
    
    FILE* fp = fopen(FILENAME, "r");                                     //open file in read mode, file pointer as fp  
    if (fp == NULL) {                                                    //if fp NNULL, exit with error message
        fprintf(stderr, "Error opening file for reading\n");
        return;
    }
    char timeBuffer[10];
    *task_count = 0;
    while (fscanf(fp, "%d,%[^,],%9s\n", &tasks[*task_count].task_number, tasks[*task_count].description, timeBuffer) == 3) {
        if (strcmp(timeBuffer, "-") != 0) { 
            strcpy(tasks[*task_count].notificationTime, timeBuffer); 
        }
        else {
            tasks[*task_count].notificationTime[0] = '\0'; 
        }
        (*task_count)++;
        if (*task_count >= MAX_NUM_TASKS) break;
    }
    fclose(fp);                     //close file
}


void add_task(TASK tasks[], int* task_count) {
    if (*task_count >= MAX_NUM_TASKS) {                                  //if task count exceeds max tasks, exit with message
        printf("Maximum number of tasks reached. Please delete a task if you want to add another one.\n");
        return;
    }
    TASK new_task;                                                      // New TASK struct to store the new task
    new_task.task_number = (*task_count) + 1;                           // Set the task number for the new task
    printf("Please enter the description of your task:\n");             // Prompt the user to enter the description for the task
    scanf(" %[^\n]", new_task.description);                             // Store the new task's description
    new_task.notificationTime[0] = '\0';                               
    tasks[*task_count] = new_task;                                      // Add the new task to the array of tasks
    (*task_count)++;                                                    // Increment the task count by 1

    // Print a confirmation message with the task number
    printf("Task #%d added.\n", new_task.task_number);
}


void delete_task(TASK tasks[], int* task_count) {
    int task_num_del;                                                           //declare var to hold task number to delete
    printf("Please enter the task number of the task you want to delete\n");    //prompt user to enter number of desired task to delete
    scanf("%i", &task_num_del);                                                 //store in var
    bool task_found = false;                                                    //set var to false, check if task num is valid
    for (int i = 0; i < *task_count; i++) {                                     //for all tasks in current task count
        if (tasks[i].task_number == task_num_del) {                             //if task_num_del is found within
            task_found = true;                                                  //task found = true
            for (int a = i; a < *task_count - 1; a++) {                         //shift other tasks down one
                tasks[a] = tasks[a + 1];
            }
            (*task_count)--;                                                    //minus current task count by 1
            printf("Task was deleted\n");
            break;
        }
    }
    if (!task_found) {                                                          //if task wasnt found, tell user
        printf("Task not found\n");
    }
}

void edit_task(TASK tasks[]) {
    int task_num;                                                               //declare var to store which task to edit
    printf("Enter the number of the task you wish to edit\n");                  //prompt user to enter in which task they want to edit
    scanf("%i", &task_num);                                                     //store in task_num
    bool task_found = false;                                                    //set var to false, to check if task is found
    for (int i = 0; i < MAX_NUM_TASKS; i++) {                                   //for all tasks, if requested task is found, task_found is true
        if (tasks[i].task_number == task_num) {
            task_found = true;
            printf("Please enter the new description of the task you want to edit\n");      //prompt user to enter new description of task
            scanf(" %[^\n]", tasks[i].description);                                         //store it in requested tasks description
            printf("Task updated\n");
            break;
        }
    }
    if (!task_found) {                                                          //if not found tell user
        printf("Task number entered was not found\n");
    }
}

void display_single_task(TASK tasks[]) {
    int task_num;                                                                   //declare var to store which task to display
    printf("Please enter the task number of the task you wish to display\n");       //prompt user to enter which task to display, store in var
    scanf("%d", &task_num);
    bool task_found = false;                                                        //set var to false, to check if task is found
    for (int i = 0; i < MAX_NUM_TASKS; i++) {                                       //for all tasks, if requested task is found, task_found is true
        if (tasks[i].task_number == task_num) {
            task_found = true;
            printf("Task #: %d\nTask Description: %s\n", tasks[i].task_number, tasks[i].description);   //print task number, task description of task
            if (tasks[i].notificationTime[0] != '\0') {  // assuming an unset notificationTime starts with a null terminator
                printf("Notification Time: %s\n", tasks[i].notificationTime);
            }
            else {
                printf("No notification set for this task.\n");
            }
            break;
        }
    }   
    if (!task_found) {                                                              //if task wasnt found tell user
        printf("Task number entered was not found\n");
    }
}

void display_ranged_tasks(TASK tasks[], int task_count) {   
    int task_start, task_end;                                                       //declare vars to hold upper and lower limits of range to display
    printf("Please enter start of range you wish to display\n");                    //prompt user to enter upper and lower limits of range and store
    scanf("%d", &task_start);
    printf("Please enter end of range you wish to display\n");
    scanf("%d", &task_end);
    if (task_start < 1 || task_end > task_count || task_start > task_end) {         //if range is invalid, return with error message
        printf("Invalid range entered\n");
        return;
    }
    for (int i = task_start - 1; i < task_end; i++) {                               //for tasks within range, print task number, task description
        printf("Task #: %d, \nTask Description: %s\n", tasks[i].task_number, tasks[i].description);
        if (tasks[i].notificationTime[0] != '\0') {                                 
            printf("Notification Time: %s\n", tasks[i].notificationTime);           // Print the notification time
        }
        else {
            printf("No notification set for this task.\n");                         // Inform the user if no notification is set
        }
        printf("\n");                                                               
    }
}
void display_all_tasks(TASK tasks[], int task_count) {
    if (task_count == 0) {                                                          //if current task count is 0, no tasks, tell user
        printf("No available tasks to display\n");
        return;
    }
    for (int i = 0; i < task_count; i++) {                                          //for all current tasks, print task number, task description
        printf("Task #: %d, \nTask Description: %s\n", tasks[i].task_number, tasks[i].description);
        if (tasks[i].notificationTime[0] != '\0') {                                 // Check if a notification time is set
            printf("Notification Time: %s\n", tasks[i].notificationTime);
        }
    }

}
      

 

void search_task(TASK tasks[], int task_count) {
    char search[MAX_SEARCH];                                                        //declare var to hold keywords, with max input size MAX_SEARCH
    printf("Please enter a keyword(s) you wish to search for\n");                   //prompt user to enter in what to search for
    scanf(" %[^\n]", search);                                                       //scan and store in search var
    bool task_found = false;                                                        //set task found to false
    for (int i = 0; i < task_count; i++) {                                          //for all current tasks
        if (strstr(tasks[i].description, search)) {                                 //if search var is found in task description
            task_found = true;                                                      //task found = true
            printf("Task #: %d, \nTask Description: %s\n", tasks[i].task_number, tasks[i].description);     //print that task out
        }
    }
    if (!task_found) {                                                              //if task not found, tell user
        printf("Task was not found\n");
    }
}

void check_and_display_notifications(TASK tasks[], int task_count) {
    time_t now = time(NULL);                                                        // Obtain the current time
    struct tm* now_tm = localtime(&now);
    char current_time_str[20];
    strftime(current_time_str, sizeof(current_time_str), "%H:%M", now_tm);

    for (int i = 0; i < task_count; i++) {
        if (strcmp(tasks[i].notificationTime, current_time_str) == 0) {
            printf("Notification for task: %s\n", tasks[i].description);           // Display the notification message
                                                          
            strcpy(tasks[i].notificationTime, "");                                 // Reset notificationTime
        }
    }
}



void set_task_notification(TASK tasks[], int* task_count) {
    int taskNumber, hours, minutes;
    char notificationTime[20];
    bool validTime = false;

    printf("Enter the task number you want to set a notification for: ");
    scanf("%d", &taskNumber);
    while (getchar() != '\n');                                                                                                     // Clear the input buffer
    int taskIndex = taskNumber - 1;                                                                                                // Adjust for zero-based index
    if (taskIndex < 0 || taskIndex >= *task_count) {                                                                               // Check for valid the task number
        printf("Invalid task number.\n");
        return;
    }
    while (!validTime) {                                                                                                           // Loop until a valid time is entered
        printf("Enter the notification time (HH:MM format): ");
        if (scanf("%2d:%2d", &hours, &minutes) == 2 && hours >= 0 && hours < 24 && minutes >= 0 && minutes < 60) {
            validTime = true;                                                                                                      // The entered time is valid, store the notification
        }
        else {
            printf("Invalid time format. Please enter the time as HH:MM.\n");
        }
        while (getchar() != '\n');                                                                                                  // Clear the input buffer
    }
    snprintf(tasks[taskIndex].notificationTime, sizeof(tasks[taskIndex].notificationTime), "%02d:%02d", hours, minutes);

    printf("Notification set for task %d at %s.\n", taskNumber, tasks[taskIndex].notificationTime);
}

