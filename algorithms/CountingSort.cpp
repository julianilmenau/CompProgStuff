#include <bits/stdc++.h>
using namespace std;

//########################################## CountingSort ######################################################

void countSort(int *arr,int n,int range)
{
	int output[n];

	int count[range + 1]={}; 
	int i;

	for(i = 0; arr[i]; ++i)
		++count[arr[i]];

	for (i = 1; i <=range; ++i)
		count[i] += count[i-1];

	for (i = 0; arr[i]; ++i)
	{
		output[count[arr[i]]-1] = arr[i];
		--count[arr[i]];
	}

	for (i = 0; arr[i]; ++i)
		arr[i] = output[i];
}

//##########################################   MAIN   ######################################################

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
	int arr[] = {2,6,10,2,6,4,5};

	countSort(arr,7,15);
	
    for (auto i:arr){
        cout<<i<<endl;
    }

	return 0;
}
