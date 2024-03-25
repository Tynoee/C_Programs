#include <stdio.h>
#include <stdlib.h>


int max(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

void knapsack(char *input_file, char *output_file) {
    FILE *input = fopen(input_file, "r");
    if (input == NULL) {
        perror("Error opening input file");
        exit(EXIT_FAILURE);
    }

    int n, capacity;
    fscanf(input, "%d %d", &n, &capacity);

    int *values = malloc(n * sizeof(int));
    int *volumes = malloc(n * sizeof(int));

    if (values == NULL || volumes == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n; i++) {
        fscanf(input, "%d %d", &values[i], &volumes[i]);
    }

    fclose(input);

    int **table = malloc((n + 1) * sizeof(int *));
    if (table == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i <= n; i++) {
        table[i] = malloc((capacity + 1) * sizeof(int));
        if (table[i] == NULL) {
            perror("Memory allocation failed");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= capacity; j++) {
            if (i == 0 || j == 0) {
                table[i][j] = 0;
            } else if (volumes[i - 1] <= j) {
                table[i][j] = max(table[i - 1][j], values[i - 1] + table[i - 1][j - volumes[i - 1]]);
            } else {
                table[i][j] = table[i - 1][j];
            }
        }
    }

    int *selected_items = malloc(n * sizeof(int));
    if (selected_items == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    int i = n, j = capacity;

    while (i > 0 && j > 0) {
        if (table[i][j] != table[i - 1][j]) {
            selected_items[i - 1] = 1;
            j -= volumes[i - 1];
        } else {
            selected_items[i - 1] = 0;
        }
        i--;
    }

    FILE *output = fopen(output_file, "w");
    if (output == NULL) {
        perror("Error opening output file");
        exit(EXIT_FAILURE);
    }

    fprintf(output, "%d\n", table[n][capacity]);

    for (int i = 0; i < n; i++) {
        fprintf(output, "%d ", selected_items[i]);
    }

    fclose(output);

    free(values);
    free(volumes);
    free(selected_items);

    for (int i = 0; i <= n; i++) {
        free(table[i]);
    }
    free(table);
}

int main() {
    char input_file[] = "data_7.txt";
    char output_file[] = "solution.txt";
    knapsack(input_file, output_file);

    return 0;
}

