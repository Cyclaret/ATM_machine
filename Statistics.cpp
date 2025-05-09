<<<<<<< HEAD
// 통계 관련 함수들은 static 키워드로 구성하여 전역 함수들을 Statistics class에 묶은 느낌의 구현방식
// 아래 멤버 함수들은 기본적으로 객체 배열 pAcctArray를 받아서 배열을 돌며 특정 기능을 수행함

=======
>>>>>>> 33f01fb7c805b403b7ca3b569054f1c035041041
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
<<<<<<< HEAD
{ // 기본적인 bubble sort
=======
{
>>>>>>> 33f01fb7c805b403b7ca3b569054f1c035041041
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