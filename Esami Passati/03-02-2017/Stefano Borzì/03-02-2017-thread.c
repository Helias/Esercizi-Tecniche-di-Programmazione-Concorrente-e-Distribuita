/*

 * Stefano Borzì X81000003

 * Una variabile intera n, inizializzata a 0, è condivisa tra 2 thread tO, tE.
 * Il thread tE, ciclicamente:
 * 	1. attende 200 ms (N.B.: la chiamata usleep(t) attende per t microsecondi)
 * 	2. genera un int casuale pari e lo somma alla variabile condivisa n
 * 	3. se ha eseguito almeno 10 cicli e n è pari termina
 * 	4. altrimenti ricomincia da (1), a meno che abbia già compiuto 1000 iterazioni, nel qual caso termina.
 * Il thread tO, ciclicamente:
 * 	1. attende 200 ms (N.B.: la chiamata usleep(n) attende per n microsecondi)
 * 	2. genera un int casuale dispari e lo somma alla variabile condivisa n
 * 	3. se ha eseguito almeno 10 cicli e n è dispari termina
 * 	4. altrimenti ricomincia da (1), a meno che abbia già compiuto 1000 iterazioni, nel qual caso termina.

 * (Non ricorrere a un array di 2 thread per l’implementazione!)

 * Il programma termina quando tutti i thread hanno terminato la propria esecuzione. I thread scriveranno di essere terminati. Possono anche visualizzare, a ogni ciclo, il valore trovato in n.
 * Nel codice, proteggere opportunamente la variabile n dagli accessi concorrenti. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

int n = 0;
pthread_mutex_t mutex;
pthread_t t0, tE;

void *t_0() {

	int r, counter = 0;

	while (1) {	

		// 1.
		usleep(200000); // 200000 microsecondi = 200 millisecondi

		// 2.
		r = (rand() % 10);
		if (r % 2 != 0) r++; // se è DISPARI incrementa di 1

		pthread_mutex_lock(&mutex);
		n += r;
		pthread_mutex_unlock(&mutex);

		counter++;

		printf("t_0 Counter: %d, random: %d, n: %d \n", counter, r, n);

		// 3.
		if (counter >= 10 && (n % 2 == 0))
			pthread_exit(NULL);
		else if (counter > 1000) // 4.
			pthread_exit(NULL);
	}
}

void *t_E() {

		int r, counter = 0;

		while (1) {

			// 1.
			usleep(200000); // 200000 microsecondi = 200 millisecondi

			// 2.
			r = (rand() % 10);
			if (r % 2 == 0) r++; // se è PARI incrementa di 1

			pthread_mutex_lock(&mutex);
			n += r;
			pthread_mutex_unlock(&mutex);

			counter++;

			printf("t_E Counter: %d, random: %d, n: %d \n", counter, r, n);

			// 3.
			if (counter >= 10 && (n % 2 != 0))
				pthread_exit(NULL);
			else if (counter > 1000) // 4.
				pthread_exit(NULL);
		}

}

int main() {
	srand(time(NULL));
	
	pthread_mutex_init(&mutex, NULL);

	pthread_create(&t0, NULL, (void *)t_0, NULL);
	pthread_create(&tE, NULL, (void *)t_E, NULL);

	pthread_join(t0, NULL);
	pthread_join(tE, NULL);

	return 0;
}
