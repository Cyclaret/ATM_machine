#include <iostream>
#include <random>
using namespace std;

#include "ATMachine.h"

ATMachine::ATMachine(int size, int balance, string password)
{
    nMaxAccountNum = size;
    nMachineBalance = balance;
    strManagerPassword = password;

    // Account 클래스의 객체 배열 동적 생성
    pAcctArray = new Account[nMaxAccountNum];
    if (pAcctArray == NULL)
    {
        cout << "동적 할당 실패";
        exit(1);
    }
    nCurrentAccountNum = 0; // 개설된 계좌 수 초기화
}

void ATMachine::displayMenu()
{
    cout << "----------------------\n"
         << "-    TUKOREA BANK    -\n"
         << "----------------------" << endl;
    cout << " 1. 계좌 개설\n"
         << "2. 계좌 조회\n"
         << "3. 계좌 해지\n"
         << "9. 업무 종료" << endl;
}

void ATMachine::createAccount()
{
    string name, password;
    // 개설된 계좌 수가 충분히 남아있으면, Account class의 create함수 호출 및 배열에 저장
    if (nCurrentAccountNum < nMaxAccountNum)
    {
        cout << "------  개설  ------" << endl;
        cout << "이름 입력: ";
        cin >> name;
        cout << "암호 입력: ";
        cin >> password;

        // mt19937 방식으로 난수 생성 후 newAccountID에 저장하여 매개변수로 보냄
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> dist(200, 900);
        int newAccountID = dist(gen);

        pAcctArray[nCurrentAccountNum].create(newAccountID, 0, name, password);
        nCurrentAccountNum++;
    }
    else
    { // 이미 배열이 다 찼으면 생성하지 않고 다시 main으로 돌아감
        cout << "더 계좌를 생성할 수 없습니다.";
    }
}

// 아래 checkMoney()는 원본 checkMoney인데, 다른 함수에서 조회 logic이 겹치므로 logic 함수만 따로 빼서 구현하고, 다른 함수에서 걔를 리팩토링하는 방식으로 구현하는 것으로 수정.

// void ATMachine::checkMoney()
// { // 계좌번호 안맞는 경우에 예외처리
//     int tempID;
//     string tempPassword; // cin때문에 잠깐 쓰는 temp변수
//     Account *targetAccount = nullptr;

//     cout << "------  조회  ------" << endl;
//     cout << "계좌번호 입력: ";
//     cin >> tempID;
//     cout << "비밀번호 입력: ";
//     cin >> tempPassword;
//     for (int i = 0; i < nCurrentAccountNum; i++)
//     {
//         if (pAcctArray[i].getAcctID() == tempID)
//         {
//             targetAccount = &pAcctArray[i]; // targetAccount에 i 위치를 기억하도록
//             break;
//         }
//     }
//     if (targetAccount == nullptr)
//     {
//         cout << "계좌번호가 맞지 않습니다." << endl;
//         return;
//     }

//     // for 돌다가 맞는 객체 나오면 break 치고 객체에 맞는 check 호출
//     int balance = targetAccount->check(tempID, tempPassword);
//     if (balance == AUTHENTIFICATION_FAIL)
//     {
//         cout << "비밀번호가 맞지 않습니다." << endl;
//     }
//     else
//     {
//         cout << "현재 잔액 : " << balance << endl;
//     }
// }

// 아래 checkMoney()는 targetAccount를 사용 안하고 check()를 2번 호출하는 방식. 동작은 똑같으나, 설계 관점상 자원 소모가 크고 가독성이 떨어짐. 설계 규칙에 안 맞음.

// void ATMachine::checkMoney()
// {
//     int tempId, balance = -1;
//     string tempPassword;

//     cout << "------  조회  ------" << endl;
//     cout << "계좌번호 입력: ";
//     cin >> tempId;
//     cout << "비밀번호 입력: ";
//     cin >> tempPassword;

//     for (int i = 0; i < nCurrentAccountNum; i++)
//     {
//         if (pAcctArray[i].check(tempId, tempPassword) != AUTHENTIFICATION_FAIL)
//         {
//             balance = pAcctArray[i].check(tempId, tempPassword);
//             break;
//         }
//     }
//     if (balance == -1)
//     {
//         cout << "계좌 또는 비밀번호가 맞지 않습니다." << endl;
//         return;
//     }
//     cout << "현재 잔액 : " << balance << endl;
// }

Account *ATMachine::findAndAuthAccount(int id, string password)
{
    for (int i = 0; i < nCurrentAccountNum; i++)
    {
        if (pAcctArray[i].check(id, password) != AUTHENTIFICATION_FAIL)
        {
            return &pAcctArray[i]; // 맞는 객체 위치 return
        }
    }
    return nullptr; // 계좌 혹은 비번 안맞으면 return nullptr
}

void ATMachine::checkMoney()
{
    int tempId;
    string tempPassword;

    cout << "------  조회  ------" << endl;
    cout << "계좌번호 입력: ";
    cin >> tempId;
    cout << "비밀번호 입력: ";
    cin >> tempPassword;

    Account *account = findAndAuthAccount(tempId, tempPassword);
    if (account == nullptr)
    {
        cout << "계좌번호 또는 비밀번호가 맞지 않습니다." << endl;
        return;
    }
    cout << "현재 잔액 : " << account->check(tempId, tempPassword) << endl;
}

ATMachine::~ATMachine() // 소멸자를 만들어놓고 쓸 수가 없네. double free때문에
{
    delete[] pAcctArray;
}

void ATMachine::closeAccount()
{
    int tempId;
    string tempPassword;

    cout << "------  해지  ------" << endl;
    cout << "계좌번호 입력: ";
    cin >> tempId;
    cout << "비밀번호 입력: ";
    cin >> tempPassword;

    Account *account = findAndAuthAccount(tempId, tempPassword);
    if (account == nullptr)
    {
        cout << "계좌번호 혹은 비밀번호가 맞지 않습니다." << endl;
    }
    account->close(); // 잔액이 있으면 불가하다고 알려줌
    // 잔액 있는 경우의 예외처리 구간
    if (account->check(tempId, tempPassword) != 0)
    {
        return;
    }
    int indexToDelete = -1;
    for (int i = 0; i < nCurrentAccountNum; i++)
    { // pAcctArray에서 삭제할 객체 index 찾기
        if (&pAcctArray[i] == account)
        {
            indexToDelete = i;
            break;
        }
    }

    if (indexToDelete != -1)
    { // i기준 뒤에 있는 객체들을 한칸씩 앞으로 덮어쓰기 : 배열 한칸 삭제
        for (int i = indexToDelete; i < nCurrentAccountNum - 1; i++)
        {
            pAcctArray[i] = pAcctArray[i + 1];
        }
        nCurrentAccountNum--; // 전체 생성된 게좌 수 하나 줄임
        cout << tempId << " 계좌가 해지되었습니다. 감사합니다." << endl;
    }
}