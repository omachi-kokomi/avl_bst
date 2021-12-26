#pragma once
#include<iostream>
#include<vector>
#include<stack>
#include<queue>
#include<sstream>
#include<fstream>
using namespace std;
vector<int> graph[100];
vector<vector<int>> mat;
int n = 0;


void adj_matrix_to_adj_list(vector<vector<int>> Mat, vector<int> Graph[], int N);
void adj_list_to_adj_matrix(vector<int> Graph[], vector<vector<int>>& Mat, int N);
bool isDirectedGraph();
int countEdges();
int countVertices();
void degreeOfEachVertex();
void In_Out_Degree_of_each_vectex();
vector<int> isolated_vectices();
vector<int> leaf_vertices();
bool isCompleteGraph();
bool isCircularGraph();
bool isBigraph();
bool isCompleteBiGraph();
int countConnectComponents(vector<int> Graph[]);
int countConnectComponents_which_are_trees();
int countCutVertices();
int countBridgeEdges();
vector<vector<int>> generate_base_undirected_graph();
vector<vector<int>> generate_complement_undirected_graph();
vector<vector<int>> generate_converse_directed_graph();
