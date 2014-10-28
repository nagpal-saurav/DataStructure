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
#define  Invalid_Index      -1

typedef struct graph_adjacency_list_struct adjacency_list;
typedef struct graph_adjacency_head_struct adjacency_head;

struct graph_internal_struct{
    graph_storage_type_e  type;
    graph_vertex_count    currentCount;
    SNGraphVertex         **vertices;
    int                   *graph;
};

typedef struct adjacency_matrix{
    int     **graph_matrix;
}graph_matrix;

struct graph_adjacency_list_struct{
    SNGraphVertex       *toVertex;
    void*               data;
    adjacency_list      *next_vertex;
};

struct graph_adjacency_head_struct{
    int                 degreeOfvertex;
    adjacency_list      *headVertex;
};

bool addVertexToGraphVertices(SNGraph *graph, SNGraphVertex* vertex);
int findVertexIndex(SNGraph* graph, SNGraphVertex* vertex);
adjacency_list* newAdjacencyEdge(SNGraphVertex* vertex);

SNGraph* newGraph(graph_storage_type_e type, graph_vertex_count count){
    SNGraph* newGraph = (SNGraph*) malloc(sizeof(SNGraph));
    if(!newGraph){
        return NULL;
    }
    newGraph->graph_data = (graph_internal*) malloc(sizeof(graph_internal));
    newGraph->graph_data->type = type;
    newGraph->vertexCount = count;
    newGraph->graph_data->currentCount = 0;
    newGraph->graph_data->vertices = (SNGraphVertex**)malloc(sizeof(SNGraphVertex*) * count);
    switch (type) {
        case graph_storage_adjacency_matrix:{
            newGraph->graph_data->graph = malloc(sizeof(int*) * count * matrix_count);
            break;
        }
        case graph_storage_adjacency_list:{
            newGraph->graph_data->graph  = malloc(sizeof(adjacency_head) * count);
            break;
        }
        default:
            break;
    }
    
    return newGraph;
}

SNGraphVertex* addVertex(SNGraph *graph, const char* name){
    SNGraphVertex* vertex = (SNGraphVertex*)malloc(sizeof(SNGraphVertex));
    vertex->vertexName = malloc(strlen(name));
    strcpy(vertex->vertexName, name);
    bool isVertexAdded = addVertexToGraphVertices(graph, vertex);
    if(isVertexAdded){
        return vertex;
    }
    free(vertex);
    return NULL;
}

SNGraphEdge* addEdge(SNGraph *graph, SNGraphVertex *vertex1, SNGraphVertex *vertex2, void* data){
    SNGraphEdge* edge = (SNGraphEdge*)malloc(sizeof(SNGraphEdge));
    if(vertex1 == vertex2){
        return NULL;
    }
    switch (graph->graph_data->type) {
        case graph_storage_adjacency_matrix:{
            int index1 = findVertexIndex(graph, vertex1);
            int index2 = findVertexIndex(graph, vertex2);
            if(index1 != Invalid_Index && index2 != Invalid_Index){
                int** graphBuf = (int**)graph->graph_data->graph;
                graphBuf[index1][index2] = graphBuf[index2][index1] = *(int*)data;
            }
            break;
        }
        case graph_storage_adjacency_list:{
            int index1 = findVertexIndex(graph, vertex1);
            if(index1 != Invalid_Index){
                adjacency_head* graphBuf =(adjacency_head*) graph->graph_data->graph;
                adjacency_list* newEdge = newAdjacencyEdge(vertex2);
                newEdge->data = data;
                if(graphBuf->degreeOfvertex == 0){
                    graphBuf->headVertex = newEdge;
                }else{
                    newEdge->next_vertex = graphBuf->headVertex->next_vertex;
                    graphBuf->headVertex->next_vertex = newEdge->next_vertex;
                }
            }
            break;
        }

    }
    return edge;
    
}

bool addVertexToGraphVertices(SNGraph *graph, SNGraphVertex* vertex){
    bool currentIndex = graph->graph_data->currentCount;
    if(currentIndex < graph->vertexCount){
        SNGraphVertex   **vertices = graph->graph_data->vertices;
        vertices[currentIndex] = vertex;
        return true;
    }
    return false;
}

int findVertexIndex(SNGraph* graph, SNGraphVertex* vertex){
    int index = -1;
    bool currentIndex = graph->graph_data->currentCount;
    SNGraphVertex   **vertices = graph->graph_data->vertices;
    for (int i = 0; i < currentIndex; i++) {
        SNGraphVertex* addedVertex  = vertices[i];
        if(addedVertex == vertex){
            index = i;
            break;
        }
    }
    return index;
}

adjacency_list* newAdjacencyEdge(SNGraphVertex* vertex){
    adjacency_list* newEdge = (adjacency_list*)malloc(sizeof(adjacency_list));
    newEdge->toVertex = vertex;
    newEdge->next_vertex = NULL;
    return newEdge;
}