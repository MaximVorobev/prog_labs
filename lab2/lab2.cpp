#include <iostream>
#include <cstdlib>
#include <fstream>
#include <ctime>
#include <cmath>
#include <iomanip>
using namespace std;

// Создание матриц
int GetN();
void NewMatr(double**&, int, int);

// Заполнение матрицы
bool GetFileMatr(double**, int, int);
void GetRandMatr(double**, int, int, int, int);
void GilbertMatr(double**, int, int);

// Вывод матриц
void PrintMatr(double**, int, int, const char*);
void PrintVect(double*, int, const char*);

// Операции с матрицами
void FindLead(double**, int);
void Mult(double**, double**, double**, int, int, int, int);
void triangMatr(double**, double**, int, bool);
double determMatr(double**, int, bool);
void Solve(double**, int, double*, bool);
void SolveSL(double**, int);
void InvMatr(double**, int);
void ErrCalc(double**, int);
void DelMatr(double**&, int);
void DelVect(double*&);

// Меню пользователя
void MainMenu(double**, int, int, const char*);
void GetMatr(double**, int, int);

int count = 0;  // Подсчет перестановок строк и столбцов

int main(){
    int n;
    cout << "Введите размерность матрицы: ";
    n=GetN();
    double** A;
    NewMatr(A, n, n+1);
    GetMatr(A, n, n+1);
    DelMatr(A, n);
    return 0;
}

/* Пользовательское меню */
void MainMenu(double** M, int n, int m, const char* namematr){
    int key;
    do{
        system("cls");
        cout << "------------" << endl;
        cout << "1. Решение СЛАУ методом Гаусса" << endl;
        cout << "2. Вычисление определителя матрицы системы" << endl;
        cout << "3. Обратная матрица системы" << endl;
        cout << "4. Вычисление погрешности" << endl;
        cout << "0. Выход" << endl;
        cout << "------------" << endl;
        PrintMatr(M, n, m, namematr);
        cout << "Выберите номер задания: ";
        cin >> key;

        switch(key){
            case 1: SolveSL(M, n); break;
            case 2: determMatr(M, n, 1); break;
            case 3: InvMatr(M, n); break;
            case 4: ErrCalc(M, n); break;
            case 0: break;
            default:  system("cls"); 
                      cout << "Неверно введен номер задания, попробуйте еще раз... " << endl; 
                      system("pause");
        }
    }while(key);
}

/* Функция получения размера матрицы */
int GetN(){
    float n;
    do{
        cin>>n;
        if(n<=0 || (n-(int)n))
            cout << " ---Ошибка, попробуйте еще раз ...";    
    }while(n<=0 || (n-(int)n));
    return n;
}

/* Функция выделения памяти */
void NewMatr(double**& M, int n, int m){
    M=new double*[n];
    for(int i=0; i<n; i++)
        M[i] = new double [m];
}

/* Функция получения матрицы из файла */
bool GetFileMatr(double** M, int n, int m){
    fstream data("data.txt", ios::in);
    if(!data){
        cout << "--- Ошибка, файл не был найден" << endl;
        return false;
    }
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            if(!(data>>M[i][j])){
                cout << "--- Ошибка, данных недостаточно" << endl;
                data.close();
                return false;
            }
    data.close();
    return true;
}

/* Заполнение матрицы случайными числами */
void GetRandMatr(double** M, int n, int m, int a, int b){
    srand(time(0));
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            M[i][j] = rand() % (b-a-1) - a;
}

void GilbertMatr(double** M, int n, int m){
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            M[i][j] = 1./(i+j+1);
}

/* Родительское меню */
void GetMatr(double** M, int n, int m){
    int key;
    do{
        system("cls");
        cout << "------------" << endl;
        cout << "1. Файл" << endl;
        cout << "2. Случайные числа" << endl;
        cout << "3. Матрица Гилберта" << endl;
        cout << "0. Выход" << endl;
        cout << "------------" << endl;
        cout << "Выберите способ ввода: ";
        cin >> key;

        switch(key){
            case 1: GetFileMatr(M, n, n+1); MainMenu(M, n, n+1, "A"); break;
            case 2: GetRandMatr(M, n, n+1, -1, 2); MainMenu(M, n, n+1, "A"); break;
            case 3: GilbertMatr(M, n, n+1); MainMenu(M, n, n+1, "A"); break;
            case 0: break;
            default:  system("cls"); 
                      cout << "Неверно введен номер задания, попробуйте еще раз... " << endl; 
                      system("pause");
        }
    }while(key);
}

/* Вывод матрицы */
void PrintMatr(double** M, int n, int m, const char* namematr){
    cout << " " << namematr << ":" << endl;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            cout<<setw(12)<<M[i][j];
        }
        cout<<endl;
    }
}

/* Вывод вектора */
void PrintVect(double* x, int n, const char* nameres){
    cout << endl << " " << nameres << ": ";
    for(int i=0; i<n; i++){
        cout<<setw(12)<<x[i];
    }
    cout << endl;
}

