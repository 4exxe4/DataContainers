#include <iostream>
#include <time.h>
using namespace std;

#define tab "\t"
#define delimiter "\n---------------------------------------\n"

class Element
{
	int Data;        //�������� ��������
	Element* pNext;  //����� ���������� ��������
	static int count;
public:
	Element(int Data, Element* pNext =  nullptr)
	{
		this->Data = Data;
		this->pNext = pNext;
		count++;
#ifdef DEBUG
		cout << "EConstructor:\t" << this << endl;
#endif // DEBUG

	}
	~Element()
	{
		count--;
#ifdef DEBUG
		cout << "EDestructor:\t" << this << endl;
#endif // DEBUG

	}
	friend class ForwardList;
	friend ForwardList operator+(const ForwardList& left, const ForwardList& right);
};
int Element::count = 0;

class ForwardList
{
	Element* head;
	size_t size;
public:
	Element* getHead()const
	{
		return head;
	}
	size_t get_size()const
	{
		return size;
	}
	ForwardList()
	{
		//����������� �� ��������� - ������� ������ ������ 
		head = nullptr; //���� ������ ����, �� ��� ������ ��������� �� ����.
		size = 0;
		cout << "FLConstructor:\t" << this << endl;
	}
	ForwardList(int size) :ForwardList()
	{
		while (size--)push_front(0);
		cout << "FLSizeConstructor:\t" << this << endl;
	}
	ForwardList(const ForwardList& other):ForwardList()
	{
		//Deep copy (��������� �����������):
		*this = other;
		cout << "FLCopyConstructor:\t" << this << endl;
	}
	ForwardList(ForwardList&& other) :ForwardList()
	{
		*this = std::move(other);
	}
	~ForwardList()
	{
		clock_t t_start = clock();
		while (head)pop_front();
		clock_t t_end = clock();
		while (head)pop_back();
		cout << "LDestructor:\t" << this << "\tcomplete for " << double(t_end-t_start)/CLOCKS_PER_SEC << endl;
	}
	//Operators:
	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other)return *this;   //0) ���������, �� �������� �� 'this' � 'other' ����� � ��� �� ��������
		while (head)pop_front();           //1) ������ �������� ������� ��������� �� ������ 
		//2) Deep copy (��������� �����������):
		for (Element* Temp = other.head; Temp; Temp = Temp->pNext)
			push_front(Temp->Data);
			//push_back(Temp->Data);
		reverse();
		cout << "FLCopyConstructor:\t" << this << endl;
		return *this;
	}
	ForwardList& operator=(ForwardList&& other)
	{
		if (this == &other)return *this;
		while (head)pop_front();
		this->head = other.head;
		this->size = other.size;
		other.head = nullptr;
		other.size = 0;
		cout << "FLMoveAssignment:\t" << this << endl;
		return *this;
	}
	
	int operator[](int index)const
	{
		Element* Temp = head;
		for (int i = 0; i < index; i++)Temp = Temp->pNext;
		return Temp->Data;
	}
	int& operator[](int index)
	{
		Element* Temp = head;
		for (int i = 0; i < index; i++)Temp = Temp->pNext;
		return Temp->Data;
	}

	// Adding elements;
	void push_front(int Data)
	{
		//1) ������� ������� � ��������� � ���� ����������� ��������
		//Element* New = new Element(Data);

		//2) ����������� ����� ��������� ������� � ������ ������:
		//New->pNext = head;

		//3) ��������� ������ �� ����� ������� (���������� ����� ������� � ������):
		//head = New;

		head = new Element(Data, head);

		size++;
	}
	void push_back(int Data)
	{
		if (head == nullptr) return push_front(Data);
		Element* Temp = head;
		while (Temp->pNext)Temp = Temp->pNext;
		Temp->pNext = new Element(Data);
		size++;
	}
	void insert(int Data, int Index)
	{
		if (Index == 0)return push_front(Data);
		if (Index >= Element::count)return push_back(Data);
		//1) ������� �� ������� �������� (������� ����� �����������)�
		Element* Temp = head;
		for (int i = 0; i < Index - 1; i++) Temp = Temp->pNext;

		////2) ������� ����������� �������:
		//Element* New = new Element(Data);

		////3) �������������� ����� ������� � ���������� ��������:
		//New->pNext = Temp->pNext;

		////4) �������������� ���������� ������� � ������:
		//Temp->pNext = New;
		Temp->pNext = new Element(Data, Temp->pNext);
		size++;
	}

	//Removing elements:
	void pop_front()
	{
		//1) ���������� ����� ���������� ��������:
		Element* Erased = head;
		//2) ��������� ��������� ������� �� ������:
		head = head->pNext;
		//3) ������� ��������� ������� �� ������:
		delete Erased;
		size--;
	}
	void pop_back()
	{
		if (!head || head->pNext == nullptr)return pop_front();
		Element* Temp = head;
		while (Temp->pNext->pNext != nullptr)Temp = Temp->pNext;
		delete Temp->pNext;
		Temp->pNext = nullptr;
		size--;
	}

	//Methods:
	void reverse()
	{
		ForwardList reverse; //���� ������ ����� ������������.
		while (head)        //���� ������ �������� ��������
		{
			reverse.push_front(head->Data); //��������� �������� ������� � ��������� ������
			pop_front(); //� ������� ��������� ������� ������
		}
		//��������� ��� ������ ���������
		//head = reverse.head; 
		//size = reverse.size;
		*this = std::move(reverse); //��� ���������� �������, ������� ����� ������� �������� MoveAssignment, ���� �� ����
		reverse.head = nullptr; //��������� ��������� ������ �������� ��������� ����������, ��� ���� ����� ������ ����������, ������� ��������� ��� �������, � �� ��������� �� �� �� ������, �� ������� ��������� ��� �������� ������, ������������� ���������� ������ � ��� �������� ������.
	}
	void print()const
	{
		/*
		Element* Temp = head; //Temp - ��� ��������.
		//�������� - ��� ���������, ��� ������ �������� ����� ���������� �������� ��������� ������.
		while (Temp)
		{
			Temp = Temp->pNext;
		}
		Temp;
		*/
		for (Element* Temp = head; Temp; Temp = Temp ->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "���������� ��������� ������: " << size << endl;
		cout << "����� ���������� ��������� ������: " << Element::count << endl;
	}
	friend ForwardList operator+(const ForwardList& left, const ForwardList& right);
};
ForwardList operator+(const ForwardList& left, const ForwardList& right)
{
	ForwardList fusion;
	for (Element* Temp = left.getHead(); Temp; Temp = Temp->pNext)
		fusion.push_front(Temp->Data);
	for (Element* Temp = right.head; Temp; Temp = Temp->pNext)
		fusion.push_front(Temp->Data);
	fusion.reverse();
	return fusion;
}

