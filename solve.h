
#ifndef SOLVE_H
#define SOLVE_H

#include <string>
#include <unordered_set>
#include "minpriorityqueue.h" // Includes <vector>, <unordered_map>, <utility>

using namespace std;

// For the mandatory running time, assume that the time for
// operations of queue, unordered_set, and map are O(1). 
// (They are for average-case, but not worst-case).
//
// For the mandatory running time below, s is the length of 
// the input string representing the maze.
// 
// For a complete description of the maze string 
// and maze solution formats, see the assignment pdf.
//
//
// Returns a string representing a shortest solution to the maze.
// Undefined behavior if the maze is not valid or has no solution.
//
// Must run in O(s*log(s)) time.
class mazesolver {
private:

	class vertex
	{
	public:
		char data;
		int name;
		vector< vertex* > neighbors;

		bool mark;
		int distance;
		int dft; //distance from twin
		vertex * prior;

		vertex(char x,int y)
		{
			data = x;
			name = y;
			mark = false;
			distance = 0;
			prior = NULL;
		}
	};
	int totalchar = 0, rows = 0, colums = 0, beginin = 0, endin = 0;
	vector<vertex*> vertexList;
	vector<int> innout; //this should only keep 2 values

	vertex * findVertex(char x)
	{
		for (int i = 0; i < vertexList.size(); i++)
		{
			if (vertexList[i]->data == x)
				return vertexList[i];
		}
		return NULL;
	}
	//perform a breadThFirst search from start vertex s
	void breadthFirstSearch(vertex * s)
	{
		/*print();
		cout << "this is the begining of BFS: " << endl;
		cout << "this is the name of this s :" << s->name << endl;
		*/
		//step 0:  initialize all algorithm data (you do this)

		//step 1: set up Q, put s in Q

		//queue<vertex*> Q;
		MinPriorityQueue<vertex*> Q;
		MinPriorityQueue<vertex*> twins;
		s->mark = true;

		//Q.push(s);
		Q.push(s, 1);

		//step 3:  The bfs loop!
		//while (!Q.empty())
		while (Q.size() > 0)
		{
			//cout << "new while loop" << endl;
			vertex * x = Q.front();
			//cout <<"this is x :"<< x->name << endl;
			//Q.pop();
			Q.popback();
			/*cout << "this is his naibors: " << x->neighbors.size() << endl;
			for (int i = 0; i < x->neighbors.size(); i++) {
				cout << "this is neighbor " <<i<<" name :" << x->neighbors[i]->name << endl;
			}*/
			//to print items in bfs order, add cout HERE!
			//cout << x->data << "(distance  " << x->distance << "), ";

			for (int i = 0; i < x->neighbors.size(); i++)
			{
				vertex * y = x->neighbors[i];
				//cout <<"this is x :" <<x->name <<" this is neighbor name :" << x->neighbors[i]->name << endl;
				if (y->mark == false||y->distance>x->distance+cost(x->data))
				{
					//update cost
					//if (y->data != ' '&& x->data != ' ' && (x->data == y->data)) {
					if(x->data != ' ' && y->data != ' ' && y->data == x->data){
						//if they are twins but this is the first one to be mark don't do anything


						//cout << "enter case where is ' ' both and equal each other x :" << x->data << " data y :" << y->data << endl;
						//int c = cost(y->data);
						//y->distance = x->distance + c;
						
						//case where the only naighbor of x is y
						if (x->neighbors.size() <= 3 ) {
							//cout << "neighbors ==2" << endl;
							y->distance = x->distance + cost(x->data);
							y->prior = x;
							y->mark = true;
							Q.push(y, 1);
						}
					}
					else 
					{
						//cout << "normal case" << endl;
						y->distance = x->distance + 1;
						y->prior = x;
						y->mark = true;
						Q.push(y, 1);
					}
					//y->distance = x->distance + 1;
					//y->prior = x;

					////put y into Q
					//y->mark = true;
					//Q.push(y,1);
					////Q.push(y);
				}
				else
				{
					if (x->data != ' ' && y->data != ' ' && y->data == x->data)
					{
						if (y->distance + cost(x->data) < x->distance) {
							x->distance = y->distance + cost(x->data);
							x->prior = y;
							y->mark = true;
							Q.push(y, 1);
							//cout << "x distance: " << x->distance << endl;
							//cout << "y distance: " << y->distance << endl;
						}
					}

				}
				//cout << endl; //comment this out later
			}
		}
		//print();

	}
	void secondplan(vertex * s) {
		for (int i = 0; i < vertexList.size(); i++) {
			vertexList[i]->distance = 0;
			vertexList[i]->mark = false;
			vertexList[i]->prior = NULL;
		}
		/*print();
		cout << "this is the begining of BFS: " << endl;
		cout << "this is the name of this s :" << s->name << endl;
		*/
		//step 0:  initialize all algorithm data (you do this)

		//step 1: set up Q, put s in Q

		//queue<vertex*> Q;
		MinPriorityQueue<vertex*> Q;
		MinPriorityQueue<vertex*> twins;
		s->mark = true;

		//Q.push(s);
		Q.push(s, 1);

		//step 3:  The bfs loop!
		//while (!Q.empty())
		while (Q.size() > 0)
		{
			//cout << "new while loop" << endl;
			vertex * x = Q.front();
			//cout <<"this is x :"<< x->name << endl;
			//Q.pop();
			Q.popback();
			/*cout << "this is his naibors: " << x->neighbors.size() << endl;
			for (int i = 0; i < x->neighbors.size(); i++) {
			cout << "this is neighbor " <<i<<" name :" << x->neighbors[i]->name << endl;
			}*/
			//to print items in bfs order, add cout HERE!
			//cout << x->data << "(distance  " << x->distance << "), ";

			for (int i = 0; i < x->neighbors.size(); i++)
			{
				vertex * y = x->neighbors[i];
				//cout <<"this is x :" <<x->name <<" this is neighbor name :" << x->neighbors[i]->name << endl;
				if (y->mark == false)
				{
					//update cost
					//if (y->data != ' '&& x->data != ' ' && (x->data == y->data)) {
					if (x->data != ' ' && y->data != ' ' && y->data == x->data) {
						//if they are twins but this is the first one to be mark don't do anything


						//cout << "enter case where is ' ' both and equal each other x :" << x->data << " data y :" << y->data << endl;
						//int c = cost(y->data);
						//y->distance = x->distance + c;

						//case where the only naighbor of x is y
						if (x->neighbors.size() <= 3) {
							//cout << "neighbors ==2" << endl;
							y->distance = x->distance + 1;
							y->prior = x;
							y->mark = true;
							Q.push(y, 1);
						}
					}
					else
					{
						//cout << "normal case" << endl;
						y->distance = x->distance + 1;
						y->prior = x;
						y->mark = true;
						Q.push(y, 1);
					}
					//y->distance = x->distance + 1;
					//y->prior = x;

					////put y into Q
					//y->mark = true;
					//Q.push(y,1);
					////Q.push(y);
				}
				else
				{
					if (x->data != ' ' && y->data != ' ' && y->data == x->data)
					{
						if (y->distance + cost(x->data) < x->distance) {
							x->distance = y->distance + cost(x->data);
							x->prior = y;
							//cout << "x distance: " << x->distance << endl;
							//cout << "y distance: " << y->distance << endl;
						}
					}

				}
				//cout << endl; //comment this out later
			}
		}
		//print();
	}
	int cost(char d) {
		if (d == '0') {
			return 0;
		}
		else if (d == '1' || d == ' ') {
			return 1;
		}
		else if (d == '2') {
			return 2;
		}
		else if (d == '3') {
			return 3;
		}
		else if (d == '4') {
			return 4;
		}
		else if (d == '5') {
			return 5;
		}
		else if (d == '6') {
			return 6;
		}
		else if (d == '7') {
			return 7;
		}
		else if (d == '8') {
			return 8;
		}
		else if (d == '9') {
			return 9;
		}
		else
			return 0;

	}

public:
	mazesolver()
	{

	}

