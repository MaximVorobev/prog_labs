#include <iostream>
#include <string>
using namespace std;

struct Product
{   
    string name;
    int quantity;
    double price;
    double total_cost = quantity * price;
    void Out();
};

void Product::Out(){
    cout << "Name: " << name << endl;
    cout << "Quantity: " << quantity << endl;
    cout << "Price: " << price << endl;
    cout << "Total cost: " << total_cost << endl;
}

struct Queue
{
    struct Node {Product data; Node* next;};
    Node *First = NULL;
    int count = 0, rest = 0;
    double money = 0;
    bool Push(Product);
    bool Pop(Product&);
    void Info();
};

bool Queue::Push(Product data){
    if (!First){
        First = new Node;
        First->next = NULL;
        First->data = data;
        count = 1;
        rest = First->data.quantity;
    }
    else{
        Node *temp;
        temp = First;
        while(temp->next!=NULL)
            temp=temp->next;
        temp->next=new Node;
        temp->next->data=data;
        rest += temp->next->data.quantity;
        temp->next->next=NULL;
        count++;
    }
    return true;
}

bool Queue::Pop(Product& data){
    if (!First) return false;
    Node* temp = First->next;
    data=First->data;
    delete First;
    First = temp;
    count--;
    return true;
}

void Queue::Info(){
    system("cls");
    if (!First) cout << "---> Queue is empty" << endl;
    else{
        cout << endl << "Queue info: " << endl;
        cout << "\tQueue size = " << count << endl;
        cout << "\tRest = " << rest << endl;
        cout << "\tMoney = " << money << endl;
    }
    system("pause");
}

void Menu();
void Arriving(Queue&);
void Sale(Queue&);

void Menu(){
    Queue q;
    int key;
    do{
        system("cls");
        cout << "------------" << endl;
        cout << "1. Goods arriving" << endl;
        cout << "2. Sale of goods" << endl;
        cout << "3. Report" << endl;
        cout << "0. Exit" << endl;
        cout << "------------" << endl;
        cout << "Enter: ";
        cin >> key;

        switch(key){
            case 1: Arriving(q); break;
            case 2: Sale(q); break;
            case 3: q.Info(); break;
            case 0: break;
            default:  system("cls"); 
                      cout << "Error data, try again..." << endl; 
                      system("pause");
        }
    }while(key);
}

void Arriving(Queue &q){
    Product p;
    string name;
    int quantity;
    double price;
    cout << "Enter product specifications(name, quantity, price): " << endl;
    cin >> name >> quantity >> price;
    while(quantity<=0 or price<0){
        cout << "Rest and price can't be less than 0" << endl;
        cout << "Quantity: ";
        cin >> quantity;
        cout << "Price: ";
        cin >> price;
    }
    p = {name, quantity, price};
    q.Push(p);
}

void Sale(Queue &q){
    Product product;
    int count;
    product = q.First->data;
    cout << "Enter the number of units of the product you want to purchase: ";
    cin >> count;
    while (count > product.quantity or count<=0){
        cout << "There is no such quantity of goods in stock, enter a smaller number:";
        cin >> count;
    }
    if (count == product.quantity){
        q.money += product.quantity * product.price;
        q.Pop(product);
    }
    else{
        q.money += count * product.price;
        q.First->data.quantity -= count; 
        q.rest -= count;
        q.First->data.total_cost -= count* product.price;
    }
}

int main()
{   
    Menu();
    return 0;
}
