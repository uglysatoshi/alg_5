#include "graphs.h"


// Конструктор графа
Graph :: Graph()
{
    AM = NULL;
    PM = NULL;
    IM = NULL;
    countVertex = 0;
    countPath = 0;
    uni = 0;
}


// Функция вноса количества вершин и путей
void Graph :: InputVertexPath()
{
    cout << "Введите количество вершин графа: "; cin >> countVertex;
    countPath = countVertex * countVertex;
}

// Функция задания списка ребер
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

// Функиция вывода списка ребер
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

// Функиция конвертирования из списка ребер в матрицу смежности
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

// Вывод матрицы смежности
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

// Конвертация списка ребер в матрицу инциденций
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

// Вывод матрицы инциденций
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

// Конвертация из списка ребер в матрицу путей
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

// Вывод матрицы путей
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

// Вывод списка связи
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

// Алгоритм Флойда
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
                PM[i][j] = min(PM[i][j], PM[i][k] + PM[k][j]); // Условие алгоритма
            }
        }
    }
    
    // Ниже вывод алгоритма
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

// Алгоритм Дейкстры
void Graph :: Dijkstra()
{
    if(PM == NULL) // Если матрица путей отсутсвует
        FromRLtoPM();// Массив для сохранения 
    int index, u;
    int distance[countVertex]; // массив для хранения веса ребер
    bool visited[countVertex]; // массив для маркировки посещеных вершин
    for (int i = 0; i < countVertex; i++) 
    {
        distance[i] = INF; visited[i]=false; 
    }
    distance[0] = 0; 
    for (int j = 0; j < countVertex - 1; j++) 
    {
        int min = INF;
        for (int i = 0; i < countVertex; i++)
        {
            if (!visited[i] && distance[i] <= min) 
            {
                min = distance[i];
                index = i;
            }
        }
        u = index;
        visited[u] = true;
        for (int i = 0; i < countVertex; i++)
        {
            // Главное условия: 
            // 1) Вершина не была посещена
            // 2) Путь не равен бесконечности
            // 3) Путь больше нуля
            // 4) Путь сохраненный ранее должен быть больше суммы данного пути и прошлого
            if (!visited[i] && PM[u][i] && distance[u] != INF && distance[u] + PM[u][i] < distance[i])
                distance[i] = distance[u]+ PM[u][i];
        }
    }

    cout << "Кратчайшие пути по алгоритму Дейкстры: " << endl;
    for(int i = 0; i < countVertex; i++)
    {
        cout << distance[i] << '\t';
    }
    cout << endl << endl;
}

// Алгоритм Крускала/Прима
void Graph :: Prim_Kruskal()
{
    if(PM == NULL)
        FromRLtoPM();

    cout << "Построение каркаса минимальной стоимости методом Прима/Крускала: " << endl;
    int no_edge = 0;
    int selected[countVertex]; //Массив для маркировки посещенных вершин
    memset(selected, false, sizeof (selected)); // Заполняем false
    selected[0] = true; // Проставляем первую вершину как посещенную
    int x, y;           

    cout << "Ребро : Вес" << endl;
    while (no_edge < countVertex - 1) 
    {
        int min = INF;
        x = 0; y = 0;
        for (int i = 0; i < countVertex; i++)
        {
            if (selected[i]) // Если вершина была посещена
            {
                for (int j = 0; j < countVertex; j++) 
                {
                    if (!selected[j] && PM[i][j])  // Если вершина не посещена и путь больше нуля
                    { 
                        if (min > PM[i][j]) // Если путь меньше бесконечности
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
        selected[y] = true; // проставляем вершину посещенной
        no_edge++;
    }
    cout << endl;
}

// Функция прохода в глубину
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
        for (int j = countVertex - 1; j >= 0; j--) // обратный обход по матрице
        {  
            if (AM[node][j] == 1 && nodes[j] != 2) // Если путь существует
            { 
                Stack.push(j); 
                nodes[j] = 1; 
            }
        }
        cout << node + 1 << '\t';
    }
    cout << endl << endl;
}

// Функиция прохода в ширину
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

// Рекурсивная функция-условие для проверки на сходимость
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

// Функция для проверки на сходимость
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

// Фунция проверки на Эйлеровость
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

// Вывод функции проверки на Эйлеровость
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
    cout << endl;
}

// Функция поиска минимального пути
void Graph :: MinimalPath()
{
    if(AM == NULL)
        FromRLtoAM();
    queue<int> Queue;
    stack<Edge> Edges;
    Edge e;
    int req = countVertex - 1;
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
                e.begin = node; e.end = j;
                Edges.push(e);
                if (node == req)
                    break;
            }
        }
    }
    cout << "Путь до вершины " << req + 1 << ": " << endl;
    cout << req + 1;
    while (!Edges.empty())
    {
        e = Edges.top();
        Edges.pop();
        if (e.end == req)
        {
            req = e.begin;
            cout << " <- " << req + 1;
        }
    }
    cout << endl << endl;
}