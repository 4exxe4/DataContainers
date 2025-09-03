#include <iostream>
using namespace std;

#define tab "\t"

class Element
{
	int Data;        //Значение элемента
	Element* pNext;  //Адрес следующего элемента
	static int count;
public:
	Element(int Data, Element* pNext =  nullptr)
	{
		this->Data = Data;
		this->pNext = pNext;
		count++;
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		count--;
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
};
int Element::count = 0;

class ForwardList
{
	Element* head;
public:
	ForwardList()
	{
		//Конструктор по умолчанию - создает пустой список 
		head = nullptr; //Если список пуст, то его голова указывает на ноль.
		cout << "FLConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		cout << "LDestructor:\t" << this << endl;
	}

	// Adding elements;
	void push_front(int Data)
	{
		//1) Создаем элемент и сохраняем в него добавляемое значение
		Element* New = new Element(Data);

		//2) Привязываем новый созданный элемент к началу списка:
		New->pNext = head;

		//3) Переносим голову на новый элемент (отправляем новый элемент в голову):
		head = New;
	}
	void push_back(int Data)
	{
		if (head == nullptr)push_front(Data);
		Element* New = new Element(Data);
		Element* Temp = head;
		while (Temp->pNext)Temp = Temp->pNext;
		Temp->pNext = New;

	}
	void insert(int Data, int Index)
	{
		if (Index == 0)return push_front(Data);
		if (Index >= Element::count)return push_back(Data);
		//1) Доходим до нужного элементв (элемент перед добавляемым)Ж
		Element* Temp = head;
		for (int i = 0; i < Index - 1; i++) Temp = Temp->pNext;

		//2) Создаем добавляемый элемент:
		Element* New = new Element(Data);

		//3) Пристыковываем новый элемент к следующему элементу:
		New->pNext = Temp->pNext;

		//4) Пристыковываем предыдущий элемент к новому:
		Temp->pNext = New;
	}

	//Removing elements:
	void pop_front()
	{
		//1) Запоминаем адрес удаляемого элемента:
		Element* Erased = head;
		//2) Исключаем удаляемый элемент из списка:
		head = head->pNext;
		//3) Удаляем удаляемый элемент из памяти:
		delete Erased;
	}
	void pop_back()
	{
		Element* Temp = head;
		while (Temp->pNext->pNext != nullptr)Temp = Temp->pNext;
		delete Temp->pNext;
		Temp->pNext = nullptr;
	}

	//Methods:
	void print()const
	{
		Element* Temp = head; //Temp - это итератор.
		//Итератор - это указатель, при помощи которого можно перебирать элементы структуры данных.
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;
		}
		Temp;
		cout << "Количество элементов списка: " << Element::count << endl;
	}
};

//#define BASE_CHECK

void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	//list.push_back(123);
	list.print();
	int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(value, index);
	list.print();
#endif

	ForwardList list1;
	list1.push_back(0);
	list1.push_back(1);
	list1.push_back(1);
	list1.push_back(2);
	list1.print();

	ForwardList list2;
	list2.push_back(3);
	list2.push_back(5);
	list2.push_back(8);
	list2.push_back(13);
	list2.push_back(21);
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);
	list2.print();

	int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите индекс добавляемого элемента: "; cin >> value;
	list1.insert(value, index);
	list1.print();
}

/*
Динамические структуры данных:

Простейшая структура данных, которую мы знаем - это массив. Это набор элементов одного типа в непрерывной области памяти. Из непрерывной области памяти вытекают как преимущества, так и недостатки массивов. Преимуществом массива является быстрый доступ к элементам который осуществляется за константное время, поскольку сводится к операции сложения.

Недостатком массивов является сложность добавления удаления элементов, что приводит к дополнительным затратам ресурсов памяти и процессорного времени, которое приводит к дополнительным затратам ресурсов памяти и процессорного времени, объем которых зависит от размера массива. Чем больше массив, тем больше ресурсов нужно затратить.

Недостатки массивов устраняют списки. Список (list) это набор элементов в произвольных областях памяти, каждый из которых, кроме значения, содержит адрес следующего элемента (иногда и предыдущее, в зависимости от типа списка). Это позволяет добавлять элементы в список за константное время, вообще не затрачивая дополнительных ресурсов. Поскольку элемент можно создать где угодно, где есть свободная память, и при этом, он будет привязан к списку. Но недостатком списка является медленный доступ к элементам, которые зависят от размеров списка.

Поскольку для того, чтобы дойти до нужного элемента списка, нужно пройти все элементы от начала списка до выбранного.

В то время, как массив обеспечивает произвольный доступ к элементам, список обеспечивает последовательный доступ к элементам.

У любого списка есть голова (head), которая содержит адрес начального элемента списка. В любой список можно зайти через голову.

Последний элемент списка всегда указывает на ноль. Указатель на ноль в элементе списка является признаком конца списка.

Реализация односвязного списка:

Односвязный список всегда реализуется при помощи двух классов:
1) Elememt - описывает структуру элемента. Состоит из поля данных и поля pNext
2) List (ForwardList) - объединяет элементы в список. Отвечает за добавление, удаление элементов и прочие операции
*/