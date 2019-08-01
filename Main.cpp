#include<iostream>
#include"RedBlackTree.h"
using namespace std;
int main(void)
{
	RedBlackTree tree(-1);
	int select;
	while (1)
	{
		cout << "1：插入 2：删除结点  3：中序遍历打印红黑树 4：可视化打印红黑树 5：清空红黑树 5：退出" << endl;
		cout << "请输入选择" << endl;
		try
		{
			cin >> select;
			if (!cin)
				throw runtime_error("输入的编号有误！");
		}
		catch (runtime_error err)
		{
			cout << err.what()
				<< "\n是否退出或者重新输入"
				<< "\nY:退出   N:重新输入" << endl;
			string c;
			cin.clear();
			cin.ignore(100, '\n');
			cin >> c;
			if (!cin || c == "Y")
				break;
			else
				continue;

		}
		switch (select)
		{
		case 1: insert(tree); break;
		case 2: remove(tree); break;
		case 3: tree.printTree(); break;
		case 4: tree.visualPrintTree(); break;
		case 5: tree.makeEmpty(); break;
		case 6: return 0;
		default:cout << "编号输入错误！\n请重新输入" << endl; break;
		}
	}
}
