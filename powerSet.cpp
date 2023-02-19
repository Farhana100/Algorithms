#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

//vector < vector <char> > powerSet;

void powerSetGenerator(char arr[], long long int size)
{
    long long int x, i, j, a;
    long long int dummy = 1;

    x = (long long)1 << size;

    for(i = 0; i < x; i++){

//        vector<char> v;
        for(j = size-1, a = i; a; j--){
            if(a & 1){
//                cout << arr[j] << ' ';
//                v.push_back(arr[j]);
            }

            a = a >> 1;
        }

        //powerSet.push_back(v);
//        cout << endl;
    }
}

int main()
{
    long long int size, maxSize = 30;
    long long int i, j;
    char c;

    clock_t t;

    for(size = 5; size <= maxSize; size++){
        char arr[size];

        ///populating
        t = clock();
        for(int m = 10000; m; m--){
            for(i = 0; i < size; i++){
                for(c = 0;!(c >= '0' and c <= '9' ) and !(c >= 'A' and c <= 'Z' ) and !(c >= 'a' and c <= 'z' );c = '0' + rand() % ('z' - '0'));
                arr[i] = c;
    //            cout << c << ' ';
            }
        }

//        cout << endl;
        t = clock() - t;

        cout << "Size: " << size << endl;

        cout << "Population time: " << t << endl;

        ///running algorithm
        t = clock();
        powerSetGenerator(arr, size);
        t = clock() - t;
        cout << "Algorithm running time: " << t << endl;

//        for(i = 0; i < powerSet.size() ; i++)
//        {
//            for(j = 0; j < powerSet[i].size(); j++){
//                cout << powerSet[i][j] << ' ';
//            }
//
//            cout << endl;
//        }
    }

    return 0;
}

