/* 
The MIT License (MIT)

Copyright (c) 2020 Anna Brondin and Marcus Nordström

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitatioceiln the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#define DEBUG
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "StepCountingAlgo.h"
#include "scoringStage.h"
#include "detectionStage.h"
#include "postProcessingStage.h"
#define PATH "INSERT PATH HERE"
static int correct_answer = 150;

static void runAlgo(void)
{
    char *line = NULL;
    size_t len = 0;
    size_t read;
    FILE *fp = fopen(PATH, "r");
    if (fp == NULL)
    {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }
    while ((read = getline(&line, &len, fp)) != -1)
    {
        long time = strtol(strtok(line, ","), NULL, 10);
        long x = (strtol(strtok(NULL, ","), NULL, 10));
        long y = (strtol(strtok(NULL, ","), NULL, 10));
        long z = (strtol(strtok(NULL, ","), NULL, 10));
        processSample(time, x, y, z);
    }
    fclose(fp);
    if (line)
        free(line);
}
static int diff = 100000;
int main(int argc, char *argv[])
{
    initAlgo();
    for (size_t scoringWindowSize = 30; scoringWindowSize <= 40; scoringWindowSize++)
    {
        for (int detectionThreshold_whole = 1; detectionThreshold_whole <= 2; detectionThreshold_whole++)
        {
            for (int detectionThreshold_frac = 1; detectionThreshold_frac <= 9; detectionThreshold_frac++)
            {
                for (int postTimeThreshold = 230; postTimeThreshold <= 280; postTimeThreshold += 5)
                {
                    changeWindowSize(scoringWindowSize);
                    changeDetectionThreshold(detectionThreshold_whole, detectionThreshold_frac);
                    changeTimeThreshold(postTimeThreshold);
                    runAlgo();
                    if (diff >= abs(getSteps() - correct_answer))
                    {
                        diff = abs(getSteps() - correct_answer);
                        printf("Steps=%d windowSize=%zu threshold=%d+1/%d timethreshold=%d diff=%d\n", getSteps(), scoringWindowSize, detectionThreshold_whole, detectionThreshold_frac, postTimeThreshold, abs(correct_answer - getSteps()));
                    }
                    resetSteps();
                    resetAlgo();
                }
            }
        }
    }
}