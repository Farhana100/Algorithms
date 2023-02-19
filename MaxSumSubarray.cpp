#include <iostream>

using namespace std;

void CrossSum(int a[], int low, int mid, int high, int &Max_left, int &Max_right, int &cross)
{
    int leftSum = -99999, rightSum = -99999, sum = 0, i;

    for(i = mid; i >= low; i--){
        sum += a[i];
        if(sum > leftSum){
            leftSum = sum;
            Max_left = i;
        }
    }
    sum = 0;
    for(i = mid+1; i <= high; i++){
        sum += a[i];
        if(sum > rightSum){
            rightSum = sum;
            Max_right = i;
        }
    }

    cross = leftSum + rightSum;
    return;
}


void MaxSumSubarray(int a[], int i, int j, int &Max_left, int &Max_right, int &Max_sum)
{
    if(i == j){
        Max_left = i;
        Max_right = i;
        Max_sum = a[i];
        return;
    }

    int fml, sml, cml, fmr, smr, cmr, fms, sms, cms;

    MaxSumSubarray(a, i, (i+j)/2, fml, fmr, fms);
    MaxSumSubarray(a, (i+j)/2  + 1, j, sml, smr, sms);
    CrossSum(a, i, (i+j)/2, j, cml, cmr, cms);

    if(cms > fms){
        if(cms > sms){
            ///cms
            Max_left = cml;
            Max_right = cmr;
            Max_sum = cms;
        }
        else{
            ///sms

            Max_left = sml;
            Max_right = smr;
            Max_sum = sms;
        }
    }
    else{
        if(fms > sms){
            ///fms

            Max_left = fml;
            Max_right = fmr;
            Max_sum = fms;
        }
        else{
            ///sms
            Max_left = sml;
            Max_right = smr;
            Max_sum = sms;
        }
    }

    return;
}

int main()
{
    int a[100];

    int n, i, Max_left, Max_right, Max_sum;

    cin >> n;

    for(i = 0; i < n; i++){
        cin>> a[i];
    }

    MaxSumSubarray(a, 0, n-1, Max_left, Max_right, Max_sum);

    cout << Max_left << ' ' << Max_right << ' ' << Max_sum << endl;

    return 0;
}

