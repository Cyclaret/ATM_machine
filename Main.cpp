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
        cout << "메뉴를 선택하세요 (ex: 1, 2, ..., 9) : ";
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
            break;
        case 4:
            atm.depositMoney();
            break;
        case 5:
            atm.withdrawMoney();
            break;
        case 6:
            atm.transfer();
            break;
        case 7:
            atm.requestSvc();
            break;
        case 8:
            atm.managerMode();
            break;
        case 9:
            return 0; // main함수가 끝나며 선언했던 소멸자 호출됨
        default:
            cout << "번호 확인 후 다시 입력하세요." << endl;
        }
    }
    return 0;
}