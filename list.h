#pragma once
#include<stdexcept>
template<typename T>
struct node
{
	T val;
	node* next;
	node* last;
	node() : next(nullptr), last(nullptr)
	{};
	node(T input, node* _next = nullptr, node* _last = nullptr) { val = input; next = _next; last = _last; };
};

template<typename T>
class list
{
private:
	node<T>* head;//为了支持for(int i=list.begin;i<list.end();i++)，end应当为最后一个节点的写一个节点，因此需要一个尾部的哨兵节点
	node<T>* tail;
	int length;
public:
	//构造函数同时是类名，是无法被主动调用的。
	list();
	list(int n);
	list(int n, T p);
	list(const list<T>& p);//拷贝构造函数
	~list();
	//下面还有参数为迭代器的构造函数
	int size();
	void clear();
	bool empty();
	//迭代器（）实现遍历
	class iterator
	{
	public:
		node<T>* cursor;
		iterator(node<T>* p = nullptr);//构造函数有缺省值则不需要再声明一个默认构造函数。缺省值写在声明处，定义的时候不需要写。
		~iterator();
		T operator*()const;//解引用的重载不用写成友元函数
		/*
		箭头用算符返回值必须是一个指针，或者是一个重载了箭头运算符的对象。
			a）如果返回的是一个指针，将调用内置的箭头运算符。执行相当于(*(p.operator->()).mem; 的操作。
			b）如果返回是一个重载了箭头运算符的对象，则继续对该对象调用其重载了的箭头运算符，直到返回的是一个指针，将对该指针调用a)的操作。操作相当于(*(p.operator->().operator->())).mem;
		总的来说重载的箭头运算符就是为了改变从哪个对象中获取成员。
		*/
		node<T>* operator->()const;//得到iterator内部的cursor,会自动对cursor解引用。用法：p->val。（不用写成p->->val！！）
		iterator operator+(int n);
		iterator operator++();//后置++
		iterator& operator++(int);//前置++
		iterator operator-(int n);
		iterator operator--();
		iterator& operator--(int);//前置++
		bool operator<(iterator p);
		bool operator>(iterator p);
		bool operator>=(iterator p);
		bool operator==(iterator p);
		bool operator!=(iterator p);
	};

	//在vector<T>前加入参数typename告诉编译器，你的vector <T>::iterator是类型而非vector <T>的成员
	//迭代器作为参数要写为传值，因为通常用法为list(a.begin(),a.end())。a.begin是临时变量不能传递给非const的变量（会溢出）。而将形参限制为const则不能实现++等操作了。
	list(typename list<T>::iterator list_begin, typename list<T>::iterator list_end);//拷贝构造函数迭代版本

	//在函数定义时，嵌套类型前都要加上typename。
	iterator begin()const;
	iterator end()const;
	iterator rbegin()const;
	iterator rend()const;
	//查找
	T back();
	T front();
	//插入
	void push_front(T input);
	void push_back(T input);//因为是在end节点和最后一个节点中间插入，所以链表为空是时要区别对待。
	//删除
	void pop_back();//同样，因为end指向哨兵节点的原因，删除最后一个元素时特殊处理
	void pop_front();
	iterator erase(iterator p);
	//因为快排和冒泡都是连续的内存访问，在双向链表下查找的时间复杂度都是常数。迭代器实现快捷些，但是相比指针操作会慢不少。
	void sort(iterator _first, iterator _last);
	void unique(iterator _first, iterator _last);//去除相邻的重复元素
	void assign(int num,T input);
	void assign(iterator _first, iterator _last);
	void display();
	void reverse();
	void merge(const list<T>& in1,const list<T>& in2) ;
};
//.h文件中类的后面要加分号。

template<typename T>
list<T>::list()//:length(0)
{
	tail = new node<T>;
	head = new node<T>;
	head ->next= tail;
	tail->last = head;
	length = 0;
}

template<typename T>
list<T>::list(int n)
{
	tail = new node<T>;
	head = new node<T>;
	head->next = tail;
	tail->last = head;
	length = 0;
	while (n--)
		push_front(0);
}

template<typename T>
list<T>::list(int n, T p)
{
	tail = new node<T>;
	head = new node<T>;
	head->next = tail;
	tail->last = head;
	length = 0;
	while (n--)
		push_front(p);
}

