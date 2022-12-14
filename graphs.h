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
        int countVertex; // количество 
        int countPath; // Количество путей в графе
        int** PM; // Матрица путей
        int** AM; // Матрица смежности
        int** IM; // Матрица инциденций
        queue <Edge> edge; // Список ребер
    public:    
        Graph(); // Констркутор
        ~Graph(); // Деструктор 
        void FromRLtoPM(); // Задание матрицы путей из списка ребер
        void PrintPM(); // Вывод матрицы путей
        void FromRLtoAM(); // Задание матрицы смежности из списка ребер
        void PrintAM(); // Вывод матрицы смежности
        void FromRLtoIM(); // Задание матрицы инциденций из списка ребер
        void PrintIM(); // Вывод матрицы инциденций
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