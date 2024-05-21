#include "testLab.h"
#include <stdio.h>

#define MAX_ITEMS    70
#define TEST_COUNT   27
#define TIME_LIMIT   500
#define MEMORY_LIMIT (1 << 10)

typedef struct TTestPackage TTestPackage;
typedef struct TTestInOut TTestInOut;
typedef struct TKnapsackItem TKnapsackItem;
typedef struct IOStream IOStream;

struct TKnapsackItem {
    int Weight;
    int Cost;
};

struct TTestPackage {
    TKnapsackItem Items[MAX_ITEMS];
    TKnapsackItem Result[MAX_ITEMS];
    size_t CountItems;
    size_t CountResultItems;
    int MaxKnapsackWeight;
    int KnapsackCost;
};

struct TTestInOut {
    TTestPackage Tests[TEST_COUNT];
};

struct IOStream {
    FILE* In;
    FILE* Out;
};

static TTestInOut TestData = {{
    { { {475, 747}, {651, 304}, {889, 204}, {94, 355}, {862, 568}, {841, 463}, {541, 980}, {975, 315}, {330, 680}, {951, 272} }, { {94, 355}, {541, 980} }, 10, 2, 749, 1335},
    { { {10, 234}, {15, 23}, {13, 45} }, { {10, 234}, {13, 45} }, 3, 2, 25,  279},
    { {  { 15, 911 },  { 56, 591 },  { 39, 67 },  { 81, 288 },  { 35, 302 },  { 61, 773 },  { 9, 787 },  { 73, 672 },  { 5, 906 },  { 51, 429 },  { 19, 671 },  { 75, 263 },  { 80, 554 },  { 27, 857 },  { 34, 916 },  { 91, 414 },  { 34, 827 },  { 92, 954 },  { 98, 740 },  { 1, 615 },  { 43, 117 },  { 95, 923 },  { 38, 696 },  { 28, 451 },  { 16, 471 } }, { { 15, 911 }, { 56, 591 }, { 61, 773 }, { 9, 787 }, { 73, 672 }, { 5, 906 }, { 51, 429 }, { 19, 671 }, { 80, 554 }, { 27, 857 }, { 34, 916 }, { 34, 827 }, { 92, 954 }, { 98, 740 }, { 1, 615 }, { 95, 923 }, { 38, 696 }, { 28, 451 }, { 16, 471 } }, 25, 19, 853, 13744},
    { {  { 53, 496 },  { 60, 117 },  { 69, 578 },  { 18, 874 },  { 61, 875 },  { 40, 959 },  { 7, 752 },  { 47, 126 },  { 93, 833 },  { 86, 922 },  { 20, 892 },  { 8, 817 },  { 1, 470 },  { 92, 103 },  { 84, 875 },  { 31, 876 },  { 15, 312 },  { 96, 257 },  { 11, 839 },  { 77, 591 },  { 63, 69 },  { 46, 203 },  { 12, 884 },  { 97, 703 },  { 9, 246 },  { 78, 786 },  { 12, 92 },  { 25, 319 },  { 96, 461 },  { 42, 300 },  { 83, 491 },  { 18, 265 } }, { { 18, 874 }, { 61, 875 }, { 40, 959 }, { 7, 752 }, { 20, 892 }, { 8, 817 }, { 1, 470 }, { 31, 876 }, { 15, 312 }, { 11, 839 }, { 12, 884 }, { 9, 246 }, { 12, 92 } }, 32, 13, 248, 8888},
    { {  { 14, 404 },  { 57, 452 },  { 68, 866 },  { 51, 54 },  { 79, 166 },  { 28, 529 },  { 67, 587 },  { 23, 990 },  { 19, 521 },  { 90, 748 },  { 45, 306 },  { 15, 389 },  { 27, 319 },  { 41, 332 },  { 68, 588 },  { 56, 222 },  { 92, 268 },  { 31, 991 },  { 79, 515 },  { 16, 61 },  { 90, 754 },  { 51, 951 },  { 17, 744 },  { 52, 437 },  { 80, 363 },  { 60, 234 },  { 6, 894 },  { 4, 180 },  { 91, 972 },  { 58, 578 },  { 75, 1000 },  { 49, 345 },  { 23, 55 },  { 14, 367 },  { 26, 745 },  { 89, 780 },  { 67, 552 },  { 66, 41 },  { 18, 242 },  { 38, 610 },  { 43, 222 },  { 8, 740 },  { 67, 826 },  { 47, 446 },  { 40, 138 },  { 15, 840 },  { 77, 487 },  { 74, 587 },  { 83, 63 },  { 7, 292 },  { 7, 742 },  { 4, 917 } }, { { 14, 404 }, { 68, 866 }, { 28, 529 }, { 23, 990 }, { 19, 521 }, { 15, 389 }, { 27, 319 }, { 31, 991 }, { 51, 951 }, { 17, 744 }, { 6, 894 }, { 4, 180 }, { 75, 1000 }, { 14, 367 }, { 26, 745 }, { 18, 242 }, { 38, 610 }, { 8, 740 }, { 67, 826 }, { 15, 840 }, { 7, 292 }, { 7, 742 }, { 4, 917 } }, 52, 23, 591, 15099},
    { {  { 27, 264 },  { 22, 700 },  { 5, 736 },  { 30, 418 },  { 32, 198 },  { 17, 917 },  { 2, 449 },  { 95, 763 },  { 6, 411 },  { 36, 780 },  { 58, 614 },  { 74, 889 },  { 86, 285 },  { 57, 821 },  { 82, 902 },  { 15, 21 },  { 25, 145 },  { 23, 609 },  { 67, 157 },  { 96, 148 },  { 26, 185 },  { 23, 666 },  { 78, 222 },  { 15, 658 },  { 95, 208 },  { 22, 322 },  { 98, 547 },  { 62, 124 },  { 22, 97 },  { 56, 314 },  { 26, 939 },  { 31, 745 },  { 43, 164 },  { 2, 811 },  { 99, 478 },  { 17, 227 },  { 98, 696 },  { 99, 735 },  { 38, 676 },  { 16, 578 },  { 50, 334 },  { 4, 848 },  { 33, 539 },  { 84, 565 },  { 8, 554 },  { 38, 441 },  { 64, 142 },  { 83, 490 },  { 55, 355 },  { 62, 992 },  { 81, 321 },  { 53, 816 },  { 13, 492 },  { 39, 939 },  { 6, 144 },  { 88, 387 },  { 45, 145 },  { 53, 180 },  { 60, 765 },  { 42, 288 },  { 34, 622 },  { 35, 637 },  { 84, 321 },  { 61, 776 },  { 96, 921 },  { 2, 562 },  { 6, 214 } }, { { 22, 700 }, { 5, 736 }, { 17, 917 }, { 2, 449 }, { 6, 411 }, { 36, 780 }, { 23, 609 }, { 23, 666 }, { 15, 658 }, { 22, 322 }, { 26, 939 }, { 31, 745 }, { 2, 811 }, { 17, 227 }, { 38, 676 }, { 16, 578 }, { 4, 848 }, { 8, 554 }, { 62, 992 }, { 13, 492 }, { 39, 939 }, { 6, 144 }, { 34, 622 }, { 35, 637 }, { 2, 562 }, { 6, 214 } }, 67, 26, 511, 16228},
    { {  { 25, 371 },  { 25, 451 },  { 99, 541 },  { 77, 193 },  { 36, 446 },  { 73, 772 },  { 10, 894 },  { 14, 220 } }, { { 25, 371 }, { 25, 451 }, { 99, 541 }, { 77, 193 }, { 36, 446 }, { 73, 772 }, { 10, 894 }, { 14, 220 } }, 8, 8, 431, 3888},
    { {  { 26, 318 },  { 31, 504 },  { 45, 910 },  { 69, 166 },  { 53, 292 },  { 50, 312 },  { 74, 852 },  { 84, 74 },  { 1, 54 },  { 60, 391 },  { 4, 675 },  { 1, 699 },  { 56, 871 },  { 53, 488 },  { 34, 639 },  { 53, 238 },  { 43, 962 },  { 19, 392 },  { 22, 958 },  { 8, 244 },  { 93, 612 },  { 82, 159 },  { 98, 395 },  { 49, 717 },  { 71, 771 },  { 1, 827 },  { 66, 86 },  { 19, 972 } }, { { 31, 504 }, { 45, 910 }, { 1, 54 }, { 4, 675 }, { 1, 699 }, { 43, 962 }, { 19, 392 }, { 22, 958 }, { 8, 244 }, { 49, 717 }, { 1, 827 }, { 19, 972 } }, 28, 12, 243, 7914},
    { {  { 92, 245 },  { 70, 940 },  { 46, 122 },  { 67, 721 },  { 100, 299 },  { 60, 516 },  { 42, 359 },  { 69, 591 },  { 44, 64 },  { 48, 833 },  { 33, 264 },  { 6, 532 },  { 53, 904 },  { 41, 205 },  { 46, 729 },  { 17, 244 },  { 67, 706 },  { 93, 644 },  { 100, 190 },  { 88, 819 },  { 52, 994 },  { 96, 24 },  { 54, 18 },  { 77, 683 },  { 85, 521 },  { 54, 600 },  { 60, 452 },  { 58, 881 },  { 23, 366 },  { 66, 682 },  { 17, 108 },  { 36, 36 },  { 93, 700 },  { 75, 363 },  { 59, 221 },  { 4, 341 },  { 15, 295 } }, { { 70, 940 }, { 67, 721 }, { 48, 833 }, { 6, 532 }, { 53, 904 }, { 46, 729 }, { 17, 244 }, { 52, 994 }, { 54, 600 }, { 58, 881 }, { 23, 366 }, { 4, 341 }, { 15, 295 } }, 37, 13, 518, 8380},
    { {  { 35, 191 },  { 91, 859 },  { 59, 500 },  { 15, 150 },  { 24, 75 },  { 36, 976 },  { 27, 187 },  { 95, 592 },  { 9, 809 },  { 47, 470 },  { 77, 464 },  { 2, 958 },  { 38, 848 },  { 13, 127 },  { 46, 646 },  { 18, 929 },  { 32, 30 },  { 45, 491 },  { 37, 893 },  { 19, 367 },  { 86, 253 },  { 14, 672 },  { 46, 294 },  { 39, 927 },  { 89, 93 },  { 44, 313 },  { 51, 562 },  { 24, 127 },  { 67, 725 },  { 74, 131 },  { 59, 959 },  { 35, 455 },  { 58, 433 },  { 11, 431 },  { 30, 315 },  { 82, 888 },  { 76, 176 },  { 77, 764 },  { 32, 263 },  { 70, 215 },  { 90, 286 },  { 43, 783 },  { 69, 849 },  { 15, 407 },  { 57, 158 },  { 74, 656 },  { 49, 448 },  { 36, 807 },  { 22, 698 },  { 47, 929 },  { 65, 349 },  { 53, 407 },  { 49, 481 },  { 76, 371 },  { 37, 919 },  { 35, 74 },  { 10, 746 },  { 39, 604 },  { 3, 373 },  { 77, 318 },  { 90, 991 } }, { { 36, 976 }, { 9, 809 }, { 2, 958 }, { 38, 848 }, { 46, 646 }, { 18, 929 }, { 37, 893 }, { 19, 367 }, { 14, 672 }, { 39, 927 }, { 67, 725 }, { 59, 959 }, { 35, 455 }, { 11, 431 }, { 43, 783 }, { 69, 849 }, { 15, 407 }, { 36, 807 }, { 22, 698 }, { 47, 929 }, { 37, 919 }, { 10, 746 }, { 39, 604 }, { 3, 373 } }, 61, 24, 752, 17710},
    { {  { 28, 153 },  { 51, 698 },  { 92, 524 },  { 52, 908 },  { 91, 257 },  { 67, 945 },  { 40, 209 },  { 77, 671 },  { 71, 708 },  { 54, 514 },  { 39, 558 },  { 8, 876 },  { 77, 938 },  { 44, 361 },  { 17, 913 },  { 64, 610 },  { 43, 245 },  { 51, 469 },  { 100, 272 },  { 60, 29 },  { 33, 136 },  { 33, 3 },  { 43, 890 },  { 98, 977 },  { 21, 256 },  { 22, 646 },  { 38, 310 },  { 10, 812 },  { 31, 755 },  { 70, 45 },  { 84, 235 },  { 15, 737 },  { 63, 270 },  { 44, 671 },  { 50, 871 },  { 17, 746 },  { 79, 207 },  { 30, 229 },  { 60, 323 },  { 71, 682 },  { 92, 426 },  { 94, 825 },  { 83, 893 } }, { { 51, 698 }, { 52, 908 }, { 67, 945 }, { 39, 558 }, { 8, 876 }, { 77, 938 }, { 17, 913 }, { 43, 890 }, { 21, 256 }, { 22, 646 }, { 10, 812 }, { 31, 755 }, { 15, 737 }, { 44, 671 }, { 50, 871 }, { 17, 746 }, { 30, 229 }, { 83, 893 } }, 43, 18, 679, 13342},
    { {  { 63, 908 },  { 63, 109 },  { 40, 620 },  { 93, 755 },  { 86, 677 },  { 57, 313 },  { 65, 516 },  { 37, 35 },  { 24, 388 },  { 11, 166 },  { 59, 600 } }, { { 63, 908 }, { 63, 109 }, { 40, 620 }, { 93, 755 }, { 86, 677 }, { 57, 313 }, { 65, 516 }, { 37, 35 }, { 24, 388 }, { 11, 166 }, { 59, 600 } }, 11, 11, 617, 5087},
    { {  { 18, 21 },  { 84, 627 },  { 24, 933 },  { 52, 961 },  { 79, 334 },  { 79, 260 },  { 33, 377 },  { 60, 3 },  { 78, 726 },  { 80, 357 },  { 28, 908 },  { 45, 661 },  { 12, 884 },  { 76, 11 },  { 90, 505 },  { 99, 330 },  { 86, 769 },  { 99, 340 },  { 38, 255 },  { 47, 519 },  { 7, 743 },  { 8, 494 },  { 29, 712 },  { 60, 508 },  { 89, 391 },  { 88, 15 },  { 93, 640 },  { 70, 235 },  { 7, 816 },  { 38, 159 },  { 62, 587 },  { 12, 358 },  { 34, 979 },  { 61, 350 },  { 11, 563 },  { 23, 962 },  { 9, 290 },  { 63, 20 },  { 2, 426 },  { 57, 333 },  { 29, 888 },  { 26, 622 },  { 40, 278 },  { 30, 1 },  { 86, 111 },  { 24, 692 },  { 66, 796 },  { 25, 277 } }, { { 24, 933 }, { 52, 961 }, { 33, 377 }, { 28, 908 }, { 45, 661 }, { 12, 884 }, { 47, 519 }, { 7, 743 }, { 8, 494 }, { 29, 712 }, { 7, 816 }, { 12, 358 }, { 34, 979 }, { 11, 563 }, { 23, 962 }, { 9, 290 }, { 2, 426 }, { 29, 888 }, { 26, 622 }, { 24, 692 }, { 66, 796 }, { 25, 277 } }, 48, 22, 560, 14861},
    { {  { 59, 58 },  { 22, 694 },  { 78, 657 },  { 92, 925 },  { 2, 876 },  { 50, 858 },  { 28, 308 },  { 53, 60 },  { 78, 114 },  { 68, 574 },  { 99, 829 },  { 66, 1000 },  { 100, 861 },  { 86, 495 },  { 22, 544 },  { 12, 471 },  { 22, 889 },  { 13, 262 },  { 39, 328 } }, { { 22, 694 }, { 78, 657 }, { 92, 925 }, { 2, 876 }, { 50, 858 }, { 28, 308 }, { 78, 114 }, { 68, 574 }, { 99, 829 }, { 66, 1000 }, { 100, 861 }, { 86, 495 }, { 22, 544 }, { 12, 471 }, { 22, 889 }, { 13, 262 }, { 39, 328 } }, 19, 17, 881, 10685},
    { {  { 3, 882 },  { 10, 606 },  { 89, 863 },  { 37, 577 },  { 64, 95 },  { 16, 584 },  { 69, 418 },  { 59, 418 },  { 44, 506 },  { 60, 967 },  { 9, 324 },  { 93, 781 },  { 74, 677 },  { 24, 54 },  { 85, 747 },  { 83, 79 },  { 40, 454 },  { 38, 510 },  { 31, 205 },  { 44, 766 },  { 28, 851 },  { 37, 120 },  { 63, 872 },  { 56, 714 },  { 60, 387 },  { 96, 675 },  { 32, 304 },  { 7, 270 },  { 67, 930 },  { 57, 107 },  { 92, 179 },  { 96, 956 },  { 68, 975 },  { 47, 36 },  { 19, 589 },  { 4, 676 },  { 67, 677 },  { 11, 342 },  { 73, 442 },  { 36, 486 },  { 28, 17 },  { 71, 515 },  { 59, 973 },  { 93, 952 },  { 54, 559 },  { 78, 233 },  { 52, 44 },  { 29, 976 },  { 65, 979 },  { 45, 567 },  { 55, 297 },  { 8, 431 },  { 41, 238 },  { 88, 290 },  { 68, 886 },  { 5, 770 },  { 41, 355 },  { 95, 266 } }, { { 3, 882 }, { 10, 606 }, { 37, 577 }, { 16, 584 }, { 60, 967 }, { 9, 324 }, { 38, 510 }, { 44, 766 }, { 28, 851 }, { 63, 872 }, { 7, 270 }, { 67, 930 }, { 68, 975 }, { 19, 589 }, { 4, 676 }, { 11, 342 }, { 36, 486 }, { 59, 973 }, { 29, 976 }, { 65, 979 }, { 8, 431 }, { 5, 770 } }, 58, 22, 688, 15336},
    { {  { 1, 851 },  { 36, 435 },  { 83, 198 },  { 62, 675 },  { 67, 310 },  { 13, 495 },  { 29, 541 },  { 71, 364 },  { 83, 757 },  { 51, 138 },  { 87, 679 },  { 14, 157 },  { 82, 651 },  { 49, 603 },  { 79, 625 },  { 6, 323 },  { 21, 524 },  { 65, 877 },  { 2, 286 },  { 56, 421 },  { 41, 951 },  { 29, 326 },  { 93, 257 },  { 18, 255 },  { 56, 267 },  { 35, 622 },  { 21, 344 },  { 18, 131 },  { 93, 610 },  { 99, 312 },  { 38, 494 },  { 65, 522 },  { 37, 573 },  { 34, 515 },  { 88, 512 },  { 36, 947 },  { 14, 371 },  { 84, 194 },  { 90, 533 },  { 11, 743 },  { 11, 810 },  { 76, 197 },  { 85, 944 },  { 20, 213 },  { 53, 369 },  { 2, 176 },  { 52, 363 } }, { { 1, 851 }, { 13, 495 }, { 29, 541 }, { 6, 323 }, { 21, 524 }, { 2, 286 }, { 41, 951 }, { 35, 622 }, { 21, 344 }, { 37, 573 }, { 34, 515 }, { 36, 947 }, { 14, 371 }, { 11, 743 }, { 11, 810 }, { 2, 176 } }, 47, 16, 315, 9072},
    { {  { 2, 223 },  { 73, 484 },  { 89, 429 },  { 32, 367 },  { 44, 439 },  { 11, 767 },  { 1, 602 },  { 67, 650 },  { 39, 820 } }, { { 2, 223 }, { 73, 484 }, { 89, 429 }, { 32, 367 }, { 44, 439 }, { 11, 767 }, { 1, 602 }, { 67, 650 }, { 39, 820 } }, 9, 9, 672, 4781},
    { {  { 11, 498 },  { 22, 191 },  { 94, 343 },  { 62, 529 },  { 21, 807 },  { 2, 344 },  { 23, 755 },  { 81, 993 },  { 45, 371 },  { 64, 801 },  { 45, 459 },  { 18, 504 },  { 6, 390 },  { 34, 431 },  { 29, 998 },  { 87, 186 },  { 7, 850 },  { 41, 529 },  { 38, 600 },  { 14, 641 },  { 60, 274 },  { 65, 377 },  { 97, 483 },  { 23, 474 },  { 71, 376 },  { 77, 695 },  { 47, 217 },  { 27, 810 },  { 37, 866 },  { 95, 687 },  { 48, 212 },  { 39, 249 },  { 55, 679 },  { 66, 907 },  { 94, 435 },  { 73, 294 },  { 34, 943 },  { 94, 721 },  { 16, 968 },  { 43, 664 },  { 98, 980 },  { 43, 195 },  { 8, 826 },  { 61, 186 },  { 92, 903 },  { 54, 167 },  { 2, 556 },  { 49, 209 } }, { { 11, 498 }, { 21, 807 }, { 2, 344 }, { 23, 755 }, { 81, 993 }, { 64, 801 }, { 18, 504 }, { 6, 390 }, { 34, 431 }, { 29, 998 }, { 7, 850 }, { 41, 529 }, { 38, 600 }, { 14, 641 }, { 23, 474 }, { 77, 695 }, { 27, 810 }, { 37, 866 }, { 55, 679 }, { 66, 907 }, { 34, 943 }, { 16, 968 }, { 43, 664 }, { 8, 826 }, { 2, 556 } }, 48, 25, 779, 17529},
    { {  { 56, 884 },  { 66, 208 },  { 54, 657 },  { 24, 607 },  { 96, 768 },  { 3, 359 },  { 1, 314 },  { 31, 965 },  { 53, 253 },  { 94, 643 },  { 32, 790 },  { 56, 280 },  { 59, 615 },  { 21, 315 },  { 4, 929 },  { 20, 194 },  { 24, 18 },  { 30, 886 },  { 65, 95 },  { 88, 395 },  { 30, 390 },  { 91, 441 },  { 58, 991 },  { 94, 135 },  { 34, 470 },  { 49, 954 },  { 78, 688 },  { 59, 724 },  { 10, 670 },  { 55, 776 },  { 16, 285 },  { 46, 193 },  { 68, 619 },  { 56, 15 },  { 60, 91 },  { 99, 645 },  { 72, 947 },  { 41, 94 },  { 26, 64 },  { 75, 516 },  { 83, 385 },  { 84, 452 },  { 18, 454 },  { 26, 841 },  { 80, 814 },  { 11, 115 },  { 50, 828 },  { 43, 655 },  { 50, 836 },  { 99, 361 },  { 90, 161 },  { 29, 999 },  { 93, 508 },  { 31, 103 },  { 21, 785 },  { 42, 189 },  { 46, 975 },  { 14, 708 },  { 78, 909 },  { 32, 534 },  { 72, 207 },  { 90, 512 },  { 84, 866 },  { 99, 311 },  { 21, 422 },  { 56, 203 },  { 86, 907 },  { 98, 477 },  { 14, 171 } }, { { 24, 607 }, { 3, 359 }, { 1, 314 }, { 31, 965 }, { 32, 790 }, { 4, 929 }, { 30, 886 }, { 58, 991 }, { 49, 954 }, { 10, 670 }, { 16, 285 }, { 18, 454 }, { 26, 841 }, { 29, 999 }, { 21, 785 }, { 46, 975 }, { 14, 708 }, { 32, 534 }, { 21, 422 } }, 69, 19, 465, 13468},
    { {  { 69, 450 },  { 36, 116 },  { 46, 685 },  { 8, 926 },  { 3, 688 },  { 100, 871 },  { 46, 187 },  { 51, 481 },  { 98, 846 },  { 44, 899 },  { 94, 505 },  { 24, 472 },  { 75, 680 },  { 45, 430 },  { 8, 46 },  { 32, 355 },  { 98, 58 },  { 11, 490 },  { 59, 688 },  { 73, 857 },  { 7, 312 },  { 2, 151 },  { 37, 628 },  { 1, 612 },  { 84, 547 },  { 66, 852 },  { 28, 381 },  { 36, 772 },  { 24, 374 },  { 91, 975 },  { 78, 692 },  { 68, 45 },  { 17, 88 },  { 46, 403 },  { 24, 332 },  { 28, 912 },  { 41, 695 },  { 79, 903 },  { 82, 600 },  { 33, 960 },  { 93, 962 },  { 35, 305 },  { 31, 611 },  { 24, 429 },  { 62, 131 },  { 22, 521 },  { 90, 964 },  { 7, 420 },  { 58, 303 },  { 77, 13 },  { 75, 138 },  { 11, 7 },  { 60, 809 },  { 29, 426 },  { 95, 798 },  { 37, 654 },  { 32, 638 },  { 75, 186 },  { 76, 523 },  { 53, 399 },  { 88, 511 },  { 95, 498 } }, { { 46, 685 }, { 8, 926 }, { 3, 688 }, { 44, 899 }, { 24, 472 }, { 11, 490 }, { 59, 688 }, { 73, 857 }, { 7, 312 }, { 2, 151 }, { 37, 628 }, { 1, 612 }, { 66, 852 }, { 28, 381 }, { 36, 772 }, { 24, 374 }, { 24, 332 }, { 28, 912 }, { 41, 695 }, { 33, 960 }, { 31, 611 }, { 24, 429 }, { 22, 521 }, { 7, 420 }, { 60, 809 }, { 29, 426 }, { 37, 654 }, { 32, 638 } }, 62, 28, 841, 17194},
    { {  { 40, 441 },  { 4, 849 },  { 81, 101 },  { 39, 678 },  { 99, 372 },  { 52, 724 },  { 61, 462 },  { 72, 881 },  { 58, 236 },  { 95, 124 },  { 32, 712 },  { 46, 29 },  { 71, 14 },  { 37, 569 },  { 15, 686 },  { 49, 571 },  { 50, 892 },  { 77, 178 },  { 93, 912 },  { 84, 710 } }, { { 40, 441 }, { 4, 849 }, { 39, 678 }, { 52, 724 }, { 61, 462 }, { 72, 881 }, { 58, 236 }, { 32, 712 }, { 37, 569 }, { 15, 686 }, { 49, 571 }, { 50, 892 }, { 93, 912 }, { 84, 710 } }, 20, 14, 704, 9323},
    { {  { 7, 353 },  { 30, 328 },  { 87, 283 },  { 99, 459 },  { 54, 92 },  { 21, 358 },  { 26, 448 },  { 73, 89 },  { 13, 484 },  { 2, 434 },  { 85, 657 },  { 21, 364 },  { 42, 293 },  { 95, 514 },  { 79, 717 },  { 27, 52 },  { 91, 564 },  { 5, 549 },  { 49, 550 },  { 65, 125 },  { 45, 349 },  { 3, 391 },  { 8, 242 },  { 81, 672 },  { 43, 915 },  { 40, 393 },  { 38, 958 },  { 59, 323 },  { 33, 970 },  { 33, 637 },  { 35, 653 },  { 77, 540 },  { 71, 264 },  { 96, 392 },  { 47, 991 },  { 93, 34 },  { 11, 494 } }, { { 7, 353 }, { 30, 328 }, { 21, 358 }, { 26, 448 }, { 13, 484 }, { 2, 434 }, { 85, 657 }, { 21, 364 }, { 42, 293 }, { 79, 717 }, { 5, 549 }, { 49, 550 }, { 45, 349 }, { 3, 391 }, { 8, 242 }, { 81, 672 }, { 43, 915 }, { 40, 393 }, { 38, 958 }, { 59, 323 }, { 33, 970 }, { 33, 637 }, { 35, 653 }, { 47, 991 }, { 11, 494 } }, 37, 25, 856, 13523},
    { {  { 38, 96 },  { 54, 533 },  { 10, 913 },  { 55, 857 },  { 92, 551 },  { 21, 615 },  { 69, 481 },  { 33, 735 },  { 14, 910 },  { 25, 446 },  { 63, 158 },  { 31, 542 },  { 87, 293 },  { 51, 211 },  { 75, 90 },  { 47, 716 },  { 25, 658 },  { 95, 683 },  { 96, 143 },  { 79, 841 },  { 6, 588 },  { 86, 384 },  { 73, 31 },  { 66, 732 },  { 1, 87 },  { 78, 344 },  { 95, 305 },  { 39, 83 },  { 54, 286 },  { 48, 492 },  { 87, 905 },  { 43, 778 },  { 86, 927 },  { 88, 498 } }, { { 54, 533 }, { 10, 913 }, { 55, 857 }, { 92, 551 }, { 21, 615 }, { 69, 481 }, { 33, 735 }, { 14, 910 }, { 25, 446 }, { 31, 542 }, { 47, 716 }, { 25, 658 }, { 95, 683 }, { 79, 841 }, { 6, 588 }, { 66, 732 }, { 1, 87 }, { 48, 492 }, { 87, 905 }, { 43, 778 }, { 86, 927 } }, 34, 21, 990, 13990},
    { {  { 10, 68 },  { 38, 499 },  { 22, 400 },  { 59, 295 },  { 21, 231 },  { 16, 642 },  { 73, 319 },  { 83, 658 },  { 31, 562 },  { 83, 917 },  { 47, 406 } }, { { 10, 68 }, { 38, 499 }, { 22, 400 }, { 59, 295 }, { 21, 231 }, { 16, 642 }, { 73, 319 }, { 83, 658 }, { 31, 562 }, { 83, 917 }, { 47, 406 }, }, 11, 11, 718, 4997},
    { { {95,55}, {4,10}, {60,47}, {32,5}, {23,4}, {72,50}, {80,8}, {62,61}, {65,85}, {46,87} },
      { {4,10}, {60,47}, {32,5}, {62,61}, {65,85}, {46,87} },
      10, 6, 269, 295
    },
    { { {92,44}, {4,46}, {43,90}, {83,72}, {84,91}, {68,40}, {92,75}, {82,35}, {6,8}, {44,54}, {32,78}, {18,40}, {56,77}, {83,15}, {25,61}, {96,17}, {70,75}, {48,29}, {14,75}, {58,63} },
      { {92,44}, {4,46}, {43,90}, {83,72}, {84,91}, {68,40}, {92,75}, {82,35}, {6,8}, {44,54}, {32,78}, {18,40}, {56,77}, {25,61}, {70,75}, {14,75}, {58,63} },
      20, 17, 878, 1024
    },
    {
        {{1,20}, {1,19}, {1,18}, {1,17}, {1,16}, {1,15}, {1,14}, {1,13}, {1,12}, {1,11}, {1,10}, {1,9}, {1,8}, {1,7}, {1,6}, {1,5}, {1,4}, {1,3}, {1,2}, {1,1}},
        {{1,20}, {1,19}, {1,18}, {1,17}, {1,16}, {1,15}, {1,14}, {1,13}, {1,12}, {1,11}, {1,10}, {1,9}, {1,8}, {1,7}, {1,6}, {1,5}, {1,4}, {1,3}, {1,2}, {1,1}},
        20, 20, 100000000, 210
    },
}};

