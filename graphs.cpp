#include "graphs.h"

Graph :: Graph()
{
    AM = NULL;
    PM = NULL;
    IM = NULL;
    countVertex = 0;
    countPath = 0;
    uni = 0;
}

Graph :: ~Graph()
{
    
}

void Graph :: InputVertexPath()
{
    cout << "Введите количество вершин графа: "; cin >> countVertex;
    countPath = countVertex * countVertex;
}

void Graph :: InputRL()
{
    int pathWeigth;
    InputVertexPath();
    for(int i = 0; i < countVertex; i++)
    {
        for (int j = 0; j < countVertex; j++)
        {
            if(i == j)
            {
                Edge temp = Edge(i, j, 0);
                edge.push(temp);
            }
            else
            {
                cout << "Введите данные о пути из " << i+1 << " в " << j+1 << ": "; cin >> pathWeigth;
                Edge temp = Edge(i, j, pathWeigth);
                edge.push(temp);
            }
        }
    }
    cout << endl;
}

void Graph :: PrintRL()
{
    queue <Edge> cEdge = edge;
    cout << "Cписок ребер: " << endl;
    cout << "Ребро : Вес" << endl;
    while(!(cEdge.empty()))
    {
        Edge temp = cEdge.front();
        if(temp.weight == 0)
        {   
            cEdge.pop();    
        }
        else
        {
            if(temp.weight == 101)
                cEdge.pop();
            else
            {
                cout << temp.begin + 1 << " - " << temp.end + 1 << " : " << temp.weight << endl;
                cEdge.pop();
            }
        }
    }
    cout << endl;
}

void Graph :: FromRLtoAM()
{
    queue <Edge> cEdge = edge;
    AM = (int**)malloc(sizeof(double) *countVertex);
    for (int i = 0; i < countVertex; i++)
    {
        AM[i] = (int*)malloc(sizeof(double) *countVertex);    
    }
    
    for(int i = 0; i < countVertex; i++)
    {
        for(int j = 0; j < countVertex; j++)
        {
            Edge temp = cEdge.front();
            if(temp.weight > 0 && temp.weight < 101)
                AM[i][j] = 1;
            else 
                AM[i][j] = 0;
            cEdge.pop();
        }
    }
}

void Graph :: PrintAM()
{
    cout << "Матрица смежности:" << endl;
    for (int i = 0; i < countVertex; i++)
    {
        for (int j = 0; j < countVertex; j++)
        {
            cout << AM[i][j] << '\t';
        }
        cout << endl;
    }
    cout << endl;
}

void Graph :: FromRLtoIM()
{
    if (AM == NULL)
        FromRLtoAM();

    IM = (int**)malloc(sizeof(double) *countVertex);
    for (int i = 0; i < countVertex; i++)
    {
        IM[i] = (int*)malloc(sizeof(double) *countVertex);    
    }

    for(int i = 0; i < countVertex; i++)
    {
        for(int j = 0; j < countVertex; j++)
        {
            if (AM[i][j] == 0)
                IM[i][j] = 0;
            else
            {
                if(AM[i][j] == AM[j][i])
                    IM[i][j] = 1;
                else
                    IM[i][j] = -1;
            }
        }
    }    

}

void Graph :: PrintIM()
{
    cout << "Матрица инцидентности:" << endl;
    for (int i = 0; i < countVertex; i++)
    {
        for (int j = 0; j < countVertex; j++)
        {
            cout << IM[i][j] << '\t';
        }
        cout << endl;
    }
    cout << endl;
}

void Graph :: FromRLtoPM()
{
    queue <Edge> cEdge = edge;
    PM = (int**)malloc(sizeof(double) *countVertex);
    for (int i = 0; i < countVertex; i++)
    {
        PM[i] = (int*)malloc(sizeof(double) *countVertex);    
    }

    for(int i = 0; i < countVertex; i ++)
    {
        for (int j = 0; j < countVertex; j ++)
        {
            Edge temp = cEdge.front();
            PM[i][j] = temp.weight;
            cEdge.pop();
        }
    }
}

