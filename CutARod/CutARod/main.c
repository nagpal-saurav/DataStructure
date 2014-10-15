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
    int maxBenefit[rodLength];
    maxBenefit[0] = price[0];
    int solution[rodLength];
    int finalSolution;
    memset(solution, -1, rodLength);
    for (int i = 0;  i < rodLength; i++) {
        for (int j=0; j < i; j++) {
            solution[i] = price[j]+maxBenefit[i-j];
        }
        for (int k=0; k<rodLength; k++) {
            
        }
        
    }
    
    return finalSolution;
}