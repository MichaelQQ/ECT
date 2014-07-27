#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INFINITY 32767
#define SIZE 6
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
                             {0,1,0,0,0,1},
                             {1,0,1,0,1,0},
                            };
    int i=0,j=0,n=0;
    int MASKED_GRAPH[SIZE][SIZE] = {0};
    int MASKED_SOURCE = 0;

    for (i=0;i<SIZE;i++)
    {
        for (j=0;j<SIZE;j++)
	{
            printf("%d ",GRAPH[i][j]);
        }
        printf("\n");
    }

    for (n=0;n<17;n++)
    {
        printf("\n\nECT_MASK = %2X\n", ECT_MASK[n]);
        for (i=0;i<SIZE;i++)
	{
            printf("i=%d,XOR=%d\t", i, (i^ECT_MASK[n]));
            for (j=0;j<SIZE;j++)
	    {
                MASKED_GRAPH[(i^ECT_MASK[n])% SIZE][(j^ECT_MASK[n])% SIZE] = GRAPH[i][j];
            }
        }

        Dijkstra(MASKED_GRAPH, (0^ECT_MASK[n])%SIZE);
        show((0^ECT_MASK[n])% SIZE);
    }
    printf("\n");
}

void Dijkstra(int Graph[SIZE][SIZE], int source)
{
    int dist[SIZE] = {0};
    bool Q[SIZE] = {false};
    int Q_count = 0;
    int alt = 0;
    int i = 0,v = 0,u = 0;

    dist[source] = 0;              // Distance from source to source
    previous[source] = -1;
    for (v = 0; v < SIZE; v++)           // Initializations
    {                
        if (v != source)
	{
            dist[v] = INFINITY;    // Unknown distance function from source to v
            previous[v] = -1;      // Previous node in optimal path from source
        }
        Q_count++;
        Q[v] = true;               // All nodes initially in Q
    }

    while (Q_count > 0)              // The main loop
    {           
        u = -1;
        i = 0;
        while (u == -1) 
	{
            if (Q[i])
                u = i;
            i++;
        }
        for (i = 0; i < SIZE; i++)
	{
            if (dist[i] < dist[u] && Q[i])
                u = i;
        }

        Q[u]=false;
        Q_count--;

        for (v=0;v<SIZE;v++)        // where v has not yet been removed from Q. 
        {
	    if(Graph[u][v]>0)             //each neighbor v of u:
	    {                 
                alt = dist[u] + Graph[u][v];       //length(u, v)
                if (alt < dist[v])        // A shorter path to v has been found
		{               
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
    int i = 0;

    for(i = 0; i < SIZE; i++) 
    {
        if (i == source)
	{
            printf("\n%d: source", i);
        }
        else
	{
            printf("\n%d: ", i);
            ptr = i;
            while (previous[ptr] != -1)
	    {
                printf("%d ", ptr);
                ptr = previous[ptr];
            }
        }
    }
}
