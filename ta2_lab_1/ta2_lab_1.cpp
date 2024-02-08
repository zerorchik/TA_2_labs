#include <iostream>
#include <ctime>
#include <fstream>
#include <Windows.h>
using namespace std;

//Функція генерація масиву
void Generation_Arr(int ArrSize, int Arr[]) {
	srand((time(NULL)));
	int variant;
	cout << "Введіть: \n '1' для автоматичної генерації \n '2' для ввода масиву власноруч \n '3' для вводу/виводу з файла " << endl;
	cin >> variant;
	switch (variant)
	{
	case 1:
		for (int i = 0; i < ArrSize; i++)
		{
			Arr[i] = rand() % 100;
		}
		break;
	case 2:
		for (int i = 0; i < ArrSize; i++)
		{
			cout << "a[" << i + 1 << "] = ";
			cin >> Arr[i];
			if (Arr[i] <= 0 || (Arr[i] - int(Arr[i]) != 0))
			{
				cout << "* -------- * ПОМИЛКА * -------- * \n";
				cout << "Введіть натуральне число!";
				exit(0);
			}
		}
		break;
	case 3:
	{
		ifstream file_In("input.txt");
		if (!file_In)
		{
			cout << " * -------- * ПОМИЛКА * -------- * \n";
			cout << "Не знайдено файлу \"input.txt\"! ";
			exit(0);
		}
		for (int i = 0; i < ArrSize; i++)
		{
			file_In >> Arr[i];
		}
		file_In.close();
		break;
	}
	default:
		cout << "* -------- * ПОМИЛКА * -------- * \n";
		cout << "Введіть (1/2/3)!";
		exit(0);
	}
}

//Функція виводу масиву
void Output_Arr(int ArrSize, int Arr[]) {
	cout << "*--------* МАТРИЦЯ *--------*" << "\n";
	for (int i = 0; i < ArrSize; i++)
	{
		cout << Arr[i] << "\t";
	}
	cout << "\n\n";

	//Реалізація виводу масиву у файл
	ofstream file_Out;
	file_Out.open("output.txt");

	file_Out << "*--------* МАТРИЦЯ *--------*" << "\n";
	for (int i = 0; i < ArrSize; i++)
	{
		file_Out << Arr[i] << "\t";
	}
	file_Out << "\n";
	file_Out.close();
}

//Функція пошуку вказаних елементів
void Search_minValue(int ArrSize, int Arr[], int MaxValue) {
	int min = 100, counter = 0;

	for (int i = 0; i < ArrSize; i++)
	{
		if (Arr[i] > MaxValue)
		{
			counter++;
		}
	}
	cout << "*-----------------------------*" << "\n";
	cout << "Кількість елементів, що більше " << MaxValue << " = " << counter << endl;
	cout << "\n";

	//Реалізація виводу результату у файл
	ofstream file_Out;
	file_Out.open("output.txt", ios::app);
	file_Out << "Кількість елементів, що більше " << MaxValue << " = " << counter << endl;
	file_Out.close();
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	cout << "\t * -------- * Комп'ютерний практикум 1 * -------- *\n";
	cout << "\t\t\t Бригада 10. Варіант 4  \n";
	cout << "\t\t\t Реалізація алгоритму \n";

	int ArrSize, MaxValue;

	cout << "\n\nВведіть розмір масиву: ";
	cin >> ArrSize;

	int* Arr = new int[ArrSize]();

	//Обмеження на вхідні дані
	if (ArrSize <= 0 || (ArrSize - int(ArrSize) != 0))
	{
		cout << " * -------- * ПОМИЛКА * -------- * \n";
		cout << "Введіть натуральне число! ";
		exit(0);
	}
	Generation_Arr(ArrSize, Arr);
	Output_Arr(ArrSize, Arr);

	cout << "Введіть число для порівняння: ";
	cin >> MaxValue;

	//Обмеження на вхідні дані
	if (MaxValue <= 0 || (MaxValue - int(MaxValue) != 0))
	{
		cout << "* -------- * ПОМИЛКА * -------- * \n";
		cout << "Введіть натуральне число!";
		exit(0);
	}
	Search_minValue(ArrSize, Arr, MaxValue);
}