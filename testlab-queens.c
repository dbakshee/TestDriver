#include "testLab.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdbool.h>

enum { MAX_SIZE = 14 };

static int testN = 0;

typedef struct {
    const int rows;
    const int cols;
    const char* in[MAX_SIZE];
    const int out;
} TestCase;

static const TestCase testInOut[] = {
    {5, 8, { //1
        "?.?...??\n",
        "?????.??\n",
        "......?.\n",
        "??.?.?.?\n",
        "?????..?\n"
    }, 1},
    {3, 3, { //2
        "???\n",
        "???\n",
        "???\n"
    }, 0},
    {1, 12, { //3
        ".....?......\n"
    }, 1},
    {1, 1, { //4
        ".\n"
    }, 0},
    {1, 1, { //5
        "?\n"
    }, 1},
    {4, 4, { //6
        "?..?\n",
        ".?..\n",
        "..?.\n",
        "...?\n"
    }, 0},
    {7, 7, { //7
        "???????\n",
        "?.....?\n",
        "?.....?\n",
        "?.....?\n",
        "?.....?\n",
        "?.....?\n",
        "???????\n"
    }, 0},
    {5, 5, { //8
        "....?\n",
        "...?.\n",
        "..?..\n",
        ".?...\n",
        "?...?\n"
    }, 0},
    {4, 4, { //9
        "?.?.\n",
        "?..?\n",
        "?.?.\n",
        "?..?\n"
    }, 0},
    {12, 12, { //10
        "............\n",
        "????????????\n",
        "????????????\n",
        "????????????\n",
        "????????????\n",
        "????????????\n",
        "????????????\n",
        "????????????\n",
        "????????????\n",
        "????????????\n",
        "????????????\n",
        "????????????\n"
    }, 0},
    {6, 7, { //11
        "???????\n",
        "???????\n",
        "???????\n",
        "???????\n",
        "???????\n",
        "???????\n"
    }, 1},
    {7, 8, { //12
        "???..???\n",
        ".???..??\n",
        "..???..?\n",
        "...???..\n",
        "?...???.\n",
        "??...???\n",
        "???...??\n"
    }, 0},
    {12, 11, { //13
        "???????????\n",
        "???????????\n",
        "???????????\n",
        "???????????\n",
        "???????????\n",
        "???????????\n",
        "???????????\n",
        "???????????\n",
        "???????????\n",
        "???????????\n",
        "???????????\n",
        "???????????\n"
    }, 0},
    {12, 12, { //14
        "?.?.?.?.?.?.\n",
        ".?.?.?.?.?.?\n",
        "?.?.?.?.?.?.\n",
        ".?.?.?.?.?.?\n",
        "?.?.?.?.?.?.\n",
        ".?.?.?.?.?.?\n",
        "?.?.?.?.?.?.\n",
        ".?.?.?.?.?.?\n",
        "?.?.?.?.?.?.\n",
        ".?.?.?.?.?.?\n",
        "?.?.?.?.?.?.\n",
        ".?.?.?.?.?.?\n"
    }, 0},
    {12, 12, { //15
        "?...........\n",
        ".....?......\n",
        "...?........\n",
        "......?.....\n",
        ".........?..\n",
        "...........?\n",
        "........?...\n",
        ".?..........\n",
        "....?.......\n",
        "..?.........\n",
        ".......?....\n",
        "..........?.\n"
    }, 1},
    {4, 5, { //16
        "....?\n",
        "..?..\n",
        "?....\n",
        "?.???\n"
    }, 1},
    {12, 12, { //17
        "............\n",
        "............\n",
        "............\n",
        "............\n",
        "............\n",
        "............\n",
        "............\n",
        "............\n",
        "............\n",
        "............\n",
        "............\n",
        "............\n"
    }, 0},
    {8, 8, { //18
        "???.???.\n",
        ".???.???\n",
        "???.???.\n",
        "??.?????\n",
        "?.???.??\n",
        ".???.?.?\n",
        "???.???.\n",
        "??...??.\n"
    }, 1},
    {10, 11, { //19
        "..???.????.\n",
        ".??..??.???\n",
        "??.??..??..\n",
        "????.?.???.\n",
        "...???.?..?\n",
        ".?.?.??...?\n",
        "??.??.???..\n",
        ".??????..??\n",
        "?.?.????..?\n",
        "???.?.??..?\n"
    }, 1},
    {12, 12, { //20
        "?...???.??.?\n",
        "?.?????.???.\n",
        "..?..????.?.\n",
        "?.??..??...?\n",
        ".???.??..???\n",
        ".?..???..?..\n",
        "..?????..?..\n",
        "??.???.??..?\n",
        "..??.???.?..\n",
        ".???..?..???\n",
        "..?...??????\n",
        ".??...????..\n"
    }, 1},
    {8, 10, { //21
        ".?....?..?\n",
        "..?..???..\n",
        "?..???...?\n",
        "?....??...\n",
        ".....?..??\n",
        "..?....???\n",
        "??.??...?.\n",
        "....??????\n"
    }, 0},
    {9, 10, { //22
        "???.?..?..\n",
        "..???.??..\n",
        "???..???..\n",
        "??????????\n",
        "?.?.???.?.\n",
        "?.???.?.??\n",
        "?....?.?.?\n",
        "???...????\n",
        "????..????\n"
    }, 1},
    {8, 9, { //23
        "?????????\n",
        "?????????\n",
        "???.?????\n",
        "????????.\n",
        "???.?????\n",
        "????.????\n",
        "?????????\n",
        "?????????\n"
    }, 1},
    {10, 10, { //24
        "?..??..???\n",
        "??.?..?...\n",
        "..?.......\n",
        "......?...\n",
        "..??...??.\n",
        "........?.\n",
        "........??\n",
        "..?..?...?\n",
        ".........?\n",
        "???.??.?..\n"
    }, 0},
    {6, 9, { //25
        "????.?.?.\n",
        "..????...\n",
        "??.????.?\n",
        "?.?.?.?.?\n",
        ".....?.??\n",
        "???......\n"
    }, 1},
    {12, 12, { //26
        "????????????\n",
        "????????????\n",
        "????????????\n",
        "????????????\n",
        "????????????\n",
        "????????????\n",
        "????????????\n",
        "????????????\n",
        "????????????\n",
        "????????????\n",
        "????????????\n",
        "????????????\n"
    }, 1}
};

