#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

pthread_t philo[5];
sem_t room, forks[5];

void *philosopher(int i) {
	int h  = 0;
		while(h < 5) {
			sem_wait(&room);
			sem_wait(&forks[h]);
			sem_wait(&forks[ ((h+1) % 5) ]);
			printf("Philosopher %d  is currently eating.\n", i);
			sleep(2);
			sem_post(&forks[ ((h+1) % 5) ]);
			sem_post(&forks[h]);
			sem_post(&room);
			h = h + 1;
		}
	return NULL;
}

int main(void) {
	int i;
	sem_init(&room, 0 , 4);

	for (i = 0; i < 5; i++) {
		if (sem_init(&forks[i],0,1) != 0) {
			printf("Error creating semaphore fork.");
			return 1;
		}
	}

	for (i=0; i<5; i++) {
		if (pthread_create (&philo[i] , NULL, philosopher, i ) ) {
			printf("Error creating thread philo4.");
			abort();
		}
	}

	for (i=0; i<5; i++) {
		if  (pthread_join (philo[i] , NULL) )  {
			printf("Error joining thread.");
			abort();
		}
	}
sem_destroy(&forks[5]);
sem_destroy(&room);
exit(0);	
}
