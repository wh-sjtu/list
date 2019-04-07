#include "list.h"
#include <iostream>
#include<vector>
using namespace std;
//ģ����Ķ���������������ͷ�ļ����С���Ϊ�������ʱ��֪������cpp�ļ����޷����ɡ�����ʱ���Ҳ�����Ķ����ˡ�
int main()
{
	
	list<int> aa;//����ʱ�Զ�����Ĭ�Ϲ��캯��	
	aa.push_back(1);
	aa.push_back(0);
	aa.push_front(2);
	aa.push_front(3);
	cout << "Ĭ�Ϲ��캯�� && push_back(0),push_back(1),push_front(2),push_front(3)" << endl;
	aa.display();

	cout << "Size()=" << aa.size() << "  " << "Empty()= " << aa.empty() << endl;
	
	list<int> bb(aa);//�쳣�Ĳ���u�����ƶ����������д���
	bb.pop_back();
	bb.pop_front();
	cout << "�������캯�� && pop_back() pop_front()" << endl;
	bb.display();

	cout << "assign������2 1���·���Ϊ3 2 1 0" << endl;
	bb.assign(aa.begin(), aa.end());
	bb.display();

	cout << "���������캯�� && erase begin()" << endl;
	list<int> cc(bb.begin(), bb.end());
	cc.erase(cc.begin());
	cc.display();

	cout << "sort 3 2 1 0" << endl;
	aa.sort(aa.begin(),aa.end()-1);
	aa.display();


	cout << "rbegin\rend�������0 1 2 3" << endl;
	list<int>::iterator ite = aa.rbegin();
	for (; ite >aa.rend(); ite--)
		cout << *ite << " ";
	cout << endl;
	
	cout << "reverse() ��ת0 1 2 3" << endl;
	aa.reverse();
	aa.display();

	cout << "ȥ��1122�е��ظ�Ԫ��" << endl;
	cc.clear();
	cc.push_back(1);
	cc.push_back(1);
	cc.push_back(2);
	cc.push_back(2);
	cc.unique(cc.begin(),cc.end());
	cc.display();

	cout << "�ϲ���1 2���͡�3 2 1 0��" << endl;
	list<int> dd;
	dd.merge(cc, aa);
	dd.display();
	return 0;
}