bool goodMove(int row, int col, char output[MAX_SIZE][MAX_SIZE]) {
    int directions[4][2] = {
        {-1, -1},
        {-1, 1},
        {1, -1},
        {1, 1}
    };

    for (int i = 0; i < testInOut[testN].rows; i++) {
        if (output[i][col] == 'A') {
            return false;
        }
    }

    for (int i = 0; i < testInOut[testN].cols; i++) {
        if (output[row][i] == 'A') {
            return false;
        }
    }

    for (int i = 0; i < 4; i++) {
        int x = row + directions[i][0];
        int y = col + directions[i][1];

        while (x >= 0 && x < testInOut[testN].rows && y >= 0 && y < testInOut[testN].cols) {
            if (output[x][y] == 'A') {
                return false;
            }

            x += directions[i][0];
            y += directions[i][1];
        }
    }

    return true;
}

bool queenTour(int row, char output[MAX_SIZE][MAX_SIZE]) {
    if (row == testInOut[testN].rows) {
        return true;
    }

    for (int col = 0; col < testInOut[testN].cols; col++) {
        if (output[row][col] == 'X') {
            if (goodMove(row, col, output)) {
                output[row][col] = 'A';

                if (queenTour(row + 1, output)) {
                    return true;
                }

                output[row][col] = 'X';
            }
        }
    }

    return false;
}

