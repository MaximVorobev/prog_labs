#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

void MakeFile();
int CountNum();

float* CreateArr(int);
void FillArr(float *&, int &);
void PrintArr(float *, int);

void AddEl(float *&, int &, int, float, bool);
void RandAdd(float *&, int &);
void HandAdd(float *&, int &);
void AddElAfter(float *&, int &);

void Delete(float *&, int &, int);
void DeleteEl(float *&, int &);
void DeleteAll(float *&, int &);

void MainMenu(float *&, int &);
void ConMenu(float *&, int &);

int main(){
    MakeFile();
    int n=CountNum();
    float *arr = CreateArr(n);
    FillArr(arr, n);
    MainMenu(arr, n);
    delete[] arr;
    arr = NULL;
    return 0;
}

/* �᭮���� ���� */
void MainMenu(float *&arr, int &n){
    int key;
    do{
        system("cls");
        cout << "------------" << endl;
        cout << "1. �������� ����� �� k-�� ������" << endl;
        cout << "2. ������� ����� � k-�� ����樨" << endl;
        cout << "3. �������� ����� ��᫥ ���祭��" << endl;
        cout << "4. ������� �� ������ � ������� ���祭���" << endl;
        cout << "0. ��室" << endl;
        cout << "------------" << endl;
        PrintArr(arr, n);
        cout << "�롥�� ����� �������: ";
        cin >> key;

        switch(key){
            case 1: ConMenu(arr, n); break;
            case 2: DeleteEl(arr, n); break;
            case 3: AddElAfter(arr, n); break;
            case 4: DeleteAll(arr, n); break;
            case 0: break;
            default:  system("cls"); 
                      cout << "����୮ ������ ����� �������, ���஡�� �� ࠧ... " << endl; 
                      system("pause");
        }
    }while(key);
}

/* ����⥯����� ���� ��� 1 ������� */ 
void ConMenu(float *&arr, int &n){
    int key;
    do{
        system("cls");
        cout << "------------" << endl;
        cout << "1. ���砩��� �᫮" << endl;
        cout << "2. ��������� � ����������" << endl;
        cout << "0. ��室" << endl;
        cout << "------------" << endl;
        PrintArr(arr, n);
        cout << "�롥�� ᯮᮡ ����� �᫠: ";
        cin >> key;

        switch(key){
            case 1: RandAdd(arr, n); break;
            case 2: HandAdd(arr, n); break;
            case 0: break;
            default: system("cls"); 
                     cout << "����୮ ������ ����� �������, ���஡�� �� ࠧ... " << endl; 
                     system("pause");
        }
    }while(key);
}

/* �������� 䠩�� */
void MakeFile(){
    int coutNum;
    float randNum;
    srand(time(0));
    fstream data("data.txt", ios::out);
    coutNum = rand() % 20 + 1;
    for(int i=0; i<coutNum; i++){
        randNum = rand()*19/RAND_MAX+1;
        data << randNum << " ";
    }
    data.close();
}

/* ������⢮ �ᥫ � 䠩�� */
int CountNum(){
    int count=0, value;
    fstream data("data.txt", ios::in);
    if(data){
        while(data>>value){
            count++;
        }
    }
    else{
        cout << "���� �� ������" << endl; 
    }
    data.close();
    return count;
}

/* �뤥����� ����� ��� ���ᨢ� */
float* CreateArr(int n){
    float *arr = new float[n];
    return arr;
}

/* ���������� ���ᨢ� ����묨 �� 䠩��*/
void FillArr(float *&arr, int &n){
    fstream data("data.txt", ios::in);
    if(data){
        for(int i=0; i<n; i++){
            data >> arr[i];
        }
    }
    else{
        cout << "�� 㤠���� ������� ����� �� 䠩��";
    }
}

void PrintArr(float *arr, int n){
    for(int i=0; i<n; i++) cout<<arr[i]<<", ";
    cout << endl;
    delete[] arr;
}

