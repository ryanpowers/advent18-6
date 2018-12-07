/*
 ============================================================================
 Name        : advent6.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

static int32_t coords[50][2];
static int32_t results1[50];
static int32_t results2[50];
static int32_t resultidx = 0;
static int32_t results3[100];

int sorter(void const * a, void const * b);
int32_t dist(int32_t x1, int32_t y1, int32_t x2, int32_t y2);

int main(void)
{
    FILE * input;

    input = fopen("input.txt", "r");
    if (input)
    {
        uint32_t index = 0;
        while (!feof(input))
        {
            uint32_t x, y;
            if (fscanf(input, "%d, %d\n", &y, &x) == 2)
            {
                coords[index][0] = x;
                coords[index][1] = y;
                index++;
            }
        }
        fclose(input);

        uint32_t region = 0;

        for (int i = 0; i < 500; i++)
        {
            for (int j = 0; j < 500; j++)
            {
                int closest;
                uint32_t closestdist = -1;
                bool multi = false;
                uint32_t sumdist = 0;
                for (int k = 0; k < index; k++)
                {
                    int32_t thedist =dist(i,j,coords[k][0],coords[k][1]);
                    sumdist+= thedist;
                    if (thedist < closestdist)
                    {
                        closestdist = thedist;
                        closest = k;
                    }
//                    else if ((thedist == closestdist) )
//                    {
//                        multi = true;
//                    }
                }
                if (sumdist < 10000)
                {
                    region++;
                }
                for (int k = 0; k < index; k++)
                {
                    int32_t thedist =dist(i,j,coords[k][0],coords[k][1]);
                    if ((thedist == closestdist) && (closest != k))
                    {
                        multi = true;
                    }
                }
                if (!multi)
                {
                    results1[closest]++;
                }
            }
        }

        for (int i = -1; i < 501; i++)
        {
            for (int j = -1; j < 501; j++)
//        for (int i = 0; i < 10; i++)
//        {
//            for (int j = 0; j < 10; j++)
            {
                int closest;
                uint32_t closestdist = -1;
                bool multi = false;
                for (int k = 0; k < index; k++)
                {
                    int32_t thedist =dist(i,j,coords[k][0],coords[k][1]);
                    if (thedist < closestdist)
                    {
                        closestdist = thedist;
                        closest = k;
                    }
//                    else if ((thedist == closestdist))
//                    {
//                        multi = true;
//                    }
                }
                for (int k = 0; k < index; k++)
                {
                    int32_t thedist =dist(i,j,coords[k][0],coords[k][1]);
                    if ((thedist == closestdist) && (closest != k))
                    {
                        multi = true;
                    }
                }
                if (!multi)
                {
//                    printf("%c", 'a'+closest);
                    results2[closest]++;
                }
                else
                {
//                    printf("%c", '.');
                }
            }
//            printf("\n");
        }


        for (int l = 0; l < index; l++)
        {
            if (results1[l] == results2[l])
            {
                results3[resultidx++] = results1[l];
                //printf("unchanged %i\n", results1[l]);
            }
        }

        /* done with parse, sort it */
        qsort(results3,resultidx,sizeof(uint32_t),sorter);

        printf("result: %d\n", results3[0]);
        printf("result: %d\n", results3[1]);

        printf("region: %d\n", region);

        return 0;
    }
    return 1;
}


int sorter(void const * a, void const * b)
{
    uint32_t const * ae = a;
    uint32_t const * be = b;

    if ( *ae < *be )
    {
        return 1;
    }
    else if ( *ae == *be )
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

int32_t dist(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
{
    return abs(x1-x2) + abs(y1-y2);
}
