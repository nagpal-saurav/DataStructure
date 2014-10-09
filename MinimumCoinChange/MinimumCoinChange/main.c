//
//  main.c
//  MinimumCoinChange
//
//  Created by Saurav Nagpal on 07/10/14.
//  Copyright (c) 2014 Saurav Nagpal. All rights reserved.
//

#include <stdio.h>
#include <string.h>

/*
 * Function: findMinimumCoinChange
 * ----------------------------
 *   Compute minimum coin change require for the rs
 *
 *   rs: integer value for rs
 *   coinSetPtr: array of coins set
 *   coinSetLength: count of coin type
 *
 *   returns: the minmum coin change require for rs
 */
int findMinimumCoinChange(int rs, const int coinSetPtr [], size_t coinSetLength);

int main(int argc, const char * argv[]) {
    // insert code here...
    int amount = 0;
    int minimumCoinChange = 0;
    int coinValue[3] = {1, 3, 5};
    printf("Enter the amount in rs:");
    scanf("%d", &amount);
    minimumCoinChange = findMinimumCoinChange(amount, coinValue, sizeof(coinValue)/sizeof(coinValue[0]));
    printf("Minimum Coin require is:%d", minimumCoinChange);
    return 0;
}

//Find
int findMinimumCoinChange(int rs, const int coinSetPtr [], size_t coinSetLength){
    int minCoinValues[rs+1];
    int finalSolutiuon = 0;
    memset(minCoinValues, -1, sizeof(minCoinValues));
    minCoinValues[0] = 0;
    //Calculating the solution from 1 to given rs.
    for(int i = 1; i <= rs ; i++){
        int solution[coinSetLength];
        memset(solution, -1, sizeof(solution));
        // All possible solution for the value i
        for (int j=0; j < coinSetLength; j++) {
            if(coinSetPtr [j] <= i){
                solution[j] = minCoinValues[i - coinSetPtr[j]] + 1;
            }
        }
        
        finalSolutiuon = -1;
        // Minimum Possible solution for the value i
        for(int k=0;k < coinSetLength;k++){
            if(solution[k] > 0 ){
                if(minCoinValues[i] == -1 || solution[k] < minCoinValues[i]){
                    minCoinValues[i] = solution[k];
                }
            }
        }
        
        
    }
    return minCoinValues[rs];
}