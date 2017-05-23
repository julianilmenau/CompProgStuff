#include <iostream>
#include <bits/stdc++.h>

using namespace std;

void fastscan(int &number)
{
    bool negative = false;
    register int c;

    number = 0;

    c = getchar_unlocked();
    if (c=='-')
    {
        negative = true;
        c = getchar_unlocked();
    }
    for (; (c>47 && c<58); c=getchar_unlocked())
        number = number *10 + c - 48;

    if (negative)
        number *= -1;
}


struct Edge {
    int a,b,weight;
};

struct Graph {
    int v,e;
    struct Edge *edges;
};

void bellmanFord(Graph * graph,int src,int  *dist) {
    int v=graph->v;
    int e=graph->e;
    for (int i=0;i<v;i++) {
        dist[i]=INT_MAX;
    }
    dist[src]=0;

    for (int i=0;i<v-1;i++) {
        for (int j=0;j<e;j++) {
            int u = graph->edges[j].a;
            int v = graph->edges[j].b;
            int weight = graph->edges[j].weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
                dist[v] = dist[u] + weight;
        }
    }
    return;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

        int nNodes,nEdges,nQuestions;
        fastscan(nNodes);
        fastscan(nEdges);
        fastscan(nQuestions);

        Graph *graph = (Graph*) malloc(sizeof(Graph));
        graph->v=nNodes;
        graph->e=nEdges;
        graph->edges = (Edge*) malloc(nEdges*sizeof(Edge));

        for (int i=0;i<nEdges;i++) {
            int a,b,weight;
            fastscan(a);
            fastscan(b);
            fastscan(weight);
            graph->edges[i]={a,b,weight};
        }

    int results[nNodes][nNodes];
    for (int i=0;i<nNodes;i++) {
        results[i][0]=-1;
    }
        for (int i=0;i<nQuestions;i++) {
            int a,b,found;
            fastscan(a);
            fastscan(b);
            if (results[a][0]==-1) {
                bellmanFord(graph,a,&results[a][0]);
                found=results[a][b];
            } else {
                found=results[a][b];
            }
            if (found==INT_MAX) {
                cout<<"oo"<<"\n";
            } else {
                cout<<found<<"\n";
            }

        }


        return 0;
}
