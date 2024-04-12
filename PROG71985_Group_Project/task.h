#pragma once
#define MAXTASKSIZE 100
#define MAX_NUM_TASKS 50

typedef struct {                                //define struct to represent tasks of to do list, 2 elements, task#, and task description
    int task_number;
    char description[MAXTASKSIZE];
    char notificationTime[20];
} TASK;

void save_data(TASK tasks[], int task_count);
void load_data(TASK tasks[], int* task_count);
void add_task(TASK tasks[], int* task_count);
void delete_task(TASK tasks[], int* task_count);
void edit_task(TASK tasks[]);
void display_single_task(TASK tasks[]);
void display_ranged_tasks(TASK tasks[], int task_count);
void display_all_tasks(TASK tasks[], int task_count);
void search_task(TASK tasks[], int task_count);
void set_task_notification(TASK tasks[], int* task_count);

