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

typedef struct graph_struct SNGraph;
typedef struct graph_vertex_struct SNGraphVertex;
typedef struct graph_vertex_edge   SNGraphEdge;
typedef int    graph_vertex_count;

typedef struct graph_internal_struct graph_internal;

struct graph_struct{
    graph_vertex_count    vertexCount;
    graph_internal        *graph_data;
};

struct graph_vertex_struct{
    char*      vertexName;
};

struct graph_vertex_edge{
    int      weight;
};

typedef enum {
   graph_storage_adjacency_matrix,
   graph_storage_adjacency_list
}graph_storage_type_e;


SNGraph* newGraph(graph_storage_type_e type, graph_vertex_count count);
SNGraphVertex* addVertex(SNGraph *graph, const char* name);
SNGraphEdge* addEdge(SNGraph *graph, SNGraphVertex *vertex1, SNGraphVertex *vertex2, void* data);

#endif /* defined(__GraphDataStructure__Graph__) */
