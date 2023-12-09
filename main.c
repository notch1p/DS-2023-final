#include "huff.h"

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
    int qFlag = 0;
    int c;

    FILE* inputFile = NULL;
    FILE* outputFile = NULL;
    FILE* logFile = NULL;

    opterr = 0;
    if (argc == 1) {
        printHelpMsg();
        return AHEDOK;
    }
    // process program arguments
    while ((c = getopt(argc, argv, "i:o:l:cxhq")) != -1) {
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
        case 'q':
            qFlag = 1;
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
        printHelpMsg();
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
        outputFile = stdout;
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
            logFile = fopen(lfile, "a");
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
        if (!qFlag)
            printf("\033[1;33m===========Encoding===========\033[0m\n");
        if (!qFlag)
            printf("Encode from %s to %s %s\n", (ifile ? ifile : "stdin"), (ofile ? ofile : "stdout"), (lFlag == 1 ? "(Logging)" : ""));
        timing(AHEDEncoding(ahed, inputFile, outputFile), "ENCODING");
        if (!qFlag)
            printf("n_Symbols=%d, Encoded Size=%lld B, Decoded Size=%lld B, Compressed ratio = %lf\n", ahed->n_symbols, ahed->codedSize, ahed->uncodedSize, (double)1 - (double)ahed->codedSize / ahed->uncodedSize);
        if (!qFlag)
            printf("\033[1;33m===========Completed===========\033[0m\n");
    } else if (xFlag == 1) {
        if (!qFlag)
            printf("\033[1;33m===========Decoding===========\033[0m\n");
        if (!qFlag)
            printf("Decode from %s to %s %s\n", (ifile ? ifile : "stdin"), (ofile ? ofile : "stdout"), (lFlag == 1 ? "Logging" : ""));
        timing(AHEDDecoding(ahed, inputFile, outputFile), "DECODING");
        if (!qFlag)
            printf("n_Symbols=%d, Encoded Size=%lld B, Decoded Size=%lld B, Compressed ratio = %lf\n", ahed->n_symbols, ahed->codedSize, ahed->uncodedSize, (double)1 - (double)ahed->codedSize / ahed->uncodedSize);
        if (!qFlag)
            printf("\033[1;33m===========Completed===========\033[0m\n");
    }
    // log
    if (logFile != NULL) {
        if (cFlag == 1)
            fprintf(logFile, "Encode from %s to %s", ifile, ofile);
        else if (xFlag == 1)
            fprintf(logFile, "Decode from %s to %s", ifile, ofile);
        fprintf(logFile, "uncodedSize = %lld\n", ahed->uncodedSize);
        fprintf(logFile, "codedSize = %lld\n", ahed->codedSize);
        fprintf(logFile, "Compressed ratio = %lf\n", (double)ahed->codedSize / ahed->uncodedSize);
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
