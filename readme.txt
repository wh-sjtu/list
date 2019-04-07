手动实现的list数据结构，具有以下功能：
	list();
	list(int n);
	list(int n, T p);
	list(const list<T>& p);//拷贝构造函数
	~list();
	//下面还有参数为迭代器的构造函数
	int size();
	void clear();
	bool empty();

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