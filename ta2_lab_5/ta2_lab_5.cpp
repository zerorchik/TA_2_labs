#include <iostream>
#include <windows.h>
#include <vector>

using namespace std;

#define CMP_EQ(a, b) ((a) == (b))
#define CMP_LT(a, b) ((a) < (b))
#define CMP_GT(a, b) ((a) > (b))

class Node
{
public:
    Node* left; //a pointer to the root of the left subtree
    Node* right; //a pointer to the root of the right subtree
    int key;
    Node(int key) : key(key) { }
};

// build returns a pointer to the root Node of the sub-tree
// lower is the lower index of the array
// upper is the upper index of the array
Node* build(const vector<int>& arr, int lower, int upper)
{
    int size = upper - lower + 1;

    // base case: array of size zero
    if (size <= 0) return NULL;

    // recursive case
    int middle = size / 2 + lower;

    // make sure you add the offset of lower
    Node* subtreeRoot = new Node(arr[middle]);
    subtreeRoot->left = build(arr, lower, middle - 1);
    subtreeRoot->right = build(arr, middle + 1, upper);
    return subtreeRoot;
}

// For convenience, In-order printing a tree
void printTree(Node* root, const char* dir, int level)
{
    if (root)
    {
        cout << "рівень " << level << " " << dir << " =\t" << root->key << endl;
        printTree(root->left, "зліва", level + 1);
        printTree(root->right, "справа", level + 1);
    }
}

// For convenience, we create a right skewed BST.
// This BST will later be balanced.
Node* buildBSTfromSortedArr(int* arr, int n)
{
    if (n == 0) return nullptr;
    Node* root = new Node(arr[0]);

    Node* cur = root;
    for (int i = 1; i < n; i++)
    {
        cur->right = new Node(arr[i]);
        cur = cur->right;
    }
    return root;
}

// Convenience function for creating an array from BST in-order traversal
vector<int> createArrayFromTree(Node* root, vector<int> arr = vector<int>())
{
    if (root == nullptr) return arr;
    arr = createArrayFromTree(root->left, arr);
    arr.push_back(root->key);
    arr = createArrayFromTree(root->right, arr);
    return arr;
}

// Function for sorting an array
int* sortArray(int* arr, int n)
{
    for (int i = 0; i < n - 1; ++i)
        for (int j = 0; j < n - i - 1; ++j)
            if (arr[j] > arr[j + 1]) swap(arr[j], arr[j + 1]);
    return arr;
}

// Function for searching an element in tree by it's key value
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

bool IsAnElementOfAnArray(vector<int> arr, int element)
{
    for (int i = 0; i < arr.size(); i++)
        if (arr[i] == element) return true;
    return false;
}

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

/* Given a non-empty binary search tree, return the node
with minimum key value found in that tree. Note that the
entire tree does not need to be searched. */
Node* minValueNode(Node* node)
{
    Node* current = node;

    /* loop down to find the leftmost leaf */
    while (current && current->left != NULL)
        current = current->left;

    return current;
}

/* Given a binary search tree and a key, this function
deletes the key and returns the new root */
struct Node* deleteNode(Node* root, int key)
{
    // If the key to be deleted is
    // smaller than the root's
    // key, then it lies in left subtree
    if (key < root->key)
        root->left = deleteNode(root->left, key);

    // If the key to be deleted is
    // greater than the root's
    // key, then it lies in right subtree
    else if (key > root->key)
        root->right = deleteNode(root->right, key);

    // if key is same as root's key, then This is the node
    // to be deleted
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

        // node with two children: Get the inorder successor
        // (smallest in the right subtree)
        Node* temp = minValueNode(root->right);

        // Copy the inorder successor's content to this node
        root->key = temp->key;

        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

void callPrintTree(Node* newRoot)
{
    cout << "\n--------Карта скарбів-------" << endl << endl;
    printTree(newRoot, "початок", 0);
    cout << "\n----------------------------" << endl;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << "\t * -------- * Комп'ютерний практикум 5 * -------- *\n";
    cout << "\t\t\t Бригада 10. Варіант 1  \n";
    cout << "\t     Реалізація збалансованого бінарного дерева\n\n";

    int arr[] = { 12, 9, 14, 19, 17, 23, 54, 50, 76, 72, 67 };
    int n = 11, temp, tempRight, tempLeft, varik;
    string temp0;
    // Sort an array
    int* sortArr = sortArray(arr, n);

    // Build a right skewed tree
    Node* root = buildBSTfromSortedArr(sortArr, n);

    // Get the array from the tree
    vector<int> newArr = createArrayFromTree(root);

    // Make the skewed tree balanced
    Node* newRoot = build(newArr, 0, n - 1);

    // In-order printing to verify
    callPrintTree(newRoot);

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
        if (!IsAnElementOfAnArray(newArr, temp))
        {
            insert(&newRoot, temp);
            newArr = createArrayFromTree(newRoot);
            newRoot = build(newArr, 0, newArr.size() - 1);
            cout << "\nТрішечки магії і з'являється золото!" << endl;
            callPrintTree(newRoot);
        }
        // Define wether the element is reached
        varik = rand() % 2;
        if (varik == 0)
        {
            cout << "\nУпс! Тунель до печери обвалився, швидше, облиш золото, якщо хочеш жити!" << endl;
            deleteNode(newRoot, temp);
            newArr = createArrayFromTree(newRoot);
            newRoot = build(newArr, 0, newArr.size() - 1);
            callPrintTree(newRoot);
        }
        // If this element is reached
        else
        {
            Node* newTemp = getNodeByValue(newRoot, temp);

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