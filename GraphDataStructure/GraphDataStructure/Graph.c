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
    graph_storage_type_e  storageType;
    graph_type            type;
    graph_vertex_count    currentCount;
    void                  **vertices;
    void                  **graph;
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
bool addEdgeBetweenTheVertex(SNGraph* graph, SNGraphVertex* vertex1, SNGraphVertex* vertex2, void* data);

SNGraph* newGraph(graph_properties *properties, graph_vertex_count count){
    SNGraph* newGraph = (SNGraph*) malloc(sizeof(SNGraph));
    if(!newGraph){
        return NULL;
    }
    newGraph->graph_data = (graph_internal*) malloc(sizeof(graph_internal));
    newGraph->graph_data->type = properties->graphType;
    newGraph->graph_data->storageType = properties->storageType;
    newGraph->vertexCount = count;
    newGraph->graph_data->currentCount = 0;
    newGraph->graph_data->vertices = malloc(sizeof(SNGraphVertex*) * count);
    switch (properties->storageType) {
        case graph_storage_adjacency_matrix:{
            int** graph_matrix = calloc(sizeof(int*), count);
            for (int i = 0; i < count; i++) {
                graph_matrix[i] = calloc(sizeof(int*), count);
            }
            newGraph->graph_data->graph = (void**)graph_matrix;
            break;
        }
        case graph_storage_adjacency_list:{
            newGraph->graph_data->graph  = malloc(sizeof(adjacency_head*) * count);
            for (int i = 0; i < count; i++) {
                newGraph->graph_data->graph[i] = malloc(sizeof(adjacency_head));
                adjacency_head* graphHead = (adjacency_head*)newGraph->graph_data->graph[i];
                graphHead[i].degreeOfvertex = 0;
                graphHead[i].headVertex = NULL;
            }
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
    switch (graph->graph_data->storageType) {
        case graph_storage_adjacency_matrix:{
            int index1 = findVertexIndex(graph, vertex1);
            int index2 = findVertexIndex(graph, vertex2);
            if(index1 != Invalid_Index && index2 != Invalid_Index){
                int** graphBuf = (int**)graph->graph_data->graph;
                if(graph->graph_data->type == graph_type_Directed){
                    graphBuf[index1][index2] = *(int*)data;
                }else{
                    graphBuf[index1][index2] = graphBuf[index2][index1] = *(int*)data;
                }
                
            }
            break;
        }
        case graph_storage_adjacency_list:{
            addEdgeBetweenTheVertex(graph, vertex1, vertex2, data);
            if(graph->graph_data->type == graph_type_Undirected){
                addEdgeBetweenTheVertex(graph, vertex2, vertex1, data);
            }
            break;
        }

    }
    return edge;
    
}

void displayGraph(SNGraph *graph){
    if(!graph){
        printf("No Graph data");
    }
    switch (graph->graph_data->storageType) {
        case graph_storage_adjacency_matrix:{
            int verticesCount = graph->graph_data->currentCount;
            int** graphBuf = (int**) graph->graph_data->graph;
            for (int i= 0; i < verticesCount; i++) {
                 SNGraphVertex *vertex = graph->graph_data->vertices[i];
                 printf("%s is connected to the",vertex->vertexName);
                 for (int j= 0; j < verticesCount; j++) {
                     if((graphBuf[i][j]) > 0){
                         SNGraphVertex *neighbour = graph->graph_data->vertices[j];
                         printf("->%s with value:%d",neighbour->vertexName, graphBuf[i][j]);
                     }
                }
                printf("\n");
            }
            break;
        }
        case graph_storage_adjacency_list:{
            int verticesCount = graph->graph_data->currentCount;
            adjacency_head** graphBuf =(adjacency_head**) graph->graph_data->graph;
            for (int i= 0; i < verticesCount; i++) {
                SNGraphVertex *vertex = graph->graph_data->vertices[i];
                adjacency_list *neighbour = (adjacency_list *)graphBuf[i]->headVertex;
                if(neighbour != NULL){
                    printf("%s is connected to the",vertex->vertexName);
                    while (neighbour != NULL) {
                        printf("->%s",neighbour->toVertex->vertexName);
                        neighbour = neighbour->next_vertex;
                    }
                }else{
                    printf("%s does not have any neighbour",vertex->vertexName);
                }
                printf("\n");
                
            }
            break;
        }
            
    }
}

void releaseGraph(SNGraph **graphPtr){
    SNGraph* graph = *graphPtr;
    if(!graph){
        printf("No Graph data");
    }
    
    switch (graph->graph_data->storageType) {
        case graph_storage_adjacency_matrix:{
            int verticesCount = graph->graph_data->currentCount;
            int** graphBuf = (int**) graph->graph_data->graph;
            for (int i= 0; i < verticesCount; i++) {
                free(graphBuf[i]);
                free(graph->graph_data->vertices[i]);
            }
            free(graph->graph_data->vertices);
            free(graphBuf);
            break;
        }
        case graph_storage_adjacency_list:{
            int verticesCount = graph->graph_data->currentCount;
            adjacency_head** graphBuf =(adjacency_head**) graph->graph_data->graph;
            for (int i= 0; i < verticesCount; i++) {
                SNGraphVertex *vertex = graph->graph_data->vertices[i];
                adjacency_list *neighbour = (adjacency_list *)graphBuf[i]->headVertex;
                if(neighbour != NULL){
                    while (neighbour != NULL) {
                        adjacency_list* currentNeighbour = neighbour;
                        neighbour = neighbour->next_vertex;
                        free(currentNeighbour);
                    }
                }
                free(vertex);
                free(graphBuf[i]);
            }
            free(graph->graph_data->vertices);
            free(graphBuf);
            break;
        }
    }
    *graphPtr = NULL;
}

/*
 *PRIVATE FUNCTION
 */
bool addVertexToGraphVertices(SNGraph *graph, SNGraphVertex* vertex){
    int currentIndex = graph->graph_data->currentCount;
    if(currentIndex < graph->vertexCount){
        graph->graph_data->vertices[currentIndex] = vertex;
        graph->graph_data->currentCount++;
        return true;
    }
    return false;
}

int findVertexIndex(SNGraph* graph, SNGraphVertex* vertex){
    int index = -1;
    int currentIndex = graph->graph_data->currentCount;
    SNGraphVertex   **vertices = (SNGraphVertex**) graph->graph_data->vertices;
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

bool addEdgeBetweenTheVertex(SNGraph* graph, SNGraphVertex* vertex1, SNGraphVertex* vertex2, void* data){
    bool isAdded = false;
    int index1 = findVertexIndex(graph, vertex1);
    if(index1 != Invalid_Index){
        adjacency_head** graphBuf =(adjacency_head**) graph->graph_data->graph;
        adjacency_list* newEdge = newAdjacencyEdge(vertex2);
        newEdge->data = data;
        if(graphBuf[index1]->degreeOfvertex == 0){
            graphBuf[index1]->headVertex = newEdge;
        }else{
            newEdge->next_vertex = graphBuf[index1]->headVertex->next_vertex;
            graphBuf[index1]->headVertex->next_vertex = newEdge;
        }
        graphBuf[index1]->degreeOfvertex++;
        isAdded = true;
    }
    return isAdded;
}