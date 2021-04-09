#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
using namespace std;

struct Pen{
    string color;
    double price;
    string color_ink;
    double length;
    void Out();
};

void Pen::Out(){
    cout << "\tColor: " << color << endl;
    cout << "\tPrice: " << price << endl;
    cout << "\tColor of ink: " << color_ink << endl;
    cout << "\tLength:" << length << endl;
}

struct Stack
{
    struct Node
    {
        Pen data; Node* prev;
    };
    Node *top = NULL;
    int count;
    bool Push(Pen);
    bool Pop(Pen&);
    void Info();
};

bool Stack::Push(Pen data){
    if (!top){
        top = new Node;
        top->prev=NULL;
        count=1;
    }
    else{
        Node *temp;
        temp=new Node;
        temp->prev=top;
        top=temp;
        count++;
    }
    top->data=data;
    return true;
}

bool Stack::Pop(Pen& data){
    if (!top) return false;
    Node* temp = top->prev;
    data=top->data;
    delete top;
    top = temp;
    count--;
    return true;
}

void Stack::Info(){
    if(!top)
        cout << "---> Stack is empty" << endl;
    else{
        cout << "Stack info: " << endl;
        cout << "\tStack size = " << count << endl;
        top->data.Out();
        cout << endl;
    }
}

void Menu();
void readFile(Stack&);
void userPush(Stack&);
void getOut(Stack&);
void Clear(Pen&, Stack&);

void Menu(){
    Stack s;
    Pen p;
    readFile(s);
    int key;
    do{
        system("cls");
        cout << "------------" << endl;
        cout << "1. Add product in the cart" << endl;
        cout << "2. Pull out the product from the cart" << endl;
        cout << "3. Clear cart" << endl;
        cout << "0. Exit" << endl;
        cout << "------------" << endl;
        s.Info();
        cout << "Enter: ";
        cin >> key;

        switch(key){
            case 1: userPush(s); break;
            case 2: getOut(s); break;
            case 3: Clear(p, s); break;
            case 0: break;
            default:  system("cls"); 
                      cout << "Error data, try again..." << endl; 
                      system("pause");
        }
    }while(key);
}

void readFile(Stack &stack){
    Pen pen;
    fstream data;
    data.open("data.txt", ios::in);
    if (!data){
        cout << "---> Error open file <---" << endl;
        return;
    }
    else{
        while (data >> pen.color >> pen.price >> pen.color_ink >> pen.length){
            stack.Push(pen);
        }
        data.close();
    }
}

void userPush(Stack& s){
    string color, color_ink;
    double price, length;
    Pen pen;
    cout << "Enter color, price, color of ink and length of pen: ";
    cin >> color >> price >> color_ink >> length;
    while(price<0 or length<=0){
        cout << "---> Price or length can't be less than 0 <---" << endl;
        cout << "Price: ";
        cin >> price;
        cout << "Length: ";
        cin >> length;
    }
    pen = {color, price, color_ink, length};
    s.Push(pen);
}

void getOut(Stack& s){
    Stack temp;
    Pen top;
    string color, color_ink;
    double price, length; 
    bool flag = true;
    if (s.count == 0){
            cout << "No products in the cart" << endl;
            system("pause");
            return;
    }
    cout << "Enter properties of the product(color, price, color of ink, length): ";
    cin >> color >> price >> color_ink >> length;
    while (flag){
        top = s.top->data;
        if ((color == top.color) && (price == top.price) && (color_ink == top.color_ink) && (length == top.length)){
            s.Pop(top);
            flag = 0;
            break;
        }
        else if (s.count>0){
            s.Pop(top);
            temp.Push(top);
        }
        if (s.count == 0) break;
    }
    while(temp.count>0){
        top = temp.top->data;
        s.Push(top);
        temp.Pop(top);
    }
    if (flag) cout << "No product in the cart" << endl;
    else cout << "The product was found" << endl;
    system("pause");
}

void Clear(Pen& pen, Stack &s){
    while (s.count){
        s.Pop(pen);
    }
}

int main()
{   
    Menu();
    return 0;
}
