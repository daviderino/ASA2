#include <iostream>
#include <vector>
#include <list>

#define SOURCE -1
#define NOTHING 0
#define SUPERMARKET 1
#define ADDRESS 2
#define SINK 3

using namespace std;

class Vertex;

class Edge {
private:
	const int capacity = 1;
	const int minFlow = -1;
	int flow = 0;
	Edge* reverse = nullptr;
	Vertex* from;
	Vertex* to;
public:
	Edge(Vertex *from, Vertex *to) {
		this->from = from;
		this->to = to;	
	}

	const int getFlow() {
		return flow;
	}

	void setReverse(Edge *r) {
		this->reverse = r;
		r->reverse = this;
	}

	Edge* getReverse() {
		return reverse;
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

	Vertex* getToVertex() {
		return to;
	}

	Vertex* getFromVertex() {
		return from;
	}

	const int getCapacity() {
		return capacity;
	}
};

class Vertex {
private:
	int id = 1337;
	int type = NOTHING;				// 0 - nothing on vertex, 1 supermarket, 2 address
	bool visited = false;

	std::vector<Edge*> edges;
public:
	void setId(int i) {
		id = i;
	}

	void addEdge(Edge *e) {
		if(e->getFromVertex() == this) {
			edges.push_back(e);
		}
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

	std::vector<Edge*> getAdjacencies() {
		return edges;
	}
};

bool DFS(Vertex *v) {
	if(v->getType() == SINK){	
		v->setVisited(true);
		return true;
	}

	for(Edge *e: v->getAdjacencies()) {
		if(!e->getToVertex()->getVisited() && e->getFlow() < e->getCapacity() && (e->getFromVertex()->getType() == SOURCE || e->getToVertex()->getType() != ADDRESS)) {
			e->getFromVertex()->setVisited(true);
			if(DFS(e->getToVertex())){
				if(e->increaseFlow() && e->getReverse() && e->getReverse()->decreaseFlow()) {
					return true;
				}
				else {
					// weird error
				}
			}
		}
	}

	return false;
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

	const int rows = std::stoi(inputM);	// number of avenues
	const int cols = std::stoi(inputN);	// number of streets
	const int S = std::stoi(inputS);	// number of supermarkets
	const int C = std::stoi(inputC);	// number of citizens;

	int index;

	if(rows > cols) {
		index = rows;
	}
	else {
		index = cols;
	}

	Vertex* source = new Vertex();
	source->setType(SOURCE);

	Vertex verticesIn[rows * cols];
	Vertex verticesOut[rows * cols];

	Vertex* sink = new Vertex();
	sink->setType(SINK);

	std::vector<Vertex*> supermarkets;
	std::vector<Vertex*> addresses;

	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++) {
			Vertex* currentIn = &verticesIn[index * i + j];
			Vertex* currentOut = &verticesOut[index * i + j];

			Edge* e1 = new Edge(currentIn, currentOut);
			Edge* e2 = new Edge(currentOut, currentIn);

			currentIn->addEdge(e1);
			e2->setReverse(e1);
			currentOut->addEdge(e2);

			currentIn->setId(index * i + j);
			currentOut->setId(-1 * (index * i + j));

			// right vertex
			if(j < (cols - 1)) {
				Edge* e = new Edge(currentOut, &verticesIn[index * i + (j+1)]);

				currentOut->addEdge(e);
			}

			// bottom vertex
			if(i < (rows - 1)) {
				Edge* e = new Edge(currentOut, &verticesIn[index * (i+1) + j]);
				currentOut->addEdge(e);
			}
			
			// left vertex 
			if(j > 0) {
				Edge* e = new Edge(currentOut, &verticesIn[index * i + (j-1)]);
				e->setReverse(verticesOut[index * i + (j - 1)].getAdjacencies()[1]);
				
				currentOut->addEdge(e);
			}

			// top vertex
			if(i > 0) {
				Edge* e = new Edge(currentOut, &verticesIn[index * (i-1) + j]);
				e->setReverse(verticesOut[index * (i-1) + j].getAdjacencies()[2]);

				currentOut->addEdge(e);
			}

		}
	}

	// supermarket 
	for(int i = 0; i < S; i++) {
		std::string a, b;
		getline(std::cin, a, ' ');
		getline(std::cin, b);

		Vertex* currentIn = &verticesIn[index * (std::stoi(a) - 1) + (std::stoi(b) - 1)];
		Vertex* currentOut = &verticesOut[index * (std::stoi(a) - 1) + (std::stoi(b) - 1)];

		Edge* e1 = new Edge(currentOut, sink);
		
		currentOut->addEdge(e1);

		Edge* e2 = new Edge(sink, currentIn);
		e2->setReverse(e1);

		sink->addEdge(e2);
		currentIn->setType(SUPERMARKET);

		supermarkets.push_back(currentIn); // MIGHT NOT BE NEEDED
	}

	// address
	for(int i = 0; i < C; i++) {
		std::string a, b;
		getline(std::cin, a, ' ');
		getline(std::cin, b);

		Vertex* currentIn = &verticesIn[index * (std::stoi(a) - 1) + (std::stoi(b) - 1)];
		Vertex* currentOut =  &verticesOut[index * (std::stoi(a) - 1) + (std::stoi(b) - 1)];

		Edge* e1 = new Edge(source, currentIn);

		source->addEdge(e1);
		currentIn->setType(ADDRESS);

		Edge* e2 = new Edge(currentOut, source);
		e2->setReverse(e1);

		currentOut->addEdge(e2);
		
		addresses.push_back(currentIn); // might not be needed
	}

	int result = 0;

	while(DFS(source)) {
		result++;

		for(int i = 0; i < rows; i++) {
			for(int j = 0; j < cols; j++) {
				verticesIn[index * i + j].setVisited(false);
				verticesOut[index * i + j].setVisited(false);
			}
		}

		source -> setVisited(false);
		sink -> setVisited(false);
	}

	std::cout << result << std::endl;
		
    return 0;
}