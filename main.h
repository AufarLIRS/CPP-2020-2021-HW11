#ifndef MAIN_H
#define MAIN_H
#include <vector>

int saveSumInVector(const std::vector<int>& data, int start, int finish)
{
  int sum = 0;
  for (int i = start; i < finish; i++)
  {
    sum += data[i];
  }
  return sum;
}

void multiplyElementsAndSave(std::vector<int>& savingVector, const std::vector<int>& vect1,
                             const std::vector<int>& vect2, int start, int finish)
{
  for (int i = start; i < finish; i++)
  {
    savingVector[i] = vect1[i] * vect2[i];
  }
}

#endif // MAIN_H
