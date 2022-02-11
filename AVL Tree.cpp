#include <iostream>//2019504
#include <string>//Syed Nazim Shah

using namespace std;
struct node {
  string phoneno, name, address, email;
  node * left;
  node * right;
  int height;
};
class avl {
  public:
    node * root;
  avl() {
    root = NULL;
  }

  int max(int a, int b) {
    if (a < b) return b;
    else return a;
  }

  int height(node * temp) {
    int h = 0;
    if (temp != NULL) {
      int l_height = height(temp -> left);
      int r_height = height(temp -> right);
      int max_height = max(l_height, r_height);
      h = max_height + 1;
    }
    return h;
  }
  int difference(node * temp) {
    int l_height = height(temp -> left);
    int r_height = height(temp -> right);
    int b_factor = l_height - r_height;
    return b_factor;
  }
  node * rrrotat(node * parent) {
    node * temp;
    temp = parent -> right;
    parent -> right = temp -> left;
    temp -> left = parent;
    return temp;
  }
  node * llrotat(node * parent) {
    node * temp;
    temp = parent -> left;
    parent -> left = temp -> right;
    temp -> right = parent;
    return temp;
  }
  node * lrrotat(node * parent) {
    node * temp;
    temp = parent -> left;
    parent -> left = rrrotat(temp);
    return llrotat(parent);
  }
  node * rlrotat(node * parent) {
    node * temp;
    temp = parent -> right;
    parent -> right = llrotat(temp);
    return rrrotat(parent);
  }
  node * balance(node * temp) {
    int balfactor = difference(temp);
    if (balfactor > 1) {
      if (difference(temp -> left) > 0)
        temp = llrotat(temp);
      else
        temp = lrrotat(temp);
    } else if (balfactor < -1) {
      if (difference(temp -> right) > 0)
        temp = rlrotat(temp);
      else
        temp = rrrotat(temp);
    }
    return temp;
  }
  node * insert(node * r, node * temp) {

    if (r == NULL) {
      r = temp;
      return r;
    } else if (temp -> phoneno < r -> phoneno) {
      r -> left = insert(r -> left, temp);
      r = balance(r);
    } else if (temp -> phoneno >= r -> phoneno) {
      r -> right = insert(r -> right, temp);
      r = balance(r);
    }
    return r;
  }
  node * minValueNode(node * temp) {
    node * current = temp;
    while (current -> left != NULL)
      current = current -> left;
    return current;
  }
  node * deletenode(node * root, string phone) {
    if (root == NULL)
      return root;

    if (phone < root -> phoneno)
      root -> left = deletenode(root -> left, phone);

    else if (phone > root -> phoneno)
      root -> right = deletenode(root -> right, phone);
    else {
      if ((root -> left == NULL) || (root -> right == NULL)) {
        node * temp = root -> left ? root -> left : root -> right;

        if (temp == NULL) {
          temp = root;
          root = NULL;
        } else
          *root = * temp;
        delete temp;
      } else {
        node * temp = minValueNode(root -> right);
        root -> phoneno = temp -> phoneno;
        root -> right = deletenode(root -> right, temp -> phoneno);
      }
    }

    if (root == NULL) return root;

    root = balance(root);
    return root;
  }
  void search(node * temp, string value) {
    if (temp == NULL) return;
    if (value == temp -> name || value == temp -> address || value == temp -> email) {
      cout << temp -> name << " " << temp -> phoneno << " " << temp -> email << " " << temp -> address << endl;
      return;
    }
    search(temp -> left, value);
    search(temp -> right, value);
  }
  void inorder(node * temp) {
    if (temp == NULL)
      return;
    inorder(temp -> left);
    cout << temp -> name << " " << temp -> phoneno << " " << temp -> email << " " << temp -> address << endl;
    inorder(temp -> right);
  }
  void preorder(node * temp) {
    if (temp == NULL)
      return;
    cout << temp -> name << " " << temp -> phoneno << " " << temp -> email << " " << temp -> address << endl;
    preorder(temp -> left);
    preorder(temp -> right);
  }
  void postorder(node * temp) {
    if (temp == NULL)
      return;
    postorder(temp -> left);
    postorder(temp -> right);
    cout << temp -> name << " " << temp -> phoneno << " " << temp -> email << " " << temp -> address << endl;
  }
};
class phonebook {
  public:
    avl newbook;

  void addcontact() {
    node * temp = new node;
    cout << "Name: "; getline(cin, temp -> name);
    cout << "Phone: "; getline(cin, temp -> phoneno);
    cout << "Address: "; getline(cin, temp -> address); 
	cout << "Email: "; getline(cin, temp -> email);
    temp -> left = NULL;
    temp -> right = NULL;
    newbook.root = newbook.insert(newbook.root, temp);
  }

  void showphonebook() {
    cout << "PREorder///////////////////////////////////" << endl;
    newbook.preorder(newbook.root);
    cout << "INorder///////////////////////////////////" << endl;
    newbook.inorder(newbook.root);
    cout << "POSTorder///////////////////////////////////" << endl;
    newbook.postorder(newbook.root);
  }
  void searchcontact() {
    string phone;
    cout << "Enter Name Address or Email: "; getline(cin, phone);
    newbook.search(newbook.root, phone);
  }
  void deletecontact() {
    string phone;
    cout << "Enter phone: "; getline(cin, phone);
    newbook.deletenode(newbook.root, phone);
  }

};
int main() {
  phonebook newbook;
  while (true) {
    int choice = 0;
    cout << "1.Enter a Contact\n2.Delete a contact\n3.Search a contact\n4.Display All Contacts\n5.Exit\n-------->>";
    cin >> choice;
    cin.ignore();
    switch (choice) {
    case 1:
      newbook.addcontact();
      break;
    case 2:
      newbook.deletecontact();
      break;
    case 3:
      newbook.searchcontact();
      break;
    case 4:
      newbook.showphonebook();
      break;
    case 5:
      return 0;
      break;
    default:
      cout << "Error!";
      break;
    }
  }
}
