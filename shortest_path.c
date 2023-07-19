#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

#define MAX_VERTICES 100
#define MAX_CITY_NAME 20
#define MAX_INPUT_LENGTH 100
#define UNDEFINED -1

char* reverse(char* word) {
    int front = 0;
    int end = strlen(word) - 1;
    while (front < end) {
        char temp = word[front];
        word[front] = word[end];
        word[end] = temp;
        front++;
        end--;
    }
    return word;
}

void print_help() {
    printf("Commands:\n");
    printf("\tlist - list all cities\n");
    printf("\t<city1> <city2> - find the shortest path between two cities\n");
    printf("\thelp - print this help message\n");
    printf("\texit - exit the program\n");
}

void print_path(char* path) {
    path = reverse(path);
    char* token = strtok(path, "\n");
    while (token != NULL) {
        printf("%s\n", reverse(token));
        token = strtok(NULL, "\n");
    }
}

int read_vertices(const char* filename, char vertices[MAX_VERTICES][MAX_CITY_NAME]) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: could not open file %s\n", filename);
        return -1;
    }

    int num_vertices = 0;
    char temp[MAX_CITY_NAME];
    while (num_vertices < MAX_VERTICES && fgets(temp, MAX_CITY_NAME, file) != NULL) {
        temp[strcspn(temp, "\n")] = '\0';
        strcpy(vertices[num_vertices], temp);
        num_vertices++;
    }
    fclose(file);
    return num_vertices;
}

int find_index(const char* city, char city_list[MAX_VERTICES][MAX_CITY_NAME], int num_vertices) {
    for (int i = 0; i < num_vertices; i++) {
        if (strcmp(city, city_list[i]) == 0) {
            return i;
        }
    }
    return -1;
}

int read_distances(const char* filename, int distances[MAX_VERTICES][MAX_VERTICES], int num_vertices, char city_list[MAX_VERTICES][MAX_CITY_NAME]) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: could not open file %s\n", filename);
        return -1;
    }

    char temp[MAX_INPUT_LENGTH];
    while (fgets(temp, MAX_INPUT_LENGTH, file) != NULL) {
        char from[MAX_CITY_NAME], to[MAX_CITY_NAME];
        int distance;
        if (sscanf(temp, "%s %s %d", from, to, &distance) == 3) {
            int from_index = find_index(from, city_list, num_vertices);
            int to_index = find_index(to, city_list, num_vertices);
            if (from_index != -1 && to_index != -1) {
                distances[from_index][to_index] = distance;
                distances[to_index][from_index] = distance;
            }
        }
    }
    fclose(file);
    return 0;
}

int find_shortest_path(int distances[MAX_VERTICES][MAX_VERTICES], char city_list[MAX_VERTICES][MAX_CITY_NAME], int num_vertices, const char* from, const char* to) {
    if (find_index(from, city_list, num_vertices) == -1
    || find_index(to, city_list, num_vertices) == -1) {
        printf("Invalid Command\n");
        print_help();
        return -1;
    }
    
    int visited[num_vertices];
    int distance[num_vertices];
    int previous[num_vertices];

    for (int i = 0; i < num_vertices; i++) {
        visited[i] = 0;
        distance[i] = INT_MAX;
        previous[i] = UNDEFINED;
    }

    int from_index = find_index(from, city_list, num_vertices);
    distance[from_index] = 0;

    for (int i = 0; i < num_vertices; i++) {
        int min_distance = INT_MAX;
        int min_vertex = UNDEFINED;
        for (int j = 0; j < num_vertices; j++) {
            if (!visited[j] && distance[j] < min_distance) {
                min_distance = distance[j];
                min_vertex = j;
            }
        }

        //printf("Min distance: %d Min vertex: %d\n", min_distance, min_vertex);

        if (min_distance == INT_MAX) {
            break;
        }
        visited[min_vertex] = 1;

        for (int j = 0; j < num_vertices; j++) {
            int new_distance;
            if (distances[min_vertex][j] == INT_MAX) new_distance = INT_MAX;
            else new_distance = distance[min_vertex] + distances[min_vertex][j];
            if (!visited[j] && new_distance < distance[j]) {
                distance[j] = new_distance;
                previous[j] = min_vertex;
            }
        }
    }
    char* path = malloc(sizeof(char) * MAX_INPUT_LENGTH);
    int path_index = 0;
    int current_vertex = find_index(to, city_list, num_vertices);
    if (previous[current_vertex] == UNDEFINED) {
        fprintf(stderr, "Path Not Found...\n");
        return -1;
    }

    int total_distance = distance[current_vertex];

    while (current_vertex != UNDEFINED) {
        char* city_name = city_list[current_vertex];
        int city_name_length = strlen(city_name);
        memcpy(&path[path_index], city_name, city_name_length);
        path_index += city_name_length;
        if (previous[current_vertex] != UNDEFINED) {
            path[path_index++] = '\n';
        }
        current_vertex = previous[current_vertex];
    }
    path[path_index] = '\0';
    print_path(path);
    free(path);
    return total_distance;
}

void list_cities(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: could not open file %s\n", filename);
        return;
    }

    char temp[MAX_CITY_NAME];
    while (fgets(temp, MAX_CITY_NAME, file) != NULL) {
        printf("%s", temp);
    }
    fclose(file);
}

int main(int argc, char** argv) {
    if (argc != 3) {
        fprintf(stderr, "Error: Need 3 arguments\n");
    }
    while (true) {
        // Prompt the user for input
        printf("Where do you want to go today? ");
        char input[MAX_INPUT_LENGTH];
        fgets(input, MAX_INPUT_LENGTH, stdin);

        // Tokenize the input
        //char *command = strtok(input, " \n");
        char* city1 = strtok(input, " \n");
        char* city2 = strtok(NULL, " \n");

        // Handle the commands
        if (strcmp(city1, "list") == 0) {
            //printf("Cities\n");
            list_cities(argv[1]);
        } else if (strcmp(city1, "help") == 0) {
            //printf("Help here\n");
            print_help();
        } else if (strcmp(city1, "exit") == 0) {
            printf("Goodbye!\n");
            break;
        } else if (city1 == NULL || city2 == NULL) {
            printf("Invalid Command\n");
            print_help();
        } else {
            char city_list[MAX_VERTICES][MAX_CITY_NAME];
            int num_vertices = read_vertices(argv[1], city_list);
            int distances[MAX_VERTICES][MAX_VERTICES];
            for (int i = 0; i < num_vertices; i++) {
                for (int j = 0; j < num_vertices; j++) {
                    if (i == j) distances[i][j] = 0;
                    else distances[i][j] = INT_MAX;
                }
            }
            read_distances(argv[2], distances, num_vertices, city_list);
            int answer = find_shortest_path(distances, city_list, num_vertices, city1, city2);
            if (answer != -1) {
                printf("Total Distance: %d\n", answer);
            }
        }
    }
}