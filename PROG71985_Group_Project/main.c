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

int main(void) {
    TASK tasks[MAX_NUM_TASKS];                                      //init TASK struct called tasks
    int task_count = 0;                                             //init task count to 0
    char selection;                                                 //declare var to hold users selection

    load_data(tasks, &task_count);                                  //load tasks, task count from file

    do {
        startmenu();
        selection = get_selection();

        switch (selection) {
        case 'a':
            add_task(tasks, &task_count);                           //add task, pass tasks array and task_count pointer
            break;
        case 'b':
            delete_task(tasks, &task_count);                        //delete task, pass tasks array and task_count pointer
            break;
        case 'c':
            edit_task(tasks);                                       // edit task pass tasks array
            break;
        case 'd':
            display_single_task(tasks);                             //display a task pass tasks array
            break;
        case 'e':
            display_ranged_tasks(tasks, task_count);                //display range of tasks pass tasks array and task_count
            break;
        case 'f':
            display_all_tasks(tasks, task_count);                   //display all tasks, pass tasks array and task_count
            break;
        case 'g':
            search_task(tasks, task_count);                         //seach for task, pass tasks array and task_count
            break;
        case 'h':                                                                       
            printf("Thank you for visiting our To-Do List Program. See you soon!\n");   //exit program with message
            break;
        default:
            printf("Selection entered was invalid, please try again!\n");   
            break;
        }

        save_data(tasks, task_count);                               //save tasks to file

    } while (selection != 'h');                                     //loop until user decides to exit program

    return 0;
}


