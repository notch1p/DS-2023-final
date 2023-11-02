#include "huff.h"
#include <time.h>

// AHED stands for Adaptive Huffman Encoding.

int main(int argc, char** argv)
{

    char* ifile = NULL;
    char* ofile = NULL;
    char* lfile = NULL;
    int lFlag = 0;
    int cFlag = 0;
    int xFlag = 0;
    int hFlag = 0;
    int c;

    FILE* inputFile = NULL;
    FILE* outputFile = NULL;
    FILE* logFile = NULL;

    opterr = 0;

    // process program arguments
    while ((c = getopt(argc, argv, "i:o:l:cxh")) != -1) {
        switch (c) {
        case 'i':
            ifile = optarg;
            break;
        case 'o':
            ofile = optarg;
            break;
        case 'l':
            lfile = optarg;
            lFlag = 1;
            break;
        case 'c':
            cFlag = 1;
            break;
        case 'x':
            xFlag = 1;
            break;
        case 'h':
            hFlag = 1;
            break;
        case '?':
        default:
            AHEDError("unknown argument");
            return AHEDFail;
            break;
        }
    }

    // help
    if (hFlag == 1) {
        printf("USAGE: ahed -h | -c | -x [-i input_file] [-o output_file] [-l log_file] \n");
        return AHEDOK;
    }

    // input file
    if (ifile == NULL)
        inputFile = stdin;
    else
        inputFile = fopen(ifile, "rb");
    if (inputFile == NULL) {
        AHEDError("can not find an input file");
        return AHEDFail;
    }

    // output file
    if (ofile == NULL) {
        strcpy(ofile,ifile);
        strcat(ofile,".huff");
        outputFile = fopen(ofile, "wb");
    } else
        outputFile = fopen(ofile, "wb");
    if (outputFile == NULL) {
        AHEDError("can not open an output file");
        return AHEDFail;
    }

    // log file
    if (lFlag == 1) {
        if (lfile == NULL) {
            AHEDError("can not open a log file");
            return AHEDFail;
        } else
            logFile = fopen(lfile, "w");
    }

    if (cFlag == 1 && xFlag == 1) {
        AHEDError("please make a decision, encode or decode?\n");
        return AHEDFail;
    }

    // encoding/decoding log structure
    tAHED* ahed = malloc(sizeof(tAHED));
    if (ahed == NULL) {
        AHEDError("not enough memory");
        return AHEDFail;
    }
    clock_t start, diff;
    double msec;
    if (cFlag == 1) {
        printf("Encode from %s to %s (Log %s)", ifile, ofile, (lFlag == 1 ? "Enabled" : "Disabled"));
        timing(AHEDEncoding(ahed, inputFile, outputFile), "ENCODING");
        printf("Encoded/Decoded = %lf\n", (double)ahed->codedSize / ahed->uncodedSize);
    } else if (xFlag == 1) {
        printf("Decode from %s to %s (Log %s)", ifile, ofile, (lFlag == 1 ? "Enabled" : "Disabled"));
        timing(AHEDDecoding(ahed, inputFile, outputFile), "DECODING");
        printf("Encoded/Decoded Size ratio = %lf\n", (double)ahed->codedSize / ahed->uncodedSize);
    }
    // log
    if (logFile != NULL) {
        if (cFlag == 1)
            printf("Encode from %s to %s", ifile, ofile);
        else if (xFlag == 1)
            printf("Decode from %s to %s", ifile, ofile);
        fprintf(logFile, "uncodedSize = %lld\n", ahed->uncodedSize);
        fprintf(logFile, "codedSize = %lld\n", ahed->codedSize);
        printf("Encoded/Decoded Size ratio = %lf\n", (double)ahed->codedSize / ahed->uncodedSize);
        fclose(logFile);
    }

    // cleanup
    free(ahed);
    if (inputFile != NULL)
        fclose(inputFile);
    if (outputFile != NULL)
        fclose(outputFile);

    return AHEDOK;
}
