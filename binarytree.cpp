#include <iostream>
#include <cstring>

using namespace std;

struct node {
  int data;
  node* parent;
  node* left;
  node* right;
};

void add(node* head, node* n);
node* search(node* head, int k);
void remove(node* head, node* n);

int main() {
  node* head = NULL;
  char action[10];
  int input;
  while (true) {
    cout << "What do you want to do? (ADD, DELETE, PRINT, SEARCH, QUIT) "; cin \
>> action;
    if (strcmp(action, "ADD") == 0 || strcmp(action, "add") == 0) {
      cout << "Enter the number to add: "; cin >> input;
      node* n = new node();
      n->data = input;
      n->parent = NULL;
      n->left = NULL;
      n->right = NULL;
      if (head == NULL) {
        head = n;
      }
      else {
        add(head, n);
      }
      // cout << head->data << endl;
    }
    else if (strcmp(action, "SEARCH") == 0 || strcmp(action, "search") == 0) {
      cout << "Enter the number to search for: "; cin >> input;
      if (search(head, input) != NULL) {
        cout << "Yes, that is in the tree." << endl;
      }
      else {
        cout << "No, that ain't in the tree." << endl;
      }
    }

    else if (strcmp(action, "DELETE") == 0 || strcmp(action, "delete") == 0) {
      cout << "Enter the number to delete: "; cin >> input;
      node* n = search(head, input);
      if (n == NULL) {
	cout << "That number isn't in the tree!" << endl;
      }
      else {
	remove(head, n);
      }
    }
    else if (strcmp(action, "QUIT") == 0 || strcmp(action, "quit") == 0) {
      break;
    }
    cout << endl;
  }
  return 0;
}

void add(node* head, node* n) {

  if (head->data >= n->data) {
    if (head->left == NULL) {
      head->left = n;
      n->parent = head;
    }
    else {
      add(head->left, n);
    }
  }

  else if (head->data < n->data) {
    if (head->right == NULL) {
      head->right = n;
      n->parent = head;
    }
    else {
      add(head->right, n);
    }
  }
}

node* search(node* head, int k) {
  if (head == NULL) {
    return NULL;
  }

  else if (head->data == k) {
    return head;
  }

  else if (head->data > k) {
    return search(head->left, k); // switch back to left
  }

  else {
    return search(head->right, k); // switch back to right
  }
}

void remove(node* head, node* n) {
  if (n->left == NULL && n->right == NULL) { // no children
    if (head == n) {
      head = NULL;
      delete n;
    }
    else if (n->parent->left == n) {
      n->parent->left = NULL;
      delete n;
    }
    else if (n->parent->right == n) {
      n->parent->right = NULL;
      delete n;
    }
  }
	
  else if (n->left == NULL) {
    if (head == n) {
      head = n->right;
      head->parent = NULL;
      delete n;
    }
    else if (n->parent->left == n) {
      n->parent->left = n->right;
      n->right->parent = n->parent;
    }
    else if (n->parent->right == n) {
      n->parent->right = n->right;
      n->right->parent = n->parent;
    }
  }
	
  else if (n->right == NULL) {
    if (head == n) {
      head = n->left;
      head->parent = NULL;
      delete n;
    }
    else if (n->parent->left == n) {
      n->parent->left = n->left;
      n->left->parent = n->parent;
    }
    else if (n->parent->right == n) {
      n->parent->right = n->left;
      n->left->parent = n->parent;
    }
  }

  else { // has both left and right
  }
}
