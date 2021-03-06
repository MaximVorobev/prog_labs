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
    cout << endl << "First item info:" << endl; 
    cout << "\tName: " << name << endl;
    cout << "\tQuantity: " << quantity << endl;
    cout << "\tPrice: " << price << endl;
    cout << "\tTotal cost: " << total_cost << endl;
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
        First->data.Out();
    }
    system("pause");
}

void Menu();
void Arriving(Queue&);
void Sale(Queue&);

void Menu(){
    Queue q;
    Product p;
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
            case 0: {
                while(q.count){
                    q.Pop(p);
                }
            }break;
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
    double price;
    product = q.First->data;
    cout << "Enter the number and price of units of the product you want to purchase: ";
    cin >> count >> price;
    while (count<=0 || count>q.rest || price<=0 || price<=product.price){
        cout << "---> Error data count or price <--- " << endl;
        cout << "Count: ";
        cin >> count;
        cout << "Price: ";
        cin >> price;
    }
    while (count){
        if (count <= product.quantity){
            q.money += count * (price - product.price);
            product.total_cost -= count * product.price;
            product.quantity -= count;
            q.rest -= count;
            count = 0;
            q.First->data.quantity = product.quantity;
            q.First->data.total_cost = product.total_cost;        
        } 
        else{
            q.money += product.quantity * (price - product.price);
            count -= product.quantity;
            q.rest -= count;
            product.quantity = 0;
        }
        if (product.quantity == 0){
            q.Pop(product);
            product = q.First->data;
        }
    }
}

int main()
{   
    Menu();
    return 0;
}
