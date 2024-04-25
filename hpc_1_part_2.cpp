#include <iostream>
#include <vector>
#include <stack>
#include <omp.h>

using namespace std;

struct Node {
    int value;
    vector<Node*> children;
};

void dfs(Node* node, int depth) {
    if (node == nullptr) return;
    cout << node->value << " (Depth: " << depth << ")" << endl;
    #pragma omp parallel for
    for (size_t i = 0; i < node->children.size(); ++i) {
        dfs(node->children[i], depth + 1); // Pass depth + 1 to the recursive call
    }
}

void deleteNodes(Node* node) {
    if (node == nullptr) return;
    for (Node* child : node->children) {
        deleteNodes(child);
    }
    delete node;
}

int main() {
    Node* root = nullptr;
    stack<Node*> nodes;
    char choice;

    do {
        cout << "Enter data for the next node: ";
        int data;
        cin >> data;
        Node* newNode = new Node{data};

        if (root == nullptr) {
            root = newNode;
            nodes.push(root);
        } else {
            Node* current = nodes.top();
            current->children.push_back(newNode);
            nodes.push(newNode);
        }

        cout << "Do you want to insert one more node? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    cout << "DFS traversal result with depth information: " << endl;
    dfs(root, 0);

    // Clean up memory
    deleteNodes(root);

    return 0;
}
