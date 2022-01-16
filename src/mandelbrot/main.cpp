/* SPDX-License-Identifier: MIT */

/*
 * A program that prints a rather crude version of the Mandelbrot fractal to the InfOS terminal.
 * Copyright (C) Kim Stonehouse <Kim.Stonehouse@ed.ac.uk> 2022. All rights reserved.
 */

#include <infos.h>

static HFILE vc;

#define BLACK 0
#define BLUE 2
#define GREEN 3
#define CYAN 4
#define RED 4
#define MAGENTA 5
#define ORANGE 6
#define L_GREY 7
#define GREY 8
#define L_BLUE 9
#define L_GREEN 10
#define L_CYAN 11
#define L_RED 12
#define L_MAGENTA 13
#define YELLOW 14
#define WHITE 15

#define MAXITERATE 10000000
#define NORM_FACT 67108864
#define NORM_BITS 26

int64_t realMin, realMax;
int64_t imagMin, imagMax;
int64_t deltaReal, deltaImag;

int width = 80; // frame is 80x25
int height = 25;

int next_pixel = 0;
int *next_pixel_ptr = &next_pixel;
int last_pixel;

static void drawchar(int x, int y, int attr, unsigned char c) {
    uint16_t u = (attr << 8) | c;
    pwrite(vc, (const char *)&u, sizeof(u), x + (y * 80));
}

void output(int value, int i, int j) {
    if (value == 10000000) {drawchar(j, i, BLACK, ' ');}
    else if (value > 9000000) {drawchar(j, i, RED, '*');}
    else if (value > 5000000) {drawchar(j, i, L_RED, '*');}
    else if (value > 1000000) {drawchar(j, i, ORANGE, '*');}
    else if (value > 500) {drawchar(j, i, YELLOW, '*');}
    else if (value > 100) {drawchar(j, i, L_GREEN, '*');}
    else if (value > 10) {drawchar(j, i, GREEN, '*');}
    else if (value > 5) {drawchar(j, i, L_CYAN, '*');}
    else if (value > 4) {drawchar(j, i, CYAN, '*');}
    else if (value > 3) {drawchar(j, i, L_BLUE, '*');}
    else if (value > 2) {drawchar(j, i, BLUE, '*');}
    else if (value > 1) {drawchar(j, i, MAGENTA, '*');}
    else {drawchar(j, i, L_MAGENTA, '*');}
}

static void mandelbrot(void *arg) {
    int my_next_pixel = fetch_and_add(next_pixel_ptr, 1);

    while (my_next_pixel <= last_pixel) {
        int x = my_next_pixel % width;
        int y = my_next_pixel / width;

        int64_t real0, imag0, realq, imagq, real, imag;
        int count;

        real0 = realMin + x*deltaReal; // current real value
        imag0 = imagMax - y*deltaImag;

        real = real0;
        imag = imag0;
        for (count = 0; count < MAXITERATE; count++) {
            realq = (real * real) >> NORM_BITS;
            imagq = (imag * imag) >> NORM_BITS;

            if ((realq + imagq) > ((int64_t) 4 * NORM_FACT)) break;

            imag = ((real * imag) >> (NORM_BITS-1)) + imag0;
            real = realq - imagq + real0;
        }

        output(count, y, x);
        my_next_pixel = fetch_and_add(next_pixel_ptr, 1);
    }

    stop_thread(HTHREAD_SELF);
}

int main(const char *cmdline) {
    vc = open("/dev/vc0", 0);

    if (is_error(vc)) {
        printf("error: unable to open vc");
        return 1;
    }

//    printf("\033\x09How many threads would you like to use?\n");
//    int numThreads = getch();
    int numThreads = 1;
    HTHREAD threads[numThreads];

    realMin = -2 * NORM_FACT;
    realMax = 1 * NORM_FACT;
    imagMin = -1 * NORM_FACT;
    imagMax = 1 * NORM_FACT;

    deltaReal = (realMax - realMin)/(width - 1);
    deltaImag = (imagMax - imagMin)/(height - 1);

    last_pixel = width * height;

    for (unsigned int k = 0; k < numThreads; k++) {
        threads[k] = create_thread(mandelbrot, (void *) 1);
    }

    for (unsigned int k = 0; k < numThreads; k++) {
        join_thread(threads[k]);
    }

    close(vc);
    // wait for input so the prompt doesn't ruin the lovely image
    // remove this when timing!
    getch();
    return 0;
}