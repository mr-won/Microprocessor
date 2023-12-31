# Microprocessor
컴퓨터공학과 마이크로프로세서 실습 정리입니다.
## 종강
![image](https://github.com/mr-won/Microprocessor/assets/58906858/3d0d99f4-207d-4203-84bc-85194fefeb94)
```
GEMS-CRC 모트(ATmeaga2560 마이크로 프로세서 활용 방법)을 다루는 과목으로 전원 및 직렬 통신 케이블 연결, 소프트웨어 개발도구
UART 장치 구동기, 소프트웨어 타이머, 운영체제 타스크, 센서 인터페이스 표준들을 위한 구동기, 부트 로더, 컴파일러 최적화 이슈 등을
포함하고 IOT 모델을 완성하는 인터넷과의 연결 방법을 학습하였습니다.
```

![image](https://github.com/wonttan/Microprocessor/assets/58906858/9f83a623-0375-4f18-b6d3-845993470962)
```
#define PORTE
*(unsigned char)0x180
PORTE = 0x10100000

 16번지로 180번에 0xa0 < 이진수로 10100000

핀의 값을 PE7가 1부터 PE0까지 10100000

PD0 라이트 1꺼지고 0이되면 켜진다

PORTA~PORTB~~~PORTL <- #include <avr/io.h>에 PORT 입출력 장치와 대응시켜놨다.
PORTL 출력하기 위해서는 PORTL
읽을때는 x = PINL
DDRL <- 8비트 (Data Direction Register) < 0과1을 내보내는거 (라이트 출력) 입력용(0), 출력용(1) 입력용으로 쓸건지 출력용으로 쓸건지

3개의 레지스터가 정의되어있다. GPI 범용
```
## 23.09.15 Pjt_01
```
led.c 작성한 후에 led.h를 작성한다.
led.h에는 함수의 프로토타입을 작성하는 데 함수 반환 타입의 오류를 미연에 방지해준다.

main.c에 있는 것들을 led.c 파일로 쪼갠다.

진행 상태를 led로 확인할 수 있다. (led 몇 번을 상황에 따라 설정해서 오류 확인용도로 사용 가능)

unsigned char = uint8_t 
```
## 23.09.15 Pjt_02
![image](https://github.com/wonchihyeon/Microprocessor/assets/58906858/5eff7ee2-c3e4-4dca-99d8-dc1b1ca95e87)   
![image](https://github.com/wonchihyeon/Microprocessor/assets/58906858/200ceecd-7e40-46ed-9b00-9387d56324c4)    
![image](https://github.com/wonchihyeon/Microprocessor/assets/58906858/dc4ee003-5374-4cc1-b361-d7fd2c3c9514)    

```
USART(Universal Synchronous and Asynchronous serial Receiver and Transmitter) registers
serial : 직렬

UART (비동기 : 보내고싶을 때 보냄)

UART 총 4개가 있는데 0번 사용

8비트 레지스터에 쓰게 되면 보내겠다.
UDR0 = 'A'(쓰기)
A = UDR0 (읽기)
읽기/쓰기용도

전송된 것을 (A = UDR0)읽는 순간 소멸
쓰는 순간 전송 시작(UDR0 = A)

속도 조절 Speed
UBRRnL : 0L
UBRRnH : 0H

UCSRnA : Control Register 8비트

sbi(UCSR0A, U2X0) <- UCSR0A 레지스터의 U2XN(==1)번 비트를 1로 변경

cbi(UCSR0B, TXEN0) <- UCSR0B 레지스터의 TXEN0(==3)번 비트를 0으로 변경

끝의 숫자 N이 비트 번호임

개행문자 캐리지 리턴 하나 쓰고 새로운 줄에서
new line이 오면 뒤에 캐리지리턴도 따라서 보내도록 설정한다.

main함수에서 A부터 Z 까지 문자를 보내고 ABCDE~Z 까지 나오고 캐리지리턴을 반복

```
```
txend -> 0 인데 컴파일러가 interrupt는 보지못하고 중간에 변동이 없으니까 그냥 무조건
0으로 넣고 !이되서 1이되서 영원히 반복되는데 이를 방지하기 위해 volatile 키워드를 넣어서 선언해준다.

volatile 휘발성-> 컴파일러가 volatile을 만나면 txend가 자꾸 바뀌는 휘발성변수구나 컴파일러가
언제 바뀔지 모르는 변수임을 알려주는 키워드가 volatile 값을 항상 읽어서 대체한다.
```
## 컴파일러 최적화 기법 Optimization
![image](https://github.com/wonchihyeon/Microprocessor/assets/58906858/95a3175b-c07f-4369-a8e9-6d915ccaac78)
```
a = 10; b = 20; a = 20; 일때 컴파일러가 a = 10;을 날려버림

컴파일러 최적화 기법

상수 접기(Constant folding)

상수 1 * 상수 2 -> 미리 계산한다.
2 * 3.14 * r 변수 일 때 2 * 3.14를 미리 계산한다. 그냥 6.28로 계산할 때보다 빠르다.

상수 전파(Constant Propagation)
r = 5; <- r 이 변하지 않는다.
3.14 * r *r <- r이 5로 변하면서 3.14 * 5 * 5 <- 상수로 대치되서 계산한다.

-Os<-기본적으로 이거쓴다. 상수전파,상수 접기 최적화 등을 한다.
상수 전파 문제가 발생하는데 최적화 옵션을 제거하면 되지 않는가?
-> 컴파일러가 곧이곧대로 번역하기 때문에 내용이 길어짐
국부적으로 해결해야 한다. 전체적인 옵션을 건들여서는 안된다.

운영체제 영역과 어플리케이션 영역을 분리한다.
```
[AVR에서의 cli(), sei()](https://article2.tistory.com/1035)
```
AVR에서의 cli는 Clear Global Interrupt Flag <- 인터럽트를 disabled 시키는 함수이다.
seti) 함수는 Set Global Interrupt Flag의 약자로 인터럽트를 enabled 시키는 함수이다.
```