/* ���������� ����� � ���ᨢ �� k-�� ������ */
void AddEl(float *&arr, int &n, int pos, float num){
    if (pos>=0 && pos<=n+1){
        n++;
        float *buff = new float[n];
        for(int i=0; i<n-1; i++){
            buff[i] = arr[i];
        }
        for(int i=n-1; i>=pos; i--){
            buff[i] = buff[i-1];
        }
        buff[pos]=num;
        arr = buff;
        delete[] buff;
        buff = NULL;
        PrintArr(arr, n);
    }
    else{
        cout << "�訡��";
    }
}

/* ���������� � ���ᨢ ��砩���� �᫠ */
void RandAdd(float *&arr, int &n){
    int pos;
    float num;
    system("cls");
    PrintArr(arr, n);
    cout << "������ ������ �᫠ num: ";
    cin >> pos;
    num = rand()*100/RAND_MAX+1;
    AddEl(arr, n, pos, num);
}

/* ��筮� ���� �᫠ � ���ᨢ */
void HandAdd(float *&arr, int &n){
    int pos;
    float num;
    system("cls");
    PrintArr(arr, n);
    cout << "������ ������ �᫠ num: ";
    cin >> pos;
    cout << "������ �᫮ num: ";
    cin >> num;
    AddEl(arr, n, pos, num);
}

/* ���������� ����� ��᫥ ���������� ���祭�� */
void AddElAfter(float *&arr, int &n){
    float findNum, num;
    int pos;
    bool flag=false;
    system("cls");
    PrintArr(arr, n);
    cout << "������ �᫮, ��᫥ ���ண� �㦭� �������� �����: ";
    cin >> findNum;
    for(int i=0; i<n; i++){
        if(arr[i] == findNum){
            pos = i;
            flag = true;
            break;
        }
    }
    if (flag){
        int key;
        cout << "1. ���砩��� �᫮" << endl;
        cout << "2. ��������� �᫮" << endl;
        cout << "�롥�� ᯮᮡ ����� �᫠: ";
        cin >> key;
        switch(key){
            case 1: {
                num = rand()*19/RAND_MAX+1;
                AddEl(arr, n, pos+1, num);
                break;
            }
            case 2: {
                cout << "������ �᫮ num: ";
                cin >> num;
                AddEl(arr, n, pos+1, num);
                break;
            }
        }
       
    }
    else{
        cout << "������ �᫠ ��� � ���ᨢ�" << endl;
        system("pause");
    }
}

/* �������� ����� ���ᨢ� � k-�� ����樨 */
void Delete(float *&arr, int &n, int pos){
    if (pos>=0 && pos<=n){
        n--;
        float *buff = new float[n];
        for (int i=0; i<pos; i++){
            buff[i]=arr[i];
        }
        for(int i=pos; i<=n; i++){
            buff[i]=arr[i+1];
        }
        arr = buff;
        delete[] buff;
        buff = NULL;
        PrintArr(arr, n);
    }
}

/* �������� ����� � k-�� ����樨 */
void DeleteEl(float *&arr, int &n){
    int pos;
    system("cls");
    PrintArr(arr, n);
    cout << "������ ������ �᫠ num: ";
    cin >> pos;
    Delete(arr, n, pos);
}

/* �������� ��� ��������� ���祭�� � ���ᨢ� */
void DeleteAll(float *&arr, int &n){
    float findNum;
    int i=0;
    bool flag = false;
    system("cls");
    PrintArr(arr, n);
    cout << "������ �᫮, ���祭�� ���ண� �㦭� 㤠���� � ���ᨢ�: ";
    cin >> findNum;
    while(i!=n){
        if(arr[i] == findNum){
            flag = true;
            Delete(arr, n, i);
            i--;
        }
        i++;
    }
    if(!flag){
        cout << "��ᥫ � ⠪�� ���祭��� ��� � ���ᨢ�" << endl;
        system("pause");
    }
}