#include <vector>
using std::vector;

struct Node{
	int x;
	int y;
	int id;
	double g;
	double rhs;
	double perpendicularArcCost;
	int parentID;
	int childID;
	bool obstacle;
	bool isDiagonal;
	vector<double> keyList;
	
};

const int size = 100;

class D_Star_Lite{
private:
	int column;
	int row;
	vector<int> path;
	vector<int> newObject;
	vector<int> updated;

	int startID;
	int endID;
	int slast;
	
	Node map[size];

public:

	void start(int startID, int endID){
		path.clear();
		this->startID = startID;
		this->endID = endID;
		slast = startID;
		

	}
};