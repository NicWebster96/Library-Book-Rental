# Library Book Rental System

## Nicholas Webster

Simulation of a library's book rental system. The persons, books, and rentals are given in text files. Options are provided to the user for various user tasks. Users and books have unique IDs.

### Spring 2019
Vectors were utilized for the initial implementation of this project.

Search, add, and removal require O(n) time.

### Spring 2020
Implemented using a multimap. This allows for quicker search, add, and removal of data. The keys for the multimap are the results of performing a modulo on the IDs.

Search, add, and removal require O(log n) time.
