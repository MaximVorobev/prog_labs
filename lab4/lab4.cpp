#include <iostream>
#include <string>
#include <fstream>
using namespace std;


struct Pen{   
    string color;
    double price;
    double length;
    int quantity;
};

struct Queue{
    struct Node {int n; char* data; Node* next;};
    Node *First = NULL;
    int count = 0;
    bool Push(char*, int);
    bool Pop(char*&, int&);
    void Info();
};

bool Queue::Push(char* data, int n){
    if (!First){
        First = new Node;
        First->next = NULL;
        First->n = n;
        First->data = new char[n];
        for(int i=0; i<n; i++){
            First->data[i] = data[i];
        }
        count = 1;
    }
    else{
        Node *temp;
        temp = First;
        while(temp->next!=NULL)
            temp=temp->next;
        temp->next = new Node;
        temp->next->data = new char[n];
        temp->next->next = NULL;
        temp->next->n = n;
        for(int i=0; i<n; i++){
            temp->next->data[i] = data[i];
        }
        count++;
    }
    return true;
}

bool Queue::Pop(char*& data, int& n){
    if (!First) return false;
    Node* temp = First->next;
    n=First->n;
    for(int i=0; i<n; i++){
        data[i] = First->data[i];
    }
    delete First->data;
    delete First;
    First = temp;
    count--;
    return true;
}

void Queue::Info(){
    if (!First) cout << "---> Queue is empty" << endl;
    else{
        cout << "Queue size = " << count << endl;
    }
}

void Menu();
void ClearBinaryFile();
void WriteBinaryFile(char*, int);
bool ReadBinaryFile(Queue&, int);
void FeedFromBinaryFile(Queue&);
void AddProduct(Queue&);
void PullOut(Queue&);
void Clear(Queue&);
void ClearExit(Queue&);
void GetSeria(char*&, int&, Pen);
void GetDeSeria(char*, int, Pen&);
void ShowProduct(Pen);

void GetSeria(char*& data, int& n, Pen a){
    size_t s1 = a.color.size();
    int n0 = sizeof(size_t);
    int n1 = s1;
    int n2 = sizeof(double);
    int n3 = n2;
    int n4 = sizeof(int);
    n = n0+n1+n2+n3+n4;
    data = new char[n];

    char* d0 = reinterpret_cast<char*>(&s1);
    char* d1 = const_cast<char*>(a.color.c_str());
    char* d2 = reinterpret_cast<char*>(&a.price);
    char* d3 = reinterpret_cast<char*>(&a.length);
    char* d4 = reinterpret_cast<char*>(&a.quantity);

    for(int i=0; i<n0; i++) data[i] = d0[i];
    for(int i=0; i<n1; i++) data[i+n0] = d1[i];
    for(int i=0; i<n2; i++) data[i+n0+n1] = d2[i];
    for(int i=0; i<n3; i++) data[i+n0+n1+n2] = d3[i];
    for(int i=0; i<n4; i++) data[i+n0+n1+n2+n3] = d4[i];
}

void GetDeSeria(char* data, int n, Pen& a){
    int n0, n1, n2, n3, n4;
    n0 = sizeof(size_t);
    n2 = sizeof(double);
    n3 = n2;
    n4 = sizeof(int);
    size_t p = *reinterpret_cast<size_t*>(data);
    n1 = p;
    string ss1(data+n0, p);

    a.color = ss1;
    a.price = *reinterpret_cast<double*>(data+n0+n1);
    a.length = *reinterpret_cast<double*>(data+n0+n1+n2);
    a.quantity = *reinterpret_cast<int*>(data+n0+n1+n2+n3);
}

void Menu(){
    Queue q;
    int key;
    FeedFromBinaryFile(q);
    do{
        system("cls");
        cout << "------------" << endl;
        cout << "1. Add product" << endl;
        cout << "2. Pull out product" << endl;
        cout << "3. Clear" << endl;
        cout << "0. Exit" << endl;
        cout << "------------" << endl;
        q.Info();
        cout << "Enter: ";
        cin >> key;

        switch(key){
            case 1: AddProduct(q); break;
            case 2: PullOut(q); break;
            case 3: Clear(q); break;
            case 0: ClearExit(q); break;
            default:  system("cls"); 
                      cout << "Error data, try again..." << endl; 
                      system("pause");
        }
    }while(key);
}

