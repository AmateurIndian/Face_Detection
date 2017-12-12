//Syed Sarjeel Yusuf
//21402744
//CS 426 Project 3
#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include <math.h>
#include <time.h>
#include "util.h"
#include <omp.h>

const int NUMOFPEOPLE = 18;
const int NUMOFFILE = 20;
const int IMGH = 180;
const int IMGW = 200;

void  create_histogram(int * hist, int ** img, int num_rows, int num_cols) {

    int row, col,i,j;
    int decimal = 0;
    int count = 0;


    for (row = 0; row < 256; row++){
        hist[row] = 0;
    }


    for(row = 1; row < num_rows-1; row++){              //Iterate through Rows
        #pragma omp parallel for private(col), firstprivate(count,decimal)

            for(col = 1; col < num_cols-1; col++){          //Iterate through Cols
                count = 0;
                decimal = 0;
                if(img[row][col] < img[row][col-1]){
                    decimal = decimal + pow(2,count);
                }
                count++;
                if(img[row][col] < img[row+1][col-1]){
                    decimal = decimal + pow(2,count);
                }
                count++;
                if(img[row][col] < img[row+1][col]){
                    decimal = decimal + pow(2,count);
                }
                count++;
                if(img[row][col] < img[row+1][col+1]){
                    decimal = decimal + pow(2,count);
                }
                count++;
                if(img[row][col] < img[row][col+1]){
                    decimal = decimal + pow(2,count);
                }
                count++;
                if(img[row][col] < img[row-1][col+1]){
                    decimal = decimal + pow(2,count);
                }
                count++;
                if(img[row][col] < img[row-1][col]){
                    decimal = decimal + pow(2,count);
                }
                count++;
                if(img[row][col] < img[row-1][col-1]){
                    decimal = decimal + pow(2,count);
                }
                count++;

                hist[decimal]++;
            }

    }
}

double distance(int * a, int *b, int size) {

    double sum = 0;
    int i;
    double nom, denom;
    #pragma omp parallel for private(nom,denom) reduction(+:sum)


        for (i = 0; i < size; i++){
            if(a[i] + b[i] != 0){
                nom = pow((a[i] -b[i]),2);
                denom = 2*(a[i]+b[i]);
                sum = sum + nom/denom;
            }
        }

    return sum;

}

int find_closest(int training_set[NUMOFPEOPLE][NUMOFFILE][256], int num_persons, int num_training, int size, int *test_image){
    int sampPeople, sampImg, count, dist, match = 0;
    int min = 1000;
    int temp[256];

    for(sampPeople = 0; sampPeople < num_persons; sampPeople++){
        for (sampImg = 0; sampImg < num_training; sampImg++){

            dist = distance(training_set[sampPeople][sampImg], &test_image[0], 256);
            if(dist < min){
                min = dist;
                match = sampPeople;
            }
        }
    }
    return match;
}

int main (int argc, char *argv[]){

    clock_t tStart, tEnd;
	tStart = clock();

	int k = atoi(argv[1]);
    int i, j, acc = 0, match =0, numOfTests = 0;
	int hist[NUMOFPEOPLE][NUMOFFILE][256], testHist[NUMOFPEOPLE][NUMOFFILE][256];
	int** result [NUMOFPEOPLE][NUMOFFILE];
    result[0][0] = alloc_2d_matrix(IMGH, IMGW);
    char buf[64];

    //TRAINING
	for (i = 0; i < NUMOFPEOPLE; i++){
		for (j = 0 ; j < NUMOFFILE; j++){
			sprintf(buf, "./images/%d.%d.txt", i+1, j+1);
			result[i][j] = read_pgm_file(buf, IMGH, IMGW);
			if (j < k ) {
				create_histogram(hist[i][j],result[i][j], IMGH, IMGW);
			}
			else {
				create_histogram(testHist[i][j],result[i][j], IMGH, IMGW);
			}
		}
	}
    //TESTING
	for(i = 0; i < NUMOFPEOPLE; i++) {
		for (j = k; j < NUMOFFILE; j++){
            match = find_closest(hist, NUMOFPEOPLE, k, 256, testHist[i][j]);
			printf("%d.%d.txt \t%d\t%d\n", i+1,j+1,match+1,i+1);
			if (match == i){
                acc++;
			}
            numOfTests++;
		}
	}
	printf("Accuracy: %d correct answers for %d tests\n", acc, numOfTests );

	tEnd = clock();
	printf("Parallel runtime: %.2f ms\n", (double)(tEnd - tStart)/CLOCKS_PER_SEC);
	return 0;
}
