#ifndef _REDBLACKTREEC_
#define _REDBLACKTREEC_
#include "RedBlackTree.h"
#include<iostream>
#include<utility>
#include<cmath>
#endif

using namespace std;

RedBlackTree::RedBlackTree(int negInf)
{
	nullNode = new RedBlackNode;
	nullNode->left = nullNode->right = nullNode;
	header = new RedBlackNode(negInf, string(), nullNode, nullNode);
}

RedBlackTree::~RedBlackTree()
{
	makeEmpty();
	delete nullNode;
	delete header;
}

void RedBlackTree::insert(int number, string name)
{
	if (number < header->number)
		cout << "键值过小！插入失败！" << endl;
	else
	{
		insert(number, name, header);
		cout << "插入成功！" << endl;
	}
}

void RedBlackTree::remove(int number)
{
	if (number <= header->number)
		cout << "该键值不能删除" << endl;
	else if (header->right == nullNode)
		cout << "红黑树为空！不能删除" << endl;
	else
	{
		remove(number, header);
		cout << "删除成功！" << endl;
	}
}

void RedBlackTree::makeEmpty()
{
	makeEmpty(header->right);
	header->right = nullNode;
	cout << "清空完成！" << endl;
}

bool RedBlackTree::isEmpty()
{
	if (header->right == nullNode)
		return true;
	else
		return false;
}

int RedBlackTree::findMax()
{
	if (isEmpty())
		cout << "红黑树为空！" << endl;
	else
		return Max(header->right)->number;
}

int RedBlackTree::findMin()
{
	if (isEmpty())
		cout << "红黑树为空！" << endl;
	else
		return Min(header->right)->number;
}

void RedBlackTree::printTree()
{
	if (isEmpty())
		cout << "红黑树为空！" << endl;
	else
	{
		cout << "红黑树的中序遍历：" << endl;
		printTree(header->right);
		cout << endl;
	}
}

void RedBlackTree::visualPrintTree()
{
	if (isEmpty())
		cout << "红黑树为空！" << endl;
	else
	{
		nullNode->number = -1;
		treeDeep = 0;
		nodes.clear();   //保证nodes为空
		nodeQueue.push(*header->right);
	    getDeep(header->right,-1);
		int count=getNodes(treeDeep);     //最大键值的位数
		int length, number, temp;         //number记录的是树第一行的前导空格
		temp = treeDeep;
		number = 0;
		while (temp--)
			number += getLength(temp, count);
		number += treeDeep*((count+1)/2);
		temp = number;
		cout << "可视化红黑树如下：" << endl;
		while (temp--)   //输出前导空格
			cout << ends;
		printFormat(nodes[0], count);
		cout << endl;
		vector<Node> tempNode(nodes.begin() + 1, nodes.end());   //获取删除已打印结点后的nodes
		nodes = std::move(tempNode);
		visualPrintTree(treeDeep, number-1,count);   //后续打印的操作函数
		cout << endl;
	}
}

void RedBlackTree::insert(int number, string name, RedBlackNode * header)
{
	current = parent = grand = header;
	nullNode->number = number;
	while (current->number != number)
	{
		great = grand; grand = parent; parent = current;
		current = number < current->number ? current->left : current->right;
		if (current->left->color == RED && current->right->color == RED)
			handleReorient(number);
	}
	if (current != nullNode)
		return;
	current = new RedBlackNode(number, name, nullNode, nullNode);
	if (number < parent->number)
		parent->left = current;
	else
		parent->right = current;
	handleReorient(number);
}

void RedBlackTree::printTree(RedBlackNode * t) const
{
	if (t == nullNode);
	else
	{
		printTree(t->left);
		cout << "(" << t->number << "," << t->name << ")" << ends;
		printTree(t->right);
	}
}

void RedBlackTree::handleReorient(int number)
{
	current->color = RED;
	current->left->color = BLACK;
	current->right->color = BLACK;   //颜色翻转
	if (parent->color == RED)
	{
		grand->color = RED;
		if (number < grand->number != number < parent->number)
			parent = rotate(number, grand);   //此时parent等于此时的current，保证在insert的循环退出时parent的位置正确
		current = rotate(number, great);
		current->color = BLACK;   //使得顶节点变黑
	}
	header->right->color = BLACK;  //保证根是黑的
}

