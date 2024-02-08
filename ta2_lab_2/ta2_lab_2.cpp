#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>

using namespace std;

#define ICHAR 80  // ������� ����� ����� �������

const int MAX_E = (int)1e6;
const int MAX_V = (int)1e3;
const int INF = (int)1e9;

float numOfVertex1, numOfEdge1;             // ������� ������, ������� �����
float sourceVertex1, destinationVertex1;    // �������, ����
int capacity[MAX_E];                        // ��������� ��������
int onEnd[MAX_E], nextEdge[MAX_E];          // ����� �����, �������� ������� �� ���� � ������ ������ M
int edgeCount, firstEdge[MAX_V];            // ������� ������ � ������ �, ������� ������ ������ �
int visited[MAX_V];                         // ������ ������� �������
int numOfVertex, numOfEdge;               
int sourceVertex, destinationVertex;

void addEdge(int u, int v, int cap) 
{
    // ����� ����� - �����, ��� �������� �������� � ��������� �����
    onEnd[edgeCount] = v;                   // ����� ������� ����� = v
    nextEdge[edgeCount] = firstEdge[u];     // ������ � ������� ������ ��� u
    firstEdge[u] = edgeCount;               // ����� ������� ������ = ���� �����
    capacity[edgeCount++] = cap;            // ��������� ��������

    // �������� ����� - �����, ��� �������� ����������� �������� �����
    onEnd[edgeCount] = u;                   // ����� ����������� ����� = u
    nextEdge[edgeCount] = firstEdge[v];     // ������ � ������� ������ ��� v
    firstEdge[v] = edgeCount;               // ����� ������� ������ = ���� �����
    capacity[edgeCount++] = 0;              // ��������� ��������
}

void ErorCheck(float a) 
{
    //��������� �� ����� ���
    if (a <= 0 || (a - int(a) != 0))
    {
        cout << "\n * -------- * ������� * -------- * \n";
        cout << "    ������� �� ���������� �����! \n\n";
        exit(0);
    }
}

int findFlow(int u, int flow) 
{
    if (u == destinationVertex) 
        return flow; // ��������� ��������� ����� �� �������
    visited[u] = true;
    for (int edge = firstEdge[u]; edge != -1; edge = nextEdge[edge]) 
    {
        int to = onEnd[edge];
        if (!visited[to] && capacity[edge] > 0) 
        {
            int minResult = findFlow(to, min(flow, capacity[edge])); // ������ ���� � �������
            if (minResult > 0)                     // ���� ������
            {                    
                capacity[edge] -= minResult;       // �� ������ ����� ������ ����
                capacity[edge ^ 1] += minResult;   // �� �������� ����� ������
                return minResult;
            }
        }
    }
    return 0; // ���� �� ������ ���� � ���� �������, ��������� 0
}

int main() 
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << "\t * -------- * ����'������� ��������� 2 * -------- *\n";
    cout << "\t\t\t ������� 10. ������ 2  \n";
    cout << "\t\t ��������� ��������� �����-����������\n\n";

    fill(firstEdge, firstEdge + MAX_V, -1);     // -1 ������, �� ����� ����

    float read;
    char   desc[ICHAR];
    FILE* finput;

    finput = fopen("Ford-Falkerson.TXT", "r");
    if (finput == NULL)
    {
        cout << "��������� ���� \"Ford-Falkerson.TXT\" �� ��������!\n";
        return(-1);
    }
    // ³�������� ������ ����� ����� �� 80 �����
    fgets(desc, ICHAR, finput);

    // ���������� ������� ������
    fscanf(finput, "%f", &numOfVertex1);
    ErorCheck(numOfVertex1);
    numOfVertex = int(numOfVertex1);
    cout << "ʳ������ ������ = " << numOfVertex << endl;

    // ���������� ������� �����
    fscanf(finput, "%f", &numOfEdge1);
    ErorCheck(numOfEdge1);
    numOfEdge = int(numOfEdge1);
    cout << "ʳ������ ����� = " << numOfEdge << endl;

    // ���������� �������
    fscanf(finput, "%f", &sourceVertex1);
    ErorCheck(sourceVertex1);
    sourceVertex = int(sourceVertex1);
    cout << "\n������� - ������� � " << sourceVertex << endl;

    // ���������� �����
    fscanf(finput, "%f", &destinationVertex1);
    ErorCheck(destinationVertex1);
    destinationVertex = int(destinationVertex1);
    cout << "���� - ������� � " << destinationVertex << endl;

    cout << "\nC����� ����� (�������, �����, ��������� ��������):\n";
    for (float i = 0, u, v, cap; i < numOfEdge; i++) 
    {
        fscanf(finput, "%f%f%f", &u, &v, &cap);
        ErorCheck(u); ErorCheck(v); ErorCheck(cap);
        int u1 = int(u), v1 = int(v), cap1 = int(cap);
        addEdge(u, v, cap);
        cout << "e" << i + 1 << " = (" << u << ", " << v << ", " << cap << ")" << endl;
    }
    // ����������� ������������� ������
    int maxFlow = 0;
    int iterationResult = 0;
    while ((iterationResult = findFlow(sourceVertex, INF)) > 0) 
    {
        fill(visited, visited + MAX_V, false);
        maxFlow += iterationResult;
    }
    // �������� ������������ ����
    cout << "\n������������ ���� ����� = ";
    cout << maxFlow << endl;
    cout << "\n����������� ������� ����, �� ���� �� �����  = ";
    cout << maxFlow * 400 << endl;
    return 0;
}