#include <string>
#include <iostream>
#include <map>
#include <algorithm>
#include <bits/stdc++.h>
#include <vector>

using namespace std;



/* This funt merges two sorted arrays and returns inversion count in
   the arrays.*/
uint64_t merge(int arr[], int temp[], int left, int mid, int right){
  uint64_t i, j, k;
  uint64_t inv_count = 0;

  i = left; /* i is index for left subarray*/
  j = mid;  /* j is index for right subarray*/
  k = left; /* k is index for resultant merged subarray*/
  while ((i <= mid - 1) && (j <= right))
  {
    if (arr[i] >= arr[j])
    {
      temp[k++] = arr[i++];
    }
    else
    {
      temp[k++] = arr[j++];

     /*this is tricky -- see above explanation/diagram for merge()*/
      inv_count = inv_count + (mid - i);
    }
  }

  /* Copy the remaining elements of left subarray
   (if there are any) to temp*/
  while (i <= mid - 1)
    temp[k++] = arr[i++];

  /* Copy the remaining elements of right subarray
   (if there are any) to temp*/
  while (j <= right)
    temp[k++] = arr[j++];

  /*Copy back the merged elements to original array*/
  for (i=left; i <= right; i++)
    arr[i] = temp[i];

  return inv_count;
}



uint64_t _mergeSort(int arr[], int temp[], int left, int right) {
  uint64_t mid, inv_count = 0;
  if (right > left)
  {
    /* Divide the array into two parts and call _mergeSortAndCountInv()
       for each of the parts */
    mid = (right + left)/2;

    /* Inversion count will be sum of inversions in left-part, right-part
      and number of inversions in merging */
    inv_count  = _mergeSort(arr, temp, left, mid);
    inv_count += _mergeSort(arr, temp, mid+1, right);

    /*Merge the two parts*/
    inv_count += merge(arr, temp, left, mid+1, right);
  }
  return inv_count;
}


uint64_t mergeSort(int arr[], int array_size)
{
    int *temp = (int *)malloc(sizeof(int)*array_size);
    return _mergeSort(arr, temp, 0, array_size - 1);
}

int main() {


  int list_count;
  cin >> list_count;
  for (int i = 0; i < list_count; i++) {
      int students;
      cin >> students;

      int student_list[students] = {0};
      for (int j = 0; j < students; j++) {
        cin >> student_list[j];
      }
      cout << mergeSort(student_list,students) << endl;

  }
}
