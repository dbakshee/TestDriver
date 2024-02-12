#include "testLab.h"
#include <stdio.h>
#include <string.h>

static int testN = 0;
static const struct {const char *const in; int n, out[32];} testInOut[] = {
    {"example\nthis is simple example", 8, {1577, 16, 17, 18, 19, 20, 21, 22}},
    {"x\n", 1, {0}},
    {"0123456789abcdef\n0123456789abcdef", 17, {11589501, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}},
    {"0123\n01230123", 9, {21, 1, 2, 3, 4, 5, 6, 7, 8}},
    {"0123\n0123x0123", 9, {21, 1, 2, 3, 4, 6, 7, 8, 9}},
    {"0123\n012300123", 9, {21, 1, 2, 3, 4, 6, 7, 8, 9}},
    {"0123\n012310123", 9, {21, 1, 2, 3, 4, 6, 7, 8, 9}},
    {"0123\n012320123", 9, {21, 1, 2, 3, 4, 6, 7, 8, 9}},
    {"0123\n012330123", 9, {21, 1, 2, 3, 4, 6, 7, 8, 9}},
    {"0123\n01220123", 5, {21, 5, 6, 7, 8}},
    {"0123\n01210123", 5, {21, 5, 6, 7, 8}},
    {"0123\n01200123", 9, {21, 1, 2, 3, 4, 5, 6, 7, 8}},
    {"\xE0\xE1\xE2\xE3\n\xE0\xE1\xE2\xE3\xE0\xE1\xE2\xE3", 9, {65, 1, 2, 3, 4, 5, 6, 7, 8}}, // абвг\nабвгабвг
    {"\xE0\xE1 \xE2\xE3\n\xE0\xE1 \xE2\xE3\xE0\xE1\xE2\xE3", 6, {209, 1, 2, 3, 4, 5}}, // аб вг\nаб вгабвг
    {"\xE0\xE1 \xE2\xE3\n\xE0\xE1\xE2\xE3\n\xE0\xE1 \xE2\xE3", 6, {209, 6, 7, 8, 9, 10}}, // аб вг\nабвг\nаб вг
    {"0123\n31230123", 6, {21, 1, 5, 6, 7, 8}},
    {"0123\n21230123", 5, {21, 5, 6, 7, 8}},
    {"0123\n11230123", 5, {21, 5, 6, 7, 8}}
};

static int FeedFromArray(void)
{
    FILE *const in = fopen("in.txt", "w+");
    if (!in) {
        printf("can't create in.txt. No space on disk?\n");
        return -1;
    }
    fprintf(in, "%s", testInOut[testN].in);
    fclose(in);
    return 0;
}

static int CheckFromArray(void)
{
    FILE *const out = fopen("out.txt", "r");
    int i, passed = 1;
    if (!out) {
        printf("can't open out.txt\n");
        testN++;
        return -1;
    }
    for (i = 0; i < testInOut[testN].n; i++) {
        int n;
        if (ScanInt(out, &n) != Pass) {
            passed = 0;
            break;
        } else if (testInOut[testN].out[i] != n) {
            passed = 0;
            printf("wrong output -- ");
            break;
        }
    }
    if (passed) {
        passed = !HaveGarbageAtTheEnd(out);
    }
    fclose(out);
    if (passed) {
        printf("PASSED\n");
        testN++;
        return 0;
    } else {
        printf("FAILED\n");
        testN++;
        return 1;
    }
}

static int LabTimeout;

static int feederBig(void)
{
    FILE *const in = fopen("in.txt", "w+");
    int i;
    DWORD t;
    if (!in) {
        printf("can't create in.txt. No space on disk?\n");
        return -1;
    }
    printf("Creating large text... ");
    fflush(stdout);
    t = GetTickCount();
    fprintf(in, "0123456789abcdef\n");
    for (i = 1; i < 1024*1024*8; i++) {
        if (fprintf(in, "0123456789abcde\n") == EOF) {
            printf("can't create in.txt. No space on disk?\n");
            fclose(in);
            return -1;
        }
    }
    fprintf(in, "0123456789abcdef");
    fclose(in);
    t = RoundUptoThousand(GetTickCount() - t);
    printf("done in T=%u seconds. Starting exe with timeout 2*T... ", (unsigned)t/1000);
    LabTimeout = (int)t*2;
    fflush(stdout);
    return 0;
}

