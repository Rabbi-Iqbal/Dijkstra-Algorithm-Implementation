#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>

using namespace std;

struct Label {
    int cost;
    int pred;
    bool explored;
};


void createArray(int** &A, int r, int s, Label *&L);
void populateArray(int **A, int n, int p);
void displayArray(int **A, int r);
void dijkstra(int **A, int n, int s, int d, Label *L);
int findMin(Label *L, int n);
void explore(int min, int **A, int n, Label *L);


void createArray(int** &A, int n, int s, Label *&L){
    A = new int *[n];
    L = new Label[n];
    for (int i = 0; i < n; i++)
    {
        A[i] = new int [n];
        L[i].cost = -1;
        L[i].explored = false;
        L[i].pred = -1;
    }
    L[s].cost = 0;
    L[s].pred = -1;
}

void populateArray(int **A, int n, int p){
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++){
            if(j == i) A[i][j] = 0;
            else if(i > j)
                A[i][j] = A[j][i];
            else{
                A[i][j] = rand()%100;
                count++;
            }
        }



    }
    int iteration = (count*(100-p)) / 100;
    for (int i = 0; i < iteration; i++){
        int c = rand() % n ;
        int r = rand() % n ;
        if(A[r][c] == -1 || (r==c))
            i--;
        else
            A[r][c] = A[c][r] = -1;
    }

}

void displayArray(int **A, int r){
    for (int i=0; i<r; i++){
        for (int j = 0; j < r; j++){
            cout<<setw(5)<<left<<A[i][j];
        }
        cout<<endl;
    }

}


int findMin(Label *L, int n){
    int minCost = -1;
    int minIndex = -1;
    for(int i = 0; i < n; i++){
        if(L[i].explored == false){
            if(L[i].cost != -1){
                if(minCost == -1){
                    minCost = L[i].cost;
                    minIndex = i;
                }
                else{
                    if(L[i].cost < minCost){
                        minCost = L[i].cost;
                        minIndex = i;
                    }
                }
            }
        }
    }

    return minIndex;
}

void explore(int min, int **A, int n, Label *L){
    int minCost;
    for(int i = 0; i < n; i++){
        if(L[i].explored == false && A[min][i] != -1 && A[min][i] != A[min][min]){
            if(L[i].cost == -1){
                L[i].cost = A[min][i] + L[min].cost;
                L[i].pred = min;
            }
            else{
                minCost = L[min].cost + A[min][i];
                if(minCost < L[i].cost){
                    L[i].cost = minCost;
                    L[i].pred = min;
                }
            }
        }
    }

    L[min].explored = true;
    cout<<endl;
    cout<<"Label: "<<endl;

    for(int j = 0; j < n; j++){
        cout <<"V: "<<j<<" C: "<<L[j].cost<<" P: "<<L[j].pred<<" E: "<<L[j].explored<<endl;
    }
}

void dijkstra(int **A, int n, int s, int d, Label *L){
    bool found;
    int min;
    while(true){
        min = findMin(L, n);
        if(min == d){
            found = true;
            break;
        }
        else if(min == -1){

            found = false;
            break;
        }
        explore(min, A, n, L);

    }
    if(found == true){
        cout<<"\nCost from source to destination: "<<L[min].cost<<endl;
        cout<<"Path: "<<d;
        int prev = L[min].pred;
        while(true){
            if(prev == -1){
                break;
            }
            else{
                cout<<" <-- "<<prev;
                prev = L[prev].pred;
            }
        }
    }
    else cout<<"Destination cannot be reached.";

}

int main(){
    srand(time(0));
    int **A;
    Label *L;
    cout << "Enter number of nodes: ";
    int n, p, s,d;
    cin>>n;
    cout<<"Enter percentage of connectivity: ";
    cin>>p;
    cout<<"Enter source and destination: ";
    cin>>s>>d;
    createArray(A, n, s, L);
    populateArray(A, n, p);
    displayArray(A, n);
   dijkstra(A, n, s, d, L);
}