bool checkOutput(char output[MAX_SIZE][MAX_SIZE]) {
    int xCount;
    for (int i = 0; i < testInOut[testN].rows; i++) {
        xCount = 0;
        for (int j = 0; j < testInOut[testN].cols; j++) {
            if (output[i][j] == 'X') {
                xCount++;
                if (testInOut[testN].in[i][j] != '?') {
                    return false;
                }
            }
            if (output[i][j] != '.' && output[i][j] != 'X' && output[i][j] != '\n') {
                return false;
            }
        }
        if (xCount != 1) {
            return false;
        }
    }

    return queenTour(0, output);
}

static int FeedFromArray(void)
{
    FILE *const in = fopen("in.txt", "w+");
    if (!in) {
        printf("can't create in.txt. No space on disk?\n");
        return -1;
    }

    if (fprintf(in, "%d %d\n", testInOut[testN].rows, testInOut[testN].cols) < 0) {
        printf("can't create in.txt. No space on disk?\n");
        fclose(in);
        return -1;
    }

    for (int i = 0; i < testInOut[testN].rows; i++) {
        if (fprintf(in, "%s", testInOut[testN].in[i]) < 0) {
            printf("can't create in.txt. No space on disk?\n");
            fclose(in);
            return -1;
        }
    }

    fclose(in);
    return 0;
}

static int CheckFromArray(void) {

    FILE* const out = fopen("out.txt", "r");
    if (out == NULL) {
        printf("can't open out.txt\n");
        testN++;
        return -1;
    }

    char line[5];
    fgets(line, sizeof(line), out);

    if (testInOut[testN].out == 0) {

        if (strcmp(line, "NO\n") != 0) {
            printf("FAILED\n");
            fclose(out);
            testN++;
            return 1;
        }

        printf("PASSED\n");
        fclose(out);
        testN++;
        return 0;
    }

    if (testInOut[testN].out == 1) {

        if (strcmp(line, "YES\n") != 0) {
            printf("FAILED\n");
            fclose(out);
            testN++;
            return 1;
        }

        char output[MAX_SIZE][MAX_SIZE];
        for (int i = 0; i < testInOut[testN].rows; i++) {
            fgets(output[i], MAX_SIZE, out);
        }

        if (checkOutput(output)) {
            printf("PASSED\n");
            fclose(out);
            testN++;
            return 0;
        }

        printf("FAILED\n");
        fclose(out);
        testN++;
        return 1;
    }

    return -1;
}

const TLabTest LabTests[] = {
    {FeedFromArray, CheckFromArray},
    {FeedFromArray, CheckFromArray},
    {FeedFromArray, CheckFromArray},
    {FeedFromArray, CheckFromArray},
    {FeedFromArray, CheckFromArray},
    {FeedFromArray, CheckFromArray},
    {FeedFromArray, CheckFromArray},
    {FeedFromArray, CheckFromArray},
    {FeedFromArray, CheckFromArray},
    {FeedFromArray, CheckFromArray},
    {FeedFromArray, CheckFromArray},
    {FeedFromArray, CheckFromArray},
    {FeedFromArray, CheckFromArray},
    {FeedFromArray, CheckFromArray},
    {FeedFromArray, CheckFromArray},
    {FeedFromArray, CheckFromArray},
    {FeedFromArray, CheckFromArray},
    {FeedFromArray, CheckFromArray},
    {FeedFromArray, CheckFromArray},
    {FeedFromArray, CheckFromArray},
    {FeedFromArray, CheckFromArray},
    {FeedFromArray, CheckFromArray},
    {FeedFromArray, CheckFromArray},
    {FeedFromArray, CheckFromArray},
    {FeedFromArray, CheckFromArray},
    {FeedFromArray, CheckFromArray}
};

TLabTest GetLabTest(int testIdx) {
    return LabTests[testIdx];
}

int GetTestCount(void) {
    return sizeof(LabTests) / sizeof(LabTests[0]);
}

const char* GetTesterName(void) {
    return "Lab M*N-Queens Problem";
}

int GetTestTimeout(void) {
    return 1000;
}

size_t GetTestMemoryLimit(void) {
    return MIN_PROCESS_RSS_BYTES;
}

