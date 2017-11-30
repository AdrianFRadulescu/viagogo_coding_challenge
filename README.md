

This is a program for solving the challenge presented in the Developer Test.pdf file.

The coding standards used are presented in the codingStandards.pdf

The concepts and assumptions are detailed in Architecture file.

To run this file after git pulling use the following commands:

    g++ -Wall -Werror -std=c++11 main.cpp event.cpp event_plane.cpp -o main.o
  
    ./main.o
The program generates random events on the grid, prints them and then asks the user to input the coordinates of a point, after which it returns the data available on the closest events it finds.
