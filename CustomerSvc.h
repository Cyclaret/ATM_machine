#ifndef CUSTOMERSVC_H
#define CUSTOMERSVC_H

#include "Account.h"
#include <string>

class CustomerSvc
{
    Account *acctArray;

    // pdf에 nMaxAccountNum로 되어있지만 현재 계좌의 수만 필요하다고 판단해 nCurrentAccountNum로 사용함
    int nCurrentAccountNum;

public:
    CustomerSvc(Account *acctArray, int nCurrentAccountNum); // 생성자
    void updatePasswdReq();                                  // 비밀번호 변경 함수를 호출하는 멤버 함수
};

#endif#ifndef CUSTOMERSVC_H
#define CUSTOMERSVC_H

#include "Account.h"

#include <string>

class CustomerSvc
{
    Account *acctArray;
    int nCurrentAccountNum;

public:
    CustomerSvc(Account *acctArray, int nCurrentAccountNum);
    void updatePasswdReq();
};

#endif