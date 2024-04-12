#include <stdio.h>
#include "menu.h"
#include "task.h"

//prog71985 Group Project
// iggy, quinton, kaiden - prog71985 - winter24
//To-Do-List
//Program Requirements
/*1. add a new appt/task/recipe/other
2. delete an existing appt/task/recipe/other
3. update an existing appt/task/recipe/other
4. display single appt/task/recipe/other
5. display range appt/task/recipe/other
6. display all appt/task/recipe/other
7. search for appt/task/recipe/other
8. friendly/easy to use UI (or menu system)
9. save accumulated data to disk
10. load accumulated data from disk
11. you may add additional features, increasing your group’s overall
mark to a maximum of 100%.
*/
#include "task.h" // Make sure this includes the definition of TASK and any new notification-related functions

// Assuming you have a MAX_NUM_TASKS defined somewhere
#define MAX_NUM_TASKS 100

// Prototype for functions not shown here
void load_data(TASK tasks[], int* task_count);
void startmenu(void);
char get_selection(void);
void add_task(TASK tasks[], int* task_count);
void delete_task(TASK tasks[], int* task_count);
void edit_task(TASK tasks[]);
void display_single_task(TASK tasks[]);
void display_ranged_tasks(TASK tasks[], int task_count);
void display_all_tasks(TASK tasks[], int task_count);
void search_task(TASK tasks[], int task_count);
void save_data(TASK tasks[], int task_count);
void check_and_display_notifications(TASK tasks[], int task_count); 

int main(void) {
    TASK tasks[MAX_NUM_TASKS];                                      // Init TASK struct called tasks
    int task_count = 0;                                             // Init task count to 0
    char selection;                                                 // Declare var to hold user's selection

    load_data(tasks, &task_count);                                  // Load tasks, task count from file

    do {
        startmenu();
        check_and_display_notifications(tasks, task_count);         // Check and display notifications
        selection = get_selection();

        switch (selection) {
        case 'a':
            add_task(tasks, &task_count);
            break;
        case 'b':
            delete_task(tasks, &task_count);
            break;
        case 'c':
            edit_task(tasks);
            break;
        case 'd':
            display_single_task(tasks);
            break;
        case 'e':
            display_ranged_tasks(tasks, task_count);
            break;
        case 'f':
            display_all_tasks(tasks, task_count);
            break;
        case 'g':
            search_task(tasks, task_count);
            break;
        case 'h':
            set_task_notification(tasks, &task_count); 
            break;
        case 'i':
            printf("Thank you for visiting our To-Do List Program. See you soon!\n");
            break;
       ;
        default:
            printf("Selection entered was invalid, please try again!\n");
            break;
        }

        save_data(tasks, task_count);                               // Save tasks to file

    } while (selection != 'h');                                     // Loop until user decides to exit program

    return 0;
}