//#define BASE_CHECK
//#define OPERATOR_PLUS_CHECK
//#define PERFORMANCE_CHECK
//#define SUBSCRIPT_OPERATOR_CHECK
//#define COPY_SEMANTIC_PERFORMANCE_CHECK
#define MOVE_SEMANTIC_CHECK

void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	int n;
	cout << "������� ������ ������: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	//list.push_back(123);
	list.print();
	//int index;                                                             //CNTRL+K+C - ����������������
	//int value;
	//cout << "������� ������ ������������ ��������: "; cin >> index;
	//cout << "������� �������� ������������ ��������: "; cin >> value;
	//list.insert(value, index);
	//list.print();
#endif //BASE_CHECK

#ifdef OPERATOR_PLUS_CHECK
	ForwardList list1;
	list1.push_back(0);
	list1.push_back(1);
	list1.push_back(1);
	list1.push_back(2);
	//list1.print();
	for (int i = 0; i < list1.get_size(); i++)cout << list1[i] << tab; cout << endl;

	ForwardList list2;
	list2.push_back(3);
	list2.push_back(5);
	list2.push_back(8);
	list2.push_back(13);
	list2.push_back(21);
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);
	//list2.print();
	for (int i = 0; i < list2.get_size(); i++)cout << list2[i] << tab; cout << endl;

	//ForwardList fusion = list1 + list2;    //CopyConstructor
	ForwardList list3;
	cout << delimiter << endl;
	list3 = list1 + list2;    //CopyAssignment
	cout << delimiter << endl;
	//fusion.print();
	for (int i = 0; i < list3.get_size(); i++)cout << list3[i] << tab; cout << endl;
	

	/*
	int index;
	int value;
	cout << "������� ������ ������������ ��������: "; cin >> index;
	cout << "������� ������ ������������ ��������: "; cin >> value;
	list1.insert(value, index);
	list1.print();
	*/
#endif //OPERATOR_PLUS_CHECK

#ifdef PERFORMANCE_CHECK
	int n;
	cout << "������� ������ ������: "; cin >> n;
	ForwardList list;
	clock_t t_start = clock();
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
		//list.push_back(rand() % 100);
	}
	clock_t t_end = clock();
	cout << "ForwardList filled for " << double(t_end - t_start) / CLOCKS_PER_SEC << " seconds. ";
	system("PAUSE");
#endif // PERFORMANCE_CHECK

