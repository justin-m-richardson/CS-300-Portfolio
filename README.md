# CS 300 Portfolio

This repository contains my portfolio artifacts from CS 300 at Southern New Hampshire University. These projects focused on using data structures and algorithms to solve a basic programming problem. The main goal was to build an advising program for ABCU that could load course data, organize it, print the courses in alphanumeric order, and allow a user to search for a specific course and view its prerequisites.

## Portfolio Artifacts

For Project One, I included my runtime and memory analysis for the different data structures I compared. I looked at a vector, hash table, and binary search tree to decide which structure would work best for the advising program.

For Project Two, I included my working C++ code for the advising program. The program loads course information from a file, stores the courses in a binary search tree, prints the course list in alphanumeric order, and lets the user search for individual course information.

## Reflection

The problem I was solving in these projects was how to store and organize course information in a way that would be useful for academic advisors. The program needed to read course data from a file, store each course, print the full course list in order, and allow the user to look up a course and its prerequisites.

I approached the problem by first comparing different data structures. I looked at how a vector, hash table, and binary search tree would handle loading, searching, sorting, and printing course data. This helped me understand why data structures matter. The structure you choose can change how simple, fast, or organized a program is. For this project, I chose the binary search tree because it gave me a good balance between searching for courses and printing them in order.

One of the roadblocks I had was making sure the program could correctly read the CSV file and handle courses with different numbers of prerequisites. I also had to make sure the menu worked correctly and that the user could not print or search for courses before loading the data. I worked through this by breaking the program into smaller pieces and testing each part one step at a time.

This project helped me think more carefully about software design before jumping straight into code. In the past, I would mostly focus on just getting the program to work. With this project, I had to think more about how the program should be organized, how the data should be stored, and what would make the program easier to use and update later.

My work on this project also helped me improve the way I write readable and maintainable code. I used separate functions for loading the file, trimming text, converting course numbers to uppercase, printing the menu, printing the course list, and searching for course information. Keeping the code separated like that made the program easier to understand and easier to fix when something did not work right.

Overall, this course helped me get a better understanding of how data structures and algorithms affect the way programs are built. It also gave me more practice writing C++ code that is organized, readable, and designed around the actual problem being solved.
