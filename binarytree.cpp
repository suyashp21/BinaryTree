/* Author: Suyash Pandit
Date: April 21, 2022
This is a Binary Search Tree, precursor to Red-Black tree */

#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

struct node {
  int data;
  node* parent;
  node* left;
  node* right;
};

void add(node* head, node* n);
node* search(node* head, int k);
void print(node* n, int k);

int main() {
  node* head = NULL;
  char action[10];
  int input;
  while (true) {
    cout << "What do you want to do? (ADD, FILEIN, DELETE, PRINT, SEARCH, QUIT) "; cin \
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

    else if (strcmp(action, "FILEIN") == 0 || strcmp(action, "filein") == 0) {
      // read in from file
      ifstream myfile ("Numbers.txt");
      for (int i=1; i<=11; i++) {
	int k;
	myfile >> k;
	node* n = new node();
	n->data = k;
	n->parent = NULL;
	n->left = NULL;
	n->right = NULL;
	if (head == NULL) {
	  head = n;
	}
	else {
	  add(head, n);
	}
      }
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

    else if (strcmp(action, "PRINT") == 0 || strcmp(action, "print") == 0) {
      cout << endl;
      print(head, 0);
    }
    

    else if (strcmp(action, "DELETE") == 0 || strcmp(action, "delete") == 0) {
      cout << "Enter the number to delete: "; cin >> input;
      node* n = search(head, input);
      if (n == NULL) {
	cout << "That number isn't in the tree!" << endl;
      }
      else {
	if (n->left == NULL && n->right == NULL) { // no children
	  if (n == head) {
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
	  if (n == head) {
	    head = head->right;
	    delete n;
	  }

	  else if (n->parent->left == n) {
	    n->parent->left = n->right;
	    n->right->parent = n->parent;
	    delete n;
	  }
	  
	  else if (n->parent->right == n) {
	    n->parent->right = n->right;
	    n->right->parent = n->parent;
	    delete n;
	  }
	}
	else if (n->right == NULL) {
	  if (n == head) {
	    head = head->left;
	  }

	  else if (n->parent->left == n) {
	    n->parent->left = n->left;
	    n->left->parent = n->parent;
	    delete n;
	  }

	  else if (n->parent->right == n) {
	    n->parent->right = n->left;
	    n->left->parent = n->parent;
	    delete n;
	  }
	}
	else { // has two children
	  if (n == head) {
	    node* n2 = n->left;
	    if (n2->right == NULL) {
	      head = n2;
	      n2->right = n->right;
	      n2->right->parent = n2;
	      n2->parent = NULL;
	      delete n;
	    }
	    else {
	      while (n2->right != NULL) {
	        n2 = n2->right;
	      }
	      n2->parent->right = n2->left;
	      if (n2->left != NULL) {
		n2->left->parent = n2->parent;
	      }
	      head = n2;
	      n2->left = n->left;
	      n2->left->parent = n2;
	      n2->right = n->right;
	      n2->right->parent = n2;
	      n2->parent = NULL;
	      delete n;
	    }
	  }

	  else {
	    node* n2 = n->left;
	    if (n2->right == NULL) {
	      if (n->parent->left == n) {
		n->parent->left = n2;
		n2->parent = n->parent;
		n2->right = n->right;
		n->right->parent = n2;
	      }
	      else if (n->parent->right == n) {
		n->parent->right = n2;
		n2->parent = n->parent;
		n2->right = n->right;
		n->right->parent = n2;
	      }
	      delete n;
	    }
	    else {
	      while (n2->right != NULL) {
		n2 = n2->right;
	      }
              n2->parent->right = n2->left;
              if (n2->left != NULL) {
                n2->left->parent = n2->parent;
              }
              n2->left = n->left;
              n2->left->parent = n2;
              n2->right = n->right;
              n2->right->parent = n2;
              n2->parent = n->parent;
	      if (n->parent->left == n) {
		n->parent->left = n2;
		n2->parent = n->parent;
	      }
	      else if (n->parent->right == n) {
		n->parent->right = n2;
		n2->parent = n->parent;
	      }
              delete n;

	      
	    }
	  }
	}
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

void print(node* n, int k) {
  if (n == NULL) {
    // do nothing
  }
  else {
    print(n->right, k+1);

    for (int i=0; i<k; i++) {
      cout << "\t";
    }
    cout << n->data << endl;

    print(n->left, k+1);
  }
}
