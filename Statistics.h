#ifndef STATISTICS_H
#define STATISTICS_H

#include "Account.h"
#include "ATMachine.h"

class Statistics
{
public:
    static int sum(Account *pArray, int size);     // 계좌 잔고 총합
    static int average(Account *pArray, int size); // 계좌 잔고 평균
    static int min(Account *pArray, int size);     // 계좌 잔고 최소
    static int max(Account *pArray, int size);     // 계좌 잔고 최고
    static void sort(Account *pArray, int size);   // 내림차순 정렬(잔액 기준)
};

#endif