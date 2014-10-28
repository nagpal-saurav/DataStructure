//
//  main.c
//  GraphDataStructure
//
//  Created by Saurav Nagpal on 25/10/14.
//  Copyright (c) 2014 Saurav Nagpal. All rights reserved.
//

#include "Graph.h"
#include <stdio.h>

int main(int argc, const char * argv[]) {
    // insert code here...
    SNGraph* graph = newGraph(graph_storage_adjacency_list, 7);
    SNGraphVertex* delhiVertex = addVertex(graph, "Delhi");
    SNGraphVertex* JaipurVertex = addVertex(graph, "Jaipur");
    SNGraphVertex* LucknowVertex = addVertex(graph, "Lucknow");
    SNGraphVertex* KanpurVertex = addVertex(graph, "Kanpur");
    SNGraphVertex* KushinagarVertex = addVertex(graph, "Kushinagar");
    SNGraphVertex* BodhVertex = addVertex(graph, "Bodh Gaya");
    SNGraphVertex* KolkataVertex = addVertex(graph, "Kolkata");
    
    int distance1 = 500;
    addEdge(graph, delhiVertex, KanpurVertex, &distance1);
    
    int distance2 = 1200;
    addEdge(graph, KanpurVertex, KolkataVertex, &distance2);
    
    int distance3 = 250;
    addEdge(graph, delhiVertex, JaipurVertex, &distance3);
    
    int distance4 = 400;
    addEdge(graph, JaipurVertex, LucknowVertex, &distance4);
    
    int distance5 = 450;
    addEdge(graph, LucknowVertex, KushinagarVertex, &distance5);
    
    int distance6 = 250;
    addEdge(graph, KushinagarVertex, BodhVertex, &distance6);
    
    int distance7 = 500;
    addEdge(graph, KushinagarVertex, KanpurVertex, &distance7);
    
    displayGraph(graph);
    return 0;
}
