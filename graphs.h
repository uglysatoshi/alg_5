#ifndef GRAPHS
#define GRAPH

#include <iostream>
#include <queue>
#include <stack>
#include <string.h>
#include <vector>

#define INF 101

using namespace std;

struct Edge
{   
    public:
        int begin;
        int end;
        int weight;
        Edge(int newBegin = int(), int newEnd = int(), int newWeigth = int())
        {   
            begin = newBegin;
            end = newEnd;
            weight = newWeigth;
        }
};

class Graph
{
    private:
        int uni;
        int countVertex; // vertexses counter
        int countPath; // paths counter
        int** PM; // path matrix
        int** AM; // adjacency matrix
        int** IM; // incidence matrix
        queue <Edge> edge; // edge list
    public:    
        Graph(); // constructor
        ~Graph(); // destructor
        void FromRLtoPM(); // path matrix
        void PrintPM(); // print path matrix
        void FromRLtoAM(); // adjacency matrix
        void PrintAM(); // Print adjacency matrix
        void FromRLtoIM(); // incidence matrix
        void PrintIM(); // Print incidence matrix
        void PrintLL(); // Вывод списка смежности
        void PrintRL(); // Вывод списка граней
        void InputRL(); // Ввод списка граней
        void InputVertexPath(); // Ввод вершин и ребер
        void Floyd(); // Алгоритм Флойда-Уоршелла
        void Prim_Kruskal(); // Алгоритм Прима/Крускала
        void Depth(); // Итеративный проход в глубину
        void Width(); // Итеративный проход в ширину
        void Dijkstra();
        void traverse(int uni, bool vsisted[]);
        bool isConnected();
        int isEulerian();
        void Euler();
        void MinimalPath();
};

#endif