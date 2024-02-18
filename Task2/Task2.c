#include <stdio.h>
#include <pthread.h>
#include <math.h>

// Global variables
double sum = 0.0;
pthread_mutex_t mutex_lock;

// Data structure for thread range
typedef struct Range {
    int start;
    int end;
    int id;
} Range;

// Thread function
void *calculatePi(void *p) {
    Range *range = p;
    double term;
    int i;
    for (i = range->start; i <= range->end; i++) {
        term = pow(-1, i) / (2.0 * i + 1);  // Leibniz formula
        pthread_mutex_lock(&mutex_lock);
        sum += term;  // Accumulate the sum
        pthread_mutex_unlock(&mutex_lock);
    }

    pthread_exit(NULL);
}

int main() {
    int iterations, no_of_threads, i;

    // User input
    printf("Enter the number of iterations: ");
    scanf("%d", &iterations);

    printf("Enter the number of threads: ");
    scanf("%d", &no_of_threads);

    // Input validation
    if (iterations <= 0 || no_of_threads <= 0) {
        printf("Please enter positive integers for iterations and threads.\n");
        return 1;
    }

    // Initialize mutex lock
    pthread_mutex_init(&mutex_lock, NULL);

    // Thread and range arrays
    pthread_t threads[no_of_threads];
    Range ranges[no_of_threads];

    // Calculate iterations per thread and remainder
    int slice_per_thread = iterations / no_of_threads;
    int remainder = iterations % no_of_threads;

    int start = 0;
    int end = slice_per_thread - 1;

    // Assign start and end indices for each thread
    for (i = 0; i < no_of_threads; i++) {
        ranges[i].start = start;
        ranges[i].end = end;
        ranges[i].id = i;
        start = ranges[i].end + 1;
        end = start + slice_per_thread - 1;
    }
    
    // Create threads and execute the 'calculatePi' function
    for (i = 0; i < no_of_threads; i++) {
        pthread_create(&threads[i], NULL, calculatePi, &ranges[i]);
    }

    // Wait for all threads to finish execution
    for (i = 0; i < no_of_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy mutex lock
    pthread_mutex_destroy(&mutex_lock);

    // Calculate the approximate value of Pi using the Leibniz formula
    double pi = 4 * sum;

    // Output the approximate value of Pi
    printf("The approximate value of PI is: %.6f\n", pi);

    return 0;
}

