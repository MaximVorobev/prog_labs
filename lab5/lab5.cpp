#include <iostream>
#include <cstring>
#include <fstream>
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


struct DLList{
    struct Node {Watch data; Node* next; Node* prev;};
    Node* F=NULL;
    Node* L=NULL;
    Node* C=NULL;
    int count;

    void Out(Watch);
    void Info();
    void Clear();

    bool MoveNext();
    bool MovePrev();
    bool MoveFirst();
    bool MoveLast();

    bool Init(Watch);
    bool AddNext(Watch);
    bool AddPrev(Watch);
    bool AddFirst(Watch);
    bool AddLast(Watch);

    bool Del(Watch&);
    bool DelNext(Watch&);
    bool DelPrev(Watch&);
    bool DelFirst(Watch&);
    bool DelLast(Watch&);
};

void DLList::Out(Watch data){
    if(!F){
        cout << "List is empty" << endl;
        return;
    }
    Node* temp = F;
    cout << "List: " << endl;;
    do{
        temp->data.Out();
        temp=temp->next;
    }while(temp);
    cout << endl;
}

void DLList::Info(){
    if(count) cout << "List node count: " << count << endl;
    else cout << "List is empty" << endl;
    if(C) cout << "Current node data = "; C->data.Out();
    cout << endl;
}

void DLList::Clear(){
    if(!MoveFirst()){
        cout << "List is empty" << endl;
        return;
    }
    Watch k;
    while (Del(k));
}

bool DLList::MoveFirst(){
    if(!F) return false;
    C = F;
    return true;
}

bool DLList::MoveLast(){
    if(!L) return false;
    C = L;
    return true;
}

bool DLList::MoveNext(){
    if(!F) return false;
    if(!C) { C = F; return true;}
    if(!C->next) return false;
    C = C->next;
    return true;
}

bool DLList::MovePrev(){
    if(!F) return false;
    if(!C) { C = F; return true;}
    if(!C->prev) return false;
    C = C->prev;
    return true;
}

bool DLList::Init(Watch data){
    if(!F){
        F = new Node;
        L = F;
        C = F;
        F->prev = NULL;
        F->next = NULL;
        F->data = data;
        count = 1;
        return true;
    }
    else return false;
}

bool DLList::AddNext(Watch data){
    if(!F) return Init(data);
    Node* temp = C->next;
    C->next = new Node;
    C->next->next = temp;
    C->next->prev = C;
    if(!temp) L = C->next;
    else temp->prev = C->next;
    C = C->next;
    C->data = data;
    count++;
    return true;
}

bool DLList::AddPrev(Watch data){
    if(!F) return Init(data);
    Node* temp = C->prev;
    C->prev = new Node;
    C->prev->next = C;
    C->prev->prev = temp;
    if(!temp) F = C->prev;
    else temp->next = C->prev;
    C = C->prev;
    C->data = data;
    count++;
    return true;
}

bool DLList::AddFirst(Watch data){
    if(MoveFirst()) return AddPrev(data);
    else return Init(data);
}

bool DLList::AddLast(Watch data){
    if(MoveLast()) return AddNext(data);
    else return Init(data);
}

bool DLList::Del(Watch& data){
    if(!F) return false;
    if(!C) return false;
    if(C==F) return DelFirst(data);
    if(C==L) return DelLast(data);
    Node* temp = C->next;
    data = C->data;
    C->prev->next = C->next;
    C->next->prev = C->prev;
    delete C;
    C = temp;
    count--;
    return true;
}

bool DLList::DelNext(Watch& data){
    if(!F) return false;
    if(!C) return false;
    if(MoveNext()) return Del(data);
    return false;
}

bool DLList::DelPrev(Watch& data){
    if(!F) return false;
    if(!C) return false;
    if(MovePrev()) return Del(data);
    return false;
}

bool DLList::DelFirst(Watch& data){
    if(!F) return false;
    if(C!=F) MoveFirst();
    Node* temp = C->next;
    data = C->data;
    if(temp) temp->prev = NULL;
    delete C;
    C = temp;
    F = temp;
    count--;
    if(!temp) { L=NULL; return false;}
    return true;
}

bool DLList::DelLast(Watch& data){
    if(!F) return false;
    if(C!=L) MoveLast();
    Node* temp = C->prev;
    data = C->data;
    if(temp) temp->next = NULL;
    delete C;
    C = temp;
    L = temp;
    count--;
    if(!temp) { F=NULL; return false;}
    return true;
}

void readFile(DLList&);
void Menu();
void AddEl(DLList&);
void DelEl(DLList&);
void SortMenu(DLList&);
void Sort(DLList&, bool);
void Output(DLList);

