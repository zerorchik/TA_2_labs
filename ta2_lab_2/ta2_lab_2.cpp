#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>

using namespace std;

#define ICHAR 80  // Довжина рядку опису системи

const int MAX_E = (int)1e6;
const int MAX_V = (int)1e3;
const int INF = (int)1e9;

float numOfVertex1, numOfEdge1;             // кількість вершин, кількість ребер
float sourceVertex1, destinationVertex1;    // джерело, сток
int capacity[MAX_E];                        // пропускна здатність
int onEnd[MAX_E], nextEdge[MAX_E];          // кінець ребра, наступна вершина на черзі в список вершин M
int edgeCount, firstEdge[MAX_V];            // кількість вершин у списку М, початок списку вершин М
int visited[MAX_V];                         // маркер відвіданої вершини
int numOfVertex, numOfEdge;               
int sourceVertex, destinationVertex;

void addEdge(int u, int v, int cap) 
{
    // Пряме ребро - ребро, чий напрямок збігається з напрямком мережі
    onEnd[edgeCount] = v;                   // кінець прямого ребра = v
    nextEdge[edgeCount] = firstEdge[u];     // додаємо в початок списку для u
    firstEdge[u] = edgeCount;               // тепер початок списку = нове ребро
    capacity[edgeCount++] = cap;            // пропускна здатність

    // Обратное ребро - ребро, чий напрямок протилежний напрямку мережі
    onEnd[edgeCount] = u;                   // кінець зворотнього ребра = u
    nextEdge[edgeCount] = firstEdge[v];     // додаємо в початок списку для v
    firstEdge[v] = edgeCount;               // тепер початок списку = нове ребро
    capacity[edgeCount++] = 0;              // пропускна здатність
}

void ErorCheck(float a) 
{
    //Обмеження на вхідні дані
    if (a <= 0 || (a - int(a) != 0))
    {
        cout << "\n * -------- * ПОМИЛКА * -------- * \n";
        cout << "    Введено НЕ натуральне число! \n\n";
        exit(0);
    }
}

int findFlow(int u, int flow) 
{
    if (u == destinationVertex) 
        return flow; // повертаємо отриманий мінімум на ланцюгу
    visited[u] = true;
    for (int edge = firstEdge[u]; edge != -1; edge = nextEdge[edge]) 
    {
        int to = onEnd[edge];
        if (!visited[to] && capacity[edge] > 0) 
        {
            int minResult = findFlow(to, min(flow, capacity[edge])); // шукаємо потік у ланцюгу
            if (minResult > 0)                     // якщо знашли
            {                    
                capacity[edge] -= minResult;       // від прямих ребер віднімаєм потік
                capacity[edge ^ 1] += minResult;   // до зворотніх ребер додаємо
                return minResult;
            }
        }
    }
    return 0; // якщо не знашли потік з цієї вершини, повернемо 0
}

int main() 
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << "\t * -------- * Комп'ютерний практикум 2 * -------- *\n";
    cout << "\t\t\t Бригада 10. Варіант 2  \n";
    cout << "\t\t Реалізація алгоритму Форда-Фалкерсона\n\n";

    fill(firstEdge, firstEdge + MAX_V, -1);     // -1 означає, що ребра немає

    float read;
    char   desc[ICHAR];
    FILE* finput;

    finput = fopen("Ford-Falkerson.TXT", "r");
    if (finput == NULL)
    {
        cout << "Текстовий файл \"Ford-Falkerson.TXT\" НЕ знайдено!\n";
        return(-1);
    }
    // Відскануємо перший рядок файлу до 80 знаків
    fgets(desc, ICHAR, finput);

    // Зчитування кількості вершин
    fscanf(finput, "%f", &numOfVertex1);
    ErorCheck(numOfVertex1);
    numOfVertex = int(numOfVertex1);
    cout << "Кількість вершин = " << numOfVertex << endl;

    // Зчитування кількості ребер
    fscanf(finput, "%f", &numOfEdge1);
    ErorCheck(numOfEdge1);
    numOfEdge = int(numOfEdge1);
    cout << "Кількість ребер = " << numOfEdge << endl;

    // Зчитування джерела
    fscanf(finput, "%f", &sourceVertex1);
    ErorCheck(sourceVertex1);
    sourceVertex = int(sourceVertex1);
    cout << "\nДжерело - вершина № " << sourceVertex << endl;

    // Зчитування стоку
    fscanf(finput, "%f", &destinationVertex1);
    ErorCheck(destinationVertex1);
    destinationVertex = int(destinationVertex1);
    cout << "Сток - вершина № " << destinationVertex << endl;

    cout << "\nCписок ребер (початок, кінець, пропускна здатність):\n";
    for (float i = 0, u, v, cap; i < numOfEdge; i++) 
    {
        fscanf(finput, "%f%f%f", &u, &v, &cap);
        ErorCheck(u); ErorCheck(v); ErorCheck(cap);
        int u1 = int(u), v1 = int(v), cap1 = int(cap);
        addEdge(u, v, cap);
        cout << "e" << i + 1 << " = (" << u << ", " << v << ", " << cap << ")" << endl;
    }
    // Знаходження максимального потоку
    int maxFlow = 0;
    int iterationResult = 0;
    while ((iterationResult = findFlow(sourceVertex, INF)) > 0) 
    {
        fill(visited, visited + MAX_V, false);
        maxFlow += iterationResult;
    }
    // Виводимо максимальний потік
    cout << "\nМаксимальний потік мережі = ";
    cout << maxFlow << endl;
    cout << "\nМаксимальна кількість авто, що доїде до Музею  = ";
    cout << maxFlow * 400 << endl;
    return 0;
}