template<typename T>
list<T>::list(const list<T>& p)
{
	tail = new node<T>;
	head = new node<T>;
	head->next = tail;
	tail->last = head;
	length = 0;

	int n = p.length;
	node<T>* temp = p.head->next;
	while (n--)
	{
		push_back(temp->val);
		temp = temp->next;
	}
}

template<typename T>
list<T>::list(typename list<T>::iterator list_begin, typename list<T>::iterator list_end)
{
	tail = new node<T>;
	head = new node<T>;
	head->next = tail;
	tail->last = head;
	length = 0;
	for (; list_begin < list_end; list_begin++)
		push_back(*list_begin);
}

template<typename T>
list<T>::~list()
{
	while (head != tail)
	{
		node<T> *temp = head;
		head=head->next;
		delete temp;
	}
	delete head;
	head = nullptr;
	tail = nullptr;
}


template<typename T>
int list<T>::size()
{
	return length;
}

template<typename T>
void list<T>::clear()
{
	while (head ->next!=tail)
	{
		node<T>* temp = head;
		head = head->next;
		delete temp;
	}
	head->last = nullptr;
}

template<typename T>
bool list<T>::empty()
{
	if (length)
		return false;
	else
		return true;
}

template<typename T>
list<T>::iterator::iterator(node<T>* p)
{
	cursor = p;
}

template<typename T>
list<T>::iterator::~iterator()
{

}

template<typename T>
T list<T>::iterator::operator*() const
{
	return cursor->val;
}

template<typename T>
node<T>* list<T>::iterator::operator->() const
{
	return cursor;
}

template<typename T>
typename list<T>::iterator list<T>::iterator::operator+(int n)
{
	while (n--)
		cursor = cursor->next;
	typename list<T>::iterator a(cursor);
	return a;
}

template<typename T>
typename list<T>::iterator   list<T>::iterator::operator++()
{
	node<T>* temp = cursor;
	cursor = cursor->next;
	typename list<T>::iterator a(temp);
	return  a;
}

template<typename T>
typename list<T>::iterator& list<T>::iterator::operator++(int)
{
	cursor = cursor->next;
	return *this;
}

template<typename T>
typename list<T>::iterator list<T>::iterator::operator-(int n)
{
	while (n--)
		cursor = cursor->last;
	typename list<T>::iterator a(cursor);
	return a;
}

template<typename T>
typename list<T>::iterator list<T>::iterator::operator--()
{
	node<T>* temp = cursor;
	cursor = cursor->last;
	typename list<T>::iterator a(temp);
	return  a;
}

template<typename T>
typename list<T>::iterator& list<T>::iterator::operator--(int)
{
	cursor = cursor->last;
	return  *this;
}


template<typename T>
bool list<T>::iterator::operator<(iterator p)
{
	if (p.cursor == cursor)
		return false;
	node<T>* temp = cursor;
	while (temp != p.cursor&&temp!=nullptr)
		temp = temp->next;
	if(temp==p.cursor)
		return true;
	else
		return false;
}

template<typename T>
inline bool list<T>::iterator::operator>(iterator p)
{
	if (p.cursor == cursor)
		return false;
	node<T> * temp = cursor;
	while (temp != p.cursor && temp != nullptr)
		temp = temp->last;
	if (temp == p.cursor)
		return true;
	else
		return false;
}

template<typename T>
inline bool list<T>::iterator::operator>=(iterator p)
{
	node<T>* temp = cursor;
	while (cursor != p.cursor && temp != nullptr)
		temp = temp->last;
	if (temp == p.cursor)
		return true;
	else
		return false;
}

template<typename T>
bool list<T>::iterator::operator==(iterator p)
{
	if (cursor==p.cursor)
		return true;
	else
		return false;
}

template<typename T>
inline bool list<T>::iterator::operator!=(iterator p)
{
	if (cursor == p.cursor)
		return false;
	else
		return true;
}

template<typename T>
typename list<T>::iterator list<T>::begin() const
{
	typename list<T>::iterator a(head->next);
	return  a;
}

template<typename T>
typename list<T>::iterator list<T>::end() const
{
	typename list<T>::iterator a(tail);
	return  a;
}

template<typename T>
typename list<T>::iterator list<T>::rbegin() const
{
	typename list<T>::iterator a(tail->last);
	return  a;
}

template<typename T>
typename list<T>::iterator list<T>::rend() const
{
	return head;
}

