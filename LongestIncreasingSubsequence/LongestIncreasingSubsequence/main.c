//
//  main.c
//  LongestIncreasingSubsequence
//
//  Created by Saurav Nagpal on 22/10/14.
//  Copyright (c) 2014 Saurav Nagpal. All rights reserved.
//

#include <string.h>
#include <stdio.h>

//Use as a heap for store the longest sequence for index
typedef struct lsIncreasingSequence_struct{
    int longesubSequence[10];
    int longesubequenceLength;
}lsIncreasingSequence;

lsIncreasingSequence longIncSubsequence(int sequence[], int seqL);

int main(int argc, const char * argv[]) {
    // insert code here...
    lsIncreasingSequence longestSubsequence;
    //int price[4] = {1, 5, 8, 9};
    int sequence[10] = {0, 2, 7, 3, 4, 9, 8, 12, 1, 15};
    longestSubsequence = longIncSubsequence(sequence, sizeof(sequence)/sizeof(sequence[0]));
    printf("longest subsequence length is :%d", longestSubsequence.longesubequenceLength);
    printf("\nlongestSubsequence is:");
    for (int i = 0; i < longestSubsequence.longesubequenceLength; i++) {
        printf("%d,",longestSubsequence.longesubSequence[i]);
    }
    return 0;
}

//return the longest sequence
lsIncreasingSequence longIncSubsequence(int sequence[], int seqL){
    lsIncreasingSequence lsubsequences[seqL+1]; //Store the longest sequence for each index
    int finalsubsequenceLength = 0;      //Store the longest sequence length
    int finalSubSequenceIndex = -1;       //Store the longest sequence index
    lsubsequences[0].longesubSequence[0] = sequence[0]; //First sequence have only first element
    lsubsequences[0].longesubequenceLength = 1;  //First sequence have only first element so count is 1
    
    //Loop Start from second element and count longest sequence for each index
    for (int i=1; i<seqL; i++) {
        //Loop check for all the possible sub sequence and check if length is largest
        for(int j=0; j <i ; j++){
            if(sequence[i] > sequence[j]){
                finalsubsequenceLength = lsubsequences[j].longesubequenceLength + 1;
                if(finalsubsequenceLength > lsubsequences[i].longesubequenceLength){
                    lsubsequences[i].longesubequenceLength = finalsubsequenceLength;
                    finalSubSequenceIndex  = j; //Store the largest increasing sub sequence for index i
                }
            }
        }
        
        //loop copy all the elements of longest sub sequence of i to index i of heap
        if(finalSubSequenceIndex != -1){
            int k = 0;
            for(; k < lsubsequences[i].longesubequenceLength-1; k++){
                lsubsequences[i].longesubSequence[k] = lsubsequences[finalSubSequenceIndex].longesubSequence[k];
            }
            lsubsequences[i].longesubSequence[k] = sequence[i];
        }
        finalSubSequenceIndex = -1;
        
        
    }
    
    //loop calculate longest increasing sub sequence from all the indexs in a heap
    finalsubsequenceLength = 0;
    for (int k=0; k<seqL; k++) {
        if(lsubsequences[k].longesubequenceLength > finalsubsequenceLength){
            finalsubsequenceLength = lsubsequences[k].longesubequenceLength;
            finalSubSequenceIndex = k;
        }
    }
    //return the longest sub sequence heap element
    return lsubsequences[finalSubSequenceIndex];
}