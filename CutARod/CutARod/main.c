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
    int price[8] = {1, 5, 8, 9, 10, 17, 17, 20};
    maxBenefit = cutroad(price, sizeof(price)/sizeof(price[0]));
    printf("Minimum Coin require is:%d", maxBenefit);
    return 0;
}

int cutroad(int price[], int rodLength){
    int maxBenefit[rodLength+1];
    int solution[rodLength];
    int finalSolution = -1;
    memset(maxBenefit, 0, rodLength);
    for (int i = 1;  i < rodLength; i++) {
        memset(solution, -1, rodLength);
        for (int j=0; j <= i; j++) {
            solution[j] = price[j]+maxBenefit[i-j];
        }
        for (int k=0; k<=i; k++) {
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