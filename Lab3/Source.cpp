// copied and modified from https://www.geeksforgeeks.org/introduction-to-binary-search-tree-data-structure-and-algorithm-tutorials/

// C++ program to insert a node
// in a BST
#include <iostream>
#include <cmath>
using namespace std;

int c = 0.55;

// Given Node
struct node
{
    int key;
    int size;
    struct node* left, * right;
};

// Function to create a new BST node
struct node* newNode(int item)
{
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->key = item;
    temp->size = 1;
    temp->left = temp->right = NULL;
    return temp;
}

// Function to insert a new node with
// given key in BST
struct node* insert(struct node* node, int key)
{

    // If the tree is empty, return a new node
    if (node == NULL)
        return newNode(key);

    // Otherwise, recur down the tree
    if (key < node->key)
    {
        node->size++;
        node->left = insert(node->left, key);
    }
    else if (key > node->key)
    {
        node->size++;
        node->right = insert(node->right, key);
    }

    // Return the node pointer
    return node;
}

// Function to do inorder traversal of BST, printing keys and size at each node
void inorderPrint(struct node* root)
{
    if (root != NULL)
    {
        inorderPrint(root->left);
        cout << "key: " << root->key << " size: " << root->size << endl;
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
    struct node* root = NULL;

    // Inserting value 50
    root = insert(root, 50);

    // Inserting value 30
    insert(root, 30);

    // Inserting value 20
    insert(root, 20);

    // Inserting value 40
    insert(root, 40);

    // Inserting value 70
    insert(root, 70);

    // Inserting value 60
    insert(root, 60);

    // Inserting value 80
    insert(root, 80);

    // Print the BST
    inorderPrint(root);

    return 0;
}

// This code is contributed by shubhamsingh10