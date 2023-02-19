#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

/**
void selectionSort(int arr[], int l, int h)
{
    if(l == h){
        return;
    }

    int min = 100001;

    int i, minIndx = 0;

    for(i = l ; i <= h ; i++){
        if(min > arr[i]){
            min = arr[i];
            minIndx = i;
        }
    }

    int t = arr[l];

    arr[l] = arr[minIndx];
    arr[minIndx] = t;

    return selectionSort(arr, l+1, h);
}
*/

void selectionSort2(int arr[], int l, int h)
{
    int min, i, minIndx;

    for(;l != h; l++){
        min = 100001;

        minIndx = 0;

        for(i = l ; i <= h ; i++){
            if(min > arr[i]){
                min = arr[i];
                minIndx = i;
            }
        }

        int t = arr[l];

        arr[l] = arr[minIndx];
        arr[minIndx] = t;

    }

    return;
}


int main()
{
    int n, i, j;

    cin >> n;

    int arr[n];

    for(i = 0; i < n; i++){
        ///best
        //arr[i] = i;
        ///average2
//        arr[i] = rand() % n;
        ///worst
        arr[i] = n-i;
//        cout << arr[i] << ' ';
    }

    cout << endl;

    clock_t t = clock();

    for(i = 0; i < 100; i++){
        selectionSort2(arr, 0, n-1);
    }

    t = clock() - t;

//    for(i = 0; i < n; i++){
//        cout << arr[i] << ' ';
//    }

    cout << endl;

    cout << t << endl;

    return 0;
}
