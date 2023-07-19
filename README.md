# Dijkstra's Algorithm

## Table of Contents

- [Description](#description)
- [Further Thinking Questions](#further-thinking-questions)

## Description

This repository contains a C program that helps users find the shortest path between various cities. The program is designed to read a list of cities and their distances from a provided dataset, allowing users to interactively find the most efficient route between any two cities.

### Commands
- list: Displays the list of all cities available in the dataset.
- <city1> <city2>: Finds the shortest path between city1 and city2 along with the total distance.
- help: Prints the available commands and their usage.
- exit: Exits the program.

### Datasets
The datasets used in the program consists of several cities and their distances from one another. The distance information is stored in two separate files: one contains the list of cities, and the other contains the distances between each pair of cities.

## Further Thinking Questions 

1. What is the difference between a directed and undirected graph?

   A directed graph has vertices with edges that go in one direction only. For example, there may be one-way directed edge from point A to point B, but no directed edge from point B to point A. In an undirected graph, vertices that are connected by an edge mean that there is no specific direction. Travel between the vertices in either direction is possible as long as they are connected by an edge.

2. What is the Big O of Dijkstra's algorithm.... 
   * Assuming you used an array (or list) to store the vertices.

      When using an array to store the vertices, finding the minimum distance to travel to adjacent vertices takes O(|V|) time. Then since each vertex has to be visited, there will be two for loops, resulting in O(|V|^2) time. Then there's also the time complexity of updating the values of adjacent vertices. This will take O(|E|) time, therefore making the total time complexity O(|V|^2 + |E|).

   * Assuming you used a heap / priority queue to store the vertices.

      When using a heap/priority queue to store the vertices, inserting vertices into the data structure as well as extracting the minimum edge takes O(log|V|) time. This has to be done |E| times in order to check each edge. Updating the vertex's distance list to every other connected vertex will take O(|V|), therefore the total time complexity is O(|V| + |E|log|V|).

3. Explain in your own words what that means for larger graphs when trying to find the shortest distance.

   This means that using a heap/priority queue will be faster than using an array, especially for larger graphs because the time difference will become greater and greater.

4. For this assignment, you didn't need the most "efficient" set of data structures (for example, a heap wasn't required). However, think on the scale of google/apple maps - they have to deal with millions of vertices and edges. What data structures would you use to store the graph? Why? Somethings to consider - would you be able to store the entire graph at a time? Could you break it up into smaller pieces? How would you do that? Would there be advantages to caching/memoization of paths? You are free to explore your thoughts on this subject/reflect on various ideas. Other than a realization of some scalability of problems, there isn't a wrong answer.

   On the scale of google/apple maps, adjacency matrices and adjecency lists would still be useful to store distances. This in conjunction with a heap/priority queue will result in faster times for determining shortest path. We probably wouldn't be able to store the entire graph at a time, so methods such as graph partitioning will be used. That way, determining the place in a certain set of nodes in a smaller graph that would lead to a shorter path to the user's destination would be easier, since all possible locations in that certain area would have been considered already. Graph partitioning could be done by grouping certain vertices based on location, on travel routes (such as by car, by plane, by train, etc.), on popularity, or on any other factor. Caching/memoization of paths would of course save time, but that would mean more space will be used to store the shortest paths. If enough space isn't available to cache all the shortest paths between every single location and every other location in the world, perhaps only the most highly requested shortest routes could be cached so that it wouldn't have to be recalculated every time it's requested by a user. However, this brings up another issue: how often would these shortest paths have to be recalculated so they are kept up to date? Different flight paths, train routes, or roads/bridges may be arise that would be more time efficient. Then there's also the fact that both google maps and apple maps display multiple routes from one destination to another. They all vary based on transportation method used, price, and other factors. Transit node routing is a method that can be used to speed up the process of finding the shortest path. It pre-computes connections between common access nodes which will then be used to compute various paths for long distance travel.

5. Related to shortest distance, is a problem called the "messenger" or "traveling sales (man/person)" problem commonly abbreviated to TSP. This problem is to find the shortest path that visits **every** vertex in a graph. Another way to look at it, is you are an delivery driver, and you have a series of packages to deliver. Can you find an optimal path for your deliveries that minimizes the total distance traveled? Imagine if you had 5 stops. How many different paths are there?  There are 120 possible paths to look at! (assuming fully connected routes). 
   * How many possible paths are there if you have 6 stops?

      720 paths because it would be 6!.

   * How many possible paths are there if you have 10 stops?

      3,628,800 paths because it would be 10!.

   Finding an optimal path for this problem could involve brute forcing it. But obviously that would require extensive resources, and it wouldn't even be feasible once n starts reaching numbers of 20 or higher. Dynamic programming can also be used, with a type of dynamic programming being branch and bound. This method involves breaking a problem down into smaller sub-problems and then using bounding functions to exclude sub-problems that don't lead to the most optimal solution.

6. What type of growth is this problem?

   This problem grows factorially with the number of vertices involved.

7. Take some time to research TSP problems. It falls under a certain classification of problems? What is it?

   TSP problems fall under the combinatorial optimization class of problems. These are problems in which there is a set of solutions to the problem, but we are tasked with finding the most optimal solution. Brute forcing these problems is usually not possible, especially when more and more variables are being included (like more cities in the TSP). Therefore these problems are classified as NP-hard difficulty problems. This means that there is no known algorithm for finding the solutions to these problems in polynomial time. Because of this, we must resort to finding just reasonable solutions in reasonable amounts of time in most cases.

8. Provide some examples of fields / problems that use TSP.

   Transportation routes for delivery trucks, sales representatives, and service technicians. It's also used in optimizing routes for waste collection trucks, public transportation, and street cleaning vehicles. This means that the design of a city itself is important because locations within the city must be accessible and if the optimal route throughout the city for the various services mentioned before is found, then service costs can be cut down. TSP is also considered in network design, as the optimal path for data packets will result in faser internet speeds and overall network performance.