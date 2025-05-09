#include <iostream>
using namespace std;

#include "CustomerSvc.h"

CustomerSvc::CustomerSvc(Account *acctArray, int nCurrentAccountNum)
{
    // 생성자
    this->acctArray = acctArray;
    this->nCurrentAccountNum = nCurrentAccountNum;
}

void CustomerSvc::updatePasswdReq()
{
    // Account class의 updatePasswd()를 호출함. 거기서 실제 변경
    int tempId;
    string oldPasswd, newPasswd;

    cout << "------  이체  ------" << endl;
    cout << "계좌번호 입력: ";
    cin >> tempId;
    cin.ignore();
    cout << "기존비번 입력: ";
    getline(cin, oldPasswd);
    cout<<"신규비번 입력: ";
    getline(cin, newPasswd);

    Account *account = nullptr;
    for(int i=0;i<nCurrentAccountNum;i++) {
        if (acctArray[i].getAcctID() == tempId) {
            account = &acctArray[i];
            break;
        }
    }

    if (account == nullptr) {
        cout<<"존재하지 않는 계좌입니다."<<endl;
        return;
    }

    // pAcctArray에서 정확한 위치를 찾고, 비밀번호를 수정하는 Account 클래스의 updatePasswd 함수 호출
    if (account->updatePasswd(oldPasswd, newPasswd)) {
        cout<<"비밀번호를 수정하였습니다."<<endl;
    }
    else {
        cout<<"기존 비밀번호가 일치하지 않습니다."<<endl;
    }
}
