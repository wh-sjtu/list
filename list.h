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
	node<T>* head;//Ϊ��֧��for(int i=list.begin;i<list.end();i++)��endӦ��Ϊ���һ���ڵ��дһ���ڵ㣬�����Ҫһ��β�����ڱ��ڵ�
	node<T>* tail;
	int length;
public:
	//���캯��ͬʱ�����������޷����������õġ�
	list();
	list(int n);
	list(int n, T p);
	list(const list<T>& p);//�������캯��
	~list();
	//���滹�в���Ϊ�������Ĺ��캯��
	int size();
	void clear();
	bool empty();
	//����������ʵ�ֱ���
	class iterator
	{
	public:
		node<T>* cursor;
		iterator(node<T>* p = nullptr);//���캯����ȱʡֵ����Ҫ������һ��Ĭ�Ϲ��캯����ȱʡֵд���������������ʱ����Ҫд��
		~iterator();
		T operator*()const;//�����õ����ز���д����Ԫ����
		/*
		��ͷ���������ֵ������һ��ָ�룬������һ�������˼�ͷ������Ķ���
			a��������ص���һ��ָ�룬���������õļ�ͷ�������ִ���൱��(*(p.operator->()).mem; �Ĳ�����
			b�����������һ�������˼�ͷ������Ķ���������Ըö�������������˵ļ�ͷ�������ֱ�����ص���һ��ָ�룬���Ը�ָ�����a)�Ĳ����������൱��(*(p.operator->().operator->())).mem;
		�ܵ���˵���صļ�ͷ���������Ϊ�˸ı���ĸ������л�ȡ��Ա��
		*/
		node<T>* operator->()const;//�õ�iterator�ڲ���cursor,���Զ���cursor�����á��÷���p->val��������д��p->->val������
		iterator operator+(int n);
		iterator operator++();//����++
		iterator& operator++(int);//ǰ��++
		iterator operator-(int n);
		iterator operator--();
		iterator& operator--(int);//ǰ��++
		bool operator<(iterator p);
		bool operator>(iterator p);
		bool operator>=(iterator p);
		bool operator==(iterator p);
		bool operator!=(iterator p);
	};

	//��vector<T>ǰ�������typename���߱����������vector <T>::iterator�����Ͷ���vector <T>�ĳ�Ա
	//��������Ϊ����ҪдΪ��ֵ����Ϊͨ���÷�Ϊlist(a.begin(),a.end())��a.begin����ʱ�������ܴ��ݸ���const�ı�������������������β�����Ϊconst����ʵ��++�Ȳ����ˡ�
	list(typename list<T>::iterator list_begin, typename list<T>::iterator list_end);//�������캯�������汾

	//�ں�������ʱ��Ƕ������ǰ��Ҫ����typename��
	iterator begin()const;
	iterator end()const;
	iterator rbegin()const;
	iterator rend()const;
	//����
	T back();
	T front();
	//����
	void push_front(T input);
	void push_back(T input);//��Ϊ����end�ڵ�����һ���ڵ��м���룬��������Ϊ����ʱҪ����Դ���
	//ɾ��
	void pop_back();//ͬ������Ϊendָ���ڱ��ڵ��ԭ��ɾ�����һ��Ԫ��ʱ���⴦��
	void pop_front();
	iterator erase(iterator p);
	//��Ϊ���ź�ð�ݶ����������ڴ���ʣ���˫�������²��ҵ�ʱ�临�Ӷȶ��ǳ�����������ʵ�ֿ��Щ���������ָ������������١�
	void sort(iterator _first, iterator _last);
	void unique(iterator _first, iterator _last);//ȥ�����ڵ��ظ�Ԫ��
	void assign(int num,T input);
	void assign(iterator _first, iterator _last);
	void display();
	void reverse();
	void merge(const list<T>& in1,const list<T>& in2) ;
};
//.h�ļ�����ĺ���Ҫ�ӷֺš�

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
		std::cerr << "list�ǿյ�" << std::endl;
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
			throw "������Χ��";
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
	if (_first >= _last)//��ֹ�����ж�
		return;
	iterator first = _first;
	iterator last = _last;
	iterator cut;
	int cut_value = *first;

	while (first <last)
	{
		while (((*last) >cut_value)&& first < last)//Ҫע���ƶ�cut_value,
			last--;
		while (((*first) <cut_value)&&first<last)
			first++;
		int temp = *first;
		first->val= (*last);
		last->val = temp;
		last--;//�������ݺ�ָ���ٴ��ƶ�
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
	//������list
	list<T>* newlist = new list<T>;
	int n =length;
	node<T>* temp = head->next;
	while (n--)
	{
		newlist->push_front(temp->val);
		temp = temp->next;
	}
	//ɾ��ԭlist
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
