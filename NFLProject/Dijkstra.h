#pragma once

#include <QVector>
#include <iostream>
#include <iomanip>
#include <queue>
using namespace std;

const int INF = 999999;

class DijkstraVertice {
public:
	// Name of this vertice
	QString name;
	// Vertices this vertice is connected to.
	QVector<int> edges;
	QVector<int> weights;

	DijkstraVertice(QString name) {
		this->name = name;
	}

	void addEdge(int index, int weight) {
		edges.push_back(index);
		weights.push_back(weight);
	}

};

class Dijkstra {
public:
	// Vertices, with both name and edges.
	QVector<DijkstraVertice> vertices;
	// Cost of each index
	QVector<int> costs;
	// Parent indexes
	QVector<int> parents;

	// A 'cloud' of indexes in the current queue
	QVector<int> currentCloud;
	// A 'cloud' of indexes to be parsed next
	QVector<int> nextCloud;

	Dijkstra(QVector<QVector<int>>& edges, QVector<QString>& verts) {
		// Create vertices with names
		for (int i = 0; i < verts.size(); i++) {
			this->vertices.push_back(verts[i]);
		}

		// Add edges and their weights onto vertices
		for (int i = 0; i < edges.size(); i++) {
			// ex: {0, 3, 1331} = index, adjacentIndex, weight
			this->vertices[edges[i][0]].addEdge(edges[i][1], edges[i][2]);
		}
	}

	// Runs the algorithm on a vertice and prints the shortest distance to all cities
	void run(QString vertice) {
		// Reset variables
		costs.clear();
		parents.clear();
		costs.resize(vertices.size(), INF); // Costs are defaulted to infinity
		parents.resize(vertices.size(), -2); // Parents are defaulted to -2, meaning none have been declared yet
		currentCloud.clear();
		nextCloud.clear();

		// Find vertice as an index
		int originIndex = -1;
		for (int i = 0; i < vertices.size(); i++) {
			if (vertices[i].name == vertice) {
				originIndex = i;
			}
		}
		if (originIndex == -1) {
			//cout << "Could not find name " << vertice << endl;
			return;
		}

		// Label origin in the cost and parent array
		costs[originIndex] = 0;
		parents[originIndex] = -1;

		currentCloud.push_back(originIndex);
		int level = 0;

		while (!currentCloud.empty()) {
			//cout << "Level: " << level++ << endl;

			// Parse current cloud to find adjacents
			for (int i = 0; i < currentCloud.size(); i++) {
				// Skip if already calculated before
				if (currentCloud[i] != originIndex && isFound(currentCloud[i])) continue;

				// Calculate cost
				if (currentCloud[i] != originIndex) calculateCost(currentCloud[i]);

				// Get all adjacents and push it to the next cloud.
				addAdjacents(currentCloud[i]);
				//currentCloud.erase(currentCloud.begin(), currentCloud.begin() + 1);
			}
			currentCloud.clear();

			// Move next cloud into current
			for (int i = 0; i < nextCloud.size(); i++) {
				currentCloud.push_back(nextCloud[i]);
			}
			nextCloud.clear();
		}

		printShortestPaths(vertice);

		//cout << "\nPrinting Costs and Parents arrays:\n";
		printData();
	}

	// Calculates the cost for this index.
	void calculateCost(int index) {
		// Find adjacents that already have parents
		QVector<int> adjacents; // use to set parent
		QVector<int> weights; // use to set distance
		for (int i = 0; i < vertices[index].edges.size(); i++) {
			if (isFound(vertices[index].edges[i])) {
				// Add as adjacent to be parsed
				adjacents.push_back(vertices[index].edges[i]);
				weights.push_back(getWeight(index, vertices[index].edges[i]));
			}
		}

		// Choose the closest distance
		int leastDistance = INF;
		int leastIndex = -1;
		for (int i = 0; i < weights.size(); i++) {
			int cost = weights[i] + costs[adjacents[i]];
			//cout << "Cost: " << cost << endl;
			if (cost < leastDistance) {
				leastDistance = cost;
				leastIndex = i;
			}
		}
		if (leastIndex == -1) {
			//cout << "ERROR" << endl;
		}

		// Set parent and cost to previous + weight
		int parentIndex = adjacents[leastIndex];
		costs[index] = leastDistance;
		parents[index] = parentIndex;
	}

