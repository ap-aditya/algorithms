#include <bits/stdc++.h>
using namespace std;

template <typename T>
class Node
{
public:
    T key;
    Node *left;
    Node *right;
    int height;

    Node(T k) : key(k), left(nullptr), right(nullptr), height(1) {}
};

template <typename T>
class AVLTree
{
private:
    Node<T> *root;

    int getHeight(Node<T> *node)
    {
        return node ? node->height : 0;
    }

    int getBalanceFactor(Node<T> *node)
    {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    void updateHeight(Node<T> *node)
    {
        if (node)
        {
            node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        }
    }

    Node<T> *rightRotate(Node<T> *y)
    {
        Node<T> *x = y->left;
        Node<T> *T2 = x->right;
        x->right = y;
        y->left = T2;
        updateHeight(y);
        updateHeight(x);
        return x;
    }

    Node<T> *leftRotate(Node<T> *x)
    {
        Node<T> *y = x->right;
        Node<T> *T2 = y->left;
        y->left = x;
        x->right = T2;
        updateHeight(x);
        updateHeight(y);
        return y;
    }

    Node<T> *findMin(Node<T> *node)
    {
        while (node && node->left)
        {
            node = node->left;
        }
        return node;
    }

    Node<T> *findMax(Node<T> *node)
    {
        while (node && node->right)
        {
            node = node->right;
        }
        return node;
    }

    Node<T> *rotate(Node<T> *node)
    {
        if (getBalanceFactor(node) > 1)
        {
            if (getBalanceFactor(node->left) < 0)
            {
                node->left = leftRotate(node->left);
            }
            return rightRotate(node);
        }
        if (getBalanceFactor(node) < -1)
        {
            if (getBalanceFactor(node->right) > 0)
            {
                node->right = rightRotate(node->right);
            }
            return leftRotate(node);
        }
        updateHeight(node);
        return node;
    }

    Node<T> *insertHelper(Node<T> *node, T key)
    {
        if (!node)
        {
            return new Node<T>(key);
        }

        if (key < node->key)
        {
            node->left = insertHelper(node->left, key);
        }
        else if (key > node->key)
        {
            node->right = insertHelper(node->right, key);
        }
        else
        {
            return node; // Duplicates not allowed
        }

        return rotate(node);
    }

    Node<T> *deleteHelper(Node<T> *node, T key)
    {
        if (!node)
        {
            return node;
        }

        if (key < node->key)
        {
            node->left = deleteHelper(node->left, key);
        }
        else if (key > node->key)
        {
            node->right = deleteHelper(node->right, key);
        }
        else
        {
            // Node with no child
            if (node->left == nullptr && node->right == nullptr)
            {
                delete node;
                return nullptr;
            }
            // Node with one child
            else if (node->left == nullptr || node->right == nullptr)
            {
                Node<T> *temp = node->left ? node->left : node->right;
                delete node;
                return temp;
            }
            else
            {
                // Node with two children
                Node<T> *temp = findMin(node->right);
                node->key = temp->key;
                node->right = deleteHelper(node->right, temp->key);
            }
        }

        return rotate(node);
    }

    bool searchHelper(Node<T> *node, T key)
    {
        if (!node)
            return false;
        if (node->key == key)
            return true;

        return key < node->key ? searchHelper(node->left, key) : searchHelper(node->right, key);
    }

    int countNodesHelper(Node<T> *node)
    {
        if (!node)
            return 0;
        return 1 + countNodesHelper(node->left) + countNodesHelper(node->right);
    }

    void clearHelper(Node<T> *node)
    {
        if (node)
        {
            clearHelper(node->left);
            clearHelper(node->right);
            delete node;
        }
    }

    void inorderHelper(Node<T> *node, vector<T> &result)
    {
        if (node)
        {
            inorderHelper(node->left, result);
            result.push_back(node->key);
            inorderHelper(node->right, result);
        }
    }

    // Range query helper
    void rangeQueryHelper(Node<T> *node, T low, T high, vector<T> &result)
    {
        if (!node)
            return;

        if (node->key >= low && node->key <= high)
        {
            result.push_back(node->key);
        }

        if (node->key > low)
        {
            rangeQueryHelper(node->left, low, high, result);
        }

        if (node->key < high)
        {
            rangeQueryHelper(node->right, low, high, result);
        }
    }

public:
    AVLTree() : root(nullptr) {}

    ~AVLTree()
    {
        clear();
    }

    void insert(T key)
    {
        root = insertHelper(root, key);
    }

    void remove(T key)
    {
        root = deleteHelper(root, key);
    }

    bool search(T key)
    {
        return searchHelper(root, key);
    }

    bool empty()
    {
        return root == nullptr;
    }

    int height()
    {
        return getHeight(root);
    }

    int size()
    {
        return countNodesHelper(root);
    }

    T findMin()
    {
        if (!root)
            throw runtime_error("Tree is empty");
        return findMin(root)->key;
    }

    T findMax()
    {
        if (!root)
            throw runtime_error("Tree is empty");
        return findMax(root)->key;
    }

    void clear()
    {
        clearHelper(root);
        root = nullptr;
    }

    vector<T> inorderTraversal()
    {
        vector<T> result;
        inorderHelper(root, result);
        return result;
    }

    // Range query: get all elements between low and high (inclusive)
    vector<T> rangeQuery(T low, T high)
    {
        vector<T> result;
        rangeQueryHelper(root, low, high, result);
        sort(result.begin(), result.end());
        return result;
    }

    // Count elements in range [low, high]
    int countInRange(T low, T high)
    {
        vector<T> elements = rangeQuery(low, high);
        return elements.size();
    }
};

// Comprehensive example usage with different data types
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "=== Generic AVL Tree Demo ===" << endl;

