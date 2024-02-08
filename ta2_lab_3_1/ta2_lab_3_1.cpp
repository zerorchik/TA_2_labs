#include <iostream>
#include <ctime>
#include <windows.h>
using namespace std;

typedef int Data;
#define N 10

struct Stack 
{
    Data* a;                // покажчик на динамічно виділену пам'ять під елементи стеку
    unsigned int size;      // кількість елементів, на які виділена пам'ять
    unsigned int n;         // кількість елементів, що зберігає стек
};

void stack_init(struct Stack* s) 
{
    s->n = 0;               // пустий стек
    s->size = N;            // об'ємом N елементів
    s->a = (Data*)malloc(s->size * sizeof(Data));
}

void stack_print(struct Stack* s)
{
    cout << "\n----------Стек----------" << endl;
    if (s->n == 0) cout << "Стек пустий!";
    for (int i = 0; i < s->n; i++)
        cout << s->a[i] << " ";
    cout << endl;
}

void stack_push(struct Stack* s, Data data) 
{
    // якщо стек повний, потрібно виділити пам'ять на 10 елементів
    if (s->n == s->size) {
        s->size += N;
        s->a = (Data*)realloc(s->a, s->size * sizeof(Data));
    }
    s->a[s->n] = data;
    s->n++;
}

void stack_pop(struct Stack* s)
{
    cout << "\n---Видалені елементи----" << endl;
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

    cout << "\t * -------- * Комп'ютерний практикум 3 * -------- *\n";
    cout << "\t\t\t Бригада 10. Варіант 5  \n";
    cout << "\t Реалізація АТД Стеку за допомогою динамічних масивів\n\n";

    cout << "Уведіть кількість елементів стеку: ";
    cin >> num;

    for (int i = 0; i < num; i++)
        stack_push(&st, rand() % 100);

    stack_print(&st);
    while (st.n != 0)
        stack_pop(&st);

    cout << endl;
    return 0;
}