/* Поиск ведущего элемента и перестановка строк и столбцов */
void FindLead(double** M, int n){
    int index_i=0, index_j=0, max = M[0][0];
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++){
            if(abs(M[i][j])>max){
                max = M[i][j];
                index_i = i;
                index_j = j;
            }
        }
    int temp;
    count = 0;
    if(index_i!=0)
        count++;
    if(index_j!=0)
        count++;
    if(max!=M[0][0]){
        // Смена строк
        for(int i=0; i<n+1; i++){
            temp = M[index_i][i];
            M[index_i][i] = M[0][i];
            M[0][i] = temp;
        }
        // Смена столбцов
        for(int i=0; i<n; i++){
            temp = M[i][0];
            M[i][0] = M[i][index_j];
            M[i][index_j] = temp;
        }
    }
}

/* Умножение матриц */
void Mult(double** M1, double** M2, double** res, int n1, int m1, int n2, int m2){
    double S=0;
    if(m1!=n2){
        cout << "--- Ошибка, матрицы различной размерности" << endl;
        return;
    }
    for(int i=0; i<n1; i++)
        for(int j=0; j<m2; j++){
            S = 0;
            for(int k=0; k<m1; k++)
                S+=M1[i][k]*M2[k][j];
            res[i][j] = round(S);
        }
}

/* Решение с помощью метода Гаусса */
void triangMatr(double** A, double** B, int n, bool flag){
    double koef;
    for(int i=0; i<n; i++)
        for(int j=0; j<n+1; j++)
            B[i][j] = A[i][j];
    if (flag == 1){
        FindLead(B, n);
        }
    double temp = 0;
    for(int i=1; i<n; i++){
        if(B[i][i] == 0){
            for(int j=i; j<n; j++)
                if(B[j][i] != 0){
                    for(int k=0; k<n+1; k++){
                            temp = B[j][k];
                            B[j][k] = B[i][k];
                            B[i][k] = temp; 
                    }
                    count++;
                }
        }
    }
    for(int k=0; k<n; k++)
        for(int i=k+1; i<n; i++){
            koef = -1.*B[i][k]/B[k][k];
            for(int j=k; j<n+1; j++)
                B[i][j] = B[i][j] + B[k][j]*koef;
        }
}

/* Вычисление определителя матрицы */
double determMatr(double** A, int n, bool flag){
    double **B;
    double determ=1;
    NewMatr(B, n, n+1);
    triangMatr(A, B, n, 1);
    for(int i=0; i<n; i++)
        determ*=B[i][i];
    if(count % 2 == 1)
        determ*=-1;
    if(flag == 1){
        system("cls");
        PrintMatr(B, n, n, "B");
        cout <<"Определитель матрицы системы: " << determ << endl;
        system("pause");
    }
    return determ;
}

void Solve(double** A, int n, double* x, bool flag){
    system("cls");
    if(determMatr(A, n, 0) == 0){
        PrintMatr(A, n, n, "A");
        cout << "СЛАУ не имеет решения" << endl;
        system("pause");
        return;
    }
    double res = 0;
    double **B;
    NewMatr(B, n, n+1);
    if(flag == 1){
        triangMatr(A, B, n, 1);
    }
    else{
        triangMatr(A, B, n, 0);
    }
    for(int i=n-1; i>=0; i--){
        res = 0;
        for(int j=i+1; j<=n-1; j++)
            res = res-x[j]*B[i][j];
        res+=B[i][n];
        x[i]=res/B[i][i];
    }
    PrintMatr(B, n, n+1, "B");
    PrintVect(x, n, "x");
    DelMatr(B, n);
}

void SolveSL(double** M, int n){
    double* x = new double[n];
    Solve(M, n, x, 1);
    DelVect(x);
    system("pause");
}

void InvMatr(double** M, int n){
    double** B;
    double** C;
    double* x = new double[n];
    NewMatr(B, n, n+1);
    NewMatr(C, n, n+1);
    for(int i=0; i<n; i++)
        for(int j=0; j<n+1; j++)
            B[i][j] = M[i][j];
    for(int k=0; k<n; k++){
        for(int i=0; i<n; i++)
            B[i][n] = 0;
        B[k][n] = 1;
        Solve(B, n, x, 0);
        for(int i=0; i<n; i++)
            C[i][k] = x[i];
    }
    system("cls");
    cout << "Обратная матрица системы: " << endl;
    PrintMatr(C, n, n, "C");
    DelVect(x);
    DelMatr(B, n);
    DelMatr(C, n);
    system("pause");
}

void ErrCalc(double** M, int n){
    system("cls");
    double s=0, delta = 0;
    double* x = new double[n];
    double* b = new double[n];
    double* b1 = new double[n];
    for(int i=0; i<n; i++)
        b[i] = M[i][n];
    Solve(M, n, x, 1);
    for(int i=0; i<n; i++){
        s = 0;
        for(int j=0; j<n; j++)
            s+=M[i][j]*x[j];
        b1[i] = s;
    }
    for(int i=0; i<n; i++){
        if(abs(b[i]-b1[i])>delta){
            delta = abs(b[i]-b1[i]);
        }
    }
    DelVect(b);
    DelVect(b1);
    DelVect(x);
    cout << "Погрешность вычислений: " << delta << endl;
    system("pause");
}

/* Очистка памяти */
void DelMatr(double**& M, int n){
    for(int i=0; i<n; i++)
        delete[] M[i];
    delete[] M;
    M = NULL;
}

void DelVect(double*& x){
    delete[] x;
    x = NULL;
}