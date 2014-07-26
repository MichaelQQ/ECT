#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INFINITY 32767
#define SIZE 6
#define SOURCE 0

void Dijkstra(int Graph[SIZE][SIZE], int source);
void show(int source);

int previous[SIZE];
int ECT_MASK[17] = { 0x00, 0x00, 0xFF, 0x88,
                     0x77, 0x44, 0x33, 0xCC,
                     0xBB, 0x22, 0x11, 0x66,
                     0x55, 0xAA, 0x99, 0xDD,
                     0xEE };

int main()
{
    int GRAPH[SIZE][SIZE] = {{0,1,0,0,0,1},
                             {1,0,1,0,1,0},
                             {0,1,0,1,0,1},
                             {0,0,1,0,1,0},
                             {0,1,0,1,0,1},
                             {1,0,1,0,1,0},
                            };
    int i=0,j=0,n=0,k=0;
    int MASKED_GRAPH[SIZE][SIZE] = {0};
    int MASKED_SOURCE = 0;
    int temp = 0;
    int ID[SIZE][2] = {{0,0},(1,1),{2,2},{3,3},{4,4},{5,5}};

    for (i=0;i<SIZE;i++){
        for (j=0;j<SIZE;j++){
            printf("%d ",GRAPH[i][j]);
        }
        printf("\n");
    }

    for (n=0;n<17;n++) {
        printf("\n\nECT_MASK = %2X", ECT_MASK[n]);
        for (k=0;k<SIZE;k++) {
            ID[k][0] = k;
            ID[k][1] = k^ECT_MASK[n];
        }
        //sort Masked ID
        for(i=0;i<SIZE;i++){
            for(j=0;j<SIZE-1-i;j++){
                if(ID[j][1] > ID[j+1][1]){
                    temp = ID[j][1];
                    ID[j][1] = ID[j+1][1];
                    ID[j+1][1] = temp;
                    temp = ID[j][0];
                    ID[j][0] = ID[j+1][0];
                    ID[j+1][0] = temp;
                }
            }
        }
        //Create Masked Graph
        for (i=0;i<SIZE;i++){
            //printf("i=%d,XOR=%d\t", ID[i][0], ID[i][1]);
            for (j=0;j<SIZE;j++){
                MASKED_GRAPH[ID[i][0]][ID[j][0]] = GRAPH[i][j];
            }
        }

        Dijkstra(MASKED_GRAPH, ID[SOURCE][0]);
        show(ID[SOURCE][0]);
    }
}

void Dijkstra(int Graph[SIZE][SIZE], int source)
{
    int dist[SIZE] = {0};
    bool Q[SIZE] = {false};
    int Q_count = 0;
    int alt=0;
    int i=0,v=0,u=0;

    dist[source] = 0;                     // Distance from source to source
    previous[source] = -1;
    for (v=0;v<SIZE;v++) {                // Initializations
        if (v != source) {
            dist[v] = INFINITY;           // Unknown distance function from source to v
            previous[v] = -1;             // Previous node in optimal path from source
        }
        Q_count++;
        Q[v] = true;                      // All nodes initially in Q
    }

    while (Q_count>0) {                        // The main loop
        u = -1;
        i = 0;
        while (u == -1) {
            if (Q[i])
                u = i;
            i++;
        }
        for (i=0;i<SIZE;i++) {
            if (dist[i] < dist[u] && Q[i])
                u = i;
        }

        Q[u]=false;
        Q_count--;

        for (v=0;v<SIZE;v++) {           // where v has not yet been removed from Q.
            if(Graph[u][v]>0) {          //each neighbor v of u:
                alt = dist[u] + Graph[u][v];       //length(u, v)
                if (alt < dist[v]) {               // A shorter path to v has been found
                    dist[v] = alt;
                    previous[v] = u;
                }
            }
        }
    }
}

void show(int source)
{
    int ptr;
    int i=0;

    for(i=0;i<SIZE;i++) {
        if (i == source){
            printf("\n%d: source",i);
        }
        else{
            printf("\n%d: ", i);
            ptr = i;
            while (previous[ptr] != -1){
                printf("%d ", ptr);
                ptr = previous[ptr];
            }
        }
    }
}
