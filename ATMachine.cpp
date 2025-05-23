#include <iostream>
#include <random>
#include <iomanip>
using namespace std;

#include "ATMachine.h"
#include "Statistics.h"

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
    cout << "1. 계좌 개설\n"
         << "2. 계좌 조회\n"
         << "3. 계좌 해지\n"
         << "4. 계좌 입금\n"
         << "5. 계좌 출금\n"
         << "6. 계좌 이체\n"
         << "7. 고객 센터\n"
         << "8. 고객 관리\n"
         << "9. 업무 종료" << endl;
}

void ATMachine::createAccount()
{
    string name, password;
    cin.ignore(); // 아래 getline이 사용자 입력으로 받는 Enter를 없애버리는 문제 해결
    // 개설된 계좌 수가 충분히 남아있으면, Account class의 create함수 호출 및 배열에 저장
    if (nCurrentAccountNum < nMaxAccountNum)
    {
        cout << "------  개설  ------" << endl;
        cout << "이름 입력: ";
        getline(cin, name);
        cout << "암호 입력: ";
        getline(cin, password);

        // mt19937 방식으로 난수 생성 후 newAccountID에 저장하여 매개변수로 보냄
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> dist(200, 900);
        int newAccountID;

        do
        { // 계좌번호 생성 후, 같은 계좌번호 있으면 다시 생성
            newAccountID = dist(gen);
            int exist = 0; // 같은 계좌번호 존재 여부

            for (int i = 0; i < nCurrentAccountNum; i++)
            { // 이미 생성된 계좌번호들과 대조
                if (pAcctArray[i].getAcctID() == newAccountID)
                {
                    exist = 1; // 중복이 있다면 for문을 종료
                    break;
                }
            }
            if (!exist)
            { // 중복이 아니라면 break;를 통해 do문을 종료함
                break;
            }
        } while (1); // 처음 1회는 반드시 실행

        pAcctArray[nCurrentAccountNum].create(newAccountID, 0, name, password);
        nCurrentAccountNum++;
    }
    else
    { // 이미 배열이 다 찼으면 생성하지 않고 다시 main으로 돌아감
        cout << "더 계좌를 생성할 수 없습니다.";
        return;
    }
}

// checkMoney(), closeAccount(), depositMoney(), withdrawMoney()에 공통적으로 사용하는, 계좌번호와 비밀번호를 받아 정확한 객체 위치를 반환하는 logic만 떼어 구현하였음
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
    cin.ignore(); // 입력으로 받은 Enter 제거
    cout << "비밀번호 입력: ";
    getline(cin, tempPassword);

    Account *account = findAndAuthAccount(tempId, tempPassword);
    if (account == nullptr)
    {
        cout << "계좌번호 또는 비밀번호가 맞지 않습니다." << endl;
        return;
    }
    cout << "현재 잔액 : " << account->check(tempId, tempPassword) << endl;
}

