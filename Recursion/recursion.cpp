#include<iostream>
using namespace std;

#define tab "\t"
//#define ELEVATOR_CHECK
#define FACTORIAL_CHECK
//#define FIBONACHI_CHECK
//#define POWER_CHECK

void elevator(int floor);
int factorial(int number);
int fibonachi(int number);
int power(int number, int degree);

void main()
{
	setlocale(LC_ALL, "");
#ifdef ELEVATOR_CHECK
	int n;
	cout << "Введите номер этажа: "; cin >> n;
	elevator(n);
	//cout << "Recursion";
	//main();  
#endif // ELEVATOR_CHECK

#ifdef FACTORIAL_CHECK
	int n;
	cout << "Введите число: "; cin >> n;
	cout << "Факториал числа " << n << " равен " << factorial(n) << endl;
	main();
#endif // FACTORIAL_CHECK

#ifdef FIBONACHI_CHECK
	int n;
	cout << endl << "Введите предел чисел Фибоначчи: "; cin >> n;
	cout << "Числа Фибоначии до числа: " << n;
	int next, i = 0;
	while ((next = fibonachi(i)) <= n)
	{
		cout << endl;
		cout << next << tab;
		i++;
	}
	main();
#endif // FIBONACHI_CHECK

#ifdef POWER_CHECK
	int number;
	int degree;
	cout << "Введите число: "; cin >> number;
	cout << "Введите степень, в которую хотите возвести число: "; cin >> degree;
	cout << "Ваше число возведенное в степень = " << power(number, degree) << endl;
	main();
#endif // POWER_CHECK
}

int factorial(int number)
{
	if (number == 0)return 1;
	return number * factorial(number - 1);
}
int fibonachi(int number)
{
	if (number <= 1) return number;
	else return fibonachi(number - 1) + fibonachi(number - 2);
}
int power(int number, int degree)
{
	if (degree == 0) return 1;
	return number * power (number, degree - 1);
}
void elevator(int floor)
{
	if (floor == 0)
	{
		cout << "Вы в подвале" << endl;
		return;
	}
	cout << "Вы на " << floor << " этаже" << endl;
	elevator(floor - 1);
	cout << "Вы на " << floor << " этаже" << endl;
}