#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void insertionSort(int arr[], int l, int h)
{
    if(l == h){
        return;
    }

    int t = arr[l];

    int i;

    for(i = l-1 ; i >= 0 && t < arr[i] ; i--){
        arr[i+1] = arr[i];
    }

    arr[i+1] = t;

    return insertionSort(arr, l+1, h);
}

int main()
{
    int n, i, j;

    cin >> n;

    int arr[n];

    for(i = 0; i < n; i++){
        ///best
 //       arr[i] = i;
        ///average
        arr[i] = rand() % n;
        ///worst
 //       arr[i] = n-i;
    }

    cout << endl;

    clock_t t = clock();

    for(i = 0; i < 100; i++){
        insertionSort(arr, 0, n);
    }

    t = clock() - t;

//    for(i = 0; i < n; i++){
//        cout << arr[i] << ' ';
//    }

    cout << t << endl;

    return 0;
}

