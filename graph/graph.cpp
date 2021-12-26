#include"graph.h"

void adj_matrix_to_adj_list(vector<vector<int>> Mat, vector<int> Graph[], int N){
    for(int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            if (Mat[i][j] == 1) Graph[i].push_back(j);
        }
}

void adj_list_to_adj_matrix(vector<int> Graph[], vector<vector<int>>& Mat, int N){
    for(int i = 0; i < N; i++) Mat.push_back(vector<int>(N, 0));
    for (int i = 0; i < N; i++) {
        for (auto j : Graph[i])
            Mat[i][j] = 1;
    }

}

// check on adjancency matrix
bool isDirectedGraph(){
    for (int i = 0; i < n; i++)
        for (int j = i; j < n; j++)
            if (mat[i][j] != mat[j][i]) return true;
    return false;
}

int countEdges(){
    int count = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < graph[i].size(); j++)
            count += 1;
    if (isDirectedGraph()) return count;
    else return count / 2;
}

int countVertices(){
    return n;
}
void degreeOfEachVertex(){
    cout << "Degree of each vertex in undirected graph\n";
    for(int i = 0; i < n; i++)
    {
        cout << "Degree of vectex " << i << "th: " << graph[i].size() << endl;
    }
}

vector<int> in_degree_of_vertex(){
    vector<int> in_degree(n, 0);
    for(int i = 0; i < n; i++)
        for(int j = 0; j < graph[i].size(); j++)
        {
            in_degree[graph[i][j]]++;
        }
    return in_degree;
}

void In_Out_Degree_of_each_vectex(){
    cout << "In-degree and out-degree of each vertex in directed graph\n";
    vector<int> in_degree = in_degree_of_vertex();
    for (int i = 0; i < n; i++){
        cout << "Vertex " << i << "th: In-degree: " << in_degree[i] << "; Out-degree: " << graph[i].size() << endl;
    }
}

vector<int> isolated_vectices(){
    vector<int> res;
    for(int i = 0; i < n; i++){
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

vector<int> leaf_vertices(){
    vector<int> res;
    if (isDirectedGraph()){
        vector<int> in_degree = in_degree_of_vertex();
        for (int i = 0; i < n; i++)
            if (in_degree[i] + graph[i].size() == 1) 
                res.push_back(i);
    }
    else{
        for(int i = 0; i < n; i++)
            if (graph[i].size() == 1)
                res.push_back(i);
    }
    return res;
}

bool isCompleteGraph(){
    for(int i = 0; i < n; i++)
        if (graph[i].size() != n-1)
            return false;
    return true;
}

bool checkCircular(int src, vector<bool>& visited, vector<int>& path){
    stack<int> s;
    s.push(src);
    while (! s.empty()){
        int u = s.top(); s.pop();
        for (int v: graph[u]){
            if (visited[v] && path[u] != v)
                return true;
            else if (visited[v] == false){
                s.push(v);
                path[v] = u;
            }
        }
    }
    return false;
}

// use DFS 
bool isCircularGraph(){
    stack<int> s;
    vector<bool> visited(n, false);
    vector<int> path(n, -1);
    for(int i = 0; i < n; i++){
        if (visited[i] == false){
            if (checkCircular(i, visited, path) == true)
                return true;
        }
    }
    return false;
}

// use BFS and coloring
bool isBigraph(){
    queue<int> q;
    vector<bool> visited(n, false);
    for(int i = 0; i < n; i++)
        if (visited[i] == false){
            vector<int> color(n, -1);   
            color[i] = 1;
            q.push(i);
            while (! q.empty()){
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

int countConnectComponents(vector<int> Graph[]){
    queue<int> q;
    int count = 0;
    vector<bool> visited(n, false);
    for(int i = 0; i < n; i++)
        if (visited[i] == false){
            count++;
            q.push(i);
            while (! q.empty()){
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

bool isCompleteBiGraph(){
    // if there is any isolated vertices so it's not complete
    vector<int> isolated = isolated_vectices();
    if (isolated.size() != 0) return false;
    // more than one connected component is not accepted
    if (countConnectComponents(graph) > 1) return false;

    // check bigraph
    queue<int> q;
    vector<bool> visited(n, false);
    vector<int> color(n, -1);   
    for(int i = 0; i < n; i++)
        if (visited[i] == false){
            color[i] = 1;
            q.push(i);
            while (! q.empty()){
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
        if (color[i] == 0) green ++;
        else purple ++;
    for(int i = 0; i < n; i++){
        if (color[i] == 0 && graph[i].size() != purple) return false; 
        if (color[i] == 1 && graph[i].size() != green) return false; 
    }    
    return true;
}


int countConnectComponents_which_are_trees(){
    queue<int> q;
    int count = 0;
    vector<bool> visited(n, false);
    vector<int> path(n, -1);
    for(int i = 0; i < n; i++)
        if (visited[i] == false){
            q.push(i);
            while (! q.empty()){
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

int countCutVertices(){
    int count = 0;
    int oldConnectedComponents = countConnectComponents(graph);
    for (int t = 0; t < n; t++)
    {
        vector<vector<int>> new_mat;
        for(int j = 0; j < n - 1; j++)
            new_mat.push_back(vector<int>(n - 1, 0));
        int ni = 0, nj = 0;
        for (int i = 0 ; i < n; i++){
            if (i == t) continue;
            nj = 0;
            for(int j = 0; j < n; j++){
                if (j == t) continue;
                new_mat[ni][nj] = mat[i][j];
                nj++;
            }
            ni++;
        }
        vector<int> new_graph[100];
        adj_matrix_to_adj_list(new_mat, new_graph, n-1);
        int newConnectedComponents = countConnectComponents(new_graph);
        if (newConnectedComponents > oldConnectedComponents) count++;
    }
    return count;
}

int countBridgeEdges(){
    int count = 0;
    int oldConnectedComponents = countConnectComponents(graph);
    for (int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            if (mat[i][j] == 1)
            {
                mat[i][j] = 0;
                mat[j][i] = 0;
                vector<int> new_graph[100];
                adj_matrix_to_adj_list(mat, new_graph, n-1);
                int newConnectedComponents = countConnectComponents(new_graph);
                if (newConnectedComponents > oldConnectedComponents) count++;
                mat[i][j] = 1;
                mat[j][i] = 1;
            }
    return count;
}

vector<vector<int>> generate_base_undirected_graph(){
    vector<vector<int>> BaseGraph;
    for(int i = 0; i < n; i++) BaseGraph.push_back(vector<int>(n, 0));
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            if (mat[i][j] == 1){
                BaseGraph[i][j] = 1;
                BaseGraph[j][i] = 1;
            }
    return BaseGraph;
}

vector<vector<int>> generate_converse_directed_graph(){
    vector<vector<int>> conversedGraph;
    for(int i = 0; i < n; i++) conversedGraph.push_back(vector<int>(n, 0));
    vector<int> edge_list_u;
    vector<int> edge_list_v;
    for(int i = 0; i < n; i++)
        for(int j : graph[i])
        {
            edge_list_u.push_back(i);
            edge_list_v.push_back(j);
        }    
    
    for(int i = 0; i < n; i++)
    {
        conversedGraph[edge_list_v[i]][edge_list_u[i]] = 1;
    }
            
    return conversedGraph;
}

vector<vector<int>> generate_complement_undirected_graph(){

    vector<vector<int>> complementGraph;
    for(int i = 0; i < n; i++) complementGraph.push_back(vector<int>(n, 0));
    
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            if (i != j)
                complementGraph[i][j] = 1 - mat[i][j];       
    return complementGraph;
}

#pragma once