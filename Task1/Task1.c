#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main() {
    int x, y;
    float sum_x = 0, sum_y = 0, sum_xy = 0, sum_x_squared = 0;
    int n = 0;

    // Open all four files
    FILE *fp1 = fopen("datasetLR1.txt", "r");
    FILE *fp2 = fopen("datasetLR2.txt", "r");
    FILE *fp3 = fopen("datasetLR3.txt", "r");
    FILE *fp4 = fopen("datasetLR4.txt", "r");

    // Checking if files opened successfully
    if (fp1 == NULL || fp2 == NULL || fp3 == NULL || fp4 == NULL) {
        printf("Error opening files\n");
        return 1;
    }

    // Read data from all files and calculate sum of x, y, xy, x^2
    // Read data from 1st file
    while (fscanf(fp1, "%d,%d", &x, &y) == 2) {
        sum_x += x;
        sum_y += y;
        sum_xy += x * y;
        sum_x_squared += x * x;
        n++;
    }
    fclose(fp1);

    // Read data from the 2nd file
    while (fscanf(fp2, "%d,%d", &x, &y) == 2) {
        sum_x += x;
        sum_y += y;
        sum_xy += x * y;
        sum_x_squared += x * x;
        n++;
    }
    fclose(fp2);
    
    // Read data from the 3rd file
    while (fscanf(fp3, "%d,%d", &x, &y) == 2) {
        sum_x += x;
        sum_y += y;
        sum_xy += x * y;
        sum_x_squared += x * x;
        n++;
    }
    fclose(fp3);
    
    // Read data from the 4th file
    while (fscanf(fp4, "%d,%d", &x, &y) == 2) {
        sum_x += x;
        sum_y += y;
        sum_xy += x * y;
        sum_x_squared += x * x;
        n++;
    }
    fclose(fp4);

    printf("%d", n);
    // Calculate coefficients using LR formula
    float b = (n * sum_xy - sum_x * sum_y) / (n * sum_x_squared - sum_x * sum_x);
    float a = (sum_y * sum_x_squared - sum_x * sum_xy) / (n * sum_x_squared - sum_x * sum_x);

    printf("The value of: a = %.2f and b = %.2f\n\n", a, b);

    // Print the linear equation
    printf("The linear equation (y=bx+a) is: y = %.2f x + %.2f\n", b, a);

    float user_x;
    bool valid_input = false;
    while (!valid_input) {
        printf("Enter the value of x: ");
        // Check if input was successful
        if (scanf("%f", &user_x) != 1) {
            printf("Invalid input for x. Please enter a valid numerical value: \n");
            // Clear input buffer
            while (getchar() != '\n');
        } else {
            valid_input = true;
        }
    }

    // Calculate corresponding value of y using the linear equation
    float user_y = b * user_x + a;
    printf("For x = %.2f, y = %.2f\n", user_x, user_y);

    return 0;
}

