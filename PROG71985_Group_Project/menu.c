#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void startmenu() {


	printf("========================================\n");
	printf("   Welcome to our To-Do List Program\n");			//print start menu for users to see their options
	printf("========================================\n\n");
	printf("Please select an option:\n\n");
	printf("  a) Add a task\n");
	printf("  b) Delete an existing task\n");
	printf("  c) Update an existing task\n");
	printf("  d) Display a task\n");
	printf("  e) Display a range of tasks\n");
	printf("  f) Display all tasks\n");
	printf("  g) Search for a task\n");
	printf("  i) Set a notification for a task\n");
	printf("  h) Quit\n\n");
}

char get_selection() {
	char selection;
	printf("Please enter your selection:\n");
	scanf(" %c", &selection);

	while (getchar() != '\n');								//clear input buffer

	return selection;
}