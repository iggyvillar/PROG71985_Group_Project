#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include "task.h"

#define FILENAME "todo_data.txt"
#define MAX_SEARCH 100

void save_data(TASK tasks[], int task_count) {                          //save to file function
    FILE* fp = fopen(FILENAME, "w");                                    //open file in write mode, file pointer as fp
    if (fp == NULL) {                                                   //if fp NULL, exit with error message
        fprintf(stderr, "Error opening file for writing\n");
        return;
    }
    fwrite(tasks, sizeof(TASK), task_count, fp);                        //write data of tasks to file
    fclose(fp);                                                         //close file
}

void load_data(TASK tasks[], int* task_count) {                         //load file function
    FILE* fp = fopen(FILENAME, "r");                                    //open file in read mode, file pointer as fp
    if (fp == NULL) {                                                   //if fp NNULL, exit with error message
        fprintf(stderr, "Error opening file for reading\n");
        return;
    }
    *task_count = fread(tasks, sizeof(TASK), MAX_NUM_TASKS, fp);        //read data store in task count ptr
    fclose(fp);                                                         //close file
}

void add_task(TASK tasks[], int* task_count) {
    if (*task_count >= MAX_NUM_TASKS) {                                 //if task count exceeds max tasks, exit with message
        printf("Maximum number of tasks reached, please delete a task if you want to add another one\n");
        return;
    }
    TASK new_task;                                                      //new TASK struct to store new_task
    new_task.task_number = (*task_count) + 1;                           //task number of new task is the current task count + 1
    printf("Please enter the description of your task\n");              //prompt user to enter in description for task
    scanf(" %[^\n]", new_task.description);                             //store in new task description
    tasks[*task_count] = new_task;                                      //add new_task to tasks struct
    (*task_count)++;                                                    //increment task count by 1
    printf("Task added\n");
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
    }
}

void display_all_tasks(TASK tasks[], int task_count) {                  
    if (task_count == 0) {                                                          //if current task count is 0, no tasks, tell user
        printf("No available tasks to display\n");
        return;
    }
    for (int i = 0; i < task_count; i++) {                                          //for all current tasks, print task number, task description
        printf("Task #: %d, \nTask Description: %s\n", tasks[i].task_number, tasks[i].description);
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

