//
//  main.c
//  MaximumSubSequenceSum
//
//  Created by Saurav Nagpal on 21/10/14.
//  Copyright (c) 2014 Saurav Nagpal. All rights reserved.
//

#include <stdio.h>

int calculateMaximumSubSequence(int array[], int size);

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    // insert code here...
    int max_sub_sequence = 0;
    //int price[4] = {1, 5, 8, 9};
    int array[8] = {1, 5, 8, 9, 10, 17, 17, 20};
    max_sub_sequence = calculateMaximumSubSequence(array, sizeof(array)/sizeof(array[0]));
    printf("Minimum Coin require is:%d", max_sub_sequence);
    return 0;
}

int calculateMaximumSubSequence(int array[], int size){
    int max[size];
    
    return max[size-1];
}