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
};

class Vertex {
private:
	const int capacity = 1;
	std::vector<Edge*> edges;
	int flow = 0;
	int type = NOTHING;				// 0 - nothing on vertex, 1 supermarket, 2 address
public:
	void addEdge(Vertex *v) {
		edges.push_back(new Edge(v));
	}

	const int getType() {
		return type;
	}

	void setType(int t) {
		type = t;
	}

	const int getFlow() {
		return flow;
	}

	const int getCapacity() {
		return capacity;
	}

	bool increaseFlow() {
		if(flow < capacity) {
			flow++;

			return true;
		}

		return false;
	}
};


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

	Vertex vertices[rows][cols];
	std::vector<Vertex*> supermarkets;
	std::vector<Vertex*> addresses;

	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++) {
			if(i > 0) {
				vertices[i][j].addEdge(&vertices[i-1][j]);
			}
			if(i < (rows - 1)) {
				vertices[i][j].addEdge(&vertices[i+1][j]);
			}
			if(j > 0) {
				vertices[i][j].addEdge(&vertices[i][j-1]);
			}
			if(j < (cols - 1)) {
				vertices[i][j].addEdge(&vertices[i][j+1]);
			}
		}
	}

	// supermarket 
	for(int i = 0; i < S; i++) {
		std::string a, b;
		getline(std::cin, a, ' ');
		getline(std::cin, b);

		Vertex* v = &vertices[std::stoi(a)][std::stoi(b)];
		v->setType(SUPERMARKET);

		supermarkets.push_back(&vertices[std::stoi(a)][std::stoi(b)]);
	}


	for(int i = 0; i < C; i++) {
		std::string a, b;
		getline(std::cin, a, ' ');
		getline(std::cin, b);

		Vertex* v = &vertices[std::stoi(a)][std::stoi(b)];
		v->setType(ADDRESS);
		addresses.push_back(&vertices[std::stoi(a)][std::stoi(b)]);
	}

    return 0;
}