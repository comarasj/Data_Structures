/* Homework2.cpp

Stephen Comarata & Dylan Wheeler

EECE 4040 Fall 2019
Homework 2
Merge Sort versus Quick Sort using Insertion Sort as the threshold

*/

#include <iostream>
using namespace std;

int threshold;
int merge_counter = 0;
int quick_counter = 0;

void insertionSort(int arr[], int l, int r)
{
    for (int i = l; i <= r; i++)
    	{
    		int temp = arr[i];
    		int j = i;
    		while (j >= l && temp < arr[j - 1])
    		{
    			arr[j] = arr[j - 1];
    			j--;
    		}
    		arr[j] = temp;
    	}
}

void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r)
{
    
    if (l < r)
    {
        if (l + r <= threshold ){
            //call insertion sort
            //bootstrap condition
            // cout << "Insertion sort called by merge sort\n";
            insertionSort(arr, l, r);
        } else {  
            int m = l + (r - l) / 2;
            merge_counter++;
            mergeSort(arr, l, m);
            mergeSort(arr, m + 1, r);

            merge(arr, l, m, r);
        }
    }
}

int partition(int arr[], int low, int high)
{
    int pivot = arr[high]; // pivot
    int i = (low - 1);     // Index of smaller element

    for (int j = low; j < high; j++)
    {
        // If current element is smaller than or
        // equal to pivot
        if (arr[j] <= pivot)
        {
            i++; // increment index of smaller element
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        if (low + high <= threshold){
            //call insertion sort 
            //bootstrap condition
            cout << "Insertion sort called by quick sort\n";
            insertionSort(arr, low, high);
        } else {
            int p = partition(arr, low, high);
            quick_counter++;
            quickSort(arr, low, p - 1);
            quickSort(arr, p + 1, high);
        }
    }
}

void show(int A[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        cout << A[i] << "\n";
}



int main()
{
    int choice = 0, repeat = 0;


while(repeat == 0){
    cout << "This program displays the usage of two sorting methods, Mergesort and Quicksort. It is done using Insertionsort as a thresholdsort." ;
    cout << "\nEnter threshold value: ";
    cin >> threshold;


// Creating the array that will be sorted
    int* arr = NULL;	
    int size;
    cout << "\nEnter the number of elements : ";
    cin >> size;
    arr = new int[size];
    for (int i = 0; i < size; i++){
	arr[i] = 0;
	}
    
    

//Special conditions for if the size is 15 or lower
    if(size <= 15){
	int entry;
	cout << "Enter 1 for manual list entry, Enter 2 for randomly generated \n";
	cin >> entry; 
	cout << "Would you like the list to be displayed? 1 for yes / 2 for no \n";
	cin >> choice;
	if(entry == 1){

		for(int i = 0; i<size; i++){
		cout << "Enter list for element " << i << ": \n";
		cin >> arr[i];
		}
	}
	else if(entry == 2){
		for(int i = 0; i<size; i++){
		arr[i] = rand() % 100;
		}
	}
     }

    if(size > 15){
	for(int i = 0; i<size; i++){
		arr[i] = (rand()%100);
		}
	}
	
	
    /*const int size = 20;
    int arr1[20] = {100, 80, 1, 2, 32, 89, 7, 50, 10, 72, 63, 42, 63, 5, 22, 101, 38, 11, 17, 95};
    int arr2[20] = {100, 80, 1, 2, 32, 89, 7, 50, 10, 72, 63, 42, 63, 5, 22, 101, 38, 11, 17, 95};
     */    
   
 
    int* arr2 = arr;
    mergeSort(arr, 0, size);
    quickSort(arr2, 0, size); 
    cout << "Sorted array\n";
   if (choice == 1){
    cout << "SORTED ARRAY USING MERGESORT\n";
    show(arr, size);
    cout << "\n";

    cout << "SORTED ARRAY USING QUICKSORT\n";
    show(arr2, size);
    cout << "\n";
    }
    cout << "Merge counter=" << merge_counter << "\n";
    cout << "Quick counter=" << quick_counter << "\n";
    merge_counter = 0;
    quick_counter = 0; 

    cout << "To restart, enter 0. To end, enter anything other than 0: \n";
    cin >> repeat;
}
    
    return 0;


}