void ATMachine::closeAccount()
{
    int tempId;
    string tempPassword;

    cout << "------  해지  ------" << endl;
    cout << "계좌번호 입력: ";
    cin >> tempId;
    cin.ignore();
    cout << "비밀번호 입력: ";
    getline(cin, tempPassword);

    Account *account = findAndAuthAccount(tempId, tempPassword);
    if (account == nullptr)
    {
        cout << "계좌번호 혹은 비밀번호가 맞지 않습니다." << endl;
        return;
    }
    int tempBalance = account->check(tempId, tempPassword); // 초기화하기 전 잔액 잠시 보관
    account->close();                                       // 잔액 문제 없는지 확인 후 초기화
    if (tempBalance != 0)
    {
        cout << "잔액이 있어 해지할 수 없습니다." << endl;
        return;
    } // close()에서 잔액 남아서 초기화 못했다면 이 함수도 바로 종료

    // pAcctArray를 돌면서 삭제할 객체 index 찾기
    int indexToDelete = -1;
    for (int i = 0; i < nCurrentAccountNum; i++)
    {
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

void ATMachine::depositMoney()
{
    int tempId, money, balance;
    string tempPassword;

    cout << "------  입금  ------" << endl;
    cout << "계좌번호 입력: ";
    cin >> tempId;
    cin.ignore();
    cout << "비밀번호 입력: ";
    getline(cin, tempPassword);
    cout << "입금액   입력: ";
    cin >> money;

    if (money <= 0)
    {
        cout << "0원 이하의 금액은 입금할 수 없습니다.\n";
        return;
    }

    Account *account = findAndAuthAccount(tempId, tempPassword);
    if (account == nullptr)
    {
        cout << "계좌번호 혹은 비밀번호가 맞지 않습니다." << endl;
        return;
    }
    balance = account->deposit(tempId, tempPassword, money);
    nMachineBalance += money;
    cout << "현재 잔액 : " << balance << endl
         << "입금 완료" << endl;
}

void ATMachine::withdrawMoney()
{
    int tempId, money, balance;

    string tempPassword;
    cout << "------  출금  ------" << endl;
    cout << "계좌번호 입력: ";
    cin >> tempId;
    cin.ignore();
    cout << "비밀번호 입력: ";
    getline(cin, tempPassword);
    cout << "출금액   입력: ";
    cin >> money;

    if (money <= 0)
    {
        cout << "0원 이하의 금액은 출금할 수 없습니다.\n";
        return;
    }

    Account *account = findAndAuthAccount(tempId, tempPassword);
    if (account == nullptr)
    {
        cout << "계좌번호 혹은 비밀번호가 맞지 않습니다." << endl;
        return;
    }
    if (money > nMachineBalance)
    {
        cout << "출금액이 ATM기기의 잔액보다 많습니다." << endl;
        return;
    }

    balance = account->withdraw(tempId, tempPassword, money);
    if (balance == -2) // withdraw에서 잔액 부족의 반환값 처리
    {
        cout << "계좌에 잔액이 부족합니다." << endl;
        return;
    }

    nMachineBalance -= money;
    cout << "현재 잔액 : " << balance << endl
         << "출금 완료" << endl;
}

ATMachine::~ATMachine()
{
    delete[] pAcctArray;
}

void ATMachine::transfer()
{
    int tempId, targetId, money;

    string tempPassword;
    cout << "------  이체  ------" << endl;
    cout << "계좌번호 입력: ";
    cin >> tempId;
    cin.ignore();
    cout << "비밀번호 입력: ";
    getline(cin, tempPassword);

    Account *account = findAndAuthAccount(tempId, tempPassword); // 계좌번호와 비밀번호를 받아 배열에서 정확환 위치 반환
    if (account == nullptr)
    {
        cout << "계좌번호 혹은 비밀번호가 맞지 않습니다." << endl;
        return;
    }
    cout << "이체계좌 입력: ";
    cin >> targetId;
    cout << "이체금액 입력: ";
    cin >> money;

    if (money <= 0)
    {
        cout << "0원 이하의 금액은 이체할 수 없습니다." << endl;
        return;
    }

    // 송금할 계좌 확인 : targetAccount에 송금할 계좌의 위치 저장
    Account *targetAccount = nullptr;

    for (int i = 0; i < nCurrentAccountNum; i++)
    {
        if (pAcctArray[i].getAcctID() == targetId)
        {
            targetAccount = &pAcctArray[i];
            break;
        }
    }

    if (targetAccount == nullptr)
    {
        cout << "송금할 계좌는 존재하지 않는 계좌입니다." << endl;
        return;
    }

    // 자신의 계좌에 잔액이 부족한 경우 withdraw()의 리턴값이 -2다.
    if (account->withdraw(tempId, tempPassword, money) == -2)
    {
        cout << "계좌에 잔액이 부족합니다." << endl;
        return;
    }

    if (targetAccount->deposit(targetId, money))
    {
        cout << "현재 잔액 : " << account->check(tempId, tempPassword) << endl;
        cout << "이체 완료" << endl;
    }
}

void ATMachine::requestSvc()
{
    // CustomerSvc 객체 생성 후 그 멤버 함수 updatePasswdReq() 호출
    CustomerSvc service(pAcctArray, nCurrentAccountNum);
    service.updatePasswdReq();
}

bool ATMachine::isManager(string password)
{
    return (password == strManagerPassword) ? true : false;
}

void ATMachine::displayReport()
{ // 통계 display 출력
    cout << "----------------------\n"
         << "ATM 현재 잔고:     " << nMachineBalance << "원\n"
         << "고객 잔고 총액:     " << Statistics::sum(pAcctArray, nCurrentAccountNum) << "원(총" << nCurrentAccountNum << "명)\n"
         << "고객 잔고 평균:     " << Statistics::average(pAcctArray, nCurrentAccountNum) << "원\n"
         << "고객 잔고 최소:     " << Statistics::min(pAcctArray, nCurrentAccountNum) << "원\n"
         << "고객 잔고 최고:     " << Statistics::max(pAcctArray, nCurrentAccountNum) << "원\n"
         << "----------------------\n"
         << "-  고객 계좌 목록  -\n"
         << "----------------------" << endl;

    Statistics::sort(pAcctArray, nCurrentAccountNum);
    for (int i = 0; i < nCurrentAccountNum; i++)
    { // setw, setfill은 문자열 formatting 관련 가독성 함수.
        cout << i + 1 << ". " << pAcctArray[i].getAccountName() << setw(7) << setfill(' ')
             << pAcctArray[i].getAcctID() << "   " << pAcctArray[i].getBalance() << "원" << endl;
    }
    cout << endl;
}

void ATMachine::managerMode()
{
    string tempPassword;

    cout << "------  관리  ------" << endl;
    cout << "관리자 비밀번호 입력: ";
    cin.ignore();
    getline(cin, tempPassword);

    if (isManager(tempPassword))
    {
        cout << "관리자입니다." << endl;
    }
    else
    {
        cout << "비밀번호가 일치하지 않습니다." << endl;
        return;
    }
    displayReport();
}