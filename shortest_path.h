#ifndef SHORTEST_PATH_H
#define SHORTEST_PATH_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

#define MAX_VERTICES 100
#define MAX_CITY_NAME 20
#define MAX_INPUT_LENGTH 100
#define UNDEFINED -1

/**
 * Reverses a path so that it can be printed from front to back.
*/
char* reverse(char* word);

/**
 * Prints all commands for user.
*/
void print_help();

/**
 * Prints the actual path between the two cities.
*/
void print_path(char* path);

/**
 * Reads the vertices file stores the values.
*/
int read_vertices(const char* filename, char vertices[MAX_VERTICES][MAX_CITY_NAME]);

/**
 * Finds the index of the city in the city_list array.
*/
int find_index(const char* city, char city_list[MAX_VERTICES][MAX_CITY_NAME], int num_vertices);

/**
 * Reads the distances between vertices of cities, given to us by a file.
*/
int read_distances(const char* filename, int distances[MAX_VERTICES][MAX_VERTICES], int num_vertices, char city_list[MAX_VERTICES][MAX_CITY_NAME]);

/**
 * Implements Dijkstra's algorithm to determine shortest path.
*/
int find_shortest_path(int distances[MAX_VERTICES][MAX_VERTICES], char city_list[MAX_VERTICES][MAX_CITY_NAME], int num_vertices, const char* from, const char* to);

#endif