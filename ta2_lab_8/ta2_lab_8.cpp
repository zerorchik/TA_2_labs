#include <iostream>
#include <windows.h>
#include <ctime>
#include <unordered_map>

using namespace std;

///***************************************** LSD Radix Sort ******************************************///
// function that returns max value of element
int getMaxLength(int arr[])
{
    return 4;
}

// function that returns the byte i of element
short int getByte(unsigned int elem, unsigned int i)
{
    if (sizeof(elem) > i) { return (elem >> ((3 - i) * 8) & (255)); }
    else return -1;
}

// main function for LSD
void radixSort_LSD(int arr[], int n)
{
    int maxLength = getMaxLength(arr);

    // Counting sort
    for (int d = maxLength - 1; d >= 0; d--) 
    {
        int* output = new int[n];
        int count[256 + 2] = { 0 };

        for (int i = 0; i < n; i++) 
            count[getByte(arr[i], d) + 2]++;

        for (int r = 0; r < 256 + 1; r++)
            count[r + 1] += count[r];

        for (int i = 0; i < n; i++) 
            output[count[getByte(arr[i], d) + 1]++] = arr[i];

        for (int i = 0; i < n; i++)
            arr[i] = output[i];
    }
}

///***************************************** MSD Radix Sort ******************************************///
// helping function for MSD
void MSD(int* arr, int* output, int low, int n, int d)
{
    int i, count[256 + 2] = { 0 };

    for (i = low; i < n; i++) 
        count[getByte(arr[i], d) + 2]++;

    for (int r = 0; r < 256 + 1; r++)
        count[r + 1] += count[r];

    for (int i = low; i < n; i++) 
        output[count[getByte(arr[i], d) + 1]++] = arr[i];

    for (int i = low; i < n; i++) 
        arr[i] = output[i - low];

    // if there is many times the same letter we launch a sort for all of them
    for (int r = 0; r < 256 + 1; r++)
        if (count[r] < count[r + 1]) MSD(arr, output, low + count[r], low + count[r + 1], d + 1);
}

// main function for MSD
void radixSort_MSD(int* arr, int n)
{
    int* output = new int[n];
    MSD(arr, output, 0, n, 0);
}

///**************************************** Helping functions ****************************************///
void createArray(int arr[], int length, int start, int end)
{
    for (int i = 0; i < length; i++)
        arr[i] = start + rand() % (end - start);
}

void addElementsToArray(int arr[], int start, int n, int end)
{
    for (int i = start; i < start + n; i++)
        arr[i] = rand() % end;
}

void printArray(int arr[], int n)
{
    for (int i = 0; i < n; i++) 
        cout << arr[i] << " ";
}

int ErorCheck(float a)
{
    if (a <= 0 || (a - int(a) != 0))
    {
        cout << "\n * -------- * ������� * -------- * \n";
        cout << " ���! ������� �� ���������� �����! \n\n";
        return 0;
    }
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    float length0, start0, end0, addLength0;
    int i, length, start, end, varik = 0, partlySorted = 0, addLength;
    string partlySorted0;

    cout << "\t * -------- * ����'������� ��������� 8 * -------- *\n";
    cout << "\t\t\t ������� 10. ������ 1  \n";
    cout << "\t ��������� ��������� ���������� � �������� �������\n\n";

    cout << "\n� ����� ����� ������ N ������\nN = ";
    cin >> length0;
    ErorCheck(length0);
    length = int(length0);
    int* arr = new int[length];

    cout << "\n���� ������� ������ �� �� ��: ";
    cin >> start0 >> end0;
    ErorCheck(start0);
    start = int(start0);
    ErorCheck(end0);
    end = int(end0);
    createArray(arr, length, start, end);

    cout << "\n�������� �������� ���������� �����? (0/1): ";
    cin >> partlySorted0;
    if (partlySorted0 == "0" || partlySorted0 == "1") partlySorted = atoi(partlySorted0.c_str());
    else
    {
        cout << "\n    * -------- * ������� * -------- * \n";
        cout << " ������������ ������ ��������� ��������!\n";
    }

    cout << "\n������ ��� ������ ����� ����� � ������� �� ���������: \n";
    printArray(arr, length);
    cout << "\n";

    cout << "\n-----------�������----------";
    cout << "\n0 - LSD - ����������\n1 - MSD - ����������";
    cout << "\n----------------------------";
    cout << "\n������ �������� ���������� (0/1): ";
    cin >> varik;

    //float Start = clock();

    switch (varik)
    {
    case 0:
        if (partlySorted == 0) cout << "\nLSD - ����������:";
        radixSort_LSD(arr, length);
        break;
    case 1:
        if (partlySorted == 0) cout << "\nMSD - ����������:";
        radixSort_MSD(arr, length);
        break;
    default:
        cout << "\n    * -------- * ������� * -------- * \n";
        cout << " ������������ ������ ��������� ��������!\n";
        return 0;
    }

    if (partlySorted == 1)
    {
        cout << "\n�������� ���������� ��� ���� ������ �� N ����� �����\nN = ";
        cin >> addLength0;

        ErorCheck(addLength0);
        addLength = int(addLength0);
        int* array = new int[length + addLength]();
        for (int i = 0; i < length; i++)
            array[i] = arr[i];

        addElementsToArray(array, length, addLength, end);
        cout << "\n����� ������ ������ ���������: \n";
        printArray(array, length + addLength);

        //float Start = clock();

        if (varik == 0)
        {
            cout << "\n\nLSD - ����������:";
            radixSort_LSD(array, length + addLength);
        }
        else
        {
            cout << "\n\nMSD - ����������:";
            radixSort_MSD(array, length + addLength);
        }

        //cout << (clock() - Start) / CLOCKS_PER_SEC;

        cout << "\n³����������� ������, �� �������� ������: \n";
        printArray(array, length + addLength);
    }
    else
    {
        //cout << (clock() - Start) / CLOCKS_PER_SEC;

        cout << "\n³����������� ������, �� �������� ������: \n";
        printArray(arr, length);
    }
    cout << "\n\n\n";
    return 0;
}