void Graph :: PrintPM()
{
    cout << "Матрица путей:" << endl;
    for (int i = 0; i < countVertex; i++)
    {
        for(int j = 0; j < countVertex; j++)
        {
            if (PM[i][j] == INF)
                cout << "INF" << "\t";
            else   
                cout << PM[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

void Graph :: PrintLL()
{
    queue <Edge> cEdge = edge;
    cout << "Перечень ребер: " << endl;
    for (int i = 0; i < countPath; i++)
    {
        Edge temp = cEdge.front();
        if(temp.weight > 0 && temp.weight < 101)
        {
            cout << temp.begin + 1 << " - " << temp.end + 1 << endl;
            cEdge.pop();
        }
        else
        {
            cEdge.pop();
        }
    }
    cout << endl;
}

void Graph :: Floyd()
{
    if(PM == NULL)
        FromRLtoPM();

    for (int k = 0; k < countVertex; k++)
    {
        for(int i = 0; i < countVertex; i++)
        {
            for (int j = 0; j < countVertex; j++)
            {
                PM[i][j] = min(PM[i][j], PM[i][k] + PM[k][j]);
            }
        }
    }

    cout << "Построение матрицы кратчайших путей Флойда-Уоршела: " << endl;
    for(int i = 0; i < countVertex; i++)
    {
        for (int j = 0; j < countVertex; j++)
        {
            if (PM[i][j] == INF)
                cout << "INF" << "\t";
            else   
                cout << PM[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

void Graph :: Dijkstra()
{
    int *distance, count, index, i, u;
    bool *visited;
    distance = new int [countVertex];
    visited = new bool [countVertex];
    for (i=0; i < countVertex; i++) 
    {
         distance[i] = 101; visited[i]=false;
    }
    distance[0] = 0;
    for (count = 0; count < countVertex - 1; count++) 
    {
        int min = 101;
        for (i=0; i< countVertex; i++)
            if (!visited[i] && distance[i] <= min)
            {
                min = distance[i];
                index=i;
            }
            u = index;
        visited[u]=true;
        for (i=0; i < countVertex; i++)
        {
            if (!visited[i] && PM[u][i] && distance[u] != 101 && distance[u] + PM[u][i] < distance[i])
                distance[i]=distance[u]+ PM[u][i];
        }
    }
    cout << "Кратчайшие пути по алгоритму Дейкстры: " << endl;
    for(int i = 0; i < countVertex; i++)
    {
        cout << distance[i] << '\t';
    }
    cout << endl << endl;
}

void Graph :: Prim_Kruskal()
{
    if(PM == NULL)
        FromRLtoPM();

    cout << "Построение каркаса минимальной стоимости методом Прима: " << endl;
    int no_edge = 0;
    int selected[countVertex];
    memset(selected, false, sizeof (selected));
    selected[0] = true;
    int x, y;           

    cout << "Ребро : Вес" << endl;
    while (no_edge < countVertex - 1) 
    {
        int min = INF;
        x = 0; y = 0;
        for (int i = 0; i < countVertex; i++)
        {
            if (selected[i])
            {
                for (int j = 0; j < countVertex; j++) 
                {
                    if (!selected[j] && PM[i][j]) 
                    { 
                        if (min > PM[i][j]) 
                        {
                            min = PM[i][j];
                            x = i;
                            y = j;
                        }
                    }
                }
            }
        }
        cout << x + 1 <<  " - " << y + 1 << " :  " << PM[x][y] << endl;
        selected[y] = true;
        no_edge++;
    }
    cout << endl;
}

void Graph :: Depth()
{
    if(AM == NULL)
        FromRLtoAM();

    cout << "Демострация обхода в глубину: " << endl;
    stack <int> Stack;
    int nodes[countVertex]; 
    for (int i = 0; i < countVertex; i++) 
        nodes[i] = 0;
    Stack.push(0); 
    while (!(Stack.empty()))
    { 
        int node = Stack.top(); 
        Stack.pop();
        if (nodes[node] == 2) 
            continue;   
        nodes[node] = 2; 
        for (int j = countVertex - 1; j >= 0; j--)
        {  
            if (AM[node][j] == 1 && nodes[j] != 2)
            { 
                Stack.push(j); 
                nodes[j] = 1; 
            }
        }
        cout << node + 1 << '\t';
    }
    cout << endl << endl;
}

void Graph :: Width()
{
    if(AM == NULL)
        FromRLtoAM();

    cout << "Демонстрация итеративного обхода в ширину: " << endl;
    queue <int> Queue;
    int nodes[countVertex];
    for (int i = 0; i < countVertex; i++)
        nodes[i] = 0; 
    Queue.push(0); 
    while (!Queue.empty())
    {
        int node = Queue.front();
        Queue.pop();
        nodes[node] = 2; 
        for (int j = 0; j < countVertex; j++)
        { 
            if (AM[node][j] == 1 && nodes[j] == 0)
            { 
                Queue.push(j);
                nodes[j] = 1;
            }
        }
        cout << node + 1 << '\t'; 
    }
    cout << endl << endl;
}



void Graph :: traverse(int uni, bool visited[])
{
    visited[uni] = true;
    for(int v = 0; v < countVertex; v++)
    {
        if(AM[uni][v])
        {
            if(!visited[v]) 
                traverse(v, visited);
        }
    }
}

bool Graph :: isConnected()
{
    bool *vis = new bool[countVertex];
    for (int i = 0; i < countVertex; i++)
    {
        vis[i] = false;
    }
    uni = countVertex - 1;
    traverse(uni, vis);

    for (int i = 0; i < countVertex; i++)
    {
        if(!vis[i])
            return false;
    }
    return true;
}

int Graph :: isEulerian()
{
    if(AM == NULL)
        FromRLtoAM();
    if(isConnected() == false)
        return 0;
    vector <int> degree(countVertex, 0);
    int oddDegree = 0;

    for(int i = 0; i < countVertex; i++)
    {
        for (int j = 0; j < countVertex; j++)
        {
            if(AM[i][j])
                degree[i] ++;
        }
        if(degree[i] % 2 != 0)
            oddDegree++;
    } 
    if(oddDegree > 2)
        return 0;
    return (oddDegree)?1:2;
}

void Graph :: Euler()
{
    int euler = isEulerian();
    if(euler == 0)
        cout << "Граф не имеет ни эйлерова цикла, ни эйлерова пути" << endl;
    else
    {
        if(euler == 1)
            cout << "Граф имеет эйлеров путь" << endl;
        else
            cout << "Граф имеет эйлеров цикл и эйлеров путь" << endl;
    }
}
