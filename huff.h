#pragma once

#include <assert.h>
#include <stdarg.h> //va_list, va_start, va_end
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

// return value of the program. 0 = OK, -1 = error
#define AHEDOK 0
#define AHEDFail -1

#define timing(a, b)                      \
    start = clock();                      \
    a;                                    \
    diff = clock() - start;               \
    msec = (double)diff * 1e3 / CLOCKS_PER_SEC; \
    printf("Time elapsed: %lfms during %s action\n", msec, b)

// Encoder/decoder log
typedef struct {
    /* size of the decoded string */
    uint64_t uncodedSize;
    /* size of the encoded string */
    uint64_t codedSize;
} tAHED;

/**
 * Encodes the input file, stores the result to the output file and log actions.
 * @param {tAHED*} ahed encoding log
 * @param {FILE*} inputFile decoded input file
 * @param {FILE*} outputFile encoded output file
 * @return 0 if encoding went OK, -1 otherwise
 */
int AHEDEncoding(tAHED* ahed, FILE* inputFile, FILE* outputFile);
/**
 * Decodes the input file, store result to the output file and log actions.
 * @param {tAHED*} ahed decoding log
 * @param {FILE*} inputFile encoded input file
 * @param {FILE*} outputFile decoded output file
 * @return 0 decoding was OK, -1 otherwise
 */
int AHEDDecoding(tAHED* ahed, FILE* inputFile, FILE* outputFile);

/**
 * Print error to stderr and exit.
 */
void AHEDError(const char* fmt, ...);
