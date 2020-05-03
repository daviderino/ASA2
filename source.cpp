#include <iostream>
#include <vector>

class Vertex;

class Edge {
private:
	const int capacity = 1;
	int flow = 0;
	Vertex* v;
public:
	Edge(Vertex *v) {
		this->v = v;
	}

	int getFlow() {
		return flow;
	}

	bool increaseFlow() {
		if(flow == 0 && v->getFlow() == 0) {
			flow++;

			return v->increaseFlow();
		}

		return false;
	}
};

class Vertex {
private:
	const int capacity = 1;
	int flow = 0;
	int type = 0;
	std::vector<Edge*> edges;
public:
	void addEdge(Vertex *v) {
		edges.push_back(new Edge(v));
	}

	int getType() {
		return type;
	}

	void setType(int t) {
		type = t;
	}

	int getFlow() {
		return flow;
	}

	bool increaseFlow() {
		if(flow == 0) {
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

		Vertex* v = &vertices[std::stoi(a)][std::stoi(b)]
		v->setType(1);

		supermarkets.push_back(&vertices[std::stoi(a)][std::stoi(b)]);
	}


	for(int i = 0; i < C; i++) {
		std::string a, b;
		getline(std::cin, a, ' ');
		getline(std::cin, b);

		v->setType(2);
		addresses.push_back(&vertices[std::stoi(a)][std::stoi(b)]);
	}

    return 0;
}
