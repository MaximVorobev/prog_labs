#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Watch{
    string name;
    string color;
    double price;
    int quantity;
    void Out();
};

void Watch::Out(){
    cout << name << " ";
    cout << color << " ";
    cout << price << " ";
    cout << quantity << " ";
    cout << endl;
}

struct Tree{
    Watch data;
    Tree* left;
    Tree* right;
};

int GetTreeSize(Tree* T);
void Add(Tree*& T, int data, bool flag);
void PrintLRR(Tree* T);
Tree* Search(Tree*& T, int data);
void Delete(Tree*& T);
void readFile();
void SortTree(Tree*& T, bool flag);
void elDbl(Tree* T);
void elStr(Tree* T);
void Menu();



int GetTreeSize(Tree* T){
    if (!T) return 0;
    if (!T->left && !T->right) return 1;
    int left=0, right=0;
    if (T->left) left = GetTreeSize(T->left);
    if (T->right) right = GetTreeSize(T->right);
    return left+right+1;
}

void Add(Tree*& T, Watch data, bool flag){
    if (!T){
        T = new Tree;
        T->data = data;
        T->left = NULL;
        T->right = NULL;
        return;
    }
    if (flag){
        if (data.price<T->data.price) Add(T->left, data, 1);
        else Add(T->right, data, 1);
        return;
    }
    else {
        if (data.name<T->data.name) Add(T->left, data, 0);
        else Add(T->right, data, 0);
        return;
    }
}

void PrintLRR(Tree* T){
    if (!T) return;
    PrintLRR(T->left);
    T->data.Out();
    PrintLRR(T->right);
}

Tree* SearchDbl(Tree*& T, double data){
    if (!T) return NULL;
    if (data > T->data.price){
        T->data.Out();
    }
    SearchDbl(T->left, data);
    SearchDbl(T->right, data);
    return T;
}

Tree* SearchStr(Tree*& T, string data){
    if (!T) return NULL;
    if (data[0] == T->data.name[0]){
        T->data.Out();
    }
    SearchStr(T->left, data);
    SearchStr(T->right, data);
    return T;
}

void Delete(Tree*& T){
    if (T){
        if (T->left) Delete(T->left);
        if (T->right) Delete(T->right);
        delete T;
        T = NULL;
    }
    else{
        cout << "Tree is empty" << endl;
    }
}

void readFile(Tree*& T){
    Watch w;
    system("cls");
    fstream f_in("input.txt", ios::in);
    if(!f_in){
        cout << "---> Error, there are no input file" << endl;
        return;
    }
    while(f_in >> w.name >> w.color >> w.price >> w.quantity){
        Add(T, w, 1);
    }
    f_in.close();
}

void SortTree(Tree*& T, bool flag){
    Delete(T);
    Watch w;
    system("cls");
    fstream f_in("input.txt", ios::in);
    if(!f_in){
        cout << "---> Error, there are no input file" << endl;
        return;
    }
    while(f_in >> w.name >> w.color >> w.price >> w.quantity){
        if (flag) Add(T, w, 1);
        else Add(T, w, 0);
    }
    f_in.close();
    system("cls");
    PrintLRR(T);
    system("pause");
}

void elDbl(Tree* T){
    double price;
    system("cls");
    cout << "Enter the price: ";
    cin >> price;
    SearchDbl(T, price);
    system("pause");
}

void elStr(Tree* T){
    string name;
    system("cls");
    cout << "Enter a letter: ";
    cin >> name;
    SearchStr(T, name);
    system("pause");
}

void Menu(){
    Tree* T = NULL;
    readFile(T);
    Watch w;
    int key;
    do{
        system("cls");
        cout << "------------" << endl;
        cout << "1. Sort(str)" << endl;
        cout << "2. Sort(int)" << endl;
        cout << "3. Choose element(str)" << endl;
        cout << "4. Choose element(int)" << endl;
        cout << "0. Exit" << endl;
        cout << "------------" << endl;
        cout << "Num of elements in the tree: " << GetTreeSize(T) << endl;
        cout << "Enter: ";
        cin >> key;

        switch(key){
            case 1: SortTree(T, 0); break;
            case 2: SortTree(T, 1); break;
            case 3: elStr(T); break;
            case 4: elDbl(T); break;
            case 0: Delete(T); break;
            default:  system("cls"); 
                      cout << "Error data, try again..." << endl; 
                      system("pause");
        }
    }while(key);
}

int main(){
    Menu();
    return 0;
}
