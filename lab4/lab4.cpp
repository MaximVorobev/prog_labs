#include <iostream>
#include <string>
using namespace std;

struct Pen{   
    string color;
    double price;
    double length;
    string color_ink;
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
        First->n=n;
        First->data=new char[n];
        for(int i=0; i<n; i++){
            First->data[i]=data[i];
        }
        count = 1;
    }
    else{
        Node *temp;
        temp = First;
        while(temp->next!=NULL)
            temp=temp->next;
        temp->next=new Node;
        temp->next->data=new char[n];
        temp->next->next=NULL;
        temp->next->n=n;
        for(int i=0; i<n; i++){
            temp->next->data[i]=data[i];
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
        cout << "Queue info: " << endl;
        cout << "\tQueue size = " << count << endl;
    }
}

void Menu();
void AddProduct(Queue&);
void PullOut(Queue&);
void Clear(Queue&);
void GetSeria(char*& data, int& n, Pen a);
void GetDeSeria(char* data, int n, Pen& a);
void ShowProduct(Pen p);

void GetSeria(char*& data, int& n, Pen a){
    size_t s1= a.color.size();
    size_t s2= a.color_ink.size();
    int n0=sizeof(size_t);
    int n1=s1;
    int n2=sizeof(double);
    int n3=n2;
    int n4=sizeof(size_t);
    int n5=s2;

    n = n0+n1+n2+n3+n4+n5;
    data=new char[n];

    char* d0=reinterpret_cast<char*>(&s1);
    char* d1=const_cast<char*>(a.color.c_str());
    char* d2=reinterpret_cast<char*>(&a.price);
    char* d3=reinterpret_cast<char*>(&a.length);
    char* d4=reinterpret_cast<char*>(&s2);
    char* d5=const_cast<char*>(a.color_ink.c_str());

    for(int i=0; i<n0; i++) data[i]=d0[i];
    for(int i=0; i<n1; i++) data[i+n0]=d1[i];
    for(int i=0; i<n2; i++) data[i+n0+n1]=d2[i];
    for(int i=0; i<n3; i++) data[i+n0+n1+n2]=d3[i];
    for(int i=0; i<n4; i++) data[i+n0+n1+n2+n3]=d4[i];
    for(int i=0; i<n5; i++) data[i+n0+n1+n2+n3+n4]=d5[i];
}

void GetDeSeria(char* data, int n, Pen& a){
    int n0, n1, n2, n3, n4, n5;
    n0=sizeof(size_t);
    n2=sizeof(double);
    n3=n2;
    n4=sizeof(size_t);
    size_t p = *reinterpret_cast<size_t*>(data);
    n1=p;
    n5=p;

    string ss1(data+n0, p);
    string ss2(data+n0+n1+n2+n3+n4, p);
    a.color = ss1;
    a.price = *reinterpret_cast<double*>(data+n0+n1);
    a.length = *reinterpret_cast<double*>(data+n0+n1+n2);
    a.color_ink = ss2;
}

void Menu(){
    Queue q;
    int key;
    do{
        system("cls");
        cout << "------------" << endl;
        cout << "1. Goods arriving" << endl;
        cout << "2. Sale of goods" << endl;
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
            case 0: break;
            default:  system("cls"); 
                      cout << "Error data, try again..." << endl; 
                      system("pause");
        }
    }while(key);
}

void AddProduct(Queue &q){
    Pen p;
    string color, color_ink;
    double price, length;
    char* data;
    int ssize;
    cout << "Enter product specifications(color, price, length): " << endl;
    cin >> color >> price >> length >> color_ink;
    while(length<=0 or price<0){
        cout << "Length and price can't be less than 0" << endl;
        cout << "Price: ";
        cin >> price;
        cout << "Length: ";
        cin >> length;
    }

    p = {color, price, length, color_ink};
    GetSeria(data, ssize, p);
    q.Push(data, ssize);
    delete[] data;
}

void PullOut(Queue &q){
    Pen p;
    int ssize, count = q.count;
    char* data;
    string color, color_ink;
    double price, length;
    system("cls");
    if (q.count == 0){
            cout << "No products in the cart" << endl;
            system("pause");
            return;
    }
    cout << "Enter the number and price of units of the product you want to purchase: ";
    cin >> color >> price >> length >> color_ink;
    while (length<=0 || price<0){
        cout << "---> Error data length or price <--- " << endl;
        cout << "Price: ";
        cin >> price;
        cout << "Length: ";
        cin >> length;
    }

    for(int i=0; i<count; i++){
        data = q.First->data;
        ssize = q.First->n;
        GetDeSeria(data, ssize, p);
        if ((color == p.color) && (price == p.price) && (length == p.length) && (color_ink == p.color_ink)){
            q.Pop(data, ssize);
            cout << "The product was found" << endl;
            data = NULL;
            delete[] data;
            system("pause");
            return;
        }
        else {
            q.Pop(data, ssize);
            q.Push(data, ssize);
        }
        data = NULL;
    }
    cout << "No product in the queue" << endl;
    delete[] data;
    system("pause");
}

void Clear(Queue& q){
    Pen p;
    char* data;
    int ssize;
    system("cls");
    while(q.count){
        data = q.First->data;
        ssize = q.First->n;
        GetDeSeria(data, ssize, p);
        ShowProduct(p);
        q.Pop(data, ssize);
        data = NULL;
    }
    delete[] data;
    system("pause");
}

void ShowProduct(Pen p){
    cout << "Pen:";
    cout << "\t Color: " << p.color
         << "\t Price: " << p.price
         << "\t Length: " << p.length 
         << "\t Color ink: " << p.color_ink << endl;
}

int main()
{   
    Menu();
    return 0;
}
