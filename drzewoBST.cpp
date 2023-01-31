#include <iostream>
using namespace std;

class Node {
private:
    int value;
    Node* left;
    Node* right;
    Node* parent;
public:
    Node(int v, Node* l, Node* r, Node* p);
    Node();
    int getValue();
    Node* getLeft();
    Node* getRight();
    Node* getParent();
    void setValue(int v);
    void setLeft(Node* l);
    void setRight(Node* r);
    void setParent(Node* p);
};

class BSTree {
private:
    Node* root;
public:
    BSTree();                        //tworzy puste drzewo
    Node* getRoot();            //zwraca wska¿nik do root - metoda pomocnicza w testowaniu
    bool empty(Node* p);        //zwraca prawdê gdy (pod)drzewo o korzeniu p jest puste
    void inorder(Node* p);      //wyœwietla w porz¹dku inorder
//BST   
    void insert(int x);            //wstawia wêze³ z wartoœci¹ x
    Node* search(int x);         //zwraca wskaŸnik do wêz³a z wartoœci¹ x (lub NULL jeœli nie istnieje)
    Node* minimum(Node* p);            //zwraca wskaŸnik do wêz³a z minimaln¹ wartoœci¹ w (pod)drzewie p
    Node* maximum(Node* p);            //zwraca wskaŸnik do wêz³a z maksymaln¹ wartoœci¹ w (pod)drzewie p
    Node* successor(Node* p);    //zwraca wskaŸnik do nastênika p
    Node* predecessor(Node* p);    //zwraca wskaŸnik do poprzednika p
    bool leaf(Node* p);	//zwraca prawdê jeœli wêze³ jest liœciem
    void del(Node* p);            //usuwa wêze³ wskazywany przez p
    int size(Node* p);                  //zwraca rozmiar (pod)drzewa o korzeniu p
    int hight(Node* p);              //zwraca wysokoœæ (pod)drzewa o korzeniu p
    void clear(Node* p);           //usuwa wszystkie wêz³y z (pod)drzewa o korzeniu p
};
Node::Node(int v, Node* l, Node* r, Node* p) {
    value = v;
    left = l;
    right = r;
    parent = p;
}
Node::Node() {
    value = 0;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}

int Node::getValue() {
    return value;
}
Node* Node::getLeft() {
    return left;
}
Node* Node::getRight() {
    return right;
}
Node* Node::getParent() {
    return parent;
}
void Node::setValue(int v) {
    value = v;
}
void Node::setLeft(Node* l) {
    left = l;
}
void Node::setRight(Node* r) {
    right = r;
}
void Node::setParent(Node* p) {
    parent = p;
}

BSTree::BSTree() {  //tworzy puste drzewo
    root = nullptr;
}
Node* BSTree::getRoot() {            //zwraca wska¿nik do root - metoda pomocnicza w testowaniu
    return root;
}
bool BSTree::empty(Node* p) {        //zwraca prawdê gdy (pod)drzewo o korzeniu p jest puste
    if (p == nullptr) return true;
    else return false;
}
void BSTree::inorder(Node* p) {
    if (!empty(p)) {
        inorder(p->getLeft());
        cout << p->getValue() << " ";
        inorder(p->getRight());
    }
    return;
}

void BSTree::insert(int x) {
    Node* n = root;
    Node* m;

    if (empty(n)) {
        root = new Node(x, nullptr, nullptr, nullptr);
        return;
    }
    while (true) {
        if (x > n->getValue()) {
            if (n->getRight() != nullptr) {
                n = n->getRight();
            }
            else {
                m = new Node(x, nullptr, nullptr, n);
                n->setRight(m);
                return;
            }
        }
        else {
            if (n->getLeft() != nullptr) {
                n = n->getLeft();
            }
            else {
                m = new Node(x, nullptr, nullptr, n);
                n->setLeft(m);
                return;
            }
        }
    }
}

Node* BSTree::search(int x) {
    Node* n = root;
    if (empty(n)) return nullptr;

    while (!empty(n)) {
        if (n->getValue() != x) {
            if (x > n->getValue()) n = n->getRight();
            else n = n->getLeft();
        }
        else return n;
    }
    return nullptr;


}

Node* BSTree::minimum(Node* p) {
    while (!empty(p->getLeft())) p = p->getLeft();
    return p;
}

Node* BSTree::maximum(Node* p) {
    while (!empty(p->getRight())) p = p->getRight();
    return p;
}

Node* BSTree::successor(Node* p) {
    Node* parent;
    Node* temp;
    if (empty(p)) return nullptr;
    else if (p->getRight() != nullptr) return minimum(p->getRight());
    else {
        parent = p->getParent();
        temp = p;
        while (!empty(parent) && parent->getRight() == temp) {
            temp = parent;
            parent = temp->getParent();
        }
        return parent;
    }
}

Node* BSTree::predecessor(Node* p) {
    Node* parent;
    Node* temp;
    if (empty(p)) return nullptr;
    else if (p->getLeft() != nullptr) return maximum(p->getLeft());
    else {
        parent = p->getParent();
        temp = p;
        while (!empty(parent) && parent->getLeft() == temp) {
            temp = parent;
            parent = temp->getParent();
        }
        return parent;
    }
}

bool BSTree::leaf(Node* p) {
    if (!empty(p) && empty(p->getRight()) && empty(p->getLeft())) return true;
    return false;
}

void BSTree::del(Node* p) {
    Node* parent = p->getParent();
    Node* temp;

    if (empty(p)) return; //jeœli nie istnieje
    else if (leaf(p)) { //jeœli istnieje i jest liœciem
        if (parent->getLeft() == p) parent->setLeft(nullptr);
        else parent->setRight(nullptr);
        delete p;
    }
    else if ((!empty(p->getLeft()) && empty(p->getRight())) || (empty(p->getLeft()) && !empty(p->getRight()))) { //jeœli ma jednego syna

        if (!empty(p->getLeft())) temp = p->getLeft(); //temp to syn niepusty
        else temp = p->getRight();

        if (empty(parent)) root = p; //syn staje siê korzeniem
        else if (parent->getLeft() == temp) {
            parent->setLeft(temp);
            temp->setParent(parent);
        }
        else {
            parent->setRight(temp);
            temp->setParent(parent);
        }
        delete p;
    }
    else {
        Node* temp = successor(p);
        p->setValue(temp->getValue());
        del(temp);
    }

}

int BSTree::size(Node* p) {
    if (empty(p)) return 0;
    else return (1 + size(p->getRight()) + size(p->getLeft()));
}

int BSTree::hight(Node* p) {
    if (empty(p)) return -1;
    else return (1 + std::max(hight(p->getRight()), hight(p->getLeft())));
}

void BSTree::clear(Node* p) {
    if (!empty(p)) {
        clear(p->getRight());
        clear(p->getLeft());
        delete p;
        p = nullptr;
    }

}

int main() {
    BSTree* t = new BSTree();
    t->insert(6);
    t->insert(4);
    t->insert(8);
    t->insert(2);
    t->insert(1);
    t->insert(3);
    t->insert(7);
    t->insert(9);

    t->inorder(t->search(6));
    cout << endl;
    t->del(t->search(9));
    //t->inorder(t->search(8));
    cout << endl << t->size(t->search(6)) << " " << t->hight(t->search(6)) << endl << endl;
    t->clear(t->search(6));
    //t->insert(6);
    //t->inorder(t->search(6));

}