	// Adds adjacent indexes to be sorted and then parsed
	void addAdjacents(int index) {
		for (int i = 0; i < vertices[index].edges.size(); i++) {
			if (!isFound(vertices[index].edges[i])) {
				// Add as adjacent to be parsed
				nextCloud.push_back(vertices[index].edges[i]);
				//cout << "Added " << vertices[i].name << endl;
			}
		}
	}

	// returns the weight inbetween two vertices
	int getWeight(int v1, int v2) {
		// {0, 3, 1331} = index, adjacentIndex, weight
		for (int i = 0; i < vertices[v1].edges.size(); i++) {
			if (v2 == vertices[v1].edges[i]) {
				return vertices[v1].weights[i];
			}
		}
		return -1;
	}

	// Returns if the parent is found 
	bool isFound(int index) {
		return parents[index] != -2;
	}

	void printData() {
		//cout << "Costs:" << endl;
		for (int cost : costs) {
			cout << cost << " ";
		}
		//cout << "\nParents:" << endl;
		for (int parent : parents) {
			cout << parent << " ";
		}
		//cout << endl;
	}

	void printShortestPaths(QString start) {
		for (int i = 0; i < costs.size(); i++) {
			//cout << "The shortest path from " << start << " to " << vertices[i].name << " is " << costs[i] << " miles" << endl;
		}
	}
};

struct dEdge {
	int start;
	int end;
	int weight;
};

class dVertex {
public:
	QString name;
	QVector<dEdge> edges;

	dVertex(QString name) {
		this->name = name;
	}

	void addEdge(int start, int index, int weight) {
		dEdge temp;
		temp.start = start;
		temp.end = index;
		temp.weight = weight;
		edges.push_back(temp);
	}

};

class Prim_jarnik {
	QVector<QVector<int>> edges;
	QVector<dVertex> vertices;
	QVector<bool> visited;
public:

	QVector<QString> startNames;
	QVector<QString> endNames;

	Prim_jarnik(QVector<QVector<int>>& edges, QVector<QString>& verts) {
		for (int i = 0; i < verts.size(); i++) {
			this->vertices.push_back(verts[i]);
		}

		for (int i = 0; i < edges.size(); i++) {
			this->vertices[edges[i][0]].addEdge(edges[i][0], edges[i][1], edges[i][2]);
		}
		this->visited.resize(vertices.size() + 1, false);
	}
	int run() {
		auto comp = [](dEdge lhs, dEdge rhs) {return lhs.weight > rhs.weight; };

		priority_queue<dEdge, QVector<dEdge>, decltype(comp)> frontier(comp);
		QVector<dVertex> mst;
		int starting = 0;
		mst.push_back(vertices[starting]);
		int total = 0;
		while (mst.size() < vertices.size()) {
			for (int i = 0; i < vertices[starting].edges.size(); i++) {
				frontier.push(vertices[starting].edges[i]);
			}
			visited[starting] = true;
			for (int i = 0; i < frontier.size(); i++) {
				if (!visited[frontier.top().end]) {
					mst.push_back(vertices[frontier.top().end]);
					startNames.push_back(vertices[frontier.top().start].name);
					endNames.push_back(vertices[frontier.top().end].name);
				//	cout << vertices[frontier.top().start].name << " to " << vertices[frontier.top().end].name << endl;
					starting = frontier.top().end;
					total += frontier.top().weight;
					qDebug() << total;
					frontier.pop();
					break;
				}
				else {
					frontier.pop();
				}
			}
		}
		return total;
	//	cout << "\nTotal distance Travelled: " << total << endl;
	}
};