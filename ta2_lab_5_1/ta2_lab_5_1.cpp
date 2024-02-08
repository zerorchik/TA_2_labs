#include <iostream>
#include <windows.h>

using namespace std;

#define CMP_EQ(a, b) ((a) == (b))
#define CMP_LT(a, b) ((a) < (b))
#define CMP_GT(a, b) ((a) > (b))

class Node
{
public:
    Node* left;
    Node* right;
    int key;
    Node(int key) : key(key) { }
};

Node* getFreeNode(int key)
{
    Node* tmp = (Node*)malloc(sizeof(Node));
    tmp->left = tmp->right = NULL;
    tmp->key = key;
    return tmp;
}

void insert(Node** head, int value)
{
    Node* tmp = NULL;
    Node* ins = NULL;
    if (*head == NULL)
    {
        *head = getFreeNode(value);
        return;
    }

    tmp = *head;
    while (tmp)
    {
        if (CMP_GT(value, tmp->key))
        {
            if (tmp->right)
            {
                tmp = tmp->right;
                continue;
            }
            else
            {
                tmp->right = getFreeNode(value);
                return;
            }
        }
        else if (CMP_LT(value, tmp->key))
        {
            if (tmp->left)
            {
                tmp = tmp->left;
                continue;
            }
            else
            {
                tmp->left = getFreeNode(value);
                return;
            }
        }
        else exit(2);
    }
}

Node* getMaxNode(Node* root)
{
    while (root->right)
        root = root->right;
    return root;
}

Node* getNodeByValue(Node* root, int value)
{
    while (root)
    {
        if (CMP_GT(root->key, value))
        {
            root = root->left;
            continue;
        }
        else if (CMP_LT(root->key, value))
        {
            root = root->right;
            continue;
        }
        else return root;
    }
    return NULL;
}

Node* minValueNode(Node* node)
{
    Node* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

struct Node* deleteNode(Node* root, int key)
{
    if (key < root->key)
        root->left = deleteNode(root->left, key);

    else if (key > root->key)
        root->right = deleteNode(root->right, key);

    else {
        // node has no child
        if (root->left == NULL and root->right == NULL)
            return NULL;

        // node with only one child or no child
        else if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }

        // node with two children
        Node* temp = minValueNode(root->right);
        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

void printTree(Node* root, const char* dir, int level)
{
    if (root)
    {
        cout << "рівень " << level << " " << dir << " =\t" << root->key << endl;
        printTree(root->left, "зліва", level + 1);
        printTree(root->right, "справа", level + 1);
    }
}

bool IsAnElementOfTree(Node* root, int n, int element, bool answer)
{
    if (root && !answer)
    {
        if (root->key == element) 
        {
            answer = true;
            return answer;
        }
        answer = IsAnElementOfTree(root->left, n, element, answer);
        answer = IsAnElementOfTree(root->right, n, element, answer);
    }
    if (answer) return true;
    else return false;
}

void callPrintTree(Node* root)
{
    cout << "\n--------Карта скарбів-------" << endl << endl;
    printTree(root, "початок", 0);
    cout << "\n----------------------------" << endl;
}

void main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << "\t * -------- * Комп'ютерний практикум 5 * -------- *\n";
    cout << "\t\t\t Бригада 10. Варіант 1  \n";
    cout << "\t\t      Реалізація бінарного дерева\n\n";

    int arr[] = { 12, 9, 14, 19, 17, 23, 54, 50, 76, 72, 67 };
    int n = 11, temp, tempRight, tempLeft, varik;
    bool answer = false;
    string temp0;
    Node* root = NULL;

    for (int i = 0; i < n; i++)
        insert(&root, arr[i]);
    callPrintTree(root);

    while (true)
    {
        // Finding an element in tree
        cout << "\nЛеприкон хоче знайти N злитків золота\nN = ";
        cin >> temp0;
        if (atoi(temp0.c_str()) >= 1 && atoi(temp0.c_str()) <= 100) temp = atoi(temp0.c_str());
        else
        {
            cout << "\n----------Помилка-----------" << endl;
            cout << "\nНемає такої кількості злитків" << endl;
            cout << "\n----------------------------" << endl;
            continue;
        }

        // If there is no such element in the tree
        if (!IsAnElementOfTree(root, n, temp, answer))
        {
            insert(&root, temp);
            n++;
            cout << "\nТрішечки магії і з'являється золото!" << endl;
            callPrintTree(root);
        }
        // Define wether the element is reached
        varik = rand() % 2;
        if (varik == 0)
        {
            cout << "\nУпс! Тунель до печери обвалився, швидше, облиш золото, якщо хочеш жити!" << endl;
            deleteNode(root, temp);
            n--;
            callPrintTree(root);
        }
        // If this element is reached
        else
        {
            Node* newTemp = getNodeByValue(root, temp);

            // check on having the left brunch
            if (newTemp->left) tempLeft = newTemp->left->key;
            else tempLeft = 0;

            // check on having the right brunch
            if (newTemp->right) tempRight = newTemp->right->key;
            else tempRight = 0;
            cout << "\nУра! Леприкон знайшов " << newTemp->key << " злитків\n\tзліва від цієї печери " << tempLeft << " злитків\n\tсправа - " << tempRight << endl;
        }
    }
}