#include <stdint.h>
#include <math.h>
#include <stdio.h>
#include "convert.h"

// Converts a number n into a string in the given base using the division method
void div_convert(uint32_t n, int base, char*out){
    //Check edge cases of invalid base and 0 input
    if (base < 2 || base > 36) {
        out[0] = '\0'; // Invalid base, return empty string
        return;
    }
    if (n == 0) {
        out[0] = '0';
        out[1] = '\0';
        return;
    }
    double log2_base = log2(base); 
    int index = 0;
    char temp[35]; // Temporary array to hold digits in reverse order
    // Convert by repeated division
    while(n>0){
        int rem = n%base;
        n = n/base;

        // Convert digit to character
        if(rem < 10){
            temp[index++] = '0' + rem;
        }
        else{
            temp[index++] = 'A' + (rem-10);
        }
    }
    // Reverse the digits into the output string
    for (int i = 0; i < index; i++) {
        out[i] = temp[index-1 - i];
    }
    out[index] = '\0';
}

// Converts a number n into a string in the given base using the subtraction method
void sub_convert(uint32_t n, int base, char *out) {
    if (base < 2 || base > 36) {
        out[0] = '\0';
        return;
    }
    if (n == 0) {
        out[0] = '0';
        out[1] = '\0';
        return;
    }

    char temp[35];  // Enough for base 2 with 32 bits + '\0'
    int index = 0;

    // Find highest power of base less than or equal to n
    uint32_t power = 1;
    while (power <= n / base) {
        power*=base;
    }
    if (power> n) {
        power /= base;
    }

    // Extract digits from most significant to least
    while (power> 0) {
        int digit = n / power;
        n -= digit * power;
        power /= base;

        if (digit < 10) {
            temp[index++] = '0' + digit;
        } else {
            temp[index++] = 'A' + (digit - 10);
        }
    }
    temp[index] = '\0';


    for (int i = 0;i <= index;i++) {
        out[i] = temp[i];
    }
}
//Prints bitwise operation tables for a number `n`
//Original value
//Left shifted by 3
//Bitwise AND with 0xFF
void print_tables(uint32_t n)
{
    char outbin[33];   // Max 32-bit binary string + null
    char outoct[12];   // Octal can go up to 11 digits (32-bit)
    char outdeci[11];  // Max decimal digits for uint32_t
    char outhex[9];    // Max 8 hex digits + null

    div_convert(n, 2, outbin);   
    div_convert(n, 8, outoct);   
    div_convert(n, 10, outdeci);
    div_convert(n, 16, outhex);
    printf("Original: Binary=%s Octal=%s Decimal=%s Hex=%s\n", outbin, outoct, outdeci, outhex);

    uint32_t shifted = n << 3;
    printf("Left Shift by 3:\n");
    div_convert(shifted, 2, outbin);
    div_convert(shifted, 8, outoct);
    div_convert(shifted, 10, outdeci);
    div_convert(shifted, 16, outhex);
    printf("Binary=%s Octal=%s Decimal=%s Hex=%s\n", outbin, outoct, outdeci, outhex);

    uint32_t anded = n & 0xFF;
    printf("AND with 0xFF:\n");
    div_convert(anded, 2, outbin);
    div_convert(anded, 8, outoct);
    div_convert(anded, 10, outdeci);
    div_convert(anded, 16, outhex);
    printf("Binary=%s Octal=%s Decimal=%s Hex=%s\n", outbin, outoct, outdeci, outhex);
}


