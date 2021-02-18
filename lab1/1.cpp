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

/* Основное меню */
void MainMenu(float *&arr, int &n){
    int key;
    do{
        system("cls");
        cout << "------------" << endl;
        cout << "1. Добавить элемент на k-ую позицию" << endl;
        cout << "2. Удалить элемент с k-ой позиции" << endl;
        cout << "3. Добавить элемент после значения" << endl;
        cout << "4. Удалить все элементы с заданным значением" << endl;
        cout << "0. Выход" << endl;
        cout << "------------" << endl;
        PrintArr(arr, n);
        cout << "Выберите номер задания: ";
        cin >> key;

        switch(key){
            case 1: ConMenu(arr, n); break;
            case 2: DeleteEl(arr, n); break;
            case 3: AddElAfter(arr, n); break;
            case 4: DeleteAll(arr, n); break;
            case 0: break;
            default:  system("cls"); 
                      cout << "Неверно введен номер задания, попробуйте еще раз... " << endl; 
                      system("pause");
        }
    }while(key);
}

/* Второстепенное меню для 1 задания */ 
void ConMenu(float *&arr, int &n){
    int key;
    do{
        system("cls");
        cout << "------------" << endl;
        cout << "1. Случайное число" << endl;
        cout << "2. Введенное с клавиатуры" << endl;
        cout << "0. Выход" << endl;
        cout << "------------" << endl;
        PrintArr(arr, n);
        cout << "Выберите способ ввода числа: ";
        cin >> key;

        switch(key){
            case 1: RandAdd(arr, n); break;
            case 2: HandAdd(arr, n); break;
            case 0: break;
            default: system("cls"); 
                     cout << "Неверно введен номер задания, попробуйте еще раз... " << endl; 
                     system("pause");
        }
    }while(key);
}

/* Создание файла */
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

/* Количество чисел в файле */
int CountNum(){
    int count=0, value;
    fstream data("data.txt", ios::in);
    if(data){
        while(data>>value){
            count++;
        }
    }
    else{
        cout << "Файл не открылся" << endl; 
    }
    data.close();
    return count;
}

/* Выделение памяти для массива */
float* CreateArr(int n){
    float *arr = new float[n];
    return arr;
}

/* Заполнение массива данными из файла*/
void FillArr(float *&arr, int &n){
    fstream data("data.txt", ios::in);
    if(data){
        for(int i=0; i<n; i++){
            data >> arr[i];
        }
    }
    else{
        cout << "Не удалось получить данные из файла";
    }
}

void PrintArr(float *arr, int n){
    for(int i=0; i<n; i++) cout<<arr[i]<<", ";
    cout << endl;
    delete[] arr;
}

/* Добавление элемента в массив на k-ую позицию */
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
        cout << "Ошибка";
    }
}

/* Добавление в массив случайного числа */
void RandAdd(float *&arr, int &n){
    int pos;
    float num;
    system("cls");
    PrintArr(arr, n);
    cout << "Введите позицию числа num: ";
    cin >> pos;
    num = rand()*100/RAND_MAX+1;
    AddEl(arr, n, pos, num);
}

/* Ручной ввод числа в массив */
void HandAdd(float *&arr, int &n){
    int pos;
    float num;
    system("cls");
    PrintArr(arr, n);
    cout << "Введите позицию числа num: ";
    cin >> pos;
    cout << "Введите число num: ";
    cin >> num;
    AddEl(arr, n, pos, num);
}

/* Добавление элемента после введенного значения */
void AddElAfter(float *&arr, int &n){
    float findNum, num;
    int pos;
    bool flag=false;
    system("cls");
    PrintArr(arr, n);
    cout << "Введите число, после которого нужно добавить элемент: ";
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
        cout << "1. Случайное число" << endl;
        cout << "2. Введенное число" << endl;
        cout << "Выберите способ ввода числа: ";
        cin >> key;
        switch(key){
            case 1: {
                num = rand()*19/RAND_MAX+1;
                AddEl(arr, n, pos+1, num);
                break;
            }
            case 2: {
                cout << "Введите число num: ";
                cin >> num;
                AddEl(arr, n, pos+1, num);
                break;
            }
        }
       
    }
    else{
        cout << "Такого числа нет в массиве" << endl;
        system("pause");
    }
}

/* Удаление элемента массива с k-ой позиции */
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

/* Удаление элемента с k-ой позиции */
void DeleteEl(float *&arr, int &n){
    int pos;
    system("cls");
    PrintArr(arr, n);
    cout << "Введите позицию числа num: ";
    cin >> pos;
    Delete(arr, n, pos);
}

/* Удаление всех введенных значений в массиве */
void DeleteAll(float *&arr, int &n){
    float findNum;
    int i=0;
    bool flag = false;
    system("cls");
    PrintArr(arr, n);
    cout << "Введите число, значения которого нужно удалить в массиве: ";
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
        cout << "Чисел с таким значением нет в массиве" << endl;
        system("pause");
    }
}