	void print()
	{
		cout << "total char :" << totalchar << endl;
		cout <<"rows: " << rows << endl;
		cout << "colums: " << colums << endl;
		cout << "vertex list size: " << vertexList.size() << endl << endl;
		//actual data on vertexList
		cout << "actual data on vertexlist" << endl;
		for (int i = 0; i < vertexList.size(); i++) {
			if ((i % rows) == 0) {
				if (i == 0) {

				}
				else
				cout << endl;
			}
			cout << vertexList[i]->data;
			//cout << "i" << i<< vertexList[i]->data<<" ";
		}
		cout << endl << endl;
		//the neighbors they have
		cout << "neighbors they have" << endl;
		for (int i = 0; i < vertexList.size(); i++) {
			if ((i % rows) == 0) {
				if (i == 0) {

				}
				else
					cout << endl;
			}
			cout << vertexList[i]->neighbors.size();
			//cout << "i" << i<< vertexList[i]->data<<" ";
		}
		cout << endl << endl;
		//their names
		cout << "their names" << endl;
		for (int i = 0; i < vertexList.size(); i++) {
			if ((i % rows) == 0) {
				if (i == 0) {

				}
				else
					cout << endl;
			}
			cout << vertexList[i]->name << "|";
			//cout << "i" << i<< vertexList[i]->data<<" ";
		}
		cout << endl << endl;
		//their distance
		cout << "their distance" << endl;
		for (int i = 0; i < vertexList.size(); i++) {
			if ((i % rows) == 0) {
				if (i == 0) {

				}
				else
					cout << endl;
			}
			cout << vertexList[i]->distance << "|";
			//cout << "i" << i<< vertexList[i]->data<<" ";
		}
		cout << endl << endl;
		cout << "this are the recorded values" << endl;
		for (int x = 0; x < innout.size(); x++) {
			cout << innout[x] << endl;
		}


	}

