#include <iostream>
#include <ctime>
#include <fstream>
#include <Windows.h>
using namespace std;

//������� ��������� ������
void Generation_Arr(int ArrSize, int Arr[]) {
	srand((time(NULL)));
	int variant;
	cout << "������: \n '1' ��� ����������� ��������� \n '2' ��� ����� ������ ��������� \n '3' ��� �����/������ � ����� " << endl;
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
				cout << "* -------- * ������� * -------- * \n";
				cout << "������ ���������� �����!";
				exit(0);
			}
		}
		break;
	case 3:
	{
		ifstream file_In("input.txt");
		if (!file_In)
		{
			cout << " * -------- * ������� * -------- * \n";
			cout << "�� �������� ����� \"input.txt\"! ";
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
		cout << "* -------- * ������� * -------- * \n";
		cout << "������ (1/2/3)!";
		exit(0);
	}
}

//������� ������ ������
void Output_Arr(int ArrSize, int Arr[]) {
	cout << "*--------* ������� *--------*" << "\n";
	for (int i = 0; i < ArrSize; i++)
	{
		cout << Arr[i] << "\t";
	}
	cout << "\n\n";

	//��������� ������ ������ � ����
	ofstream file_Out;
	file_Out.open("output.txt");

	file_Out << "*--------* ������� *--------*" << "\n";
	for (int i = 0; i < ArrSize; i++)
	{
		file_Out << Arr[i] << "\t";
	}
	file_Out << "\n";
	file_Out.close();
}

//������� ������ �������� ��������
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
	cout << "ʳ������ ��������, �� ����� " << MaxValue << " = " << counter << endl;
	cout << "\n";

	//��������� ������ ���������� � ����
	ofstream file_Out;
	file_Out.open("output.txt", ios::app);
	file_Out << "ʳ������ ��������, �� ����� " << MaxValue << " = " << counter << endl;
	file_Out.close();
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	cout << "\t * -------- * ����'������� ��������� 1 * -------- *\n";
	cout << "\t\t\t ������� 10. ������ 4  \n";
	cout << "\t\t\t ��������� ��������� \n";

	int ArrSize, MaxValue;

	cout << "\n\n������ ����� ������: ";
	cin >> ArrSize;

	int* Arr = new int[ArrSize]();

	//��������� �� ����� ���
	if (ArrSize <= 0 || (ArrSize - int(ArrSize) != 0))
	{
		cout << " * -------- * ������� * -------- * \n";
		cout << "������ ���������� �����! ";
		exit(0);
	}
	Generation_Arr(ArrSize, Arr);
	Output_Arr(ArrSize, Arr);

	cout << "������ ����� ��� ���������: ";
	cin >> MaxValue;

	//��������� �� ����� ���
	if (MaxValue <= 0 || (MaxValue - int(MaxValue) != 0))
	{
		cout << "* -------- * ������� * -------- * \n";
		cout << "������ ���������� �����!";
		exit(0);
	}
	Search_minValue(ArrSize, Arr, MaxValue);
}