RedBlackTree::RedBlackNode * RedBlackTree::rotate(int number, RedBlackNode * theParent)     //单旋转
{
	if (number < theParent->number)
	{
		number < theParent->left->number ?
			rotateWithLeftChild(theParent->left):        
			rotateWithRightChild(theParent->left);      
		return theParent->left;
	}
	else
	{
		number < theParent->right->number ?
			rotateWithLeftChild(theParent->right) :      
			rotateWithRightChild(theParent->right);      
		return theParent->right;
	}
}

void RedBlackTree::rotateWithLeftChild(RedBlackNode *& k2)
{
	RedBlackNode *k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	k2 = k1;
}

void RedBlackTree::rotateWithRightChild(RedBlackNode *& k1)
{
	RedBlackNode *k2 = k1->right;
	k1->right = k2->left;
	k2->left = k1;
	k1 = k2;
}

void RedBlackTree::remove(int number, RedBlackNode *& t)   //t是实际的根结点
{
	pair<int, Color> returnValue = findDeleteNode(number,nullptr, t);
	if (returnValue.second == BLACK)               //只有当实际删除的结点为黑色的时候才需要调整
	{
		t->color = RED;					//先使假根结点变红  确保循环正确进行
		nullNode->number = returnValue.first;
		nullNode->color = BLACK;    //保证current可以到达退出条件和起始状态下的的循环必定可以正常进行
		grand = parent = current = header;  //初始化 此时各指针指向假根
		while (current->number!=returnValue.first||current->left!=nullNode||current->right!=nullNode)
		{
			grand = parent;
			parent = current;
			returnValue.first < current->number? brother = parent->right, current = parent->left: (brother = parent->left,current = parent->right);       //这个括号非常重要
			if(current->left->color==RED||current->right->color==RED)    //当current指向的结点的儿子中有红色结点时先进行下一步
				repairTree1(returnValue.first);   //调整函数1
			else                   //当current指向的结点的儿子没有红色结点时根据其兄弟结点的颜色分为三种情况（加上对称的共有5种）单旋与双旋
				repairTree2();   //调整函数2
		}
	}
	if (parent->left == current)   //确保删除后的后续结点正常
		parent->left = nullNode;  
	else
		parent->right = nullNode;
	delete current;
	t->color = BLACK;    //保证假根为黑色
}

void RedBlackTree::makeEmpty(RedBlackNode * t)
{
	if (t == nullNode);
	else
	{
		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t;
	}
}

void RedBlackTree::repairTree1(int number)      //当current有红色儿子时  分为三类情况（需要调整：2种 不需要调整：1种）
{
	grand = parent;
	parent = current;
	current = number < current->number ? current->left : current->right;
	if (current->color != RED)    //如果此的current指向的结点不为红这需要旋转调整
	{
		if (parent->right->color == RED)    //current的右兄弟为红色
		{
			rotateWithRightChild(parent);
			if (parent->number > grand->number)   //重新构成链接
				grand->right = parent;
			else
				grand->left = parent;
			swap(parent->color, parent->left->color);           //颜色对换
			current = parent->left;   //旋转后将current置于正确位置
		}
		else                              //current的左兄弟为红色
		{
			parent = rotate(number, grand);
			if (parent->number > grand->number)   //重新构成链接
				grand->right = parent;
			else
				grand->left = parent;
			swap(parent->color, parent->right->color);      //颜色对换
			current = parent->right;   //旋转后将current置于正确位置
		}
	}
	nullNode->color = BLACK;     //保证空结点颜色为黑
}

