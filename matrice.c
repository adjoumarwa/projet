
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define N1 3
#define M1 3
#define N2 3
#define M2 3
#define N (N1 * M2)
#define NUM_THREADS 3 // Adjust as needed

// Matrices B, C, et A
int B[N1][M1];
int C[M1][M2];
int A[N1][M2];

// Buffer  d'une dimension
int buffer[N];
int in = 0;  // Index d'écriture
int out = 0; // Index de lecture

// Sémaphores pour synchroniser l'accès aux données
sem_t empty;
sem_t full;
pthread_mutex_t mutex;
// Fonction producteur
void* producteur(void* arg) {
    for (int i = 0; i < N1; ++i) {
        // Calcul de la ligne i de la matrice  A
        for (int j = 0; j < M2; ++j) {
            A[i][j] = 0;
            for (int k = 0; k < M1; ++k) {
                A[i][j] += B[i][k] * C[k][j];
            }
        }

        // Ajouter la ligne dans le tampon
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buffer[in] = i;  
       in = (in + 1) % N;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }

    pthread_exit(NULL);
}

// Fonction consommateur
void consommateur() {
    for (int i = 0; i < N1; ++i) {
        // Traiter la ligne i au besoin
        int row;
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        row = buffer[out];
        out = (out + 1) % N;
         pthread_mutex_unlock(&mutex);
        sem_post(&empty);

       
    }
}

int main() {
    //verification 
    if(M2 != N1) {
        printf("can't multiple \n");
        exit(EXIT_FAILURE);
    }
    // Initialisation des matrices B et C avec des valeurs aléatoires
    for (int i = 0; i < N1; ++i) {
        for (int j = 0; j < M1; ++j) {
            B[i][j] = rand() % 10;  
    }
    }

    for (int i = 0; i < M1; ++i) {
        for (int j = 0; j < M2; ++j) {
            C[i][j] = rand() % 10; 
        }
    }
//affiche matrice B C 
    printf("\n matrice  B \n");
    for (int i = 0; i < N1; i++)
    {
        for (int j = 0; j < M1; j++)
            printf("%d  ", B[i][j]);
        printf("\n");
    }
    printf("\nmatrice   C \n");
    for (int i = 0; i < N2; i++) {
        for (int j = 0; j < M2; j++)
            printf("%d  ", C[i][j]);
        printf("\n");
    }
    // Initialisation des sémaphores
     pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, N);
    sem_init(&full, 0, 0);

    // Création des threads producteurs
    pthread_t producteur_threads[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_create(&producteur_threads[i], NULL, producteur, NULL);
    }

    // Thread consommateur
    consommateur();

    // Attente de la fin des threads producteurs
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(producteur_threads[i], NULL);
    }

    // Affichage de la matrice résultante A
    printf("Matrice résultante A :\n");
    for (int i = 0; i < N1; ++i) {
        for (int j = 0; j < M2; ++j) {
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }

    // Destruction des sémaphores
     pthread_mutex_init(&mutex, NULL);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;

}
