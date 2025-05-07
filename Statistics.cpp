#include "Statistics.h"

int Statistics::sum(Account *pArray, int size)
{
    int total = 0;
    for (int i = 0; i < size; i++)
    {
        total += pArray[i].getBalance();
    }
    return total;
}

int Statistics::average(Account *pArray, int size)
{
    int total = sum(pArray, size);
    return total / size;
}

int Statistics::max(Account *pArray, int size)
{
    int max = pArray[0].getBalance();
    for (int i = 1; i < size; i++)
    {
        if (max < pArray[i].getBalance())
        {
            max = pArray[i].getBalance();
        }
    }
    return max;
}

int Statistics::min(Account *pArray, int size)
{
    int min = pArray[0].getBalance();
    for (int i = 1; i < size; i++)
    {
        if (min > pArray[i].getBalance())
        {
            min = pArray[i].getBalance();
        }
    }
    return min;
}

void Statistics::sort(Account *pArray, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = i; j < size - 1; j++)
        {
            if (pArray[j].getBalance() < pArray[j + 1].getBalance())
            {
                Account temp = pArray[j];
                pArray[j] = pArray[j + 1];
                pArray[j + 1] = temp;
            }
        }
    }
}