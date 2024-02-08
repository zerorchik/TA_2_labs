#include <iostream>
#include <string>
#include <windows.h>
#include <random>

#define CONST_M 29      // ������ ����� - ��������� � ����������� ��� ��������
#define CONST_C 0.33    // ��������� � ��� ��������� ���������

using namespace std;

// ���� ��������
class Student
{
public:
    Student* next;      // �� ����� ���糿 �������� ������� ������ ������� � ������'����� ������
    string name;
    string surname;
    string age;
    int hash;

    // ����������� ��������
    Student(string name, string surname, string age, int hash)
    {
        this->name = name;
        this->surname = surname;
        this->age = age;
        this->hash = hash;
        this->next = NULL;
    }

    // ��������� �������� (����������� ���� return 0)
    ~Student()
    {
        cout << "* Delete " << this->surname << " *" << endl;
        if (this->next != NULL)
            delete this->next;
    }
};

// ���-�������, ������������ � ������ ������ (����� ������� ������ ���� ���� �������)
class HashTable
{
    Student* table[CONST_M];

    // ���-������� ������ 
    // ���� ���� ASCII ����, ����� �� �� ��������� � � ������ ������ �� ������
    static int hashDivision(string str)
    {
        int asciSum = GetASCII(str);
        return asciSum % CONST_M;
    }

    // ���-������� �������� 
    // ���� ���� ASCII ����, ������� �� �� ��������� �, ������ ���� �������, ������� ��������� �� ��������� � � ������ ������� �������
    static int hashMultiplication(string str)
    {
        int asciSum = GetASCII(str);
        return (int)(CONST_M * ((asciSum * CONST_C) - (int)(asciSum * CONST_C)));
    }

    static int GetASCII(string str)
    {
        int asciSum = 0;
        for (int i = 0; i < str.length(); i++)
            asciSum += str[i];
        return asciSum;
    }

public:
    // ����������� �������
    HashTable()
    {
        for (int i = 0; i < CONST_M; i++)
            table[i] = NULL;
    }

    // ��������� ������� (����������� ���� return 0)
    ~HashTable()
    {
        cout << "\n* Delete table *" << endl << endl;
        for (int i = 0; i < CONST_M; i++)
            delete table[i];
    }

    // �������� ������� ������� � ������� � �������� ���� ����� �� ��� ����� 
    void push(string name, string surname, string age, int type)
    {
        int hashNumber = FindHashNumber(surname, type);
        Student* pers = new Student(name, surname, age, hashNumber);
        Student* place = table[hashNumber];

        cout << pers->surname << " (#" << pers->hash << ")" << endl;

        if (place == NULL)
        {
            table[hashNumber] = pers;
            return;
        }

        while (place->next != NULL)
            place = place->next;
        place->next = pers;
    }

    // ������ �������� � ������� �� ���� ���볿
    Student* find(string surname, int type)
    {
        int hashNumber = FindHashNumber(surname, type);
        Student* result = table[hashNumber];
        if (!result)
        {
            cout << "Student not found!" << endl;
            return NULL;
        }
        while (result->surname != surname)
        {
            if (!result->next)
            {
                cout << "Student not found!" << endl;
                return NULL;
            }
            result = result->next;
        }
        return result;
    }

    static int FindHashNumber(string surname, int type)
    {
        int hashNumber;
        switch (type)
        {
        case 0:
            hashNumber = hashDivision(surname);
            break;
        case 1:
            hashNumber = hashMultiplication(surname);
            break;
        }
        return hashNumber;
    }
};

int main()
{
    HashTable newTable;
    string type0;
    int type;

    cout << "\t * -------- * Computer Workshop 4 * -------- * " << endl;
    cout << "\t\t     Brigade 10. Variant 1 " << endl;
    cout << "\t\t\t Open hashing " << endl << endl;

    cout << "------------Menu------------" << endl;
    cout << " 0 - realised on division" << endl;
    cout << " 1 - realised on multiplication" << endl;
    cout << "----------------------------" << endl;
    cout << "Choose hash-function (0/1): ";
    cin >> type0;
    if (type0 != "0" && type0 != "1")
    {
        cout << "\n-----------Error------------" << endl;
        cout << "\nNo such type" << endl;
        cout << "\n----------------------------" << endl;
        return 0;
    }
    type = atoi(type0.c_str());     // ����������� string � int

    cout << "\n----------Students----------" << endl << endl;

    newTable.push("Sofiia", "Pavlova", "04.03.2004", type);
    newTable.push("Valeria", "Ryabenko", "03.09.2003", type);
    newTable.push("Sofiia", "Hohol", "13.09.2004", type);
    newTable.push("Anna", "Gonchar", "04.11.2004", type);
    newTable.push("Kate", "Kolomoychenko", "03.12.2003", type);
    newTable.push("Kate", "Boyko", "07.12.2003", type);
    newTable.push("Amaliya", "Pavlenko", "07.01.2004", type);
    newTable.push("Tanya", "Guseva", "23.01.2004", type);
    newTable.push("Mariia", "Krushinska", "27.01.2004", type);
    newTable.push("Lisa", "Djhioeva", "17.03.2004", type);
    newTable.push("Kate", "Melnicova", "28.03.2004", type);

    string studentName;
    cout << "\nEnter student's surname to find her date of birth: ";
    cin >> studentName;
    cout << "\n-----------Result-----------" << endl << endl;
    Student* search = newTable.find(studentName, type);
    if (search)
        cout << search->name << " " << search->surname << " - " << search->age << endl;
    cout << "\n----------------------------" << endl;

    return 0;
}