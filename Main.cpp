#include "Account.h"
#include "ATMachine.h"

#include <iostream>
using namespace std;

int main()
{
    int select;
    // 고객 수(100명), ATM 잔금 초기화, 관리자 암호
    ATMachine atm(100, 50000, "admin");

    while (1)
    {
        atm.displayMenu(); // ui 띄우기
        cout << "메뉴를 선택하세요: ";
        cin >> select;
        cout << endl;

        switch (select)
        {
        case 1:
            atm.createAccount();
            break;
        case 2:
            atm.checkMoney();
            break;
        case 3:
            atm.closeAccount();
        case 9:
            return 0; // 소멸자를 명시적으로 호출하면 double free 문제가 뜬다.
        default:
            cout << "번호 확인 후 다시 입력하세요." << endl;
        }
    }
    return 0;
}