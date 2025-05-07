#ifndef CUSTOMERSVC_H
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