static int checkerBig(void)
{
    FILE *const out = fopen("out.txt", "r");
    unsigned i, passed = 1;
    const int bigOut[] = {
        11589501, 134217713, 134217714, 134217715, 134217716, 134217717,
        134217718, 134217719, 134217720, 134217721, 134217722, 134217723,
        134217724, 134217725, 134217726, 134217727, 134217728
    };
    if (!out) {
        printf("can't open out.txt\n");
        testN++;
        return -1;
    }
    for (i = 0; i < sizeof(bigOut)/sizeof(bigOut[0]); i++) {
        int n;
        if (ScanInt(out, &n) != Pass) {
            passed = 0;
            break;
        } else if (bigOut[i] != n) {
            passed = 0;
            printf("wrong output -- ");
            break;
        }
    }
    if (passed) {
        passed = !HaveGarbageAtTheEnd(out);
    }
    fclose(out);
    if (passed) {
        printf("PASSED\n");
        testN++;
        return 0;
    } else {
        printf("FAILED\n");
        testN++;
        return 1;
    }
}

static int NoSpaceFor(FILE *in) {
    printf("can't create in.txt. No space on disk?\n");
    if (in) {
        fclose(in);
    }
    return -1;
}

static int FeedBig2(void)
{
    FILE *const in = fopen("in.txt", "w");
    if (!in) {
        return NoSpaceFor(in);
    }
    printf("Creating large text... ");
    fflush(stdout);
    DWORD ms = GetTickCount();
    for (int i = 0; i < 1000000; ++i) {
        int err;
        if (i == 0) {
            err = fputs("0123456789abcdef\n", in); // hash 11589501
        } else if (i % 10001 == 0) {
            err = fputs("0123456789-bcdef ", in); // no match
        } else if (i % 500000 == 0) {
            err = fputs("---3123456789abcdef--- ", in); // h-match, 0-mismatch
        } else if (i % 700000 == 0) {
            err = fputs("---0423456789abcdef--- ", in); // h-match, 1-mismatch
        } else if (i % 800000 == 0) {
            err = fputs("---0153456789abcdef--- ", in); // h-match, 2-mismatch
        } else if (i % 3 == 0) {
            err = fputs("0123456789 abcdef ", in);
        } else {
            err = fputs("0123456789abcdez ", in);
        }
        if (err == EOF) {
            return NoSpaceFor(in);
        }
    }
    fclose(in);
    ms = GetTickCount() - ms;
    printf("done in T=%u ms. Starting exe with timeout 10*T... ", ms);
    fflush(stdout);
    LabTimeout = 10 * ms;
    return 0;
}

static int CheckBig2(void)
{
    testN++;
    FILE *out = fopen("out.txt", "r");
    if (!out) {
        printf("can't open out.txt\n");
        return -1;
    }
    const int bigOut[] = {
        11589501, 8666637, 12133303, 12133304, 13866639, 13866640, 13866641,
    };
    for (int i = 0; i < (int)(sizeof(bigOut)/sizeof(bigOut[0])); i++) {
        int n;
        if (ScanInt(out, &n) != Pass) {
            goto wrong_output;
        }
        if (bigOut[i] != n) {
            goto wrong_output;
        }
    }
    if (HaveGarbageAtTheEnd(out)) {
        goto wrong_output;
    }
    fclose(out);
    printf("PASSED\n");
    return 0;

wrong_output:
    fclose(out);
    printf("wrong output -- FAILED\n");
    return 1;
}

