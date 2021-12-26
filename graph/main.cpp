#include<iostream>
#include<queue>
#include<stack>
#include<vector>
#include<sstream>
#include<iostream>
#include<fstream>
using namespace std;

vector<int> graph[100];
vector<vector<int>> mat;
int n = 0;


void readGraph1() {
    fstream fi;
    int num;
    fi.open("C:\\Users\\PHUOC THAO\\source\\repos\\graph\\Debug\\graph1.txt", ios::in);
    fi >> n;
    for (int i = 0; i < n; i++)
    {
        vector<int> temp;
        for (int j = 0; j < n; j++) {
            fi >> num;
            temp.push_back(num);
        }
        mat.push_back(temp);
    }
    fi.close();
}

void readGraph2() {
    fstream fi;
    int num;
    fi.open("C:\\Users\\PHUOC THAO\\source\\repos\\graph\\Debug\\graph2.txt", ios::in);
    fi >> n;
    fi.ignore();
    for (int i = 0; i < n; i++)
    {
        string s;
        getline(fi, s);
        vector<int> result;
        istringstream iss(s);
        for (int t; iss >> t; )
            graph[i].push_back(t);
    }
    fi.close();
}

void printGraph(vector<vector<int>> a) {
    for (int i = 0; i < a.size(); i++)
    {
        for (int j = 0; j < a[i].size(); j++)
            cout << a[i][j] << " ";
        cout << endl;
    }
}

void printGraph2(vector<int> a[], int N) {
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < a[i].size(); j++)
            cout << a[i][j] << " ";
        cout << endl;
    }
}

void writeGraph1(vector<vector<int>> Mat, int N) {
    fstream fo;
    fo.open("C:\\Users\\PHUOC THAO\\source\\repos\\graph\\Debug\\graph1.txt", ios::out);
    fo << N << endl;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            fo << Mat[i][j] << " ";

        fo << endl;
    }
    fo.close();
}

void writeGraph2(vector<int> Graph[], int N) {
    fstream fo;
    fo.open("C:\\Users\\PHUOC THAO\\source\\repos\\graph\\Debug\\graph2.txt", ios::out);
    fo << N << endl;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < Graph[i].size(); j++)
            fo << Graph[i][j] << " ";

        fo << endl;
    }
    fo.close();
}

void adj_matrix_to_adj_list(vector<vector<int>> Mat, vector<int> Graph[], int N) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            if (Mat[i][j] == 1) Graph[i].push_back(j);
        }
}

void adj_list_to_adj_matrix(vector<int> Graph[], vector<vector<int>>& Mat, int N) {
    for (int i = 0; i < N; i++) Mat.push_back(vector<int>(N, 0));
    for (int i = 0; i < N; i++) {
        for (auto j : Graph[i])
            Mat[i][j] = 1;
    }

}

// check on adjancency matrix
bool isDirectedGraph() {
    for (int i = 0; i < n; i++)
        for (int j = i; j < n; j++)
            if (mat[i][j] != mat[j][i]) return true;
    return false;
}

int countEdges() {
    int count = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < graph[i].size(); j++)
            count += 1;
    if (isDirectedGraph()) return count;
    else return count / 2;
}

int countVertices() {
    return n;
}
void degreeOfEachVertex() {
    cout << "Degree of each vertex in undirected graph\n";
    for (int i = 0; i < n; i++)
    {
        cout << "Degree of vectex " << i << "th: " << graph[i].size() << endl;
    }
}

vector<int> in_degree_of_vertex() {
    vector<int> in_degree(n, 0);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < graph[i].size(); j++)
        {
            in_degree[graph[i][j]]++;
        }
    return in_degree;
}

void In_Out_Degree_of_each_vectex() {
    cout << "In-degree and out-degree of each vertex in directed graph\n";
    vector<int> in_degree = in_degree_of_vertex();
    for (int i = 0; i < n; i++) {
        cout << "Vertex " << i << "th: In-degree: " << in_degree[i] << "; Out-degree: " << graph[i].size() << endl;
    }
}

vector<int> isolated_vectices() {
    vector<int> res;
    for (int i = 0; i < n; i++) {
        bool allZeroRow = true, allZeroCol = true;
        for (int j = 0; j < n; j++) {
            if (mat[i][j] == 1)
            {
                allZeroRow = false;
                break;
            }
            if (mat[j][i] == 1)
            {
                allZeroCol = false;
                break;
            }
        }
        if (allZeroCol && allZeroRow) res.push_back(i);
    }
    return res;
}

