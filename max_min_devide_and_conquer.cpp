#include <iostream>

using namespace std;

void MaxMin(int a[], int i, int j, int &Max, int &Min)
{
    if(i == j){
        Max = a[i];
        Min = a[i];
        return;
    }
    if(i == j-1){
        Max = max(a[i], a[j]);
        Min = min(a[i], a[j]);
        return;
    }

    int fmax, fmin, smax, smin;

    MaxMin(a, i, (i+j)/2, fmax, fmin);
    MaxMin(a, (i+j)/2 +1, j, smax, smin);

    Max = max(fmax, smax);
    Min = min(fmin, smin);

    return;
}

int main()
{
    int a[100];

    int n, i, Max, Min;

    cin >> n;

    for(i = 0; i < n; i++){
        cin>> a[i];
    }

    MaxMin(a, 0, n-1, Max, Min);

    cout << Max << ' ' << Min << endl;

    return 0;
}