void ClearBinaryFile(){
    fstream f_out;
    f_out.open("out.dat", ios::out | ios::binary);
    f_out.close();
}

void WriteBinaryFile(char* data, int n){
    fstream f_out;
    f_out.open("out.dat", ios::app | ios::binary);
    f_out.write((char*)&n, sizeof(int));
    f_out.write(data, n);
    f_out.close();
}

bool ReadBinaryFile(Queue& q, int m){
    fstream f_in("out.dat", ios::in | ios::binary);
    if(!f_in){
        cout << "---> Error, there are no input binary file" << endl;
        return false;
    }
    int n;
    Pen p;
    while(!f_in.eof()){
        for(int i=0; i<m; i++){
            if(f_in.read((char*)&n, sizeof(int))){
                char* data = new char[n];
                f_in.read(data, n);
                i++;
                q.Push(data, n);
                delete[] data;
            }
        }
    }
    f_in.close();
    return true;
}

void FeedFromBinaryFile(Queue& q){
    Pen p[] = {
        {"blue", 12.7, 7, 2},
        {"white", 7, 4.8, 5}
    };
    char* data;
    int ssize, m=2;
    system("cls");
    ClearBinaryFile();
    for(int i=0; i<m; i++){
        GetSeria(data, ssize, p[i]);
        ShowProduct(p[i]);
        WriteBinaryFile(data, ssize);
    }
    ReadBinaryFile(q, m);
    system("pause");
}

void AddProduct(Queue &q){
    Pen p;
    string color;
    double price, length;
    char* data;
    int ssize, quantity;
    system("cls");
    cout << "Enter product specifications(color, price, length, quantity): " << endl;
    cin >> color >> price >> length >> quantity;
    while (length<=0 || price<0 || quantity<0){
        cout << "---> Error data length, price or quantity <--- " << endl;
        cout << "Price: ";
        cin >> price;
        cout << "Length: ";
        cin >> length;
        cout << "Quantity: ";
        cin >> quantity;
    }

    p = {color, price, length, quantity};
    GetSeria(data, ssize, p);
    q.Push(data, ssize);
    data = NULL;
    delete[] data;
}

void PullOut(Queue &q){
    Pen p;
    string color;
    double price, length;
    int ssize, quantity, count = q.count;
    char* data;
    system("cls");
    if (q.count == 0){
            cout << "No products in the queue" << endl;
            system("pause");
            return;
    }
    cout << "Enter product specifications(color, price, length, quantity): ";
    cin >> color >> price >> length >> quantity;
    while (length<=0 || price<0 || quantity<0){
        cout << "---> Error data length, price or quantity <--- " << endl;
        cout << "Price: ";
        cin >> price;
        cout << "Length: ";
        cin >> length;
        cout << "Quantity: ";
        cin >> quantity;
    }

    for(int i=0; i<count; i++){
        data = q.First->data;
        ssize = q.First->n;
        GetDeSeria(data, ssize, p);
        if ((color == p.color) && (price == p.price) && (length == p.length) && (quantity == p.quantity)){
            q.Pop(data, ssize);
            cout << "The product was found" << endl;
            data = NULL;
            delete[] data;
            system("pause");
            return;
        }
        else {
            GetDeSeria(data, ssize, p);
            q.Pop(data, ssize);
            GetSeria(data, ssize, p);
            q.Push(data, ssize);
        }
    }
    cout << "No product in the queue" << endl;
    data = NULL;
    delete[] data;
    system("pause");
}

void Clear(Queue& q){
    Pen p;
    char* data;
    int ssize, i = 1;
    system("cls");
    while(q.count){
        data = q.First->data;
        ssize = q.First->n;
        GetDeSeria(data, ssize, p);
        q.Pop(data, ssize);
        cout << i << ". ";
        ShowProduct(p);
        i++;
        data = NULL;
    }
    data = NULL;
    delete[] data;
    system("pause");
}

void ClearExit(Queue& q){
    Pen p;
    char* data;
    int ssize;
    while(q.count){
        data = q.First->data;
        ssize = q.First->n;
        GetDeSeria(data, ssize, p);
        q.Pop(data, ssize);
        data = NULL;
    }
    data = NULL;
    delete[] data;
}

void ShowProduct(Pen p){
    cout << "\tColor: " << p.color
         << "\tPrice: " << p.price
         << "\tLength: " << p.length 
         << "\tQuantity included: " << p.quantity << endl;
}

int main(){ 
    Menu();
    return 0;
}
