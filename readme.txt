�ֶ�ʵ�ֵ�list���ݽṹ���������¹��ܣ�
	list();
	list(int n);
	list(int n, T p);
	list(const list<T>& p);//�������캯��
	~list();
	//���滹�в���Ϊ�������Ĺ��캯��
	int size();
	void clear();
	bool empty();

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