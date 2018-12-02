//
//  sortData.cpp
//  Project4
//
//  Created by Joseph Lovoi on 11/21/18.
//  Copyright © 2018 Joseph Lovoi. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <vector>
#include <chrono>
#include <string>

using namespace std;

class sortData {
protected:
    int N;
    vector<int> elements;
public:
    sortData();
    sortData(int N);
    sortData(vector<int> elements);
    vector<int> bubbleSort(vector<int> elements);
    vector<int> quickSort(vector<int> elements);
    void quickSort(vector<int> &vect, int start, int end);
    int partition(vector<int> &vect, int index, int pivot);
    vector<int> mergeSort(vector<int> elements);
    void mergeSort(int *arr, int start, int end);
    void merge(int *arr, int start, int mid, int end);
    void displayVector(vector<int> sortedElements);
    ~sortData();
};

sortData::sortData() {
    N = 0;
}

sortData::sortData(int N) {
    (*this).N = N;
}

sortData::sortData(vector<int> elements) {
    (*this).elements = elements;
}

vector<int> sortData::bubbleSort(vector<int> elements) {
    // vector to return
    vector<int> ret = elements;
    // int used to swap out-of-order numbers
    int swap;
    // bool used to determine if loop needs to be run again
    bool finished = false;
    
    while (!finished) {
        // if the if statement below is never true for an entire loop, then we are finished
        finished = true;
        for (int i = 0; i < (N - 1); i++) {
            // compare two adjacent numbers
            if (ret[i] > ret[i+1]) {
                // if this is reached, the loop should be run again, so set finished to false
                finished = false;
                swap = ret[i];
                ret[i] = ret[i+1];
                ret[i+1] = swap;
            }
        }
    }
    
    return ret;
}

vector<int> sortData::quickSort(vector<int> elements) {
    // vector to return
    vector<int> ret = elements;
    
    // start recursion
    quickSort(ret, -1, int(ret.size())-1);
    
    return ret;
}

// overloaded recursive function used by quickSort
void sortData::quickSort(vector<int> &vect, int start, int end) {
    if (start < end) {
        // Use end as the pivot
        int pivot = end;
        
        int part = partition(vect, start, pivot);
        
        quickSort(vect, start, part-1);
        quickSort(vect, part, end);
    }
}

// function used to supplement quickSort
int sortData::partition(vector<int> &vect, int index, int pivot) {
    int pivotval = vect[pivot];
    int loop = index + 1;
    //cout << "index: " << index << " pivotval: " << pivot << endl;
    //cout << "new pivot val: " << pivotval << endl;
    
    while (loop <= pivot) {
        // Move the start index right to find index to swap
        if (vect[loop] <= pivotval) {
            index++;
            // swap vect[loop] and vect[index]
            int temp = vect[index];
            vect[index] = vect[loop];
            vect[loop] = temp;
        }
        // increment looping iterator
        loop++;
    }
    // return the new partition index (part)
    return index;
}

vector<int> sortData::mergeSort(vector<int> elements) {
    // vector to return
    vector<int> ret;
    int arr[N];
    int i = 0;
    
    // Store the vector in an array
    for (vector<int>::iterator it = elements.begin(); it != elements.end(); it++) {
        arr[i] = *it;
        i++;
    }
    // start recursion
    mergeSort(arr, 0, N-1);
    
    // Store array into return vector
    for (int i = 0; i < N; i++) {
        ret.push_back(arr[i]);
    }
    
    return ret;
}

void sortData::mergeSort(int *arr, int start, int end) {
    if (start < end) {
        // get middle index
        int mid = (start + end) / 2;
        
        // Recursively call mergsort until we can no longer split vectors in half
        mergeSort(arr, start, mid);
        mergeSort(arr, mid+1, end);
        
        //cout << "calling merge for " << arr[start] << " at " << start << " " << arr[end] << " at " << end << endl;
        merge(arr, start, mid, end);
//        for (int i = 0; i < N; i++) {
//            cout << arr[i] << " ";
//        }
//        cout << endl << endl;;
    }
}

void sortData::merge(int *arr, int start, int mid, int end) {
    int i = start;
    int k = start;
    int j = mid + 1;
    int temp[end];
    
    while (i <= mid && j <= end) {
        if (arr[i] < arr[j]) {
            temp[k] = arr[i];
            i++;
        }
        else {
            temp[k] = arr[j];
            j++;
        }
        k++;
    }
    
    if (i > mid) {
        for (int it = j; it <= end; it++) {
            temp[k] = arr[it];
            k++;
        }
    }
    else{
        for (int it = i; it <= mid; it++) {
            temp[k] = arr[it];
            k++;
        }
    }
    
    for (int it = start; it <= end; it++) {
        arr[it] = temp[it];
    }
}

void sortData::displayVector(vector<int> sortedElements) {
    int i = 0;
    cout << "Printing sorted elements: " << endl;
    for (auto it = sortedElements.begin(); it != sortedElements.end(); it++) {
        if (i % 25 == 0) {
            cout << endl;
        }
        
        cout << *it << " ";
        i++;
    }
    cout << endl;
}


int main() {
    
    sortData *sd = nullptr;
    char line[10];
    vector<int> elements;
    vector<int> bubble;
    vector<int> quick;
    vector<int> merge;
    cin.getline(line, 10);
    while (!cin.eof()) {
        if (line[0] == '\r') {
            cin.getline(line, 10);
            continue;
        }
        if (line[0] == 'C') {
            elements.clear();
        }

        if (line[0] == 'N') {
            line[0] = ' ';
            int num = stoi(line);
            sd = new sortData(stoi(line));
            cin.getline(line,10); // blank
            cin.getline(line,10);

            for (int i = 0; i < num; i++) {
//                cout << " Adding: " << line << endl;
                elements.push_back(stoi(line));
                cin.getline(line, 10);
            }
        }

        if (line[0] == 'B') {
            cout << "Bubble: " << endl;
            bubble = (*sd).bubbleSort(elements);
            (*sd).displayVector(bubble);
        }

        if (line[0] == 'Q') {
            cout << "Quick: " << endl;
            quick = (*sd).quickSort(elements);
            (*sd).displayVector(quick);
        }

        if (line[0] == 'M') {
            cout << "Merge: " << endl;
            merge = (*sd).mergeSort(elements);
            (*sd).displayVector(merge);
        }
        cout << "=======================" << line << endl;
        cin.getline(line, 10);
    }
}
