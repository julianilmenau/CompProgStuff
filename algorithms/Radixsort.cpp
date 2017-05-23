#include <bits/stdc++.h>
using namespace std;

// ############################################ Array radixsort #########################################################

int getMax(int arr[], int n)
{
	int mx = arr[0];
	for (int i = 1; i < n; i++)
		if (arr[i] > mx)
			mx = arr[i];
	return mx;
}

void countSort(int arr[], int n, int exp)
{
	int output[n]; 
	int i, count[10] = {0};

	for (i = 0; i < n; i++)
		count[ (arr[i]/exp)%10 ]++;

	for (i = 1; i < 10; i++)
		count[i] += count[i - 1];

	for (i = n - 1; i >= 0; i--)
	{
		output[count[ (arr[i]/exp)%10 ] - 1] = arr[i];
		count[ (arr[i]/exp)%10 ]--;
	}
	for (i = 0; i < n; i++)
		arr[i] = output[i];
}

void radixsort(int arr[], int n)
{
	int m = getMax(arr, n);

	for (int exp = 1; m/exp > 0; exp *= 10)
		countSort(arr, n, exp);
}


// ############################################ Array<Pair> radixsort #########################################################

int pairGetMax(pair<int,int> arr[], int n)
{
	int mx = arr[0].second;
	for (int i = 1; i < n; i++)
		if (arr[i].second > mx)
			mx = arr[i].second;
	return mx;
}

void pairCountSort(pair<int,int> arr[], int n, int exp)
{
	pair<int,int> output[n]; 
	int i, count[10] = {0};

	for (i = 0; i < n; i++)
		count[ (arr[i].second/exp)%10 ]++;

	for (i = 1; i < 10; i++)
		count[i] += count[i - 1];

	for (i = n - 1; i >= 0; i--)
	{
		output[count[ (arr[i].second/exp)%10 ] - 1] = arr[i];
		count[ (arr[i].second/exp)%10 ]--;
	}
	for (i = 0; i < n; i++)
		arr[i] = output[i];
}

void pairRadixsort(pair<int,int> arr[], int n)
{
	int m = pairGetMax(arr, n);
	

	for (int exp = 1; m/exp > 0; exp *= 10)
		pairCountSort(arr, n, exp);
}

// ###################################  PRINTING   ################################################

void print(int arr[], int n)
{
	for (int i = 0; i < n; i++)
		cout << arr[i] << " ";
}

void pairPrint(pair<int,int> arr[], int n)
{
	for (int i = 0; i < n; i++)
		cout << arr[i].first << " ";
}

int main()
{
  	ios_base::sync_with_stdio(false);
  	cin.tie(NULL);
  
	int arr[] = {170, 45, 75, 90, 802, 24, 2, 66};
	pair<int,int> arr2[] = {make_pair(1,170), make_pair(2,45), make_pair(3,75), make_pair(4,90), make_pair(5,802), make_pair(6,24),make_pair(7,2), make_pair(8,66)};
	int n = sizeof(arr)/sizeof(arr[0]);
	radixsort(arr, n);
	pairRadixsort(arr2,n);
	print(arr, n);
	cout<<endl;
	pairPrint(arr2,n);
	return 0;
}
