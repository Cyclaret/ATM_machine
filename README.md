# ATM Program (C++)

## 📌 소개
ATM 시뮬레이션 프로그램입니다.  
계좌 생성, 입금, 출금, 해지 등 기본 기능 + 추가기능을 구현하였습니다.

---

## 🛠️ 사용 기술
- C++
- OOP (객체지향 설계)
- Makefile 기반 빌드 자동화

---

## ⚙️ 실행 방법

### 🔧 필수 환경
- **g++ (C++17 이상)**
- **make** (Visual Studio 사용자는 아래 참고)

---

### 🖥️ macOS / Linux 사용자의 경우 (Visaul Studio Code)

```bash
make          # 컴파일 및 실행
```

### 🪟 Windows 사용자의 경우 (Visual Studio)

Visual Studio에서 실행하려면 다음 단계를 따라주세요:

1. **Visual Studio 실행**
2. 새 콘솔 앱 프로젝트 생성 (빈 프로젝트)
3. 기존 소스 파일(`.cpp`, `.h`)을 프로젝트에 추가
4. `Main.cpp`를 시작 파일로 설정
5. `F5` 또는 `Ctrl+F5`로 실행

⚠️ 주의: Visual Studio는 `Makefile`을 사용하지 않습니다. 빌드는 IDE 내부 빌드 시스템을 사용합니다.

---

## 📁 .gitignore 내용

```
# Ignore object files
*.o

# Ignore executable (macOS/Linux)
atm_program

# Ignore executable (Windows)
atm_program.exe

# Ignore VS Code settings
.vscode/

# Ignore macOS system files
.DS_Store
```
