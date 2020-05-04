#include <iostream>
#include <vector>

#define NOTHING 0
#define SUPERMARKET 1
#define ADDRESS 2

class Vertex;

class Edge {
private:
	const int capacity = 1;
	const int minFlow = -1;
	int flow = 0;
	Vertex* v;						// destination vertex
public:
	Edge(Vertex *v) {
		this->v = v;
	}

	const int getFlow() {
		return flow;
	}

	bool increaseFlow() {
		if(flow < capacity) {
			flow++;

			return true;
		}

		return false;
	}

	bool decreaseFlow() {
		if(flow >= minFlow) {
			flow--;

			return true;
		}

		return false;
	}

	Vertex* getVertex() {
		return v;
	}
};

class Vertex {
private:
	int type = NOTHING;				// 0 - nothing on vertex, 1 supermarket, 2 address
	bool visited = false;

	std::vector<Edge*> edges;
public:
	// adds edge from this vertex to v
	void addEdge(Vertex *v) {
		edges.push_back(new Edge(v));
	}

	const int getType() {
		return type;
	}

	void setType(int t) {
		type = t;
	}

	void setVisited(bool visited) {
		this->visited = visited;
	}

	const bool getVisited() {
		return visited;
	}

	const int getFlow() {
		return flow;
	}

	const int getCapacity() {
		return capacity;
	}

	std::vector<Edge*> getAdjacencies() {
		return edges;
	}

	bool increaseFlow() {
		if(flow < capacity) {
			flow++;

			return true;
		}

		return false;
	}
};

void DFS(Vertex *v) {
	v->setVisited(true);

	for(Edge *e: v->getAdjacencies()) {
		
	}
}


int main() {
    std::string inputM;		
	std::string inputN;		
	std::string inputS;		
	std::string inputC;		

	getline(std::cin, inputM, ' ');
	getline(std::cin, inputN);
	getline(std::cin, inputS, ' ');
	getline(std::cin, inputC);

	const int cols = std::stoi(inputM);	// number of avenues
	const int rows = std::stoi(inputN);	// number of streets
	const int S = std::stoi(inputS);	// number of supermarkets
	const int C = std::stoi(inputC);	// number of citizens;

	Vertex* source = new Vertex();

	Vertex verticesIn[rows * cols];
	Vertex verticesOut[rows * cols];

	Vertex* sink = new Vertex();

	std::vector<Vertex*> supermarkets;
	std::vector<Vertex*> addresses;

	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++) {
			verticesIn[rows * i + j].addEdge(&verticesOut[rows * i + j]);
			
			if(i > 0) {
				verticesOut[rows * i + j].addEdge(&verticesIn[rows * (i-1) + j])
			}
			if(i < (rows - 1)) {
				verticesOut[rows * i + j].addEdge(&verticesIn[rows * (i+1) + j])
			}
			if(j > 0) {
				verticesOut[rows * i + j].addEdge(&verticesIn[rows * i + (j-1)])
			}
			if(j < (cols - 1)) {
				verticesOut[rows * i + j].addEdge(&verticesIn[rows * i + (j+1)])
			}
		}
	}

	// supermarket 
	for(int i = 0; i < S; i++) {
		std::string a, b;
		getline(std::cin, a, ' ');
		getline(std::cin, b);

		Vertex* v = &verticesOut[rows * std::stoi(a) + std::stoi(b)];
		v->addEdge(sink);
		v->setType(SUPERMARKET);
		verticesIn[rows * std::stoi(a) + std::stoi(b)].setType(SUPERMARKET);

		supermarkets.push_back(v);
	}

	// address
	for(int i = 0; i < C; i++) {
		std::string a, b;
		getline(std::cin, a, ' ');
		getline(std::cin, b);

		Vertex* v = &verticesIn[rows * std::stoi(a) + std::stoi(b)];

		source->addEdge(v);
		v->setType(ADDRESS);
		verticesOut[rows * std::stoi(a) + std::stoi(b)].setType(ADDRESS);
		
		addresses.push_back(v);
	}

	// Ford-Fulkerson

	
    return 0;
}