static size_t currentTest = 0;
IOStream stream = {NULL, NULL};

static int FeedFromArray(void) {
    stream.In = fopen("in.txt", "w+");
    if (!stream.In) {
        printf("can't create in.txt. No space on disk?\n");
        return -1;
    }
    fprintf(stream.In, "%lu %d\n", TestData.Tests[currentTest].CountItems, TestData.Tests[currentTest].MaxKnapsackWeight);
    for (size_t i = 0; i < TestData.Tests[currentTest].CountItems; ++i) {
        fprintf(stream.In, "%d %d\n", TestData.Tests[currentTest].Items[i].Weight, TestData.Tests[currentTest].Items[i].Cost);
    }
    fclose(stream.In);
    return 0;
}

static int CheckFromArray(void) {
    stream.Out = fopen("out.txt", "r");
    if (!stream.Out) {
        printf("can't open out.txt\n");
        currentTest++;
        return -1;
    }
    int knapsackCost = 0;
    const char* result = ScanInt(stream.Out, &knapsackCost);
    if (result != Pass) {
        return 1;
    }
    if (knapsackCost != TestData.Tests[currentTest].KnapsackCost) {
        printf("Wrong knapsack cost output. Found %d, but excepted %d. -- Failed\n", knapsackCost, TestData.Tests[currentTest].KnapsackCost);
        return 1;
    }

    int weight = 0, cost = 0;
    size_t readItemsCount = 0;
    while(fscanf(stream.Out, "%d %d", &weight, &cost) == 2) {
        if (readItemsCount >= TestData.Tests[currentTest].CountResultItems) {
            printf("Output too long -- failed\n");
            return 1;
        }
        if (TestData.Tests[currentTest].Result[readItemsCount].Weight != weight || TestData.Tests[currentTest].Result[readItemsCount].Cost != cost) {
            printf("Wrong item output. Found %d %d, but excepted %d %d. -- Failed\n", weight, cost, TestData.Tests[currentTest].Result[readItemsCount].Weight, TestData.Tests[currentTest].Result[readItemsCount].Cost);
            return 1;
        }
        ++readItemsCount;
    }
    if (readItemsCount < TestData.Tests[currentTest].CountResultItems) {
        printf("Output too short -- Failed\n");
        return 1;
    }
    printf("PASSED\n");
    ++currentTest;
    fclose(stream.Out);
    return 0;
}

const TLabTest labTests[] = {
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
};

TLabTest GetLabTest(int testIdx) {
    (void)testIdx;
    TLabTest labTest = { FeedFromArray, CheckFromArray };
    return labTest;
}

int GetTestCount(void) {
    return TEST_COUNT;
}

const char* GetTesterName(void) {
    return "Lab 11 Knapsack problem";
}

int GetTestTimeout(void) {
    return TIME_LIMIT;
}

size_t GetTestMemoryLimit(void) {
    return MIN_PROCESS_RSS_BYTES + MEMORY_LIMIT;
}
