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
/*
 *Graph Typedef
 */
typedef struct graph_adjacency_list_struct adjacency_list;
typedef struct graph_adjacency_head_struct adjacency_head;

/*
 *It contains the graph internal member.
 */
struct graph_internal_struct{
    graph_storage_type_e  storageType; //Storage type for graph
    graph_type            type;         //Type  of graph
    graph_vertex_count    currentCount; //Current Count of vertices added in graph
    void                  **vertices;   //Array contains  all the vertices of graph
    void                  **graph;      //refrence for all the edges of graph and structure depend upon the storage type
};

/*
 *It contains the adjacency matrix member.
 */
typedef struct adjacency_matrix{
    int     **graph_matrix; //2-D array for adjacency Matrix
}graph_matrix;

/*
 *This structure represent the link list for adjacency list.
 */
struct graph_adjacency_list_struct{
    SNGraphVertex       *toVertex;   //refrence for the vertex
    void*               data;        //any Data related to relationship like for weighted graph weight
    adjacency_list      *next_vertex; //Pointer to next vertex
};

/*
 *This structure represent the head of adjacency list.
 */
struct graph_adjacency_head_struct{
    int                 degreeOfvertex; // It will have degree of vertex
    adjacency_list      *headVertex;    // It contain refrence for head for all the vertices
};

/********************************
 *Private Method Decleration Start
 ********************************/
/*
 * Function: addVertexToGraphVertices
 * ----------------------------
 *   add a vertex in a vertices array of graph
 *
 *   graph: the refrence for the graph in which vertex has to be add
 *   vertex: the refrence to the newly created  vertex
 *
 *   returns: the retuns whteher vertex added or not.
 */
bool addVertexToGraphVertices(SNGraph *graph, SNGraphVertex* vertex);

/*
 * Function: findVertexIndex
 * ----------------------------
 *   find the index of vertex in graph vertices array
 *
 *   graph: the refrence for the graph in which vertex has to be add
 *   vertex: the refrence of the vertex to be find
 *
 *   returns: the retuns the index of vertex if find else -1.
 */
int findVertexIndex(SNGraph* graph, SNGraphVertex* vertex);

/*
 * Function: newAdjacencyEdge
 * ----------------------------
 *   create a new edge for adjacency list and return the refrence of the edge
 *
 *   vertex: the refrence of the end vertex of the edge
 *
 *   returns: the retuns the refrence of adjacency list which contain the end vertex with edge data.
 */
adjacency_list* newAdjacencyEdge(SNGraphVertex* vertex);

/*
 * Function: addEdgeBetweenTheVertex
 * ----------------------------
 *   add a edge in a adjacency list graph between the vertex
 *
 *   graph: the refrence for the adjacency list graph in which edge has to be add
 *   vertex1: the start vertex of edge
 *   vertex2: the end vertex of edge
 *   data   : the data related to the edge (Specefic to weighted graph)
 *
 *   returns: the retuns whteher edge added or not.
 */
bool addEdgeBetweenTheVertex(SNGraph* graph, SNGraphVertex* vertex1, SNGraphVertex* vertex2, void* data);
/********************************
 *Private Method Decleration End
 ********************************/


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