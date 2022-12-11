#include "graphs.cpp"

int main()
{
    Graph graph;
    graph.InputRL();
    graph.PrintRL();
    graph.FromRLtoAM();
    graph.PrintAM();
    graph.FromRLtoIM();
    graph.PrintIM();
    graph.FromRLtoPM();
    graph.PrintPM();
    graph.PrintLL();
    graph.Floyd();
    graph.Prim_Kruskal();
    graph.Depth();
    graph.Width();
    graph.Dijkstra();
    graph.Euler();
}