void readFile(DLList& List){
    Watch w;
    system("cls");
    fstream f_in("input.txt", ios::in);
    if(!f_in){
        cout << "---> Error, there are no input file" << endl;
        return;
    }
    while(f_in >> w.name >> w.color >> w.price >> w.quantity){
        List.AddNext(w);
    }
    f_in.close();
}

void AddEl(DLList& List){
    Watch w;
    int count = List.count, pos, i=1;
    system("cls");
    cout << "Enter product specifications(name, color, price, quantity): " << endl;
    cin >> w.name >> w.color >> w.price >> w.quantity;
    while (w.price<=0 || w.quantity<=0){
        cout << "---> Error data price or quantity <--- " << endl;
        cout << "Price: ";
        cin >> w.price;
        cout << "Quantity: ";
        cin >> w.quantity;
    }
    system("cls");
    cout << "There are " << count << " elements in list" << endl;
    cout << "Enter the position of element: ";
    cin >> pos;
    while (pos > count+1 || pos < 1){
        cout << "Error data pos" << endl;
        cout << "pos = ";
        cin >> pos;
    }

    if (List.MoveFirst() && pos!=1){
        while(i<pos-1){
            List.MoveNext();
            i++;
        }
        List.AddNext(w);
    }
    else List.AddFirst(w);

    system("cls");
    List.Out(w);
    system("pause");
}

void DelEl(DLList& List){
    Watch w;
    int count = List.count, pos, i=1;

    if(List.count == 0){
        cout << "List is empty" << endl;
        system("pause");
        return;
    }
    system("cls");
    List.Out(w);
    cout << "Enter the position of element: ";
    cin >> pos;
    while (pos > count+1 || pos < 1){
        cout << "Error data pos" << endl;
        cout << "pos = ";
        cin >> pos;
    }
    
    if (pos!=1){
        while (i<pos-1){
            List.MoveNext();
            i++;
        }
        List.DelNext(w);
    }
    else List.DelFirst(w);

    cout << "The element was deleted" << endl;
    List.Out(w);
    system("pause");
}

void SortMenu(DLList& List){
    int key;
    do{
        system("cls");
        cout << "------------" << endl;
        cout << "1. Sort integer" << endl;
        cout << "2. Sort string" << endl;
        cout << "0. Exit" << endl;
        cout << "------------" << endl;
        cout << "Enter: ";
        cin >> key;

        switch(key){
            case 1: Sort(List, true); break;
            case 2: Sort(List, false); break;
            case 0: break;
            default:  system("cls"); 
                      cout << "Error data, try again..." << endl; 
                      system("pause");
        }
    }while(key);
}

void Sort(DLList& List, bool flag){
    Watch temp;
    int size = List.count, id;
    system("cls");
    if (size < 2){
        cout << "Not enough items to sort" << endl;
        return;
    }
    for(int i=1; i<size+1; i++){
        List.MoveFirst();
        id = 1;
        for(int j=1; j<size-i+1; j++){
            while(id<j){
                List.MoveNext();
                id++;
            }
            if (flag){
                if (List.C->data.price > List.C->next->data.price){
                    temp = List.C->next->data;
                    List.DelNext(temp);
                    List.MovePrev();
                    List.AddPrev(temp);
                }
            }
            else {
                if ((strcmp(List.C->data.name.c_str(), List.C->next->data.name.c_str()))>0){
                temp = List.C->next->data;
                List.DelNext(temp);
                List.MovePrev();
                List.AddPrev(temp); 
                }
            }
        }
    }
    List.Out(temp);
    system("pause");
}

void Output(DLList List){
    system("cls");
    fstream f_out("output.txt", ios::out);
    if(!f_out){
        cout << "---> Error, there are no output file" << endl;
        return;
    }
    if(List.MoveFirst()){
        for(int i=1; i<List.count+1; i++){
            f_out << i << ". " << List.C->data.name << " " << List.C->data.color << " " << List.C->data.price << " " << List.C->data.quantity << endl;
            List.MoveNext();
        }
    }
    f_out.close();
}

void Menu(){
    DLList List;
    readFile(List);
    int key;
    do{
        system("cls");
        cout << "------------" << endl;
        cout << "1. Add element" << endl;
        cout << "2. Delete element" << endl;
        cout << "3. Sort list" << endl;
        cout << "4. Clear list" << endl;
        cout << "5. Output in file" << endl;
        cout << "0. Exit" << endl;
        cout << "------------" << endl;
        List.Info();
        cout << "Enter: ";
        cin >> key;

        switch(key){
            case 1: AddEl(List); break;
            case 2: DelEl(List); break;
            case 3: SortMenu(List); break;
            case 4: List.Clear(); break;
            case 5: Output(List); break;
            case 0:  List.Clear(); break;
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