    // Test with integers
    cout << "\n1. Testing with integers:" << endl;
    AVLTree<int> intAVL;
    vector<int> intData = {50, 30, 70, 20, 40, 60, 80, 10, 25};

    for (int x : intData)
    {
        intAVL.insert(x);
    }

    cout << "Inserted: ";
    for (int x : intData)
        cout << x << " ";
    cout << "\nSorted: ";
    vector<int> intSorted = intAVL.inorderTraversal();
    for (int x : intSorted)
        cout << x << " ";
    cout << "\nHeight: " << intAVL.height() << ", Size: " << intAVL.size() << endl;

    cout << "Min: " << intAVL.findMin() << ", Max: " << intAVL.findMax() << endl;
    cout << "Search 40: " << (intAVL.search(40) ? "Found" : "Not Found") << endl;

    // Test range query
    vector<int> range = intAVL.rangeQuery(25, 60);
    cout << "Range [25, 60]: ";
    for (int x : range)
        cout << x << " ";
    cout << endl;

    // Test deletion
    intAVL.remove(30);
    intAVL.remove(70);
    cout << "After deleting 30, 70: ";
    intSorted = intAVL.inorderTraversal();
    for (int x : intSorted)
        cout << x << " ";
    cout << "\nNew height: " << intAVL.height() << endl;

    // Test with doubles
    cout << "\n2. Testing with doubles:" << endl;
    AVLTree<double> doubleAVL;
    vector<double> doubleData = {3.14, 2.71, 1.41, 4.20, 2.50, 3.50};

    for (double x : doubleData)
    {
        doubleAVL.insert(x);
    }

    cout << "Inserted: ";
    for (double x : doubleData)
        cout << fixed << setprecision(2) << x << " ";
    cout << "\nSorted: ";
    vector<double> doubleSorted = doubleAVL.inorderTraversal();
    for (double x : doubleSorted)
        cout << fixed << setprecision(2) << x << " ";
    cout << "\nHeight: " << doubleAVL.height() << endl;

    // Test with strings
    cout << "\n3. Testing with strings:" << endl;
    AVLTree<string> stringAVL;
    vector<string> stringData = {"apple", "banana", "cherry", "date", "elderberry", "fig"};

    for (const string &s : stringData)
    {
        stringAVL.insert(s);
    }

    cout << "Inserted: ";
    for (const string &s : stringData)
        cout << s << " ";
    cout << "\nSorted: ";
    vector<string> stringSorted = stringAVL.inorderTraversal();
    for (const string &s : stringSorted)
        cout << s << " ";
    cout << "\nHeight: " << stringAVL.height() << endl;

    cout << "Search 'cherry': " << (stringAVL.search("cherry") ? "Found" : "Not Found") << endl;
    cout << "Min: " << stringAVL.findMin() << ", Max: " << stringAVL.findMax() << endl;

    // Test with characters
    cout << "\n4. Testing with characters:" << endl;
    AVLTree<char> charAVL;
    vector<char> charData = {'m', 'a', 'z', 'b', 'y', 'c', 'x'};

    for (char c : charData)
    {
        charAVL.insert(c);
    }

    cout << "Inserted: ";
    for (char c : charData)
        cout << c << " ";
    cout << "\nSorted: ";
    vector<char> charSorted = charAVL.inorderTraversal();
    for (char c : charSorted)
        cout << c << " ";
    cout << "\nHeight: " << charAVL.height() << endl;

    return 0;
}
