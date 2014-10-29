//
//  main.c
//  GraphDataStructure
//
//  Created by Saurav Nagpal on 25/10/14.
//  Copyright (c) 2014 Saurav Nagpal. All rights reserved.
//

#include "Graph.h"
#include <stdio.h>

SNGraph* createSampleGraphList();
SNGraph* createSampleGraphMatrix();

int main(int argc, const char * argv[]) {
    // insert code here...
    SNGraph* graph_list = createSampleGraphList();
    displayGraph(graph_list);
    releaseGraph(&graph_list);
    
    SNGraph* graph_matrix = createSampleGraphMatrix();
    return 0;
}

SNGraph* createSampleGraphList(){
    
    SNGraph* graph_list = newGraph(graph_storage_adjacency_list, 7);
    SNGraphVertex* delhiVertex = addVertex(graph_list, "Delhi");
    SNGraphVertex* JaipurVertex = addVertex(graph_list, "Jaipur");
    SNGraphVertex* LucknowVertex = addVertex(graph_list, "Lucknow");
    SNGraphVertex* KanpurVertex = addVertex(graph_list, "Kanpur");
    SNGraphVertex* KushinagarVertex = addVertex(graph_list, "Kushinagar");
    SNGraphVertex* BodhVertex = addVertex(graph_list, "Bodh Gaya");
    SNGraphVertex* KolkataVertex = addVertex(graph_list, "Kolkata");
    
    int distance1 = 500;
    addEdge(graph_list, delhiVertex, KanpurVertex, &distance1);
    
    int distance2 = 1200;
    addEdge(graph_list, KanpurVertex, KolkataVertex, &distance2);
    
    int distance3 = 250;
    addEdge(graph_list, delhiVertex, JaipurVertex, &distance3);
    
    int distance4 = 400;
    addEdge(graph_list, JaipurVertex, LucknowVertex, &distance4);
    
    int distance5 = 450;
    addEdge(graph_list, LucknowVertex, KushinagarVertex, &distance5);
    
    int distance6 = 250;
    addEdge(graph_list, KushinagarVertex, BodhVertex, &distance6);
    
    int distance7 = 500;
    addEdge(graph_list, KushinagarVertex, KanpurVertex, &distance7);
    return graph_list;
}

SNGraph* createSampleGraphMatrix(){
    SNGraph* graph_matrix = newGraph(graph_storage_adjacency_matrix, 7);
    
    SNGraphVertex* delhiVertex = addVertex(graph_matrix, "Delhi");
    SNGraphVertex* JaipurVertex = addVertex(graph_matrix, "Jaipur");
    SNGraphVertex* LucknowVertex = addVertex(graph_matrix, "Lucknow");
    SNGraphVertex* KanpurVertex = addVertex(graph_matrix, "Kanpur");
    SNGraphVertex* KushinagarVertex = addVertex(graph_matrix, "Kushinagar");
    SNGraphVertex* BodhVertex = addVertex(graph_matrix, "Bodh Gaya");
    SNGraphVertex* KolkataVertex = addVertex(graph_matrix, "Kolkata");
    
    int distance1 = 500;
    addEdge(graph_matrix, delhiVertex, KanpurVertex, &distance1);
    
    int distance2 = 1200;
    addEdge(graph_matrix, KanpurVertex, KolkataVertex, &distance2);
    
    int distance3 = 250;
    addEdge(graph_matrix, delhiVertex, JaipurVertex, &distance3);
    
    int distance4 = 400;
    addEdge(graph_matrix, JaipurVertex, LucknowVertex, &distance4);
    
    int distance5 = 450;
    addEdge(graph_matrix, LucknowVertex, KushinagarVertex, &distance5);
    
    int distance6 = 250;
    addEdge(graph_matrix, KushinagarVertex, BodhVertex, &distance6);
    
    int distance7 = 500;
    addEdge(graph_matrix, KushinagarVertex, KanpurVertex, &distance7);
    
    return graph_matrix;
}
