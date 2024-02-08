#include <iostream>
#include <windows.h>
#include <vector>
#include <ctime>

using namespace std;

void shellSort(int arr[], int n)
{
    // Start with a big gap, then reduce the gap
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        // Do a gapped insertion sort for this gap size.
        // The first gap elements a[0..gap-1] are already in gapped order
        // keep adding one more element until the entire array is
        // gap sorted
        for (int i = gap; i < n; i += 1)
        {
            // add a[i] to the elements that have been gap sorted
            // save a[i] in temp and make a hole at position i
            int temp = arr[i];

            // shift earlier gap-sorted elements up until the correct
            // location for a[i] is found
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];

            //  put temp (the original a[i]) in its correct location
            arr[j] = temp;
        }
    }
}

void countSort(int arr[], int n)
{
    int max = arr[0];
    int min = arr[0];
    for (int i = 0; i < n; i++) 
    {
        if (arr[i] > max) max = arr[i];
        if (arr[i] < min) min = arr[i];
    }
    int range = max - min + 1;

    vector<int> count(range), output(n);
    for (int i = 0; i < n; i++)
        count[arr[i] - min]++;

    for (int i = 1; i < count.size(); i++)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--) 
    {
        output[count[arr[i] - min] - 1] = arr[i];
        count[arr[i] - min]--;
    }

    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}

// A utility function to swap two elements
void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

/* This function takes last element as pivot, places
the pivot element at its correct position in sorted
array, and places all smaller (smaller than pivot)
to left of pivot and all greater elements to right
of pivot */
int partition(int arr[], int low, int high)
{
    int pivot = arr[high]; // pivot
    int i = (low - 1); // Index of smaller element and indicates the right position of pivot found so far

    for (int j = low; j <= high - 1; j++)
    {
        // If current element is smaller than the pivot
        if (arr[j] < pivot)
        {
            i++; // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

/* The main function that implements QuickSort
arr[] --> Array to be sorted,
low --> Starting index,
high --> Ending index */
void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
        at right place */
        int pi = partition(arr, low, high);

        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void createArray(int arr[], int n, int end)
{
    for (int i = 0; i < n; i++)
        arr[i] = rand() % end;
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

    cout << "\t * -------- * ����'������� ��������� 6 * -------- *\n";
    cout << "\t\t\t ������� 10. ������ 1  \n";
    cout << "\t     ��������� ������� ��������� ����������\n\n";

    float length0, end0, addLength0;
    int i, length, end, varik = 0, partlySorted, addLength;
    string partlySorted0;

    cout << "\n�������� ����� N ������\nN = ";
    cin >> length0;
    ErorCheck(length0);
    length = int(length0);
    int* arr = new int[length];
    int* array = new int[length];

    cout << "\n����������� ������� ������ = ";
    cin >> end0;
    ErorCheck(end0);
    end = int(end0);
    createArray(arr, length, end);

    cout << "\n�������� �������� ���������� �����? (0/1): ";
    cin >> partlySorted0;
    if (partlySorted0 == "0" || partlySorted0 == "1") partlySorted = atoi(partlySorted0.c_str());
    else 
    {
        cout << "\n    * -------- * ������� * -------- * \n";
        cout << " ������������ ������ ��������� ��������!\n";
    }

    cout << "\n������ ������ ��������� � ������� �� ���������: \n";
    printArray(arr, length);
    cout << "\n";

    cout << "\n-----------�������----------";
    cout << "\n0 - ���������� �����\n1 - ���������� ����������\n2 - ������ ����������";
    cout << "\n----------------------------";
    cout << "\n������ �������� ���������� (0/1/2): ";
    cin >> varik;

    float start = clock();

    switch (varik) 
    {
    case 0:
        if (partlySorted == 0) cout << "\n���������� �����:";
        shellSort(arr, length);
        break;
    case 1:
        if (partlySorted == 0) cout << "\n���������� ϲ���������:";
        countSort(arr, length);
        break;
    case 2:
        if (partlySorted == 0) cout << "\n������ ����������:";
        quickSort(arr, 0, length - 1);
        break;
    default:
        cout << "\n    * -------- * ������� * -------- * \n";
        cout << " ������������ ������ ��������� ��������!\n";
        return 0;
    }

    if (partlySorted == 1)
    {
        cout << "\n���� �� ��������� �������� �� N ������\nN = ";
        cin >> addLength0;

        ErorCheck(addLength0);
        addLength = int(addLength0);
        int* array = new int[length + addLength]();
        for (int i = 0; i < length; i++)
            array[i] = arr[i];

        addElementsToArray(array, length, addLength, end);
        cout << "\n����� ������ ������ ���������: \n";
        printArray(array, length + addLength);

        //float start = clock();

        if (varik == 0) 
        {
            cout << "\n\n���������� �����:";
            shellSort(array, length + addLength);
        }
        else if (varik == 1) 
        {
            cout << "\n\n���������� ϲ���������:";
            countSort(array, length + addLength);
        }
        else 
        {
            cout << "\n\n������ ����������:";
            quickSort(array, 0, length + addLength - 1);
        }

        //cout << (clock() - start) / CLOCKS_PER_SEC;

        cout << "\n³����������� ������, �� �������� ������ �������: \n";
        printArray(array, length + addLength);
    }
    else 
    {
        //cout << (clock() - start) / CLOCKS_PER_SEC;

        cout << "\n³����������� ������, �� �������� ������ �������: \n";
        printArray(arr, length);
    }

    cout << "\n\n\n";
    return 0;
}