#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

sem_t processlock;

void sharedAccess(){
	printf("Preforming critical task on customer data\n");
}

void *accountingTask(void *ptr){
	printf("Accounting task\n");
	sem_wait(&processlock);
	sharedAccess();
	sem_post(&processlock);
}

void *salesTask(void *ptr){
	printf("Sales task\n");
	sem_wait(&processlock);
	sharedAccess();
	sem_post(&processlock);
}

int main (void) {
	sem_init(&processlock, 0, 1);
	pthread_t threader[6];	
	int selection;
	int tasks[6];
	
	selectioncase:
	printf("Please select case 1, 2, 3, or 4 for testing:");
	selection = getchar();
	// printf("selection %i \n", selection); // debug statement

	// Process user selection
	switch (selection) {
		case 49:
			//printf("Selection 1\n"); // debug statement
			tasks[0] = 1;
			tasks[1] = 2;
			tasks[2] = 2;
			tasks[3] = 1;
			tasks[4] = 1;
			tasks[5] = 2;
			break;
		case 50:
			//printf("Selection 2\n"); // debug statement
			tasks[0] = 1;
			tasks[1] = 2;
			tasks[2] = 1;
			tasks[3] = 1;
			tasks[4] = 2;
			tasks[5] = 1;
			break;
		case 51:
			//printf("Selection 3\n"); // debug statement
			tasks[0] = 2;
			tasks[1] = 1;
			tasks[2] = 2;
			tasks[3] = 1;
			tasks[4] = 1;
			tasks[5] = 2;
			break;
		case 52:
			//printf("Selection 4\n"); // debug statement
			tasks[0] = 1;
			tasks[1] = 2;
			tasks[2] = 1;
			tasks[3] = 2;
			tasks[4] = 2;
			tasks[5] = 1;
			break;
		default:
			printf("Improper case selection, please try again\n");
			while ((selection = getchar()) != '\n' && selection != EOF); // Clears keyboard input buffer.

			goto selectioncase;
			break;
	}

	// Create all threads for execution
	for (int i = 0; i < 6; i++) {
		//printf("Loop Counter: %i", i);  //Debug statement		
		if (tasks[i] == 1){
			pthread_create(&threader[i], 0, &accountingTask, 0);
		}
		else{
			pthread_create(&threader[i], 0, &salesTask, 0);
		}
	}
	
	// join all threads
	for (int i = 0; i < 6; i++) {
		pthread_join(threader[i], 0);
	}
}


