## C-optimize variables

This is a script for optimizing the constants in [C-step-counter](https://github.com/MarcusNordstrom/C-Step-Counter).

## Guide

 - Clone the repo
 - Edit *PATH* in main to your CSV file collected from [C-process-raw-data](https://github.com/MarcusNordstrom/C-process-raw-data).
 - Set *correct_answer* to the amount of steps in the CSV file
 - Run cmake
 - Execute the binary

After you've done this the program finds better and better variables and prints it.

If you see that the search range is not enough you can edit the for-loops in main to have a bigger range.
