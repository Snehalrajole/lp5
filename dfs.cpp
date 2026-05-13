DFS

#include <iostream>
#include <stack>
#include <omp.h>

using namespace std;

// Tree Node Structure
struct Node
{
    int data;
    Node *left, *right;
};

// Insert node level-wise
Node* insert(Node* root, int data)
{
    if (!root)
    {
        root = new Node;
        root->data = data;
        root->left = root->right = NULL;

        return root;
    }

    // Queue for insertion
    Node* queue[100];

    int front = 0, rear = 0;

    queue[rear++] = root;

    while (front < rear)
    {
        Node* temp = queue[front++];

        // Insert left child
        if (!temp->left)
        {
            temp->left = new Node{data, NULL, NULL};

            return root;
        }
        else
        {
            queue[rear++] = temp->left;
        }

        // Insert right child
        if (!temp->right)
        {
            temp->right = new Node{data, NULL, NULL};

            return root;
        }
        else
        {
            queue[rear++] = temp->right;
        }
    }

    return root;
}

// Parallel DFS Traversal
void parallelDFS(Node* root)
{
    if (!root)
        return;

    stack<Node*> s;

    // Push root node
    s.push(root);

    cout << "\nParallel DFS Traversal: ";

    while (!s.empty())
    {
        // Get top node
        Node* curr = s.top();

        s.pop();

        // Print node
        cout << curr->data << " ";

        // Parallel processing of child nodes
        #pragma omp parallel sections
        {
            // Left child
            #pragma omp section
            {
                #pragma omp critical
                {
                    if (curr->left)
                        s.push(curr->left);
                }
            }

            // Right child
            #pragma omp section
            {
                #pragma omp critical
                {
                    if (curr->right)
                        s.push(curr->right);
                }
            }
        }
    }
}

// Main Function
int main()
{
    Node* root = NULL;

    int data;
    char ch;

    // Input tree nodes
    do
    {
        cout << "Enter data: ";
        cin >> data;

        root = insert(root, data);

        cout << "Add more nodes (y/n)? ";
        cin >> ch;

    } while (ch == 'y' || ch == 'Y');

    // Call DFS
    parallelDFS(root);

    return 0;
}