#ifdef SUBSCRIPT_OPERATOR_CHECK

	int n;
	cout << "������� ������ ������: "; cin >> n;

	clock_t start;
	clock_t end;

	ForwardList list(n);
	start = clock();
	for (int i = 0; i < list.get_size(); i++)
		list[i] = rand() % 100;
	end = clock();
	cout << "������ ��������" <<double(end-start)/CLOCKS_PER_SEC << endl;
	system("PAUSE");
	for (int i = 0; i < list.get_size(); i++)
		cout << list[i] << tab;
	cout << endl;

#endif // SUBSCRIPT_OPERATOR_CHECK

#ifdef COPY_SEMANTIC_PERFORMANCE_CHECK
	int n;
	cout << "������� ������ ������: "; cin >> n;

	clock_t t_start, t_end;

	ForwardList list1;
	t_start = clock();
	for (int i = 0; i < n; i++)
		list1.push_front(rand()%100);
	t_end = clock();
	cout << "������ �������� �� " << double(t_end - t_start) / CLOCKS_PER_SEC << " ������ " << endl;
	system("PAUSE");
	t_start = clock();
	ForwardList list2 = list1;
	t_end = clock();
	cout << "����������� ��������� �� " << double(t_end - t_start) / CLOCKS_PER_SEC << " ������ " << endl;

	//for (int i = 0; i < list1.get_size(); i++)cout << list1[i] << tab; cout << endl;
	//for (int i = 0; i < list2.get_size(); i++)cout << list2[i] << tab; cout << endl;
#endif

#ifdef MOVE_SEMANTIC_CHECK

	clock_t t_start, t_end;
	ForwardList list1;
	ForwardList list2;
	t_start = clock();
	for (int i = 0; i < 5000000; i++)list1.push_front(rand());
	for (int i = 0; i < 5000000; i++)list2.push_front(rand());
	t_end = clock();
	cout << "Lists filled for " << double(t_end - t_start) / CLOCKS_PER_SEC << " seconds" << endl;
	system("PAUSE");

	t_start = clock();
	ForwardList list3 = list1 + list2;
	t_end = clock();
	cout << "Lists concatenated for " << double(t_end - t_start) / CLOCKS_PER_SEC << " seconds" << endl;

	t_start = clock();
	ForwardList list4 = list3;
	t_end = clock();
	cout << "Lists copied for " << double(t_end - t_start) / CLOCKS_PER_SEC << " seconds" << endl;
#endif // MOVE_SEMANTIC_CHECK
}

/*
������������ ��������� ������:

���������� ��������� ������, ������� �� ����� - ��� ������. ��� ����� ��������� ������ ���� � ����������� ������� ������. �� ����������� ������� ������ �������� ��� ������������, ��� � ���������� ��������. ������������� ������� �������� ������� ������ � ��������� ������� �������������� �� ����������� �����, ��������� �������� � �������� ��������.

����������� �������� �������� ��������� ���������� �������� ���������, ��� �������� � �������������� �������� �������� ������ � ������������� �������, ������� �������� � �������������� �������� �������� ������ � ������������� �������, ����� ������� ������� �� ������� �������. ��� ������ ������, ��� ������ �������� ����� ���������.

���������� �������� ��������� ������. ������ (list) ��� ����� ��������� � ������������ �������� ������, ������ �� �������, ����� ��������, �������� ����� ���������� �������� (������ � ����������, � ����������� �� ���� ������). ��� ��������� ��������� �������� � ������ �� ����������� �����, ������ �� ���������� �������������� ��������. ��������� ������� ����� ������� ��� ������, ��� ���� ��������� ������, � ��� ����, �� ����� �������� � ������. �� ����������� ������ �������� ��������� ������ � ���������, ������� ������� �� �������� ������.

��������� ��� ����, ����� ����� �� ������� �������� ������, ����� ������ ��� �������� �� ������ ������ �� ����������.

� �� �����, ��� ������ ������������ ������������ ������ � ���������, ������ ������������ ���������������� ������ � ���������.

� ������ ������ ���� ������ (head), ������� �������� ����� ���������� �������� ������. � ����� ������ ����� ����� ����� ������.

��������� ������� ������ ������ ��������� �� ����. ��������� �� ���� � �������� ������ �������� ��������� ����� ������.

���������� ������������ ������:

����������� ������ ������ ����������� ��� ������ ���� �������:
1) Elememt - ��������� ��������� ��������. ������� �� ���� ������ � ���� pNext
2) List (ForwardList) - ���������� �������� � ������. �������� �� ����������, �������� ��������� � ������ ��������
*/