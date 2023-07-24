#pragma once
#include <memory>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>



class MST {
private:
	int row, column, vertexCount{0}, edgeCount{0}, input[6][6], output[6][6];
	bool visited[6];
	std::unique_ptr<int[]> road;
	std::vector<int> vertices;
	std::ifstream file;
	std::ofstream book;

public:
	MST() { 
	road=std::make_unique<int[]>(36);
	
	file.open("input.txt");
		if (!file)
		{
			std::cout << "Could not open the file." << std::endl;
			exit(1);
		}
	}
	~MST() {
		file.close();
		book.close();
	}

	void read() {

		int num,stone=0,toss=0;

		while (file >> num) {
			road[stone] = num;
			stone++;
		}

			for (int i = 0; i < 6; i++) {
				for (int j = 0; j < 6; j++) {
					input[i][j] = road[toss];
					toss++;
				}
				vertexCount++;
			}

			num = 0;
			while(num < 6){
				for (int i = num; i < 6; i++) {
					if (input[num][i] != 0) { edgeCount++; }
				}
				num++;
			}

	}

	void MSTbuilder(int v) {
		int i, next, min, r = v, l = v, x = v, y = v;
		bool set=false,repeat = false;
		std::string txt = "output" + std::to_string(v) + ".txt";
		setRow(v);
		setColumn(v);
		vertices.push_back(getColumn());

		book.open(txt);
		if (!book)
		{
			std::cout << "Could not open the file." << std::endl;
			exit(1);
		}

		for (i = 0; i < 6; i++) {
			for (int j = 0; j < 6; j++) {
				output[i][j] = 0;
			}
		}

		while (repeat == false){
			min = 99;
			visited[getColumn()] = true;
			next = 0;

			while (next < vertices.size()) {

				for (i = 0; i < 6; i++) {
					if (input[vertices[next]][i] != 0 && input[vertices[next]][i] != output[vertices[next]][i] && input[vertices[next]][i] != input[x][y] && input[vertices[next]][i] != input[r][l]) {
						if (min > input[vertices[next]][i] && min != 0) {
							min = input[vertices[next]][i];
							setRow(vertices[next]);
							setColumn(i);
						}
					}
				}
				next++;
			}


			if (visited[getColumn()] == true && r == x && l == y) {
				r = getRow();
				l = getColumn();
			}
			else if(visited[getColumn()] == true) {
				x = getRow();
				y = getColumn();
			}
			else {
				output[getRow()][getColumn()] = min;
				output[getColumn()][getRow()] = min;
				std::cout << "Add edge " << getRow() << " to " << getColumn() << std::endl;
				for (i = 0; i < vertices.size(); i++) {
					if (getColumn() == vertices[i]) {
						set = true;
					}
				}
				if(set==false){ vertices.push_back(getColumn()); }
			}

			if (vertices.size() == 6) { repeat = true; }
		}


		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 6; j++) {
				std::cout << output[i][j] << " ";
			}
			std::cout << std::endl;
		}
		write();

	}

	void write() {
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 6; j++) {
				book << output[i][j] << " ";
			}
			book << "\n";
		}
	}

	void setRow(int x) { row = x; }
	void setColumn(int y) { column = y; }
	int getRow() { return row; }
	int getColumn() { return column; }

	void setVertexCount(int v) { vertexCount = v; }
	int getVertexCount() { return vertexCount; }
	void setEdgeCount(int e) { edgeCount = e; }
	int getEdgeCount() { return edgeCount; }

	void printGraph() {
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 6; j++) {
				std::cout << input[i][j] <<" ";
			}
			std::cout << std::endl;
		}
	}

};