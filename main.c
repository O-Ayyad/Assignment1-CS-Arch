#include "convert.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LEN 512    // Max length of a line from test file
#define MAX_OUTPUT_LEN 128  // Max length for converted output string

// Helper to trim newline and trailing whitespace chars from a string
void trim(char *str) {
    size_t len = strlen(str);
    while (len > 0 && (str[len - 1] == '\n' || isspace(str[len - 1]))) {
        str[--len] = '\0';
    }
}


//Helper to check and print test results
void check_test_result(const char *func_name, int test_num, uint32_t input1, int input2, const char *output, const char *expected) {
    if (strcmp(output, expected) == 0) {
        printf("Test %d: %s(%u, %d) -> \"%s\" [PASS]\n", test_num, func_name, input1, input2, output);
    } else {
        printf("Test %d: %s(%u, %d) -> Expected: \"%s\", Got: \"%s\" [FAIL]\n", test_num, func_name, input1, input2, expected, output);
    }
}

int main() {
    //Open test case file
    FILE *file = fopen("A1_tests.txt", "r");
    if (!file) {
        perror("Failed to open A1_tests.txt");
        return 1;
    }

    //Open or create file for output
    FILE *out = freopen("output.txt", "w", stdout);    
    if (!out) {
        perror("Failed to open output.txt");
        return 1;
    }

    char line[MAX_LINE_LEN];    // Buffer to hold each line from file
    int total = 0;
    int passed = 0;    // Test counters
    int test_num = 1;   // Sequential test numbering

    // Read each line from the test file
    while (fgets(line, sizeof(line), file)) {
        trim(line); // Remove trailing newline/whitespace

        // Skip comments and empty lines
        if (line[0] == '#' || strlen(line) == 0) {
            continue;
        }

        char func[32] = {0};  // To store function name
        char expected[MAX_OUTPUT_LEN] = {0}; // To store expected result

        uint32_t input1;
        int input2;
        int scanned;

        // Handle div_convert test
        if (strncmp(line, "div_convert", 11) == 0) {
            scanned = sscanf(line, "%s %u %d %s", func, &input1, &input2, expected);
            if (scanned != 4) {
                printf("Invalid div_convert test line: %s\n", line);
                continue;
            }

            char output[MAX_OUTPUT_LEN];
            div_convert(input1, input2, output);

            // Handle div_convert test
            check_test_result("sub_convert", test_num, input1, input2, output, expected);
        
        // Handle sub_convert test
        } else if (strncmp(line, "sub_convert", 11) == 0) {
            scanned = sscanf(line, "%s %u %d %s", func, &input1, &input2, expected);
            if (scanned != 4) {
                printf("Invalid sub_convert test line: %s\n", line);
                continue;
            }

            char output[MAX_OUTPUT_LEN];
            sub_convert(input1, input2, output);

            check_test_result("sub_convert", test_num, input1, input2, output, expected);

        //Print tables
        } else if (strncmp(line, "print_tables", 12) == 0) {
            scanned = sscanf(line, "%s %u %s", func, &input1, expected);
            if (scanned != 3 ) {
                printf("Invalid print_tables line: %s\n", line);
                continue;
            }
            printf("Test %d: print_tables(%u) ->\n", test_num, input1);
            print_tables(input1);
            passed++;
        } else {
            printf("Unknown test function in line: %s\n", line);
            continue;
        }
        test_num++;
        total++;
        printf("\n"); //New line after every test
    }

    printf("\nSummary: %d/%d tests passed\n", passed, total);
    fclose(file);
    fclose(out);

    return 0;
}
