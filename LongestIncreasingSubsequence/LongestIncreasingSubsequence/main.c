//
//  main.c
//  LongestIncreasingSubsequence
//
//  Created by Saurav Nagpal on 22/10/14.
//  Copyright (c) 2014 Saurav Nagpal. All rights reserved.
//

#include <string.h>
#include <stdio.h>

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

lsIncreasingSequence longIncSubsequence(int sequence[], int seqL){
    lsIncreasingSequence lsubsequences[seqL+1];
    int finalsubsequenceLength = 0;
    int finalSubSequenceIndex = -1;
    lsubsequences[0].longesubSequence[0] = 0;
    lsubsequences[0].longesubequenceLength = 1;
    for (int i=1; i<seqL; i++) {
        for(int j=0; j <i ; j++){
            if(sequence[i] > sequence[j]){
                finalsubsequenceLength = lsubsequences[j].longesubequenceLength + 1;
                if(finalsubsequenceLength > lsubsequences[i].longesubequenceLength){
                    lsubsequences[i].longesubequenceLength = finalsubsequenceLength;
                    finalSubSequenceIndex  = j;
                }
            }
        }
        
        if(finalSubSequenceIndex != -1){
            int k = 0;
            for(; k < lsubsequences[i].longesubequenceLength-1; k++){
                lsubsequences[i].longesubSequence[k] = lsubsequences[finalSubSequenceIndex].longesubSequence[k];
            }
            lsubsequences[i].longesubSequence[k] = sequence[i];
        }
        finalSubSequenceIndex = -1;
        
        
    }
    
    finalsubsequenceLength = 0;
    for (int k=0; k<seqL; k++) {
        if(lsubsequences[k].longesubequenceLength > finalsubsequenceLength){
            finalsubsequenceLength = lsubsequences[k].longesubequenceLength;
            finalSubSequenceIndex = k;
        }
    }
    
    return lsubsequences[finalSubSequenceIndex];
}