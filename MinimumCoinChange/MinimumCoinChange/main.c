//
//  main.c
//  MinimumCoinChange
//
//  Created by Saurav Nagpal on 07/10/14.
//  Copyright (c) 2014 Saurav Nagpal. All rights reserved.
//

#include <stdio.h>
#include <string.h>

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    return 0;
}

int findMinimumCoinChange(int rs, const int (*coinSetPtr) []){
    int coinSetLength = sizeof(coinSetPtr) / sizeof(int);
    int minCoinValues[rs+1];
    memset(minCoinValues, -1, rs+1);
    minCoinValues[0] = 0;
    for(int i = 1; i <= rs ; i++){
        int solution[coinSetLength];
        memset(solution, -1, coinSetLength);
        for (int j=0; j < coinSetLength; j++) {
            if((*coinSetPtr)[j] <= i){
                solution[j] = minCoinValues[i-(*coinSetPtr)[j]] + 1;
            }
        }
    }
    return minCoinValues[rs];
}