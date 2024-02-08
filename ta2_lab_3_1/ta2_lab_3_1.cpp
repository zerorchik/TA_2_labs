#include <iostream>
#include <ctime>
#include <windows.h>
using namespace std;

typedef int Data;
#define N 10

struct Stack 
{
    Data* a;                // �������� �� �������� ������� ���'��� �� �������� �����
    unsigned int size;      // ������� ��������, �� �� ������� ���'���
    unsigned int n;         // ������� ��������, �� ������ ����
};

void stack_init(struct Stack* s) 
{
    s->n = 0;               // ������ ����
    s->size = N;            // ��'���� N ��������
    s->a = (Data*)malloc(s->size * sizeof(Data));
}

void stack_print(struct Stack* s)
{
    cout << "\n----------����----------" << endl;
    if (s->n == 0) cout << "���� ������!";
    for (int i = 0; i < s->n; i++)
        cout << s->a[i] << " ";
    cout << endl;
}

void stack_push(struct Stack* s, Data data) 
{
    // ���� ���� ������, ������� ������� ���'��� �� 10 ��������
    if (s->n == s->size) {
        s->size += N;
        s->a = (Data*)realloc(s->a, s->size * sizeof(Data));
    }
    s->a[s->n] = data;
    s->n++;
}

void stack_pop(struct Stack* s)
{
    cout << "\n---������� ��������----" << endl;
    for (int i = 0; i < 3; i++)
    {
        if (s->n == 0) break;
        cout << s->a[s->n - 1] << " ";
        s->n--;
    }
    cout << endl;
    stack_print(s);
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int num;
    struct Stack st;
    stack_init(&st);

    cout << "\t * -------- * ����'������� ��������� 3 * -------- *\n";
    cout << "\t\t\t ������� 10. ������ 5  \n";
    cout << "\t ��������� ��� ����� �� ��������� ��������� ������\n\n";

    cout << "������ ������� �������� �����: ";
    cin >> num;

    for (int i = 0; i < num; i++)
        stack_push(&st, rand() % 100);

    stack_print(&st);
    while (st.n != 0)
        stack_pop(&st);

    cout << endl;
    return 0;
}