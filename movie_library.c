#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Movie {
    char title[100];
    int releaseYear;
    char genre[50];
    float rating;
};

void displayMovies(struct Movie* movies, int numMovies) {
    printf("\nMovie List:\n");
    for (int i = 0; i < numMovies; i++) {
        printf("Title: %s\n", movies[i].title);
        printf("Release Year: %d\n", movies[i].releaseYear);
        printf("Genre: %s\n", movies[i].genre);
        printf("Rating: %.2f\n", movies[i].rating);
        printf("------------------------\n");
    }
}

const char* filename = "movies.txt";
void writeToFile(struct Movie* movies, int numMovies) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    fwrite(movies, sizeof(struct Movie), numMovies, file);

    fclose(file);
}


void readFromFile(struct Movie* movies, int* numMovies) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    *numMovies = fread(movies, sizeof(struct Movie), *numMovies, file);

    fclose(file);
}

void searchMovies(struct Movie* movies, int numMovies, const char* searchTerm) {
    printf("\nSearch Results:\n");
    for (int i = 0; i < numMovies; i++) {
        if (strstr(movies[i].title, searchTerm) || strstr(movies[i].genre, searchTerm)) {
            printf("Title: %s\n", movies[i].title);
            printf("Release Year: %d\n", movies[i].releaseYear);
            printf("Genre: %s\n", movies[i].genre);
            printf("Rating: %.2f\n", movies[i].rating);
            printf("------------------------\n");
        }
    }
}

int compareMovies(const void* a, const void* b) {
    return ((struct Movie*)a)->releaseYear - ((struct Movie*)b)->releaseYear;
}

void sortMoviesByReleaseYear(struct Movie* movies, int numMovies) {
    qsort(movies, numMovies, sizeof(struct Movie), compareMovies);
}

void sortMoviesByRating(struct Movie* movies, int numMovies) {
    qsort(movies, numMovies, sizeof(struct Movie),
          (int (*)(const void*, const void*))&strcmp);
}

int main() {
    const int MAX_MOVIES = 100;

    struct Movie movies[MAX_MOVIES];
    int numMovies = 0;

    int choice;
    char searchTerm[100];

    do {
        printf("\n1. Add Movie\n");
        printf("2. Display Movies\n");
        printf("3. Save Movies to File\n");
        printf("4. Load Movies from File\n");
        printf("5. Search Movies\n");
        printf("6. Sort Movies by Release Year\n");
        printf("7. Sort Movies by Rating\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\nEnter Movie Title: ");
                scanf("%s", movies[numMovies].title);
                printf("Enter Release Year: ");
                scanf("%d", &movies[numMovies].releaseYear);
                printf("Enter Genre: ");
                scanf("%s", movies[numMovies].genre);
                printf("Enter Rating: ");
                scanf("%f", &movies[numMovies].rating);
                numMovies++;
                break;

            case 2:
                displayMovies(movies, numMovies);
                break;

            case 3:
                writeToFile(movies, numMovies);
                printf("Movies saved to file.\n");
                break;

            case 4:
                readFromFile(movies, &numMovies);
                printf("Movies loaded from file.\n");
                break;

            case 5:
                printf("Enter search term: ");
                scanf("%s", searchTerm);
                searchMovies(movies, numMovies, searchTerm);
                break;

            case 6:
                sortMoviesByReleaseYear(movies, numMovies);
                printf("Movies sorted by release year.\n");
                break;

            case 7:
                sortMoviesByRating(movies, numMovies);
                printf("Movies sorted by rating.\n");
                break;

            case 0:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);

    return 0;
}

