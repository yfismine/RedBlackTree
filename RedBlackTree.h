#ifndef _REDBLACKTREEH_
#define _REDBLACKTREEH_
#pragma once
#include<string>
#include<memory>
#include<vector>
#include<queue>
#endif
using namespace std;

class RedBlackTree
{
public:
	RedBlackTree() = delete;
	explicit RedBlackTree(int negInf);
	~RedBlackTree();
	void insert(int number, string name);
	void remove(int number);
	void makeEmpty();
	bool isEmpty();
	int findMax();
	int findMin();
	void printTree();
	void visualPrintTree();
private:
	enum Color {RED,BLACK};  //结点颜色
	struct RedBlackNode
	{
		int number;
		string name;
		RedBlackNode *left;
		RedBlackNode *right;
		Color color;
		RedBlackNode(int num=0, string nam=string(), RedBlackNode *lt = nullptr, RedBlackNode *rt = nullptr, Color fl = BLACK)
			:number(num), name(nam), left(lt), right(rt), color(fl) {};
	};
	struct Node   //可视化打印的元素
	{
		int number;
		Color color;
	};
	RedBlackNode *header;
	RedBlackNode *nullNode;
	RedBlackNode *brother;
	RedBlackNode *current;
	RedBlackNode *parent;
	RedBlackNode *grand;
	RedBlackNode *great;
	vector<Node> nodes;  //层序遍历后的数组
	int treeDeep;  //红黑树的深度
	queue<RedBlackNode> nodeQueue; //层序遍历时的优先队列
	void insert(int number, string name, RedBlackNode *header);
	void printTree(RedBlackNode *t) const;
	void handleReorient(int number);   //插入时维持红黑性质的调整函数
	RedBlackNode *rotate(int number, RedBlackNode *theParent);
	void rotateWithLeftChild(RedBlackNode *&k2);
	void rotateWithRightChild(RedBlackNode *&k1);
	void remove(int number,RedBlackNode*& t);
	void makeEmpty(RedBlackNode *t);
	void repairTree1(int number);    //删除时维持红黑性质的调整函数1
	void repairTree2();              //删除时维持红黑性质的调整函数1
	pair<int,Color> findDeleteNode(int number,RedBlackNode*lastStep,RedBlackNode *t);  //寻找实际的删除结点
	RedBlackNode *Min(RedBlackNode *t);
	RedBlackNode *Max(RedBlackNode *t);
	void getDeep(RedBlackNode *t,int deep);   //获取红黑树的深度
	void visualPrintTree(int deep,int number,int count);  //可视化打印
	int getNodes(int deep);   //获取层序遍历顺序
	void printFormat(const Node &n, int count);   //格式化输出结点
	int getLength(int deep, int count);    //获取红黑树的边长
};

void insert(RedBlackTree &tree);
void remove(RedBlackTree &tree);

