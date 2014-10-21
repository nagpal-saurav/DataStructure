//
//  main.c
//  MaximumSubSequenceSum
//
//  Created by Saurav Nagpal on 21/10/14.
//  Copyright (c) 2014 Saurav Nagpal. All rights reserved.
//

#include "string.h"
#include <stdio.h>

int calculateMaximumSubSequence(int array[], int size);

int main(int argc, const char * argv[]) {
    // insert code here...
    // insert code here...
    int max_sub_sequence = 0;
    //int price[4] = {1, 5, 8, 9};
    int array[8] = {-2, -3, 4, -1, -2, 1, 5, -3};
    max_sub_sequence = calculateMaximumSubSequence(array, sizeof(array)/sizeof(array[0]));
    printf("Minimum Coin require is:%d", max_sub_sequence);
    return 0;
}

int calculateMaximumSubSequence(int array[], int size){
    int max[size];
    memset(max, 0, size);
    int maximumSubsequence = 0;
    max[0] = array[0];
    for(int i = 1; i < size;i++){
        if(max[i - 1] > 0){
            max[i] = max[i-1]+array[i];
        }else{
            max[i] = array[i];
        }
        if(maximumSubsequence < max[i]){
            maximumSubsequence = max[i];
        }
    }
    return maximumSubsequence;
}