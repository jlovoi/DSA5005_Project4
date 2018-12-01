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
    void mergeSort(vector<int> &vect, int start, int end);
    void merge(vector<int> &vect, int start, int mid, int end);
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
    cout << endl;
    // return the new partition index (part)
    return index;
}

vector<int> sortData::mergeSort(vector<int> elements) {
    // vector to return
    vector<int> ret = elements;
    
    // start recursion
    mergeSort(ret, 0, int(ret.size())-1);
    
    return ret;
}

void sortData::mergeSort(vector<int> &vect, int start, int end) {
    if (start < end) {
        // get middle index
        int mid = (start + end) / 2;
        
        // Recursively call mergsort until we can no longer split vectors in half
        mergeSort(vect, start, mid);
        mergeSort(vect, mid+1, end);
        
        merge(vect, start, mid, end);
    }
}

void sortData::merge(vector<int> &vect, int start, int mid, int end) {
    // split the vector in half, store in two temporary vectors
    vector<int> temp1;
    for (int i = start; i < mid; i++) {
        temp1.push_back(vect[i]);
    }
    vector<int> temp2;
    for (int i = mid; i < end; i++) {
        temp2.push_back(vect[i]);
    }
    cout << "start: " << start << " mid: " << mid << " end: " << end << endl;
    cout << "temp1: ";
    for (int x : temp1) {
        cout << x << " ";
    }
    cout << endl << "temp2: ";
    for (int x : temp2) {
        cout << x << " ";
    }
    cout << endl;
    // iterators for these two vectors:
    int t1 = 0;
    int t2 = 0;
    // iterator for the index of the main vector
    int it = start;
    // merge the elements in order
    while (t1 < temp1.size() && t2 < temp2.size()) {
        cout << "it: " << it << endl;
        if (temp1[t1] <= temp2[t2]) {
            vect[it] = temp1[t1];
            t1++;
        }
        else {
            vect[it] = temp2[t2];
            t2++;
        }
        it++;
    }
    
    // add leftover elements that werent added before
    while (t1 < temp1.size()) {
        vect[it] = temp1[t1];
        t1++;
        it++;
    }
    while (t2 < temp2.size()) {
        vect[it] = temp2[t2];
        t2++;
        it++;
    }
    cout << endl;
}

int main() {
    vector<int> elements {5, 3 ,1, 2, 4, 7, 13, 55, 63, 45 ,76, 9, 10};
    sortData *sd = new sortData(5);
    vector<int> merge = (*sd).mergeSort(elements);
    for (int x : merge) {
        cout << x << " ";
    }
    return 0;
}