	void addVertex(char x,int y)
	{
		vertexList.push_back(new vertex(x, y));
	}
	//add a directed edge going from
	//x to y
	void addDirectedEdge(char x, char y)
	{
		vertex * xVert = findVertex(x);
		vertex * yVert = findVertex(y);

		if (xVert != NULL && yVert != NULL)
			xVert->neighbors.push_back(yVert);
		else
			cout << "You misspelled something..." << endl;
	}

	//add bi-directional edge
	void addEdge(char x, char y)
	{
		addDirectedEdge(x, y);
		addDirectedEdge(y, x);
	}

	void getdata(string maze)
	{
		//int rows = 0, colums = 0, tc = 0; //(rows go side to side) (colums go up and down)
		totalchar = maze.size();
		for (int i = 0; i < totalchar; i++) {
			//cout << "this is the charcter in the string in i: " << i << " : " << maze[i] << endl;
			if (maze[i] == '\n') {
				rows = i;
				i = totalchar;//to exit loop ;)
			}
		}
		//cout << "this far" << endl;
		//cout << "this is the numbers of chars in a row: " << rows << endl;
		colums = totalchar / rows;

		/*for (int y = 0; y < colums; y++) {
		for (int x = 0; x < rows; x++) {

		cout << x << "," << y << " ";
		}
		cout << endl;
		}*/
		int index = 0;
		for (int x = 0; x < maze.size(); x++) {
			if (maze[x] != '\n') {
				//cout << "papi" << endl;
				addVertex(maze[x], index);
				if (maze[x] != ' ') {
					vertexList[vertexList.size() - 1];
					int vl = vertexList.size();
				//	//cout << "this is the case :" << (vl - 2) << endl;

						for(int i = 0; i < (vl-2); i++) {
							//cout << "this is i :" << i << endl;
							if (vertexList[i]->data == maze[x] && maze[x]!='#') {
							//	cout << "vertex list i " << vertexList[i]->data << endl;
								//cout << "maze list x " << maze[x]<< endl;
								//cout << "wtf" << endl;
								vertexList[i]->neighbors.push_back(vertexList[vertexList.size() - 1]);
								vertexList[vertexList.size() - 1]->neighbors.push_back(vertexList[i]);
							}
						}
				//		//cout << "this should not happen" << endl;
				}
				index++;
			}
			else if (maze[x] == '\n') {
				totalchar = totalchar - 1;
			}
			else
			{
				cout << "oh shit there is another case" << endl;
				//I honestly don't think there can be other case :c
			}

		}

		//cout << "this is total character: " << totalchar << endl;
		//cout << "this is the rows: " << rows << endl;
		//cout << "this is the colums: " << colums << endl;
		//cout << "this is the amout of vertex added; " << vertexList.size() << endl;

		//for (int i = 0; i < vertexList.size(); i++) {
		//	if ((i % rows) == 0) {
		//		cout << endl;
		//	}
		//	cout << i;
		//	//cout << "i" << i<< vertexList[i]->data<<" ";
		//}
		//cout << endl;
		for (int x = 0; x < colums; x++) {
			//cout<< "x: " << x << endl;
			for (int j = (x*(rows - 1) + x); j <= (x*(rows - 1) + x + (rows - 1)); j++) {
				//cout << "j: " << j << " " << vertexList[j]->data<< endl;
				if (j >= totalchar) {
					//cout << "the program fail j: " << j << " total char is: " << totalchar << endl;
					return;
					//will change this to a fail statement
					/*cout << vertexList[j]->data << endl;
					cout << vertexList[j + 1]->data << endl;
					cout << vertexList.size() << endl;*/
				}
				//case for first row
				else if (j <= (0 * (rows - 1) + 0 + (rows - 1)))
				{
					//cout <<"Enter the top case j:"<<j<<" :" <<vertexList[j]->data << endl;
					if (vertexList[j]->data != '#') {
						//set this as a posible empty space
						//cout << "if space then it should do this" << endl;
						//cout << "	j+rows: " << j + rows << " this is totalchar" << totalchar << endl;
						if (j + rows < totalchar)
						{
							//cout << "this will add the vertex connection" << endl;
							//this should not happen because its the top case and it should not connect to its side
							//if (vertexList[j]->data != '#' &vertexList[j + 1]->data != '#') {
							//	//cout << "first if" << endl;
							//	vertexList[j]->neighbors.push_back(vertexList[j + 1]);
							//	vertexList[j + 1]->neighbors.push_back(vertexList[j]);
							//}
							if (x < (colums)& vertexList[j]->data != '#'&vertexList[j + rows]->data != '#') {
								//cout << "second if" << endl;
								vertexList[j]->neighbors.push_back(vertexList[j + rows]);
								vertexList[j + rows]->neighbors.push_back(vertexList[j]);
								innout.push_back(j);
							}
						}
					}
				}
				//case for bottom row
				else if (j >= vertexList.size() - rows) { //else if (j >=((colums-1)*(rows-1)+(colums-1))) {
														  //cout << "enter the bottom case j:" << j << " :" << vertexList[j]->data << endl;
					if (vertexList[j]->data != '#') {
						//set this as a posible empty space
						//cout << "if space then it should do this" << endl;
						//don't connect because it conquers down and not up
						//should record this value for exit
						innout.push_back(j);
					}
				}
				//case for left side
				else if (j == (x*(rows - 1) + x)) {
					//cout << "enter the left side case j:" << j << " :" << vertexList[j]->data << endl;
					if (vertexList[j]->data != '#' &vertexList[j + 1]->data != '#') {
						//cout << "first if" << endl;
						vertexList[j]->neighbors.push_back(vertexList[j + 1]);
						vertexList[j + 1]->neighbors.push_back(vertexList[j]);
						//should record this one as something
						innout.push_back(j);
					}
				}
				//case for right side
				else if (j == (x*(rows - 1) + x + (rows - 1))) {
					//cout << "enter the right side case j:" << j << " :" << vertexList[j]->data << endl;
					//should not connect but should record
					if (vertexList[j]->data != '#')
						innout.push_back(j);
				}
				else
				{
					//cout << "center j:" << j << " :" << vertexList[j]->data << endl;

					if (vertexList[j]->data != '#' &vertexList[j + 1]->data != '#') {
						//cout << "first if" << endl;
						vertexList[j]->neighbors.push_back(vertexList[j + 1]);
						vertexList[j + 1]->neighbors.push_back(vertexList[j]);
					}
					if (x < (colums)& vertexList[j]->data != '#'&vertexList[j + rows]->data != '#') {
						//cout << "second if" << endl;
						vertexList[j]->neighbors.push_back(vertexList[j + rows]);
						vertexList[j + rows]->neighbors.push_back(vertexList[j]);
					}
				}

				//if (vertexList[j]->data != '#' &vertexList[j + 1]->data != '#') {
				//	//cout << "first if" << endl;
				//	vertexList[j]->neighbors.push_back(vertexList[j + 1]);
				//	vertexList[j + 1]->neighbors.push_back(vertexList[j]);
				//}
				//if (x < (colums)& vertexList[j]->data != '#'&vertexList[j + rows]->data != '#') {
				//	//cout << "second if" << endl;
				//	vertexList[j]->neighbors.push_back(vertexList[j + rows]);
				//	vertexList[j + rows]->neighbors.push_back(vertexList[j]);
				//}
			}
		}

		//time to get begin and end :D //maybe later

		//create a loop that goes from top side, to left/right then left/right then bottom
		//for (int i = 0; i < vertexList.size(); i++) {
		//	cout << i << " : " << vertexList[i]->data << endl;
		//}
		//int indexforloop = 0;
		//while (indexforloop < vertexList.size())
		//{
		//	//from 0 - rows-1
		//	if (indexforloop == 0)
		//	{
		//		for (int i = 0; i < rows; i++)
		//		{
		//			if (vertexList[i]->data == ' ' && beginin == 0)
		//			{
		//				beginin = i;
		//			}
		//			else if (vertexList[i]->data == ' ' && endin == 0)
		//			{

		//			}
		//				
		//		}

		//	}
		//

		//then from vlsize-rows - vlsize
		//}
	}
	void dobs() {

		breadthFirstSearch(vertexList[innout[1]]);

	}
	void second() {
		secondplan(vertexList[innout[1]]);
	}
	void changespaces() {
		//vertex * v = findVertex(x);
		//system("pause");
		//print();
		vertex * pat = vertexList[innout[0]]; //e ->x
		//cout << "change space " << endl;
		//cout << "this is pat: " << pat->data << endl;
		for (vertex * j = pat; j != vertexList[innout[1]]; j = j->prior) { //s ->y
			if (j == vertexList[innout[0]]) {
				//dont change
			}
			else
			{
				j->data = 'o';//change data
			}
			//j->data = 'o';

		}
		vertexList[innout[0]]->data = 'o';
		vertexList[innout[1]]->data = 'o';
		//print();
	}
	bool check() {
		if (vertexList[innout[0]]->distance == 0 && vertexList[innout[1]]->distance == 0)
		{
			return false;
		}
		else
			return true;
	}
	
