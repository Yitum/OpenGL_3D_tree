class Tree{
public:
	//variables
	float positionX, positionY, positionZ;
	float height;
	float base;
	float size;
	bool animation;
	int treeBranch;
	int treeLevel;
	GLuint makeaTree;

	//functions
	Tree(float positionX, float PositionY, float positionZ, float height, float base, float size);
	void Tree::render();
	void Tree::setTreeLevel(int level);
	void Tree::setTreeBranch(int branch);
	void Tree::setLeafStyle(int num);
	void Tree::setLeafColor(float R, float G, float B);
	void Tree::setTrunkColor(float R, float G, float B);
	void Tree::setRange(float range);
	void Tree::enableRandomAngle(bool state);
	void Tree::enableRandomColor(bool state);
	void Tree::buildTree();


private:
	//variables
	float angle;
	int leafStyle;
	float range;
	bool randomColor;
	float leafRed, leafGreen, leafBlue;
	float trunkRed, trunkGreen, trunkBlue;
	bool randomAngle;
	float staticAngle;

	//functions
	void Tree::init();
	void Tree::makeCylinder(float height, float base);
	void Tree::makeTree(float height, float base, float range);
};