void RedBlackTree::repairTree2()      //curent的没有红色儿子时   根据其兄弟结点的颜色分为三种情况（加上对称的共有5种）单旋与双旋
{
	if (brother->left->color == RED || brother->right->color == RED)  //兄弟结点的两个儿子颜色有一个为红
	{
		int flag = 0;    //标记是否为双旋转
		if (brother->left->color == RED)
		{
			if (brother->left->number < parent->number != brother->left->number < brother->number)    //双旋转
			{
				brother=rotate(brother->left->number, parent);
				flag = 1;
			}
			rotate(brother->number, grand);
			if (flag == 0)   //单旋转
			{
				brother->left->color = BLACK;
				parent->color = BLACK;
				brother->color = RED;
				current->color = RED;      //颜色变换
			}
			else            //双旋转
			{
				parent->color = BLACK;
				current->color = RED;    //颜色变换
			}
		}
		else
		{
			if (brother->right->number < parent->number != brother->right->number < brother->number)    //双旋转
			{
				brother=rotate(brother->right->number, parent);
				flag = 1;
			}
			rotate(brother->right->number, grand);
			if (flag == 0)   //单旋转
			{
				brother->right->color = BLACK;
				parent->color = BLACK;
				brother->color = RED;
				current->color = RED;      //颜色变换
			}
			else            //双旋转
			{
				parent->color = BLACK;
				current->color = RED;    //颜色变换
			}
		}
	}
	else    //兄弟结点的两个儿子颜色都为黑色
	{
		parent->color = BLACK;
		current->color = brother->color = RED;
	}
	nullNode->color = BLACK;     //保证空结点颜色为黑
}

pair<int,RedBlackTree::Color> RedBlackTree::findDeleteNode(int number,RedBlackNode*lastStep, RedBlackNode * t)
{
	if (t == nullNode)
		throw runtime_error("该结点不存在！");
	if (number < t->number)
		return findDeleteNode(number,t, t->left);
	else if (t->number < number)
		return findDeleteNode(number,t, t->right);
	else if (t->left != nullNode && t->right != nullNode)    //两个孩子
	{
		t->number = Min(t->right)->number;  //只替换键值颜色不替换
		t->name = Min(t->right)->name;
		return findDeleteNode(t->number,t, t->right);    //替换结点变成新的待删除结点
	}
	else
	{
		int number;
		string name;
		Color deleteColor;
		if (t->left != nullNode)        //寻找真正待删除的结点 并将其转化为叶子结点 并且将parent,current置于正确地方 (分三种情况）
		{
			number = t->left->number;
			deleteColor = t->left->color;
			parent = t;
			current = t->left;
			name = t->left->name;
			t->left->number = t->number;
			t->left->name = t->name;
			t->number = number;
			t->name = name;
			t->right = t->left;
			t->left = nullNode;
			
		}
		else if(t->right!=nullNode)
		{
			number = t->right->number;
			deleteColor = t->right->color;
			parent = t;
			current = t->right;
			name = t->right->name;
			t->right->number = t->number;
			t->right->name = t->name;
			t->number = number;
			t->name = name;
			t->left = t->right;
			t->right = nullNode;
		}
		else
		{
			parent = lastStep;
			current = t;
			number = t->number;
			deleteColor = t->color;
		}                                    
		return { number,deleteColor};      //由于红黑树的性质只有孩子的结点必定为叶子结点的父亲，该孩子就必定为叶子
	}
}

RedBlackTree::RedBlackNode * RedBlackTree::Min(RedBlackNode * t)
{
	if (t->left == nullNode)
		return t;
	else
		return Min(t->left);
}

RedBlackTree::RedBlackNode * RedBlackTree::Max(RedBlackNode * t)
{
	if (t->left == nullNode)
		return t;
	else
		return Max(t->right);
}

void RedBlackTree::getDeep(RedBlackNode * t,int deep)
{
	int deep1 = 0, deep2 = 0;
	if (t == nullNode)
	{
		if (treeDeep < deep)
			treeDeep = deep;
	}
	else
	{
		getDeep(t->left, deep + 1);
		getDeep(t->right, deep + 1);
	}
}

