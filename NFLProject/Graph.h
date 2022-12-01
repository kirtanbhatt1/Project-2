#pragma once
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <QString>
#include <utility>
#include <QVector>


enum edge_status { UNDISCOVERED, DISCOVERY, BACK, CROSS };
struct Vertex;
struct Edge
{
	Vertex* end1;
	Vertex* end2;
	int distance;
	bool visited;
	edge_status status;
};
struct Vertex
{
	QVector<Edge*> adjacentEdges;
	QString name;
	bool visited = false;
	Vertex(QString s) : name(s) {}
};
class Graph
{
public:
	
	typedef std::map<QString, Vertex*> vertexMap;
	
	void DFS(Vertex*&);
	// Function to perform a Depth-First-Search on a graph 
	void BFS(Vertex*&);
	// Function to perform a Breadth-first Search on the graph
	void insertVertex(const QString&);
	// Function to insert the vertex into the graph
	// 
	// Postcondition: Inserts vertex with QString into the graph
	void insertEdge(const QString& from, const QString& to, int cost);
	// Function to insert the edge into the graph
// 
// Postcondition: Inserts edge with starting and ending locations 
// with cost into the graph
	Vertex*& getVertex(const QString&);
	// Function to return the reference of the vertex with the name QString
	// 
	// Postcondition: Returns the vertex 
	void edgeType();
	// Function to return the type of edge
	// 
	// Postcondition: Returns type of edge (Undiscovered, Discovery, Back)
	void clear();
	// Function to clear the graph
	//
	// Postcondition: The graph is cleared
	int returnTotalDistance();
	// Function to return the total distance
	// 
	// Postcondition: Returns the total distance traveled
private:
	vertexMap vMap;
	QVector<Edge*> allEdges;
	void sortEdges(Vertex* in_Vertex);
	Vertex* oppositeVertex(Vertex* in_Vertex, Edge* in_edge);
	int totalDistance = 0;
};