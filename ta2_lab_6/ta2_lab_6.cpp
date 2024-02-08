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
        cout << "\n * -------- * ПОМИЛКА * -------- * \n";
        cout << " Упс! Уведено не натуральне число! \n\n";
        return 0;
    }
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << "\t * -------- * Комп'ютерний практикум 6 * -------- *\n";
    cout << "\t\t\t Бригада 10. Варіант 1  \n";
    cout << "\t     Реалізація простих алгоритмів сортування\n\n";

    float length0, end0, addLength0;
    int i, length, end, varik = 0, partlySorted, addLength;
    string partlySorted0;

    cout << "\nЛеприкон зібрав N скарбів\nN = ";
    cin >> length0;
    ErorCheck(length0);
    length = int(length0);
    int* arr = new int[length];
    int* array = new int[length];

    cout << "\nМаксимальна кількість золота = ";
    cin >> end0;
    ErorCheck(end0);
    end = int(end0);
    createArray(arr, length, end);

    cout << "\nСтворити частково сортований масив? (0/1): ";
    cin >> partlySorted0;
    if (partlySorted0 == "0" || partlySorted0 == "1") partlySorted = atoi(partlySorted0.c_str());
    else 
    {
        cout << "\n    * -------- * ПОМИЛКА * -------- * \n";
        cout << " Неправильний варіант виконання програми!\n";
    }

    cout << "\nПерелік скарбів леприкона у порядку їх отримання: \n";
    printArray(arr, length);
    cout << "\n";

    cout << "\n-----------Менюшка----------";
    cout << "\n0 - Сортування Шелла\n1 - Сортування підрахунком\n2 - Швидке сортування";
    cout << "\n----------------------------";
    cout << "\nОберіть алгоритм сортування (0/1/2): ";
    cin >> varik;

    float start = clock();

    switch (varik) 
    {
    case 0:
        if (partlySorted == 0) cout << "\nСОРТУВАННЯ ШЕЛЛА:";
        shellSort(arr, length);
        break;
    case 1:
        if (partlySorted == 0) cout << "\nСОРТУВАННЯ ПІДРАХУНКОМ:";
        countSort(arr, length);
        break;
    case 2:
        if (partlySorted == 0) cout << "\nШВИДКЕ СОРТУВАННЯ:";
        quickSort(arr, 0, length - 1);
        break;
    default:
        cout << "\n    * -------- * ПОМИЛКА * -------- * \n";
        cout << " Неправильний варіант виконання програми!\n";
        return 0;
    }

    if (partlySorted == 1)
    {
        cout << "\nДрузі до леприкона принесли ще N скарбів\nN = ";
        cin >> addLength0;

        ErorCheck(addLength0);
        addLength = int(addLength0);
        int* array = new int[length + addLength]();
        for (int i = 0; i < length; i++)
            array[i] = arr[i];

        addElementsToArray(array, length, addLength, end);
        cout << "\nНовий перелік скарбів леприкона: \n";
        printArray(array, length + addLength);

        //float start = clock();

        if (varik == 0) 
        {
            cout << "\n\nСОРТУВАННЯ ШЕЛЛА:";
            shellSort(array, length + addLength);
        }
        else if (varik == 1) 
        {
            cout << "\n\nСОРТУВАННЯ ПІДРАХУНКОМ:";
            countSort(array, length + addLength);
        }
        else 
        {
            cout << "\n\nШВИДКЕ СОРТУВАННЯ:";
            quickSort(array, 0, length + addLength - 1);
        }

        //cout << (clock() - start) / CLOCKS_PER_SEC;

        cout << "\nВідсортований список, що леприкон віднесе майстру: \n";
        printArray(array, length + addLength);
    }
    else 
    {
        //cout << (clock() - start) / CLOCKS_PER_SEC;

        cout << "\nВідсортований список, що леприкон віднесе майстру: \n";
        printArray(arr, length);
    }

    cout << "\n\n\n";
    return 0;
}