void RedBlackTree::visualPrintTree(int deep, int number,int count)
{
	int currentDeep = 1;   //当前的深度（真根看作第0层）
	int nextinterval=0;    //树与树的间隔
	while (currentDeep != deep+1)
	{
		int temp = getLength(deep - currentDeep, count);    //计算该层树边的长度
		int sp = count+1;   //同树中边的间隔
		int interval = sp + (temp - 1) * 2;   //同层中一棵树中结点的间隔
		while (temp--)
		{
			int i = 0;
			int temp2 = number--;
			while (temp2--)    //输出前导空格
				cout << ends;
			while (i!=pow(2,currentDeep))   //打印树的边
			{
				int temp1 = sp;
				if (i >0)   //当i>0 时就要考虑同层树与树的间隔了
				{
					int temp3 = nextinterval;
					/*if (i == pow(2, currentDeep - 1)&&currentDeep>=3)
						temp3 = lastStep;*/
					if (temp3 < 0)   //保证循环正常退出
						temp3 = 0;
					while (temp3--)
						cout << ends;
				}
				if (nodes[i].number != -1)   //当该边有结点时打印该边，否则打印空格
					cout << "/";
				else
					cout << ends;
				while (temp1--)
					cout << ends;
				if (nodes[i+1].number != -1)
					cout << "\\";
				else
					cout << ends;
				i += 2;
			}
			nextinterval -= 2;     //循环退出时nextinterval多减了一次2
			sp = sp + 2;
			cout << endl;
		}
		number++;
		number -= count / 2;     //这里注意  不是简单的减1了
		int temp4 = number--;
		while (temp4--)  //打印前导空格
			cout << ends;
		int i = 0;
		while (i != pow(2,currentDeep))   //打印该层的结点
		{
			printFormat(nodes[i], count);
			int temp5;
			if (i % 2)
				temp5 = nextinterval - (count - (count + 1) / 2) * 2+2;
			else
				temp5 = interval - (count  - (count + 1) / 2)*2;  //不要化简 否则会出错
			if (temp5 < 0)     //保证循环可以退出
				temp5 = 0;
			while (temp5--)  //打印间隔空格
				cout << ends;
			i++;
		}
		cout << endl;
		vector<Node> tempNode(nodes.begin() + pow(2,currentDeep), nodes.end());
		nodes = std::move(tempNode);
		currentDeep++;
		nextinterval = interval - (count - (count + 1) / 2) * 2 - 2;
	}
}

int RedBlackTree::getNodes(int deep)  //层序遍历
{
	int maxnumber=0;   //最大键值
	int i = pow(2, deep);   //确保所有结点被存入
	int count = 1;   //最大结点的位数
	while (i--)
	{
		RedBlackNode temp = nodeQueue.front();
		if (temp.number > maxnumber)
			maxnumber = temp.number;
		nodeQueue.pop();
		nodes.push_back({ temp.number,temp.color });
		nodeQueue.push(*temp.left);
		nodeQueue.push(*temp.right);
	}
	while (!nodeQueue.empty())
	{
		RedBlackNode temp = nodeQueue.front();
		if (temp.number > maxnumber)
			maxnumber = temp.number;
		nodeQueue.pop();
		nodes.push_back({ temp.number,temp.color });
	}
	while (maxnumber / 10)
	{
		count++;
		maxnumber /= 10;
	}
	if (count % 2)
		count++;
	int n = 1;
	while (4 * n++ - 2 < count);
	return 4 * n - 6;    //数学公式推导出的式子
}

void RedBlackTree::printFormat(const Node & n, int count)
{
	if (n.number != -1)
	{
		int i = 1;
		int number = n.number;
		while (number / 10)
		{
			i++;
			number /= 10;
		}
		i = count - i;
		if (n.color == RED)
		{
			cout << "R";
			while (i--)
				cout << ends;
			cout << n.number;
		}
		else
		{
			cout << "B";
			while (i--)
				cout << ends;
			cout << n.number;
		}
	}
	else
	{
		int i = count + 1;
		while (i--)
			cout << ends;
	}
}

int RedBlackTree::getLength(int deep, int count)
{
	return count/2*(pow(2, deep + 1) - 1);  //数学推导出来的公式
}

void insert(RedBlackTree & tree)
{
	int number;
	string name;
	cout << "请输入键值和名称：" << endl;
	cin >> number >> name;
	tree.insert(number, name);
}

void remove(RedBlackTree & tree)
{
	int number;
	cout << "请输入待删除的结点键值：" << endl;
	cin >> number;
	try
	{
		tree.remove(number);
	}
	catch (runtime_error &e)
	{
		cout << e.what() << endl;
	}
}
