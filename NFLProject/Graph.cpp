#include "Graph.h"
Vertex*& Graph::getVertex(const QString& name)
{
	vertexMap::iterator itr = vMap.find(name);
	// check if name exists
	if (itr != vMap.end()) {
		Vertex*& your_Vertex = itr->second;
		return your_Vertex;
	}
} // end getVertex
void Graph::insertVertex(const QString& name)
{
	vertexMap::iterator itr = vMap.find(name);
	if (itr == vMap.end()) {
		Vertex* v;
		v = new Vertex(name);
		vMap[name] = v;
		return;
	}
	cout << "\nVertex already exists!";
} // end insertVertex
void Graph::sortEdges(Vertex* vertex)
{
	sort(vertex->adjacentEdges.begin(), vertex->adjacentEdges.end(),
		[](Edge* A, Edge* B) { return B->distance > A->distance; });
} // end sortEdges
void Graph::insertEdge(const QString& beginVal, const QString& endVal, int
	cost)
{
	Vertex* e1 = (vMap.find(beginVal)->second);
	Vertex* e2 = (vMap.find(endVal)->second);
	Edge* currentEdge = new Edge;
	currentEdge->end1 = e1;
	currentEdge->end2 = e2;
	currentEdge->distance = cost;
	currentEdge->status = UNDISCOVERED;
	e1->adjacentEdges.push_back(currentEdge);
	sortEdges(e1);
	e2->adjacentEdges.push_back(currentEdge);
	sortEdges(e2);
	allEdges.push_back(currentEdge);
} // end insertEdge
Vertex* Graph::oppositeVertex(Vertex* in_Vertex, Edge* in_edge)
{
	if (in_Vertex->name == in_edge->end1->name)
		return in_edge->end2;
	else
		return in_edge->end1;
} // end oppositeVertex
int Graph::returnTotalDistance() { return totalDistance; }
// end returnTotalDistance


void Graph::clear() {
	for (vertexMap::iterator itr = vMap.begin(); itr != vMap.end(); ++itr)
		itr->second->visited = false;
	for (int i = 0; i < allEdges.size(); ++i)
		allEdges.at(i)->status = UNDISCOVERED;
	totalDistance = 0;
} // end clear

void Graph::BFS(Vertex*& start)
{
	start->visited = true;
	queue<Vertex*> BFSqueue;
	BFSqueue.push(start);
	while (!BFSqueue.empty())
	{
		start = BFSqueue.front();
		//cout << start->name << endl;
		BFSqueue.pop();
		for (int i = 0; i < start->adjacentEdges.size(); ++i)
		{
			if (start->adjacentEdges.at(i)->status == UNDISCOVERED)
			{
				Vertex* opposite = oppositeVertex(start, start->adjacentEdges.at(i));
				if (!opposite->visited)
				{
					start->adjacentEdges.at(i)->status = DISCOVERY;
					opposite->visited = true;
					totalDistance += start->adjacentEdges.at(i)->distance;
					BFSqueue.push(opposite);
				}
				else
				{
					start->adjacentEdges.at(i)->status = CROSS;
				}
			}
		}
	}
} // end BFS
void Graph::DFS(Vertex*& start)
{
	start->visited = true;
	for (int i = 0; i < start->adjacentEdges.size(); ++i)
	{
		if (start->adjacentEdges.at(i)->status == UNDISCOVERED)
		{
			Vertex* opposite = oppositeVertex(start, start->adjacentEdges.at(i));
			if (!opposite->visited)
			{
				start->adjacentEdges.at(i)->status = DISCOVERY;
				//cout << start->name << " -> " << opposite->name << endl;
				totalDistance += start->adjacentEdges.at(i)->distance;
				DFS(opposite);
			}
			else {
				start->adjacentEdges.at(i)->status = BACK;
			}
		}
	}
} // end DFS