template<typename T>
T list<T>::back()
{
	return tail->last->val;
}

template<typename T>
T list<T>::front()
{
	return head->next->val;
}

template<typename T>
void list<T>::push_front(T input)
{
	node<T>*  temp = new node<T>(input);
	head->next->last = temp;
	temp->next = head->next;
	head->next = temp;
	temp->last = head;

	length++;
}

template<typename T>
void list<T>::push_back(T input)
{
	node<T>* temp = new node<T>(input);
	tail->last->next = temp;
	temp->last = tail->last;
	tail->last = temp;
	temp->next = tail;
	length++;
}

template<typename T>
void list<T>::pop_back()
{
	try
	{
		if (head->next==tail)
		{
			throw std::out_of_range("hha");
		}
	}
	catch (std::out_of_range)
	{
		std::cerr << "list是空的" << std::endl;
		system("pause");
	}

	node<T>* temp = tail->last;
	tail->last = tail->last->last;
	tail->last->next = tail;
	delete temp;
	length--;
}

template<typename T>
void list<T>::pop_front()
{
	try
	{
		if (head->next == tail)
		{
			throw std::out_of_range("asd");
		}
	}
	catch (std::out_of_range)
	{
		std::cerr << "err!list is empty" << std::endl;
		system("pause");
	}

	node<T>* temp = head->next;
	head->next = head->next->next;
	head->next->last=head;
	delete temp;
	length--;
}
template<typename T>
typename list<T>::iterator list<T>::erase(iterator p)
{
	try
	{
		if (p.cursor == head || p.cursor == tail)
		{
			throw "超出范围了";
		}
	}
	catch(const char* msg)
	{
		std:: cerr << msg << std::endl;
		system("pause");
	}

	p->next->last = p->last;
	p->last->next = p->next;
	typename list<T>::iterator a(p->next);
	delete p.cursor;
	return a;

}

template<typename T>
void list<T>::sort(iterator _first, iterator _last)
{
	if (_first >= _last)//终止条件判断
		return;
	iterator first = _first;
	iterator last = _last;
	iterator cut;
	int cut_value = *first;

	while (first <last)
	{
		while (((*last) >cut_value)&& first < last)//要注意移动cut_value,
			last--;
		while (((*first) <cut_value)&&first<last)
			first++;
		int temp = *first;
		first->val= (*last);
		last->val = temp;
		last--;//交换数据后指针再次移动
		first++;
	}

	sort(_first, first-1);
	sort(first+1, _last);
}

template<typename T>
inline void list<T>::unique(iterator _first, iterator _last)
{
	
	while (_first != _last)
	{
		if(_first->next->val == (*_first))
		{
			iterator temp= _first->next;
			_first->next = temp->next;
			temp->last=_first.cursor;
			delete temp.cursor;
		}
		_first = _first->next;
	}
}

template<typename T>
void list<T>::assign(int n, T input)
{
	clear();
	tail = new node<T>;
	head = new node<T>;
	head->next = tail;
	tail->last = head;
	length = 0;
	while (n--)
		push_front(input);
}

template<typename T>
void list<T>::assign(iterator _first, iterator _last)
{
	clear();
	tail = new node<T>;
	head = new node<T>;
	head->next = tail;
	tail->last = head;
	length = 0;
	for (; _first < _last; _first++)
		push_back(*_first);
}

template<typename T>
void list<T>::display()
{
	list<int>::iterator temp= begin();
	for (; temp < end(); temp++)
		std::cout << *temp << " ";
	std::cout << std::endl;
}

template<typename T>
void list<T>::reverse()
{
	//创建新list
	list<T>* newlist = new list<T>;
	int n =length;
	node<T>* temp = head->next;
	while (n--)
	{
		newlist->push_front(temp->val);
		temp = temp->next;
	}
	//删除原list
	while (head != tail)
	{
		node<T>* temp = head;
		head = head->next;
		delete temp;
	}
	delete head;
	head = nullptr;
	tail = nullptr;

	*this = *newlist;
}

template<typename T>
void list<T>::merge(const list<T>& in1, const list<T>& in2)
{
	 iterator ite = in1.begin();
	 for (; ite != in1.end(); ite++)
		 push_back(ite->val);

	 ite = in2.begin();
	 for (; ite != in2.end(); ite++)
		push_back(ite->val);
}
