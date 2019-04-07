#include "list.h"
#include <iostream>
#include<vector>
using namespace std;
//模板类的定义和声明必须放在头文件当中。因为分离编译时不知道参数cpp文件就无法生成。链接时就找不到类的定义了。
int main()
{
	
	list<int> aa;//声明时自动调用默认构造函数	
	aa.push_back(1);
	aa.push_back(0);
	aa.push_front(2);
	aa.push_front(3);
	cout << "默认构造函数 && push_back(0),push_back(1),push_front(2),push_front(3)" << endl;
	aa.display();

	cout << "Size()=" << aa.size() << "  " << "Empty()= " << aa.empty() << endl;
	
	list<int> bb(aa);//异常的测试u不能移动到程序运行处。
	bb.pop_back();
	bb.pop_front();
	cout << "拷贝构造函数 && pop_back() pop_front()" << endl;
	bb.display();

	cout << "assign函数将2 1重新分配为3 2 1 0" << endl;
	bb.assign(aa.begin(), aa.end());
	bb.display();

	cout << "迭代器构造函数 && erase begin()" << endl;
	list<int> cc(bb.begin(), bb.end());
	cc.erase(cc.begin());
	cc.display();

	cout << "sort 3 2 1 0" << endl;
	aa.sort(aa.begin(),aa.end()-1);
	aa.display();


	cout << "rbegin\rend逆序输出0 1 2 3" << endl;
	list<int>::iterator ite = aa.rbegin();
	for (; ite >aa.rend(); ite--)
		cout << *ite << " ";
	cout << endl;
	
	cout << "reverse() 反转0 1 2 3" << endl;
	aa.reverse();
	aa.display();

	cout << "去除1122中的重复元素" << endl;
	cc.clear();
	cc.push_back(1);
	cc.push_back(1);
	cc.push_back(2);
	cc.push_back(2);
	cc.unique(cc.begin(),cc.end());
	cc.display();

	cout << "合并“1 2”和“3 2 1 0”" << endl;
	list<int> dd;
	dd.merge(cc, aa);
	dd.display();
	return 0;
}
