//
//  Graph.c
//  GraphDataStructure
//
//  Created by Saurav Nagpal on 25/10/14.
//  Copyright (c) 2014 Saurav Nagpal. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "Graph.h"

#define  matrix_count       2u

struct graph_internal_struct{
    graph_storage_type_e  type;
    graph_vertex_count    vertexCount;
    SNGraphVertex         *vertices;
    int                   *graph;
};



typedef struct graph_matrix_struct{
    int     **graph_matrix;
}graph_matrix;



SNGraph* newGraph(graph_storage_type_e type, graph_vertex_count count){
    SNGraph* newGraph = (SNGraph*) malloc(sizeof(SNGraph));
    newGraph->graph_data = (graph_internal*) malloc(sizeof(graph_internal));
    newGraph->graph_data->type = type;
    newGraph->vertexCount = count;
    newGraph->graph_data->vertices = malloc(sizeof(SNGraphVertex) * count);
    switch (type) {
        case graph_storage_adjacency_matrix:{
                newGraph->graph_data->graph = malloc(sizeof(int) * count * matrix_count);
            }
            break;
        case graph_storage_adjacency_list:{
            
            break;
        }
        default:
            break;
    }
    
    return newGraph;
}

bool addVertex(SNGraph *graph, const char* name){
    SNGraphVertex* vertex = (SNGraphVertex*)malloc(sizeof(SNGraphVertex));
    vertex->vertexName = malloc(strlen(name));
    strcpy(vertex->vertexName, name);
    
    return true;
}

bool addEdge(SNGraph *graph, SNGraphVertex *vertex1, SNGraphVertex *vertex2){
    return true;
}