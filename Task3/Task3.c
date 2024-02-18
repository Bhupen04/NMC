#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <pthread.h>

// Global variables
int *prime_arr, primecount = 0;
FILE *fileptr;
pthread_mutex_t mutex;

// Structure to define a range of numbers for each thread
struct calculate {
    int start;
    int finish;
};

// Function to check if a number is prime
int check_prime(int n) {
    int i;
    if (n <= 1)
        return 0;
    for (i = 2; i <= sqrt(n); i++) {
        if (n % i == 0)
            return 0;
    }
    return 1;
}

// Thread function to find prime numbers in a range
void *is_prime(void *ptr) {
    int i;
    struct calculate *arg = ptr;
    int st = arg->start, fi = arg->finish;

    for (i = st; i <= fi; i++) {
        int num = prime_arr[i];
        if (check_prime(num)) {
            pthread_mutex_lock(&mutex);
            primecount++;
            fprintf(fileptr, "%d\n", num);
            pthread_mutex_unlock(&mutex);
        }
    }
    pthread_exit(NULL);
}

int main() {
    int i, n = 0, j = 0, nof = 3;
    FILE *fptr;
    char filename[15], chr;
    int no_of_threads;

    // Count the total number of lines in input files to determine array size
    for (i = 1; i <= nof; i++) {
        sprintf(filename, "PrimeData%d.txt", i);
        fptr = fopen(filename, "r");
        chr = getc(fptr);
        while (chr != EOF) {
            if (chr == '\n') {
                if (chr != ' ')
                    n++;
            }
            chr = getc(fptr);
        }
        fclose(fptr);
    }

    // Get user input for the number of threads to use
    printf("Enter the number of threads to utilize: ");
    scanf("%d", &no_of_threads);

    // Create an array to store numbers from files
    struct calculate divider[no_of_threads];
    prime_arr = (int *)malloc(n * sizeof(int));

    // Read numbers from files into the array
    for (i = 1; i <= nof; i++) {
        sprintf(filename, "PrimeData%d.txt", i);
        fptr = fopen(filename, "r");

        while (!feof(fptr)) {
            fscanf(fptr, "%d\n", &prime_arr[j]);
            j++;
        }
        fclose(fptr);
    }

    // Open output file
    fileptr = fopen("Prime.txt", "w");

    // Initialize mutex
    pthread_mutex_init(&mutex, NULL);

    // Create threads to find prime numbers
    pthread_t threads[no_of_threads];
    for (i = 0; i < no_of_threads; i++) {
        divider[i].start = i * (n / no_of_threads);
        divider[i].finish = (i == no_of_threads - 1) ? n - 1 : (i + 1) * (n / no_of_threads) - 1;
        pthread_create(&threads[i], NULL, is_prime, &divider[i]);
    }

    // Wait for all threads to finish
    for (i = 0; i < no_of_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy mutex
    pthread_mutex_destroy(&mutex);

    // Output results
    printf("\nTotal Prime Count: %d\n", primecount);
    fprintf(fileptr, "\n\nThere are a total of %d prime numbers.", primecount);
    free(prime_arr);
    printf("\nProcess complete!!\n\n\"Prime.txt\" file has been created.\n");
    fclose(fileptr);

    return 0;
}

