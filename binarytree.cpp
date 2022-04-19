#include <iostream>
#include <cstring>

using namespace std;

struct node {
  int data;
  node* left;
  node* right;
};

void add(node* head, node* n);
bool search(node* head, int k);

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
      if (head == NULL) {
        head = n;
      }
      else {
        add(head, n);
      }
    }
    else if (strcmp(action, "SEARCH") == 0 || strcmp(action, "search") == 0) {
      cout << "Enter the number to search for: "; cin >> input;
      if (search(head, input)) {
        cout << "Yes, that is in the tree." << endl;
      }
      else {
        cout << "No, that ain't in the tree." << endl;
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
    }
    else {
      add(head->left, n);
    }
  }

  else if (head->data < n->data) {
    if (head->right == NULL) {
      head->right = n;
    }
    else {
      add(head->right, n);
    }
  }
}

bool search(node* head, int k) {
  if (head == NULL) {
    return false;
  }

  else if (head->data == k) {
    return true;
  }

  else if (head->data > k) {
    return search(head->left, k); // switch back to left
  }

  else {
    return search(head->right, k); // switch back to right
  }
}