static int FeedBig3(void)
{
    FILE *in = fopen("in.txt", "w");
    if (!in) {
        return NoSpaceFor(in);
    }
    printf("Creating large text... ");
    fflush(stdout);
    DWORD ms = GetTickCount();
    for (int i = 0; i < 1000000; ++i) {
        int err;
        if (i == 0) {
            err = fputs("01\n", in); // hash 3
        } else if (i % 100001 == 0) {
            err = fputs("02468acegikmoqsuwy ", in); // no match
        } else if (i % 500000 == 0) {
            err = fputs("---31aaaaaaaaaaaaaa--- ", in); // h-match, 0-mismatch
        } else if (i % 700000 == 0) {
            err = fputs("---04aaaaaaaaaaaaaa--- ", in); // h-match, 1-mismatch
        } else {
            err = fputs("02468acegikmoqsuwy ", in);
        }
        if (err == EOF) {
            return NoSpaceFor(in);
        }
    }
    fclose(in);
    ms = GetTickCount() - ms;
    printf("done in T=%u ms. Starting exe with timeout 10*T... ", ms);
    fflush(stdout);
    LabTimeout = 10 * ms;
    return 0;
}

static int CheckBig3(void)
{
    testN++;
    FILE *out = fopen("out.txt", "r");
    if (!out) {
        printf("can't open out.txt\n");
        return -1;
    }
    const int bigOut[] = {
        3, 9499985, 13299989, 13299990,
    };
    for (int i = 0; i < (int)(sizeof(bigOut)/sizeof(bigOut[0])); i++) {
        int n;
        if (ScanInt(out, &n) != Pass) {
            goto wrong_output;
        }
        if (bigOut[i] != n) {
            goto wrong_output;
        }
    }
    if (HaveGarbageAtTheEnd(out)) {
        goto wrong_output;
    }
    fclose(out);
    printf("PASSED\n");
    return 0;

wrong_output:
    printf("wrong output -- FAILED\n");
    fclose(out);
    return 1;
}

static int big4Loc1 =      123;
static int big4Loc2 =    45678;
static int big4Loc3 = 12345678;

static int FeedBig4(void)
{
    FILE *in = fopen("in.txt", "w+");
    if (!in) {
        return NoSpaceFor(in);
    }
    printf("Creating large text... ");
    fflush(stdout);
    DWORD ms = GetTickCount();
    if (fputs("a\n", in) == EOF) {
        return NoSpaceFor(in);
    }
    for (int i = 1; i <= big4Loc3; ++i) {
        int err;
        if (i == big4Loc1 || i == big4Loc2 || i == big4Loc3) {
            err = fputc('d', in); // match
        } else {
            err = fputc('b', in); // mismatch
        }
        if (err == EOF) {
            return NoSpaceFor(in);
        }
    }
    fclose(in);
    ms = GetTickCount() - ms;
    printf("done in T=%u ms. Starting exe with timeout 10*T... ", ms);
    fflush(stdout);
    LabTimeout = 10 * ms;
    return 0;
}

static int CheckBig4(void)
{
    testN++;
    FILE *const out = fopen("out.txt", "r");
    if (!out) {
        printf("can't open out.txt\n");
        return -1;
    }
    int hash, loc1, loc2, loc3;
    if (4 != fscanf(out, "%i%i%i%i", &hash, &loc1, &loc2, &loc3)) {
        goto wrong_output;
    }
    if (hash != 1 || loc1 != big4Loc1 || loc2 != big4Loc2 || loc3 != big4Loc3) {
        goto wrong_output;
    }
    if (HaveGarbageAtTheEnd(out)) {
        goto wrong_output;
    }
    printf("PASSED\n");
    return 0;

wrong_output:
    printf("wrong output -- FAILED\n");
    fclose(out);
    return 1;
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
    {feederBig, checkerBig},
    {FeedBig2, CheckBig2},
    {FeedBig3, CheckBig3},
    {FeedBig4, CheckBig4},
};

TLabTest GetLabTest(int testIdx) {
    return LabTests[testIdx];
}

int GetTestCount(void) {
    return sizeof(LabTests)/sizeof(LabTests[0]);
}

const char* GetTesterName(void) {
    return "Lab 1-1 Rabin-Karp";
}

static int LabTimeout = 3000;
int GetTestTimeout(void) {
    return LabTimeout;
}

size_t GetTestMemoryLimit(void) {
    return MIN_PROCESS_RSS_BYTES;
}
