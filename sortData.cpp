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
    sortData(vector<int> elements);
    ~sortData();
    vector<int> bubbleSort(vector<int> elements);
    vector<int> quickSort(vector<int> elements);
    vector<int> mergeSort(vector<int> elements);
    void displayVector(vector<int> sortedElements);
};

sortData::sortData() {
    (*this).N = 0;
    elements = new vector<int>();
}
