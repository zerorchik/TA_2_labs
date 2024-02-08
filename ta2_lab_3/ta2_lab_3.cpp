#include <iostream>
#include <ctime>
#include <windows.h>
using namespace std;

typedef int Data;
#define N 10
Data a[N];

struct Stack 
{
    Data a[N];   // �������� �����
    int n;       // �� �������
};

bool stack_empy(struct Stack* s)
{
    if (s->n == 0) return true;
    else return false;
}

void stack_print(struct Stack* s) 
{
    cout << "\n----------����----------" << endl;
    if (stack_empy(s)) cout << "���� ������!";
    for (int i = 0; i < s->n; i++) 
        cout << s->a[i] << " ";
    cout << endl;
}

void stack_push(struct Stack* s, Data data) 
{
    s->a[s->n] = data;
    s->n++;
}

void stack_pop(struct Stack* s)
{
    cout << "\n---������� ��������----" << endl;
    for (int i = 0; i < 3; i++) 
    {
        if (stack_empy(s)) break;
        cout << s->a[s->n - 1] << " ";
        s->n--;
    }
    cout << endl;
    stack_print(s);
}

void stack_init(struct Stack* s) 
{
    s->n = 0;
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
    while (!stack_empy(&st))
        stack_pop(&st);

    cout << endl;
    return 0;
}