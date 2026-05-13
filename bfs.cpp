BFS


#include <iostream>
#include <queue>
#include <omp.h>

using namespace std;

// Tree Node Structure
struct Node {
    int data;
    Node *left, *right;
};

// Insert node level-wise
Node* insert(Node* root, int data) {

    if (!root) {
        root = new Node;
        root->data = data;
        root->left = root->right = NULL;
        return root;
    }

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {

        Node* temp = q.front();
        q.pop();

        // Insert left child
        if (!temp->left) {
            temp->left = new Node{data, NULL, NULL};
            return root;
        }
        else {
            q.push(temp->left);
        }

        // Insert right child
        if (!temp->right) {
            temp->right = new Node{data, NULL, NULL};
            return root;
        }
        else {
            q.push(temp->right);
        }
    }

    return root;
}

// Parallel BFS Traversal
void bfs(Node* root) {

    if (!root)
        return;

    queue<Node*> q;
    q.push(root);

    cout << "\nParallel BFS Traversal:\n";

    while (!q.empty()) {

        int size = q.size();

        #pragma omp parallel for
        for (int i = 0; i < size; i++) {

            Node* curr = NULL;

            // Critical section for queue access
            #pragma omp critical
            {
                if (!q.empty()) {
                    curr = q.front();
                    q.pop();

                    cout << curr->data << " ";
                }
            }

            // Push child nodes
            if (curr != NULL) {

                #pragma omp critical
                {
                    if (curr->left)
                        q.push(curr->left);

                    if (curr->right)
                        q.push(curr->right);
                }
            }
        }
    }
}

// Main Function
int main() {

    Node* root = NULL;

    int data;
    char ch;

    do {
        cout << "Enter data: ";
        cin >> data;

        root = insert(root, data);

        cout << "Add more nodes (y/n)? ";
        cin >> ch;

    } while (ch == 'y' || ch == 'Y');

    bfs(root);

    return 0;
}