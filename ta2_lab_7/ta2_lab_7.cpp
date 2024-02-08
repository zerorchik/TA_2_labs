#include <iostream>
#include <windows.h>
#include <ctime>

using namespace std;

// Merges two subarrays of array[].
// First subarray is array[begin..mid]
// Second subarray is array[mid+1..end]
void merge(int array[], int const left, int const mid, int const right)
{
	auto const subArrayOne = mid - left + 1;
	auto const subArrayTwo = right - mid;

	// Create temp arrays
	auto* leftArray = new int[subArrayOne],
		* rightArray = new int[subArrayTwo];

	// Copy data to temp arrays leftArray[] and rightArray[]
	for (auto i = 0; i < subArrayOne; i++)
		leftArray[i] = array[left + i];
	for (auto j = 0; j < subArrayTwo; j++)
		rightArray[j] = array[mid + 1 + j];

	auto indexOfSubArrayOne = 0,	// Initial index of first sub-array
		indexOfSubArrayTwo = 0;		// Initial index of second sub-array
	int indexOfMergedArray = left;	// Initial index of merged array

	// Merge the temp arrays back into array[left..right]
	while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) 
	{
		if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]) 
		{
			array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
			indexOfSubArrayOne++;
		}
		else 
		{
			array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
			indexOfSubArrayTwo++;
		}
		indexOfMergedArray++;
	}
	// Copy the remaining elements of
	// left[], if there are any
	while (indexOfSubArrayOne < subArrayOne) 
	{
		array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
		indexOfSubArrayOne++;
		indexOfMergedArray++;
	}
	// Copy the remaining elements of
	// right[], if there are any
	while (indexOfSubArrayTwo < subArrayTwo) 
	{
		array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
		indexOfSubArrayTwo++;
		indexOfMergedArray++;
	}
}

// begin is for left index and end is
// right index of the sub-array
// of arr to be sorted */
void mergeSort(int array[], int const begin, int const end)
{
	if (begin >= end) return;	// Returns recursively

	auto mid = begin + (end - begin) / 2;
	mergeSort(array, begin, mid);
	mergeSort(array, mid + 1, end);
	merge(array, begin, mid, end);
}

// To heapify a subtree rooted with node i which is
// an index in array[]. n is size of heap
void heapify(int array[], int length, int i)
{
	int largest = i;	// Initialize largest as root
	int l = 2 * i + 1;	// left = 2*i + 1
	int r = 2 * i + 2;	// right = 2*i + 2

	// If left child is larger than root
	if (l < length && array[l] > array[largest]) largest = l;

	// If right child is larger than largest so far
	if (r < length && array[r] > array[largest]) largest = r;

	// If largest is not root
	if (largest != i) 
	{
		swap(array[i], array[largest]);
		// Recursively heapify the affected sub-tree
		heapify(array, length, largest);
	}
}

// main function to do heap sort
void heapSort(int array[], int length)
{
	// Build heap (rearrange array)
	for (int i = length / 2 - 1; i >= 0; i--)
		heapify(array, length, i);

	// One by one extract an element from heap
	for (int i = length - 1; i >= 0; i--) 
	{
		// Move current root to end
		swap(array[0], array[i]);

		// call max heapify on the reduced heap
		heapify(array, i, 0);
	}
}

void swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

int partition(int array[], int low, int high)
{
	int pivot = array[high];
	int i = (low - 1);

	for (int j = low; j <= high - 1; j++)
	{
		if (array[j] < pivot)
		{
			i++;
			swap(&array[i], &array[j]);
		}
	}
	swap(&array[i + 1], &array[high]);
	return (i + 1);
}

void quickSort(int array[], int low, int high)
{
	if (low < high)
	{
		int pi = partition(array, low, high);
		quickSort(array, low, pi - 1);
		quickSort(array, pi + 1, high);
	}
}

void printArray(int array[], int length)
{
	for (auto i = 0; i < length; i++)
		cout << array[i] << " ";
	cout << "\n";
}

void createArray(int array[], int length, int end)
{
	for (int i = 0; i < length; i++)
		array[i] = rand() % end;
}

void addElementsToArray(int array[], int start, int n, int end)
{
	for (int i = start; i < start + n; i++)
		array[i] = rand() % end;
}

