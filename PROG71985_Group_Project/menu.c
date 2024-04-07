#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void startmenu() {
	printf("\nWelcome to our To-Do List Program\n\n");		//print start menu for users to see their options
	printf("a) add a task\n");
	printf("b) delete an existing task\n");
	printf("c) update an existing task\n");
	printf("d) display a task\n");
	printf("e) display a range of tasks\n");
	printf("f) display all tasks\n");
	printf("g) search for task\n");
	printf("h) quit\n");

}
char get_selection() {
	char selection;
	printf("Please enter your selection:\n");
	scanf(" %c", &selection);

	while (getchar() != '\n');								//clear input buffer

	return selection;
}