vector<int> leaf_vertices() {
    vector<int> res;
    if (isDirectedGraph()) {
        vector<int> in_degree = in_degree_of_vertex();
        for (int i = 0; i < n; i++)
            if (in_degree[i] + graph[i].size() == 1)
                res.push_back(i);
    }
    else {
        for (int i = 0; i < n; i++)
            if (graph[i].size() == 1)
                res.push_back(i);
    }
    return res;
}

bool isCompleteGraph() {
    for (int i = 0; i < n; i++)
        if (graph[i].size() != n - 1)
            return false;
    return true;
}

bool checkCircular(int src, vector<bool>& visited, vector<int>& path) {
    stack<int> s;
    s.push(src);
    visited[src] = true;
    while (!s.empty()) {
        int u = s.top(); s.pop();
        for (int v : graph[u]) {
            if (visited[v] && path[u] != v)
                return true;
            else if (visited[v] == false) {
                s.push(v);
                path[v] = u;
                visited[v] = true;
            }
        }
    }
    return false;
}

// use DFS 
bool isCircularGraph() {
    stack<int> s;
    vector<bool> visited(n, false);
    vector<int> path(n, -1);
    for (int i = 0; i < n; i++) {
        if (visited[i] == false) {
            if (checkCircular(i, visited, path) == true)
                return true;
        }
    }
    return false;
}

// use BFS and coloring
bool isBigraph() {
    queue<int> q;
    vector<bool> visited(n, false);
    for (int i = 0; i < n; i++)
        if (visited[i] == false) {
            vector<int> color(n, -1);
            color[i] = 1;
            q.push(i);
            while (!q.empty()) {
                int u = q.front(); q.pop();
                for (int v : graph[u])
                {
                    if (visited[v] == false && color[v] == -1)
                    {
                        color[v] = 1 - color[u];
                        q.push(v);
                        visited[v] = true;
                    }
                    else if (color[v] == color[u])
                        return false;
                }
            }
        }
    return true;
}

int countConnectComponents(vector<int> Graph[], int V) {
    queue<int> q;
    int count = 0;
    vector<bool> visited(V, false);
    for (int i = 0; i < V; i++)
        if (visited[i] == false) {
            count++;
            q.push(i);
            while (!q.empty()) {
                int u = q.front(); q.pop();
                for (int v : Graph[u])
                {
                    if (visited[v] == false)
                    {
                        q.push(v);
                        visited[v] = true;
                    }

                }
            }
        }
    return count;
}

bool isCompleteBiGraph() {
    // if there is any isolated vertices so it's not complete
    vector<int> isolated = isolated_vectices();
    if (isolated.size() != 0) return false;
    // more than one connected component is not accepted
    if (countConnectComponents(graph, n) > 1) return false;

    // check bigraph
    queue<int> q;
    vector<bool> visited(n, false);
    vector<int> color(n, -1);
    for (int i = 0; i < n; i++)
        if (visited[i] == false) {
            color[i] = 1;
            q.push(i);
            while (!q.empty()) {
                int u = q.front(); q.pop();
                for (int v : graph[u])
                {
                    if (visited[v] == false && color[v] == -1)
                    {
                        color[v] = 1 - color[u];
                        q.push(v);
                        visited[v] = true;
                    }
                    else if (color[v] == color[u])
                        return false;
                }
            }
        }

    // count how many vertices are there in each color set
    int green = 0;
    int purple = 0;
    for (int i = 0; i < n; i++)
        if (color[i] == 0) green++;
        else purple++;
    for (int i = 0; i < n; i++) {
        if (color[i] == 0 && graph[i].size() != purple) return false;
        if (color[i] == 1 && graph[i].size() != green) return false;
    }
    return true;
}


int countConnectComponents_which_are_trees() {
    queue<int> q;
    int count = 0;
    vector<bool> visited(n, false);
    vector<int> path(n, -1);
    for (int i = 0; i < n; i++)
        if (visited[i] == false) {
            q.push(i);
            while (!q.empty()) {
                int u = q.front(); q.pop();
                for (int v : graph[u])
                {
                    if (visited[v] == false)
                    {
                        q.push(v);
                        visited[v] = true;
                        path[v] = u;
                    }

                }
            }
            if (checkCircular(i, visited, path) == false) count++;
        }
    return count;
}

void newGraph(vector<vector<int>>& new_mat, int vertex) {
    int ni = 0, nj = 0;
    for (int i = 0; i < n; i++) {
        if (i == vertex) continue;
        nj = 0;
        for (int j = 0; j < n; j++) {
            if (j == vertex) continue;
            new_mat[ni][nj] = mat[i][j];
            nj++;
        }
        ni++;
    }
}

