// Most basics copied and modified from https://www.geeksforgeeks.org/introduction-to-binary-search-tree-data-structure-and-algorithm-tutorials/

// C++ program to insert a node
// in a BST
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

double c = 0.75;

// Given Node
struct node
{
    int key;
    struct node* left, * right;
};

// Function to create a new BST node
node* newNode(int item)
{
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

// Recursive function to calculate the size of a given binary tree | from https://www.techiedelight.com/find-size-largest-bst-in-binary-tree/#:~:text=A%20simple%20solution%20is%20to%20traverse%20the%20binary,BST%20returned%20by%20the%20left%20and%20right%20subtrees.
int size(node* root)
{
    // base case: empty tree has size 0
    if (root == nullptr) {
        return 0;
    }

    // recursively calculate the size of the left and right subtrees and
    // return the sum of their sizes + 1 (for root node)
    return size(root->left) + 1 + size(root->right);
}

// checks if given node x has either child too big, and returns either true if so, else false
bool sizeCheck(struct node* x) {
    if (x != nullptr) {
        //cout << "Inspecting node with key value " << x->key << endl;
        if (x->left != nullptr && size(x->left) > (c * size(x))) {
            //cout << "Left child subtree at node value " << x->left->key << " is too big!" << endl;
            return true;
        }
        if (x->right != nullptr && size(x->right) > (c * size(x))) {
            //cout << "Right child subtree at node value " << x->right->key << " is too big!" << endl;
            return true;
        }
        else {
            //cout << "All good here" << endl;
            return false;
        }
    }
    else {
        //cout << "No such node" << endl;
        return false;
    }
}

// Taken from https://www.geeksforgeeks.org/convert-normal-bst-balanced-bst/
/* This function traverse the skewed binary tree and
   stores its nodes pointers in vector nodes[] */
void storeBSTNodes(node* root, vector<node*>& nodes)
{
    // Base case
    if (root == NULL)
        return;

    // Store nodes in Inorder (which is sorted
    // order for BST)
    storeBSTNodes(root->left, nodes);
    nodes.push_back(root);
    storeBSTNodes(root->right, nodes);
}

/* Recursive function to construct binary tree */
node* buildTreeUtil(vector<node*>& nodes, int start, int end)
{
    // base case
    if (start > end)
        return NULL;

    /* Get the middle element and make it root */
    int mid = (start + end) / 2;
    node* root = nodes[mid];

    /* Using index in Inorder traversal, construct
       left and right subtress */
    root->left = buildTreeUtil(nodes, start, mid - 1);
    root->right = buildTreeUtil(nodes, mid + 1, end);

    return root;
}

// This functions converts an unbalanced BST to
// a balanced BST
node* buildTree(node* root)
{
    // Store nodes of given BST in sorted order
    vector<node*> nodes;
    storeBSTNodes(root, nodes);

    // Constructs BST from nodes[]
    int n = nodes.size();
    return buildTreeUtil(nodes, 0, n - 1);
}


// Taken from https://www.geeksforgeeks.org/binary-search-tree-set-1-search-and-insertion/
// C function to search a given key in a given BST
node* search(node* root, int key)
{
    // Base Cases: root is null or key is present at root
    if (root == NULL || root->key == key)
        return root;

    // Key is greater than root's key
    if (root->key < key)
        return search(root->right, key);

    // Key is smaller than root's key
    return search(root->left, key);
}

void childCheck(node* x) {
    if (sizeCheck(x->left)) {
        x->left = buildTree(x->left);
    }
    if (sizeCheck(x->right)) {
        x->right = buildTree(x->right);
    }
}

// copy of search with sizeCheck in it, for use when inspecting an insertion path by 
// searching for the newly inserted key and scanning each node along the path for if
// their children are naughty and need to be checked.
node* searchPathSizeCheck(node* root, int key)
{
    if(sizeCheck(root->left) || sizeCheck(root->right)){
        childCheck(root);
        return root;
    }
    // Base Cases: root is null or key is present at root
    if (root == NULL || root->key == key)
        return root;

    // Key is greater than root's key
    if (root->key < key)
        return searchPathSizeCheck(root->right, key);

    // Key is smaller than root's key
    if (root->key > key) {
        return searchPathSizeCheck(root->left, key);
    }
}

// Function to insert a new node with
// given key in BST
node* insert(node* node, int key)
{
    // If the tree is empty, return a new node
    if (node == NULL)
        return newNode(key);

    // Otherwise, recur down the tree
    if (key < node->key)
    {
        node->left = insert(node->left, key);
    }
    else if (key > node->key)
    {
        node->right = insert(node->right, key);
    }
    // Return the node pointer
    return node;
}

// Function to do inorder traversal of BST, printing key and size at each node
void inorderPrint(struct node* root)
{
    if (root != NULL)
    {
        inorderPrint(root->left);
        cout << "key: " << root->key << " size: " << size(root) << endl;
        inorderPrint(root->right);
    }
}


// Driver Code
int main()
{

    /* Let us create following BST
              50
           /     \
          30      70
         /  \    /  \
       20   40  60   80
   */
    node* root = NULL;
    srand(time(0));
    int firstNum = rand() % 100;
    cout << "inserting random number 1: " << firstNum << endl;
    root = insert(root, firstNum);

    int i = 0;
    while (i < 299){
        int x = rand() % 10000;
        cout << "inserting random number " << i + 2 << ": " << x << endl;
        insert(root, x);
        if(sizeCheck(root)){
            root = buildTree(root);
        }
        else {
            searchPathSizeCheck(root, x);
        }
        i++;
    }
// example of manual insertion and checks
/*    // Inserting value 50
    root = insert(root, 50);
    searchPathSizeCheck(root, 50);

    // Inserting value 30
    insert(root, 30);
    searchPathSizeCheck(root, 30);

    // Inserting value 20
    insert(root, 20);
    searchPathSizeCheck(root, 20);

    // Inserting value 40
    insert(root, 40);
    searchPathSizeCheck(root, 40);

    // Inserting value 70
    insert(root, 70);
    searchPathSizeCheck(root, 70);

    // Inserting value 60
    insert(root, 60);
    searchPathSizeCheck(root, 60);

    // Inserting value 80
    insert(root, 80);
    searchPathSizeCheck(root, 80);

    //inserting even more shit
    insert(root, 90);
    searchPathSizeCheck(root, 90);
    insert(root, 100);
    searchPathSizeCheck(root, 100);
    insert(root, 110);
    searchPathSizeCheck(root, 110);
    insert(root, 5);
    searchPathSizeCheck(root, 5);
    insert(root, 105);
    searchPathSizeCheck(root, 105);
    insert(root, 10);
    searchPathSizeCheck(root, 10); */

    cout << endl;
    cout << "Current c value: " << c << endl;
    cout << endl;
    inorderPrint(root);
    return 0;
}