int ErorCheck(float a)
{
	if (a <= 0 || (a - int(a) != 0))
	{
		cout << "\n * -------- * ПОМИЛКА * -------- * \n";
		cout << " Упс! Уведено не натуральне число! \n\n";
		return 0;
	}
	else return 1;
}

int FoundError() 
{
	cout << "\n    * -------- * ПОМИЛКА * -------- * \n";
	cout << " Неправильний варіант виконання програми!\n";
	return 0;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	cout << "\t * -------- * Комп'ютерний практикум 7 * -------- *\n";
	cout << "\t\t\t Бригада 10. Варіант 1  \n";
	cout << "     Реалізація алгоритмів сортування для великих обсягів даних\n\n";

	float length0, end0, addLength0;
	int i, length, end, varik = 0, partlySorted = 0, addLength, var;
	string partlySorted0, var0;

	cout << "\nСортувати скарби короля леприконів чи всіх родин гномів королівства? (0/1): ";
	cin >> var0;
	if (var0 == "0" || var0 == "1") var = atoi(var0.c_str());
	else return FoundError();

	if (!var) cout << "\nУ короля леприконів усього N скарбів\nN = ";
	else cout << "\nУ родин гномів усього N скарбів\nN = ";
	cin >> length0;
	ErorCheck(length0);
	length = int(length0);
	int* arr = new int[length];
	int* array = new int[length];

	cout << "\nМаксимальна вартість скарбу = ";
	cin >> end0;
	ErorCheck(end0);
	end = int(end0);
	createArray(arr, length, end);

	if (!var) 
	{
		cout << "\nВідсортувати скарби в державній скарбничці? (0/1): ";
		cin >> partlySorted0;
		if (partlySorted0 == "0" || partlySorted0 == "1") partlySorted = atoi(partlySorted0.c_str());
		else return FoundError();
	}

	if(!var) cout << "\nСкарби короля леприконів: \n";
	else cout << "\nСкарби всіх родин гномів: \n";
	printArray(arr, length);

	cout << "\n-----------Менюшка----------";
	cout << "\n0 - Сортування злиттям\n1 - Пірамідальне сортування\n2 - Швидке сортування";
	cout << "\n----------------------------";
	cout << "\nОберіть алгоритм сортування (0/1/2): ";
	cin >> varik;

	//float start = clock();

	switch (varik)
	{
	case 0:
		if (partlySorted == 0) cout << "\nСОРТУВАННЯ ЗЛИТТЯМ:";
		mergeSort(arr, 0, length - 1);
		break;
	case 1:
		if (partlySorted == 0) cout << "\nПІРАМІДАЛЬНЕ СОРТУВАННЯ:";
		heapSort(arr, length);
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
		cout << "\nУ гномів королівства ще N скарбів\nN = ";
		cin >> addLength0;

		ErorCheck(addLength0);
		addLength = int(addLength0);
		int* newArray = new int[length + addLength]();
		for (int i = 0; i < length; i++)
			newArray[i] = arr[i];

		addElementsToArray(newArray, length, addLength, end);
		cout << "\nНовий перелік скарбів: \n";
		printArray(newArray, length + addLength);

		//float start = clock();

		if (varik == 0)
		{
			cout << "\nСОРТУВАННЯ ЗЛИТТЯМ:";
			mergeSort(newArray, 0, length + addLength - 1);
		}
		else if (varik == 1)
		{
			cout << "\nПІРАМІДАЛЬНЕ СОРТУВАННЯ:";
			heapSort(newArray, length + addLength);
		}
		else
		{
			cout << "\nШВИДКЕ СОРТУВАННЯ:";
			quickSort(newArray, 0, length + addLength - 1);
		}

		//cout << (clock() - start) / CLOCKS_PER_SEC;

		cout << "\nПомічники короля надали упорядкований список скарбів: \n";
		printArray(newArray, length + addLength);
	}
	else
	{
		//cout << (clock() - start) / CLOCKS_PER_SEC;

		cout << "\nПомічники короля надали упорядкований список скарбів: \n";
		printArray(arr, length);
	}

	cout << "\n\n\n";
}