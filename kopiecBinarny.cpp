#include <iostream>
using namespace std;

class MinHeap {
private:
    int* kopiec;
    int capacity;
    int size;
public:
    MinHeap(int c);            //tworzy pusty kopiec o pojemno�ci c
    MinHeap();                //konstruktor do test�w kopca - nale�y utworzy� kopiec z nast�puj�c� zawarto�ci�: 1, 2, 4, 6, 5, 4, 7, 7, 7, 9, 6
    bool empty();
    bool full();
    int getLeft(int i);                    //zwraca pozycj� lewego syna
    int getRight(int i);                //zwraca pozycj� prawego syna
    int getParent(int i);                //zwraca pozycj� ojca
    int getSize();                        //zwraca rozmiar kopca
    void setSize(int s);                //ustawia rozmiar kopca na s
    int getValue(int i);                //zwraca warto�� z pozycji i
    void setValue(int i, int x);        //ustawia warto�� x na pozycji i
    void showHeap();                //pokazuje kopiec

    void bottomUp(int i);                //przywraca w�asno�� kopca metod� wynurzania
    void topDown(int i);                //przywraca w�asno�� kopca metod� zatapiania

    void insert(int x);                    //wstawia element z warto�ci� x (tutaj warto�� jest jednocze�nie priorytetem)
    void deleteMin();                     //usuwa element z minimaln� warto�ci�
    int minimum();                        //zwraca minimaln� warto��
    void del(int i);                         //usuwa element na pozycji i
    void decreaseKey(int i, int x);        //zmniejsza warto�� priotytetu dla danych na pozycji i, ustawia x   

    //friend std::ostream& operator<<(std::ostream& out, MinHeap& h);
};

MinHeap::MinHeap(int c) {
    capacity = c;
    kopiec = new int[capacity];
    size = 0;
}

MinHeap::MinHeap() {
    this->capacity = 15;
    this->kopiec = new int[capacity] {1, 2, 4, 4, 4, 5, 7, 10, 9, 6};
    this->size = 10;
}

bool MinHeap::empty() {
    if (size == 0) return true;
    else return false;
}

bool MinHeap::full() {
    if (size == capacity) return true;
    else return false;
}

void MinHeap::setValue(int i, int x) {        //ustawia warto�� x na pozycji i
    if (i > capacity) return;
    else kopiec[i] = x;
}

void MinHeap::showHeap() {
    for (int i = 0; i < size; i++)
        cout << kopiec[i] << " ";
    cout << endl;
}

void MinHeap::bottomUp(int i) {                //przywraca w�asno�� kopca metod� wynurzania
    int child = i;
    int parent = (child - 1) / 2;

    while (child > 0 && kopiec[child] < kopiec[parent]) {
        swap(kopiec[child], kopiec[parent]);
        child = parent;
        parent = (child - 1) / 2;
    }

}
void MinHeap::topDown(int i) {                //przywraca w�asno�� kopca metod� zatapiania
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int lowest = i;

    if (left < size && kopiec[left] < kopiec[lowest])
        lowest = left;
    if (right < size && kopiec[right] < kopiec[lowest])
        lowest = right;
    if (lowest != i) {
        swap(kopiec[i], kopiec[lowest]);
        topDown(lowest);
    }
}
void MinHeap::insert(int x) {                    //wstawia element z warto�ci� x (tutaj warto�� jest jednocze�nie priorytetem)
    if (!full()) {
        kopiec[size] = x;
        bottomUp(size);
        size++;
    }
}
int MinHeap::minimum() {                        //zwraca minimaln� warto��
    if (!empty()) {
        return kopiec[0];
    }
    return -1;

}
void MinHeap::deleteMin() {                     //usuwa element z minimaln� warto�ci�
    if (!empty()) {
        size--;
        swap(kopiec[0], kopiec[size]);
        topDown(0);
    }

}
void MinHeap::del(int i) {                         //usuwa element na pozycji i
    if (!full()) {
        size--;
        swap(kopiec[i], kopiec[size]);
        topDown(i);
        bottomUp(i);
    }

}
void MinHeap::decreaseKey(int i, int x) {        //zmniejsza warto�� priotytetu dla danych na pozycji i, ustawia x  
    if (!empty() && kopiec[i] > x) {
        setValue(i, x);
        bottomUp(i);
    }

}
int main() {
    MinHeap* h = new MinHeap(10);
    h->insert(8);
    h->insert(4);
    h->insert(6);
    h->insert(2);
    h->insert(1);
    h->insert(9);
    h->showHeap();

    h->deleteMin();
    h->showHeap();

    cout << h->minimum() << endl;
    h->decreaseKey(3, 1);
    h->showHeap();

    h->del(1);
    h->showHeap();
}
