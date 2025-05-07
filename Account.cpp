#include <iostream>
using namespace std;

#include "Account.h"

Account::Account() {}

void Account::create(int id, int money, string name, string password)
{
    nID = id;
    nBalance = money;
    strAccountName = name;
    strPassword = password;

    cout << strAccountName << "님 " << nID << "번 계좌번호가 정상적으로 개설되었습니다. 감사합니다." << endl;
}

int Account::check(int id, string password)
{
    if (authenticate(id, password)) // id, password 인증하는 inline 함수
    {
        return nBalance;
    }
    else
    {
        return AUTHENTIFICATION_FAIL;
    }
}

void Account::close()
{
    // 계좌 보고 잔액이 있으면 해지 불가, 문제 없으면 전부 초기화함
    if (nBalance != 0)
    {
        return;
    }
    nID = -1;
    nBalance = 0;
    strAccountName = "";
    strPassword = "";
}

int Account::deposit(int id, string password, int money)
{
    if (authenticate(id, password))
    {
        nBalance += money;
        return nBalance;
    }
    else
    {
        return AUTHENTIFICATION_FAIL;
    }
}

int Account::withdraw(int id, string password, int money)
{
    if (authenticate(id, password))
    {
        if (nBalance >= money)
        {
            nBalance -= money;
            return nBalance;
        }
        else
        { // 계좌에 잔액이 부족한 경우
            return -2;
        }
    }
    else
    {
        return AUTHENTIFICATION_FAIL;
    }
}

bool Account::deposit(int id, int money)
{
    // id랑 money를 받았어. 정확한 객체 위치로 이미 받은거니까 여기선 단순히 money를 넣고 bool하기만 하면 됨.
    nBalance += money;
    return true;
}

bool Account::updatePasswd(string oldPasswd, string newPasswd)
{
    if (oldPasswd == strPassword)
    {
        strPassword = newPasswd;
        return true;
    }
    return false;
}