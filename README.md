# CS 3503 - Assignment 1 - Number Base Converter

## Author
Omar Ayyad

## Descriptions
This is my implementation of a number base converter. The program reads from `A1_tests.txt` and outputs the result to `output.txt` 

The program has three main functions:

### 1. `div_convert`

- Converts a number to a target base using **repeated division**.
- The method repeatedly divides the number by the base and records remainders.
- The remainders collected in reverse order form the representation in the new base.
- Supports bases typically from **2 up to 32**.
- Outputs the converted number as a **string**.

### 2. `sub_convert`

- Converts a number to a target base using **subtraction of powers of the base**.
- Also outputs the converted number as a **string**.
- Useful as an alternative or verification method.

### 3. `print_tables`

- Takes any number and converts it to **binary**, **octal**, **decimal (base-10)**, and **hexadecimal**.
- Performs **3 left-shift bit operations** on the number.
- Performs a **bitwise AND operation with 0xFF**.
- Prints the results of all these operations in all four bases.

## Build Instructions

Open a terminal in the project directory and run:

```bash
gcc convert.c main.c -o convert_program

./convert_program
```

## Notes
The program writes its output to a file named output.txt in the current working directory.

Make sure you have write permissions in the active directory where you run the program.

If output.txt already exists, it will be overwritten.