int countCutVertices() {
    int count = 0;
    int oldConnectedComponents = countConnectComponents(graph, n);
    for (int t = 0; t < n; t++)
    {
        vector<vector<int>> new_mat;
        for (int j = 0; j < n - 1; j++)
            new_mat.push_back(vector<int>(n - 1, 0));
        newGraph(new_mat, t);
        vector<int> new_graph[100];
        adj_matrix_to_adj_list(new_mat, new_graph, n - 1);
        int newConnectedComponents = countConnectComponents(new_graph, n-1);
        if (newConnectedComponents > oldConnectedComponents) count++;
    }
    return count;
}

int countBridgeEdges() {
    int count = 0;
    int oldConnectedComponents = countConnectComponents(graph, n);
    for (int i = 0; i < n; i++)
        for (int j = i; j < n; j++)
            if (mat[i][j] == 1)
            {
                mat[i][j] = 0;
                mat[j][i] = 0;
                vector<int> new_graph[100];
                adj_matrix_to_adj_list(mat, new_graph, n);
                int newConnectedComponents = countConnectComponents(new_graph, n);
                if (newConnectedComponents > oldConnectedComponents) count++;
                mat[i][j] = 1;
                mat[j][i] = 1;
            }
    return count;
}

vector<vector<int>> generate_base_undirected_graph() {
    vector<vector<int>> BaseGraph;
    for (int i = 0; i < n; i++) BaseGraph.push_back(vector<int>(n, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (mat[i][j] == 1) {
                BaseGraph[i][j] = 1;
                BaseGraph[j][i] = 1;
            }
    return BaseGraph;
}

vector<vector<int>> generate_converse_directed_graph() {
    vector<vector<int>> conversedGraph;
    for (int i = 0; i < n; i++) conversedGraph.push_back(vector<int>(n, 0));
    vector<int> edge_list_u;
    vector<int> edge_list_v;
    for (int i = 0; i < n; i++)
        for (int j : graph[i])
        {
            edge_list_u.push_back(i);
            edge_list_v.push_back(j);
        }

    for (int i = 0; i < n; i++)
    {
        conversedGraph[edge_list_v[i]][edge_list_u[i]] = 1;
    }

    return conversedGraph;
}

vector<vector<int>> generate_complement_undirected_graph() {

    vector<vector<int>> complementGraph;
    for (int i = 0; i < n; i++) complementGraph.push_back(vector<int>(n, 0));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (i != j)
                complementGraph[i][j] = 1 - mat[i][j];
    return complementGraph;
}



int main() {
    readGraph2();
    printGraph2(graph, n);
    // readGraph2(graph, n);
    adj_list_to_adj_matrix(graph, mat, n);
    printGraph(mat);
    writeGraph1(mat, n);
    cout << "Directed Graph: " << isDirectedGraph() << endl;
    cout << "Number of edges: " << countEdges() << endl;
    cout << "Number of vertices" << countVertices() << endl;
    degreeOfEachVertex();
    cout << "isolated vertices: ";
    vector<int> isolated = isolated_vectices();
    for (int i = 0; i < isolated.size(); i++) cout << isolated[i] << " ";
    cout << "\nleaf vertices: ";
    vector<int> leaf = leaf_vertices();
    for (int i = 0; i < leaf.size(); i++) cout << leaf[i] << " ";
    cout << endl;
    cout << "Complete graph: " << isCompleteGraph() << endl;
    cout << "Circular graph: " << isCircularGraph() << endl;
    cout << "Bigraph: " << isBigraph() << endl;
    cout << "Complete bigraph: " << isCompleteBiGraph() << endl;
    cout << "connected component: " << countConnectComponents(graph, n) << endl;
    cout << "connected component which the number of trees is: " << countConnectComponents_which_are_trees() << endl;
    cout << "number of cut vertices: " << countCutVertices() << endl;
    cout << "number of bridge edge: " << countBridgeEdges() << endl;
    cout << "complement graph: \n";
    vector<vector<int>> complementGraph = generate_complement_undirected_graph();
    printGraph(complementGraph);

    /*vector<vector<int>> baseGraph = generate_base_undirected_graph();
    cout << "Base Undirected Graph:\n";
    printGraph(baseGraph);
    vector<vector<int>> conversedGraph = generate_converse_directed_graph();
    cout << "Conversed Directed Graph: \n";
    printGraph(conversedGraph);*/

    return 0;
}