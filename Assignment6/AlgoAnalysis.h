#ifndef AlgoAnalysis_H
#define AlgoAnalysis_H

class AlgoAnalysis
{
public:
  AlgoAnalysis();
  AlgoAnalysis(std::string);
  ~AlgoAnalysis();

  void runAnalysis();
private:
  void swap(double *a, double *b);
  void printArray(double myArr[], int size);
  std::string fileName;
  double *myArr1;
  double *myArr2;
  double *myArr3;
  double *myArr4;
  int numOfData;

  int pivot(double myArr[], int start, int end);
  void quickSort(double myArr[], int start, int end);
  void insertionSort(double myArr[], int numOfData);
  void bubbleSort(double myArr[], int numOfData);

  bool isSorted(double myArr[], int numOfData);
  void shuffle(double myArr[], int numOfData);
  void bogoSort(double myArr[], int numOfData);
};
#endif
