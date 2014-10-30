//
//  Graph.h
//  GraphDataStructure
//
//  Created by Saurav Nagpal on 25/10/14.
//  Copyright (c) 2014 Saurav Nagpal. All rights reserved.
//

#ifndef __GraphDataStructure__Graph__
#define __GraphDataStructure__Graph__

#include <stdbool.h>
/*
 *Graph Typedef
 */
typedef struct graph_struct SNGraph;
typedef struct graph_vertex_struct SNGraphVertex;
typedef struct graph_vertex_edge   SNGraphEdge;
typedef struct graph_internal_struct graph_internal;
typedef int    graph_vertex_count;

/*
 *It conatains constants for the storage type used for graph (2-D Array or link list)
 */
typedef enum {
    graph_storage_adjacency_matrix,
    graph_storage_adjacency_list
}graph_storage_type_e;
/*
 *It conatains constants various graph type Directed or Undirected
 */
typedef enum {
    graph_type_Directed,
    graph_type_Undirected
}graph_type;


/*
 *It represent the graph and the newly created garph will be refrence of this struct.
 */
struct graph_struct{
    graph_vertex_count    vertexCount;
    graph_internal        *graph_data;
};

/*
 *It represent the vertex of graph and the newly created vertex will be refrence of this struct.
 */
struct graph_vertex_struct{
    char*      vertexName;
};

/*
 *It represent the edge of graph and the newly created edge will be refrence of this struct.
 */
struct graph_vertex_edge{
    int      weight;
};

/*
 *It contains the graph properties and to create a new graph this property need to specify.
 */
typedef struct graph_properties_struct{
    graph_type               graphType;
    graph_storage_type_e     storageType;
}graph_properties;

/*
 * Function: newGraph
 * ----------------------------
 *   allocate a new graph and return the refernce for it
 *
 *   properties: contain the properties for the graph
 *   count: the number of vertices in graph
 *
 *   returns: the refernce for the graph
 */
SNGraph* newGraph(graph_properties *properties, graph_vertex_count count);

/*
 * Function: addVertex
 * ----------------------------
 *   add a vertex in a graph
 *
 *   graph: the refrence for the graph in which vertex has to be add
 *   name: the name of vertex
 *
 *   returns: the refernce of the added vertex
 */
SNGraphVertex* addVertex(SNGraph *graph, const char* name);

/*
 * Function: addEdge
 * ----------------------------
 *   add a edge in a graph between the vertex
 *
 *   graph: the refrence for the graph in which edge has to be add
 *   vertex1: the start vertex of edge
 *   vertex2: the end vertex of edge
 *   data   : the data related to the edge (Specefic to weighted graph)
 *
 *   returns: the refernce of the added edge
 */
SNGraphEdge* addEdge(SNGraph *graph, SNGraphVertex *vertex1, SNGraphVertex *vertex2, void* data);

/*
 * Function: displayGraph
 * ----------------------------
 *   prints all the vertices with its connected neighbour
 *
 *   graph: the refrence for the graph in which vertex has to be add
 *
 *
 *   returns:
 */
void displayGraph(SNGraph *graph);

/*
 * Function: releaseGraph
 * ----------------------------
 *   release the memory used by graph.
 *
 *   graph: the pointer to refrence for the graph in which vertex has to be add
 *
 *
 *   returns:
 */
void releaseGraph(SNGraph **graphPtr);

#endif /* defined(__GraphDataStructure__Graph__) */
