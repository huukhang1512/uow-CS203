#include <iostream>
#include <fstream>
#include <cmath>
#include <queue>
#include <stack>

#include <algorithm>
using std::cin;
using std::cout;
using std::endl;
using std::exception;

using std::ifstream;
using std::queue;
using std::vector;
using std::stack;

ifstream openNewFile(char *filePath)
{

    cout << "Loading file from path " << filePath << "..." << endl;
    ifstream file(filePath);

    if (file.fail())
    {
        throw std::invalid_argument("Unable to locate the file, please make sure your file path is correct");
    }
    return file;
}

class Node
{
public:
    int x, y;
    Node()
    {
        x = 0;
        y = 0;
    };
    void setCoordinate(int _x, int _y)
    {
        x = _x;
        y = _y;
    };
};

double euclidean(Node a, Node b)
{
    double x = a.x - b.x;
    double y = a.y - b.y;
    float dist;

    dist = x * x + y * y;
    return sqrt(dist);
};

void printPath(vector<int> const &path, int vertex, int source)
{
    if (vertex == -1)
        return;

    printPath(path, path[vertex], source);
    if (vertex != source)
        cout << "->";
    cout << vertex;
}

int bellmanFord(int edges[][3], int src, int dest, int vertices, int edgesNo)
{
    vector<int> path(21, -1);
    vector<int> dist(21, 1e8);
    dist[src] = 0;
    for (int i = 1; i <= vertices - 1; i++)
    {
        for (int j = 0; j < edgesNo; j++)
        {
            int u = edges[j][0];
            int v = edges[j][1];
            int w = edges[j][2];

            if (dist[u] != 1e8 && dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                path[v] = u;
            }
        }
    }
    for (int i = 0; i < edgesNo; i++)
    {
        int u = edges[i][0];
        int v = edges[i][1];
        int w = edges[i][2];
        if (dist[u] != 1e8 && dist[u] + w < dist[v])
        {
            cout << "Graph contains negative weight cycle";
            return -1;
        }
    }
    cout << "Length of the shortest between node " << src << " and node " << dest << ": " << dist[dest] << endl;
    cout << "Shortest Path: ";

    printPath(path, dest, src);
    return dist[dest] == 1e8 ? -1 : dist[dest];
}

void dfs(int start, int end, int vertices, vector<bool> &visited, int **graph, int &paths, int &longest, vector<int> stack, int weight, int &biggest, vector<int>&longestPath)
{
    visited[start] = true;
    if (start == end)
    {
        if(weight > biggest) {
            biggest = weight;
            longestPath = stack;
        }
    }
    else
    {
        int *neighbours = graph[start];
        for (int i = 0; i < vertices; i++)
        {
            if (neighbours[i] != 0 && !visited[i])
            {
                stack.push_back(i);
                dfs(i, end, vertices, visited, graph, paths, longest, stack, graph[start][i] + weight, biggest, longestPath);
                stack.pop_back();
            }
        }
    }
    visited[start] = false;
}
int main(int argc, char *argv[])
{
    try
    {
        // Read from standard input
        char filePath[50] = "./data/a3-sample.txt";
        int v, e;

        // cout << "Please enter the path to the text file (max 50 characters): ";
        // cin.getline(filePath,50);
        ifstream file = openNewFile(filePath);
        file >> v >> e;

        int **graph;
        graph = new int *[v + 1];
        for (int i = 0; i < v + 1; i++)
            graph[i] = new int[v + 1];

        int edges[e][3];
        Node nodePos[v + 1];

        for (int i = 0; i <= v; i++)
        {
            for (int j = 0; j <= v; j++)
            {
                graph[i][j] = 0;
            }
        }
        int edgesNo = 0;
        int vertices = 0;

        int vertex, x, y;
        while (v > 0)
        {
            vertices++;
            file >> vertex >> x >> y;
            nodePos[vertex].setCoordinate(x, y);
            v--;
        }

        int startV, endV, w;
        while (e > 0)
        {
            file >> startV >> endV >> w;
            graph[startV][endV] = w;
            edges[edgesNo][0] = startV;
            edges[edgesNo][1] = endV;
            edges[edgesNo][2] = w;
            edgesNo++;
            e--;
        }
        int start, end;
        file >> start >> end;

        // for (int i = 0; i < 21; i++)
        // {
        //     for (int j = 0; j < 21; j++)
        //     {
        //         cout << graph[i][j] << ", ";
        //     }
        //     cout << endl;
        // }

        cout << "Number of vertices: " << vertices << endl;
        cout << "Number of edges: " << edgesNo << endl;
        cout << "Start vertex: " << start << endl;
        cout << "Goal vertex: " << end << endl;
        cout << "Euclidean distance between start and goal vertex: " << euclidean(nodePos[start], nodePos[end]) << end << endl;
        bellmanFord(edges, start, end, vertices, edgesNo);
        vector<bool> visited(vertices+1, false);
        int paths = 0;
        cout << endl;
        int longest = -1;
        vector<int> stack({start});
        vector<int> longestPath;
        dfs(start, end, vertices+1, visited, graph, paths, longest, stack,0,longest, longestPath);

        cout << "Longest Path: ";
        for(int j = 0; j < longestPath.size();j++){
            if(j != 0)
                cout << "->";
            cout << longestPath[j];
        }
        cout << endl;
        cout << "Longest Path Weight: "<< longest << endl;
    }
    catch (exception &e)
    {
        cout << e.what() << endl;
        return 1;
    }
}