	string str() {
		//	cout << "enter str" << endl;
		string s = "";
		//maze += "##### #\n";
		for (int i = 0; i < vertexList.size(); i++) {
			if ((i % rows) == 0) {
				//cout << endl;
				s += "\n";
			}
			s += vertexList[i]->data;
			//cout << "i" << i<< vertexList[i]->data<<" ";
		}
		s.erase(s.begin(), s.begin() + 1);
		s += "\n";
		/*cout <<"this is the solution" << endl;
		cout << s << endl;*/

		return s;
	}
};

void makevertex(string maze)
{
	//we need rows and colums total character
	int rows = 0, colums = 0, tc = 0; //(rows go side to side) (colums go up and down)

	tc = maze.size();
	//cout << "this is total size of string: " << tc << endl;

	//loop the string until you find the end of the first row
	for (int i = 0; i < tc; i++) {
	//	cout << "this is the charcter in the string in i: " << i << " : " << maze[i] << endl;
		if (maze[i] == '\n') {
			rows = i;
			i = tc;//to exit loop ;)
		}
	}
	//cout << "this is the numbers of chars in a row: " << rows << endl;
	colums = tc / rows;

	for (int y = 0; y < colums; y++) {
		for (int x = 0; x < rows; x++) {

			cout << x << "," << y << " ";
		}
		cout << endl;
	}
}

string solve(string maze)
{
	//string solu = "";
	//cout << maze;
	//cout << "this is maze size :" << maze.size() << endl;
	mazesolver ms;
	ms.getdata(maze);
	//cout << "exit get data" << endl;
	
	//ms.print();
	//system("pause");

	ms.dobs();
	//ms.print();
	
	if (!ms.check()) {
		//cout << "enter check" << endl;
		//this is the case where the maze cannot be solve by not using teletrasportation
		ms.second();
		//ms.print();
	}
	/*if (!ms.check()) {
		cout << "valio v" << endl;
		return "valiov";
	}*/
	//system("pause");
	//ms.print();
	//system("pause");
	//cout << "exit dobs" << endl;
	ms.changespaces();
	//get input: string
	//turn it into vertex: 
	//makevertex(maze);
	//cout << "exit changespace" << endl;
	//break it down
	//process it
	//return it
	return ms.str();
}

#endif 

