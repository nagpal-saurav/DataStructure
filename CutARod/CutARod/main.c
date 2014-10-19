//
//  main.c
//  CutARod
//
//  Created by Saurav Nagpal on 15/10/14.
//  Copyright (c) 2014 Saurav Nagpal. All rights reserved.
//

#include <string.h>
#include <stdio.h>

int cutroad(int price[], int rodLength);

int main(int argc, const char * argv[]) {
    // insert code here...
    int maxBenefit = 0;
    //int price[4] = {1, 5, 8, 9};
    int price[8] = {1, 5, 8, 9, 10, 17, 17, 20};
    maxBenefit = cutroad(price, sizeof(price)/sizeof(price[0]));
    printf("Minimum Coin require is:%d", maxBenefit);
    return 0;
}

//
int cutroad(int price[], int rodLength){
    int maxBenefit[rodLength + 1]; // Store the max benefit for all the length 0...8 in our case
    int solution[rodLength];     // use for calculating all the possible result for each length 1...8
    int finalSolution = -1;
    memset(maxBenefit, 0, rodLength);
    //Start from the length 1 to 8. This loop used for calculate the maxbenefit for the lenght 1 to 8.
    for (int i = 1;  i < rodLength +1; i++) {
        memset(solution, -1, rodLength);
        //Loop used fo calculate possible solution for particular lenght like for 2.M[2] = max (p[1] + M[1] , p[2]+M[0])
        for (int j=0; j < i; j++) {
            solution[j] = price[j]+maxBenefit[i-j-1];
        }
        // Calculate max benefit from all the possible solution.
        for (int k=0; k< i; k++) {
            if(solution[k] >= 0){
                if (finalSolution == -1 || finalSolution < solution[k]){
                    finalSolution = solution[k];
                }
            }
        }
        maxBenefit[i] = finalSolution;
    }
    return maxBenefit[rodLength];
}