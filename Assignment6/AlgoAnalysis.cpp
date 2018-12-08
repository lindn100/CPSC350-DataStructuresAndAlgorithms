#include <iostream>
#include "AlgoAnalysis.h"
#include <string>
#include <fstream>
#include <chrono>
#include <bits/stdc++.h> //used for bogosort: REF: https://www.geeksforgeeks.org/bogosort-permutation-sort/
#include <stdlib.h> //for rand

using namespace std;
using namespace std::chrono;

AlgoAnalysis::AlgoAnalysis()
{
  this->fileName = "test.txt";
  //testing that the file exists, if not exits program
  if(!ifstream(fileName))
  {
    cout << "File not found. Exiting program." << endl;
    exit(0);
  }
  //run the simulation
  runAnalysis();
}

AlgoAnalysis::AlgoAnalysis(string x)
{
  this->fileName = x;

  if(!ifstream(fileName))
  {
    cout << "File not found. Exiting program." << endl;
    exit(0);
  }

  runAnalysis();
}

AlgoAnalysis::~AlgoAnalysis()
{
  delete myArr1;
  delete myArr2;
  delete myArr3;
}

void AlgoAnalysis::runAnalysis()
{
  ifstream readFile(fileName);
  readFile >> numOfData;

  myArr1 = new double[numOfData];
  myArr2 = new double[numOfData];
  myArr3 = new double[numOfData];
  myArr4 = new double[numOfData];

  for(int i = 0; i < numOfData; ++i)
  {
    readFile >> myArr1[i];
    myArr2[i] = myArr1[i];
    myArr3[i] = myArr1[i];
    myArr4[i] = myArr1[i];
  }
  auto start = high_resolution_clock::now();
  quickSort(myArr1, 0, numOfData-1);
  auto end = high_resolution_clock::now();
//  printArray(myArr1, numOfData);
  cout << "Total milliseconds elapsed for QuickSort: " << duration_cast<milliseconds>(end-start).count() << endl;

  start = high_resolution_clock::now();
  insertionSort(myArr2, numOfData);
  end = high_resolution_clock::now();
//  printArray(myArr2, numOfData);
  cout << "Total milliseconds elapsed for Insertion Sort: " << duration_cast<milliseconds>(end-start).count() << endl;

  start = high_resolution_clock::now();
  bubbleSort(myArr3, numOfData);
  end = high_resolution_clock::now();
//  printArray(myArr3, numOfData);
  cout << "Total milliseconds elapsed for Bubble Sort: " << duration_cast<milliseconds>(end-start).count() << endl;

  srand(time(0));
  start = high_resolution_clock::now();
  bogoSort(myArr4, numOfData);
  end = high_resolution_clock::now();
//  printArray(myArr4, numOfData);
  cout << "Total milliseconds elapsed for Bogo Sort: " << duration_cast<milliseconds>(end-start).count() << endl;



}

void AlgoAnalysis::swap(double *a, double *b)
{
  double temp = *a;
  *a = *b;
  *b = temp;
}

void AlgoAnalysis::printArray(double myArr[], int size)
{
  for(int i = 0; i < size; ++i)
  {
    cout << myArr[i] << endl;
  }
}

int AlgoAnalysis::pivot(double myArr[], int start, int end)
{
  double pivotValue = myArr[start];
  int pivotPosition = start;

  for(int i = start+1; i <=end; ++i)
  {
    if(myArr[i] < pivotValue)
    {
      swap(&myArr[pivotPosition + 1], &myArr[i]); //swap pivot position and i
      swap(&myArr[pivotPosition], &myArr[pivotPosition+1]); //swap pivot position and pivotposition+1
      ++pivotPosition;
    }
  }
  return pivotPosition;
}

void AlgoAnalysis::quickSort(double myArr[], int start, int end) //low is first index, high is last index
{
    //REF: Visual help: https://www.hackerearth.com/practice/algorithms/sorting/quick-sort/visualize/
  //REF: http://www.cplusplus.com/forum/general/102131/
  int p; //the pivot position

  if(start < end) //if not sorted already
  {
    p = pivot(myArr, start, end); //pick the pivot value as the value in the middle of low and high
    quickSort(myArr, start, p-1); //sort before the pivot
    quickSort(myArr, p+1, end); //sort after the pivot
  }
  return; //on recursive calls where nothing needs to be done, just return
}

void AlgoAnalysis::insertionSort(double myArr[], int numOfData)
{
  //REF here is just notes from in class
  for(int j = 1; j < numOfData; ++j) //start at the second index
  {
    double temp = myArr[j]; //store the marked item
    int k = j; //k is the index at j
    while(k > 0 && myArr[k-1] >= temp)
    {
      myArr[k] = myArr[k-1];//current = previous
      --k; //decrement k
    }
    myArr[k] = temp; //insert temp element into myArr[k] at end of the sorted beginning section
  }
}

void AlgoAnalysis::bubbleSort(double myArr[], int numOfData)
{
  for(int i = 0; i < numOfData; ++i)
  {
    for(int j = 0; j < (numOfData - 1); ++j)
    {
      if(myArr[j] > myArr[j+1])
      {
        swap(&myArr[j], &myArr[j+1]);
      }
    }
  }
}

//REF 4 bogoSort: https://www.geeksforgeeks.org/bogosort-permutation-sort/
//Note: for any big set of data, bogosort takes FOREVER, since its O(infinity)
//for example, a simple list of 10 numbers took it 15910 milliseconds

bool AlgoAnalysis::isSorted(double myArr[], int numOfData)
{
  while(--numOfData > 0)
  {
    if(myArr[numOfData] < myArr[(numOfData-1)])
    {
      return false;
    }
  }
  return true;
}

void AlgoAnalysis::shuffle(double myArr[], int numOfData)
{
  for(int i = 0; i < numOfData; ++i)
  {
    swap(&myArr[i], &myArr[rand()%numOfData]);
  }
}

void AlgoAnalysis::bogoSort(double myArr[], int numOfData)
{
  while(!isSorted(myArr, numOfData))
  {
    shuffle(myArr, numOfData);
  }
}
