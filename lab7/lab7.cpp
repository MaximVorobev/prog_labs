#include <iostream>
#include <queue>
#include <fstream>
using namespace std;

int getN();
void feedMatr(int**&, int);
void feedArr(int*&, int);
void Dijkstra(int**, int*&, int, int, int);
int findWay(int**, int*, int, int*&);
void feedFile(int**, int*, int, int*, int);
void DeleteMatr(int**&, int);
void DeleteArr(int*&);


int getN(){
    int num;
    cin >> num;
    while(num < 1){
        cout << "Error data" << endl;
        cin >> num;
    }
    return num;
}

void feedMatr(int**& AMatrix, int N){
    int temp;
    AMatrix = new int* [N];
    for(int i=0; i<N; i++){
        AMatrix[i] = new int [N];
    }
    fstream f_in("input.txt", ios::in);
    if(!f_in){
        cout << "---> Error, there are no input file" << endl;
        return;
    }
    for(int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            if(f_in>>temp){
                AMatrix[i][j] = temp;
            }
        }
    }
}

void feedArr(int*& MarkNode, int N){
    MarkNode = new int [N];
    for(int i=0; i<N; i++){
        MarkNode[i] = INT_MAX;
    }
}

void Dijkstra(int** AMatrix, int*& MarkNode, int N, int begin, int end){
    priority_queue<pair <int, int>> Q;
    begin--; end--;
    MarkNode[begin] = 0;
    Q.push(make_pair(0, begin));
    while(!Q.empty()){
        int len = -Q.top().first;
        int v = Q.top().second;
        Q.pop();
        if (len > MarkNode[v]) continue;
        for (int i=0; i<N; i++){
            int length = AMatrix[v][i];
            if (MarkNode[i] > MarkNode[v] + length && length > 0){
                MarkNode[i] = MarkNode[v] + length;
                Q.push(make_pair(-MarkNode[i], i));
            }
        }
    }
}

int findWay(int** AMatrix, int* MarkNode, int N, int begin, int end, int*& arrNode){
    queue<int> Q;
    arrNode = new int [N];
    int temp = end-1, j = 0;
    arrNode[j] = end;
    while(temp != begin-1){
        for(int i=0; i<N; i++){
            if (AMatrix[temp][i] > 0){
                Q.push(i);
            }
        }
        while(!Q.empty()){
            int node = Q.front();
            if (MarkNode[temp] == MarkNode[node] + AMatrix[temp][node]){
                j++;
                arrNode[j] = node+1;
                temp = node;
            }
            Q.pop();
        }
    }
    j++;
    arrNode[j] = begin;
    return j;
}

void feedFile(int** AMatrix, int* MarkNode, int N, int* arrNode, int len_way){
    fstream f_out("output.txt", ios::out);
    if(!f_out){
        cout << "---> Error, there are no input file" << endl;
        return;
    }

    f_out << "Matrix:\n\t   ";
    for(int i=1; i<N+1; i++){
        f_out << i << " ";
    }
    f_out << "\n";
    for(int i=0; i<N; i++){
        f_out  << "\t" << i+1 << "| ";
        for(int j=0; j<N; j++){
            f_out << AMatrix[i][j] << " ";
        }
        f_out << "\n";
    }

    f_out << "\nMarks of nodes:\n";
    for(int i=0; i<N; i++){
        f_out << "\t" << i+1 << ". " << MarkNode[i] << endl;
    }
    f_out << "\n";
    f_out << "The shortest way from " << arrNode[len_way] << " to " << arrNode[0] << ": " << endl;
    for(int i=len_way-1; i>0; i--){
        f_out << arrNode[i] << "->";
    }
    f_out << arrNode[0];
    f_out.close();
}

void DeleteMatr(int**& AMatrix, int N){
    for(int i=0; i<N; i++){
        delete[] AMatrix[i];
    }
    delete[] AMatrix;
    AMatrix = NULL;
}

void DeleteArr(int*& Arr){
    delete[] Arr;
    Arr = NULL;
}

int main(){
    int begin, end, len_way;
    int N; /* Число вершин */
    cout << "Enter the number of nodes: ";
    N = getN();
    int** AMatrix; /* Матрица смежности */
    int* MarkNode; /* Массив меток вершин */
    int* arrWay;
    feedMatr(AMatrix, N);
    feedArr(MarkNode, N);
    cout << "Enter the starting vertex: ";
    begin = getN();
    cout << "Enter the end vertex: ";
    end = getN();
    while (end == begin){
        cout << "Error end == begin" << endl;
        end = getN();
    }

    Dijkstra(AMatrix, MarkNode, N, begin, end);
    len_way = findWay(AMatrix, MarkNode, N, begin, end, arrWay);
    feedFile(AMatrix, MarkNode, N, arrWay, len_way);

    DeleteMatr(AMatrix, N);
    DeleteArr(MarkNode);
    DeleteArr(arrWay);
    return 0;
}
