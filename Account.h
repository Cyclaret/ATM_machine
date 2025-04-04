#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
using std::string;

#define AUTHENTIFICATION_SUCCESS 1 // 계정 인증 성공
#define AUTHENTIFICATION_FAIL -1   // 계정 인증 실패

class Account
{
private:
    int nID;               // 계좌 번호 (초기 값 = -1), 계좌 해지시 초기값으로 변경
    int nBalance;          // 잔고 (초기 값 = 0)
    string strAccountName; // 고객명
    string strPassword;    // 계좌 비밀번호

private:
    inline bool authenticate(int id, string password)
    {
        return (id == nID) && (password == strPassword);
    }

public:
    Account();
    void create(int id, int money, string name, string password); // 계좌 개설
    int check(int id, string password);                           // return 값 : nBalance(잔고) or 인증 실패(AUTHENTIFICATION_FAIL)
    int getAcctID() { return nID; }                               // 계좌 번호 읽어오기
    void close();
};

#endif