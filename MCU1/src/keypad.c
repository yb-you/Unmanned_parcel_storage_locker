#include "stm32f10x.h"
#include <stdio.h>


int mode_Password_Room;
uint8_t Key;
uint8_t Room[3];
int Room_index;

uint8_t Password_correct_101[4]={'1','2','3','4'};
uint8_t Password_in_101[4];
int position_101;
uint8_t Password_correct_102[4]={'4','5','6','7'};
uint8_t Password_in_102[4];
int position_102;
uint8_t Password_correct_103[4]={'7','8','9','0'};
uint8_t Password_in_103[4];
int position_103;
uint8_t Password_correct_104[4]={'1','3','5','7'};
uint8_t Password_in_104[4];
int position_104;

uint8_t new_password[4];
int password_index;
uint8_t new_password2[4];
int password_index2;
int mode_Password_Change;
extern uint8_t lock;
extern uint8_t locking;

extern int usart3_start;
void Key_in_Room(uint8_t Key)////////////////////입력호수 저장 함수///////////////////////
{
    Room[Room_index]=Key;
}

void new_password_in(uint8_t Key)////////////////////새 비밀번호 저장 함수///////////////////////
{
    new_password[password_index]=Key;
}
void new_password_in2(uint8_t Key)////////////////////새 비밀번호 저장 함수2///////////////////////
{
    new_password2[password_index2]=Key;
}
void password_in(uint8_t Key)//////////////////////비밀번호 확인 함수////////////////////////
{
    if(Room[0]=='1'&& Room[1]=='0'&&Room[2]=='1')           //방 호수가 101호 일 경우
        {
            position_102=position_103=position_104=0;
            Password_in_101[position_101]= Key;                 //101호 비밀번호 확인 변수에 저장
        }
    else if(Room[0]=='1'&& Room[1]=='0'&&Room[2]=='2')      //방 호수가 102호 일 경우
        {
            position_101=position_103=position_104=0;   
            Password_in_102[position_102]= Key;                 //102호 비밀번호 확인 변수에 저장
        }
    else if(Room[0]=='1'&& Room[1]=='0'&&Room[2]=='3')
        {
            position_101=position_102=position_104=0;
            Password_in_103[position_103]= Key;
        }
    else if(Room[0]=='1'&& Room[1]=='0'&&Room[2]=='4')
        {
            position_101=position_102=position_103=0;
            Password_in_104[position_104]= Key;
        }
}

void Keypad_password(void)////////////////////////키패드 입력 함수///////////////////////////////////////////
{
    mode_Password_Change=0;

    if(mode_Password_Room==0)//////////초기
    {
        //USART_SendData(USART3, 0);
        delay_m();
        while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
            USART_SendData(USART3, 123);                                //세그먼트를 끈 후
        DelayMs(300);
        while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
            USART_SendData(USART3, 0);                                  //통신 전달 초기화
        lcd16x2_clrscr();
        lcd16x2_put_custom_char(0, 0, 0);
        lcd16x2_puts("Operating lock");                 //LCD 출력
        lcd16x2_put_custom_char(0, 1, 0);
        lcd16x2_puts("push '*'");
        if(Key=='*') {mode_Password_Room=1;   Key='F';}                 //'*'을 누를 경우 다음 모드로 변환
    }
    if(mode_Password_Room==1)/////////////////////////////////////방 호수 입력모드
    {
        delay_m();
        printf("push the Room.no and push '*'\n");          
        lcd16x2_clrscr();
        lcd16x2_put_custom_char(0, 0, 0);
        lcd16x2_puts("push the Room.No");               //LCD출력
        lcd16x2_put_custom_char(0, 1, 0);
        lcd16x2_puts("and push '*'");
        if(Key!='F')                                                    //키패드 입력을 받은 경우
        {
            delay_m();
            Key_in_Room(Key);                                                   //입력 호수 저장
            while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
                USART_SendData(USART3, Key);                                    //입력 호수 통신 전달
            DelayMs(300);                                                       //통신 후
            while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
                USART_SendData(USART3, 0);                                      //통신변수 초기화
            Room_index++;                                                       //다음 방호수 입력
            if(Key=='*')                                                        //'*'을 누를 경우 (입력 끝)
            {
                delay_m();
                while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
                    USART_SendData(USART3, 123);                                     //세그먼트를 끈 후
                DelayMs(300);
                while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
                    USART_SendData(USART3, 0);                                       //통신 변수 초기화
                mode_Password_Room=2; Room_index=0;                                  //다음 모드 변환
            }
            Key='F';
        }
    }
    if(mode_Password_Room==2)////////////////////////////////////방 비밀번호 입력모드
    {
        delay_m();
        if(Room[0]=='1'&& Room[1]=='0'&&Room[2]=='1')               //방 호수가 101호 일 경우
        {
            printf("push the password Room1. and push '#'\n");
            lcd16x2_clrscr();
            lcd16x2_put_custom_char(0, 0, 0);
            lcd16x2_puts("push P/W Room1");                         //LCD출력
            lcd16x2_put_custom_char(0, 1, 0);
            lcd16x2_puts("and push '#'");
            if(Key!='F')                                            //키패드를 입력 받은 경우
            {
                delay_m();
                while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
                    USART_SendData(USART3, 100);                                //방 비밀번호 입력받았다는 변수 100 전달
                DelayMs(300);
                while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
                    USART_SendData(USART3, 0);
                password_in(Key);                                               //방 비밀번호 입력 함수에 전달
                position_101++;                                                 //101호 입력 비밀번호 배열 인덱스 증가
                if(Key=='#')                                                    //'#'을 누를 경우 (입력 끝)
                    {
                        delay_m();
                        while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
                            USART_SendData(USART3, 123);                        //세그먼트를 끈 후
                        DelayMs(300);
                        while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
                            USART_SendData(USART3, 0);                          //통신 변수 초기화
                        mode_Password_Room=3;                                   //다음 모드로 전환
                        position_101=0;
                    }
                Key='F';
            }
        }
        else if(Room[0]=='1'&& Room[1]=='0'&&Room[2]=='2')          //102호일 경우 (101호와 같은 방식)
        {
            printf("push the password Room2. and push '#'\n");
            lcd16x2_clrscr();
            lcd16x2_put_custom_char(0, 0, 0);
            lcd16x2_puts("push P/W Room2");
            lcd16x2_put_custom_char(0, 1, 0);
            lcd16x2_puts("and push '#'");
            if(Key!='F')
            {
                delay_m();
                while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
                    USART_SendData(USART3, 100);
                DelayMs(300);
                while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
                    USART_SendData(USART3, 0);
                password_in(Key);
                position_102++;
                if(Key=='#')
                {
                    delay_m();
                    while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
                        USART_SendData(USART3, 123);
                    DelayMs(300);
                    while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
                        USART_SendData(USART3, 0);
                    mode_Password_Room=3;
                    position_102=0;
                }
                Key='F';
            }
        }
        else if(Room[0]=='1'&& Room[1]=='0'&&Room[2]=='3')          //103호일 경우 (101호와 같은 방식)
        {
            printf("push the password Room3. and push '#'\n");
            lcd16x2_clrscr();
            lcd16x2_put_custom_char(0, 0, 0);
            lcd16x2_puts("push P/W Room3");
            lcd16x2_put_custom_char(0, 1, 0);
            lcd16x2_puts("and push '#'");
            if(Key!='F')
            {
                delay_m();
                while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
                    USART_SendData(USART3, 100);
                DelayMs(300);
                while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
                    USART_SendData(USART3, 0);
                password_in(Key);
                position_103++;
                if(Key=='#')
                {
                    delay_m();
                    while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
                        USART_SendData(USART3, 123);
                    DelayMs(300);
                    while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
                        USART_SendData(USART3, 0);
                    mode_Password_Room=3;
                    position_103=0;
                }
                Key='F';
            }
        }
        else if(Room[0]=='1'&& Room[1]=='0'&&Room[2]=='4')          //104호일 경우 (101호와 같은 방식)
        {
            printf("push the password Room4. and push '#'\n");
            lcd16x2_clrscr();
            lcd16x2_put_custom_char(0, 0, 0);
            lcd16x2_puts("push P/W Room4");
            lcd16x2_put_custom_char(0, 1, 0);
            lcd16x2_puts("and push '#'");
            if(Key!='F')
            {
                delay_m();
                while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
                    USART_SendData(USART3, 100);
                DelayMs(300);
                while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
                    USART_SendData(USART3, 0);
                password_in(Key);
                position_104++;
                if(Key=='#') 
                {
                /*    delay_m();
                    while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
                        USART_SendData(USART3, 123);
                    delay_m();
                    delay_m();
                    delay_m();
                    while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
                        USART_SendData(USART3, 0);
                */
                    mode_Password_Room=3;
                    position_104=0;
                }
                Key='F';
            }
        }
        else                                                //방호수가 존재하지 않을 경우
        {
            delay_m();
            while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
                USART_SendData(USART3, 123);
            DelayMs(300);
            while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
                USART_SendData(USART3, 0);
            printf("Not exist Room.no\n");                  //LCD 출력
            lcd16x2_clrscr();
            lcd16x2_put_custom_char(0, 0, 0);
            lcd16x2_puts("Not exist");
            DelayMs(1000);
            mode_Password_Room=1;                           //이전 모드로 돌아감
        }
     }
    if(mode_Password_Room==3)/////////////////////////////////방비밀번호 확인모드
    {
        if(Room[0]=='1'&& Room[1]=='0'&&Room[2]=='1')                   //101호일 경우
            {
                if((Password_in_101[0]==Password_correct_101[0])            //101호의 정답 비밀번호와 입력 비밀번호가 모두 같을 경우
                    &&(Password_in_101[1]==Password_correct_101[1])
                    &&(Password_in_101[2]==Password_correct_101[2])
                    &&(Password_in_101[3]==Password_correct_101[3]))
                {
                    printf("open Room.101!\n");
                    lcd16x2_clrscr();
                    lcd16x2_put_custom_char(0, 0, 0);
                    lcd16x2_puts("open Room.101");                                      //LCD 출력
                    delay_m();
                    while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
                        USART_SendData(USART3, 11);                                     //101호  열림 변수 11 전달
                        DelayMs(300);                                                   //통신 받을 시간을 준 후
                    while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
                            USART_SendData(USART3, 0);                                  //통신 변수 초기화
                    DelayMs(1000);                 
                    
                    locking=1;                                                          //도어락 열림
                    mode_Password_Room=0;                                               //모드 초기화
                }
                else                                                        //비밀번호가 틀릴 경우
                {
                    printf("not correct\n");
                    lcd16x2_clrscr();
                    lcd16x2_put_custom_char(0, 0, 0);
                    lcd16x2_puts("incorrect P/W");                          //LCD출력
                    DelayMs(1000);
                    mode_Password_Room=0;                                   //모드 초기화
                }
             }
        else if(Room[0]=='1'&& Room[1]=='0'&&Room[2]=='2')             //102호일 경우(101호와 동일)
            {
                if((Password_in_102[0]==Password_correct_102[0])
                    &&(Password_in_102[1]==Password_correct_102[1])
                    &&(Password_in_102[2]==Password_correct_102[2])
                    &&(Password_in_102[3]==Password_correct_102[3]))
                {
                    printf("102correct!\n");
                    lcd16x2_clrscr();
                    lcd16x2_put_custom_char(0, 0, 0);
                    lcd16x2_puts("open Room.102");
                    delay_m();
                    while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
                        USART_SendData(USART3, 21);
                        DelayMs(300);
                    while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
                            USART_SendData(USART3, 0);
                    DelayMs(1000);
                    locking=1;
                    
                    mode_Password_Room=0;
                }
                else
                {
                    printf("not correct\n");
                    lcd16x2_clrscr();
                    lcd16x2_put_custom_char(0, 0, 0);
                    lcd16x2_puts("incorrect P/W");
                    DelayMs(1000);
                    mode_Password_Room=0;
                }
             }
        else if(Room[0]=='1'&& Room[1]=='0'&&Room[2]=='3')             //103호일 경우(101호와 동일)
            {
                if((Password_in_103[0]==Password_correct_103[0])
                    &&(Password_in_103[1]==Password_correct_103[1])
                    &&(Password_in_103[2]==Password_correct_103[2])
                    &&(Password_in_103[3]==Password_correct_103[3]))
                {
                    printf("103correct!\n");
                    lcd16x2_clrscr();
                    lcd16x2_put_custom_char(0, 0, 0);
                    lcd16x2_puts("open Room.103");
                    delay_m();
                    while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
                        USART_SendData(USART3, 31);
                        DelayMs(300);
                    while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
                            USART_SendData(USART3, 0);
                    DelayMs(1000);
                    locking=1;
                    
                    mode_Password_Room=0;
                }
                else
                {
                    printf("not correct\n");
                    lcd16x2_clrscr();
                    lcd16x2_put_custom_char(0, 0, 0);
                    lcd16x2_puts("incorrect P/W");
                    DelayMs(1000);
                    mode_Password_Room=0;
                }
             }
        else                                                                 //104호일 경우(101호와 동일)
            {   
                printf("ROOM4\n");
                if((Password_in_104[0]==Password_correct_104[0])
                    &&(Password_in_104[1]==Password_correct_104[1])
                    &&(Password_in_104[2]==Password_correct_104[2])
                    &&(Password_in_104[3]==Password_correct_104[3]))
                {
                    printf("104correct!\n");
                    lcd16x2_clrscr();
                    lcd16x2_put_custom_char(0, 0, 0);
                    lcd16x2_puts("open Room.104");
                    delay_m();
                    while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
                        USART_SendData(USART3, 41);
                        DelayMs(300);
                    while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
                            USART_SendData(USART3, 0);
                    DelayMs(1000);
                    locking=1;
                    
                    mode_Password_Room=0;
                }
                else
                {
                    printf("not correct\n");
                    lcd16x2_clrscr();
                    lcd16x2_put_custom_char(0, 0, 0);
                    lcd16x2_puts("incorrect P/W");
                    DelayMs(1000);
                    mode_Password_Room=0;
                }
             }
    }
}

void password_change()//////////////////////비밀번호 변경 함수////////////////////////
{
    mode_Password_Room=0;
    if(mode_Password_Change==0)/////////////////////////초기 모드
    {
        /*delay_m();
        while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
            USART_SendData(USART3, 123);
        DelayMs(1000);
        while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
            USART_SendData(USART3, 0);
    */
        lcd16x2_clrscr();
        lcd16x2_put_custom_char(0, 0, 0);
        lcd16x2_puts("Unlocking");
        if(Key=='#') {mode_Password_Change=1; password_index=0; password_index2=0; Key='F';}    //'#'을 누를 경우 다음 모드로 전환
        if(Key=='0') {                                                                          //'0'을 누를 경우 도어락 닫힘
            locking=0;                                                          //도어락 작동
                if(Room[0]=='1'&& Room[1]=='0'&&Room[2]=='1')                           //101호일 경우
                {
                    delay_m();
                    while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
                        USART_SendData(USART3, 10);                                     //101호 닫힘 변수 10 전달 
                        DelayMs(500);                                                   //통신 받을 시간 딜레이
                    while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
                            USART_SendData(USART3, 0);                                  //통신 변수 초기화
                }
                else if(Room[0]=='1'&& Room[1]=='0'&&Room[2]=='2')                           //102호일 경우
                {
                    delay_m();
                    while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
                        USART_SendData(USART3, 20);                                     //102호 닫힘 변수 20 전달 
                        DelayMs(500);
                    while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
                            USART_SendData(USART3, 0);
                }
                else if(Room[0]=='1'&& Room[1]=='0'&&Room[2]=='3')                           //103호일 경우
                {
                    delay_m();
                    while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
                        USART_SendData(USART3, 30);
                        DelayMs(500);
                    while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
                            USART_SendData(USART3, 0);
                }
                else                                                                         //104호일 경우
                {
                    delay_m();
                    while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
                        USART_SendData(USART3, 40);
                        DelayMs(500);
                    while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
                        USART_SendData(USART3, 0);
                }
            password_index=0; password_index2=0; Key='F';
        }
    }
    if(mode_Password_Change==1)/////////////////////////////////////새 비밀번호 입력모드
    {
        delay_m();
        printf("push the new password. and push '#'\n");
        lcd16x2_clrscr();
        lcd16x2_put_custom_char(0, 0, 0);
        lcd16x2_puts("push the newP/W");                            //LCD출력
        lcd16x2_put_custom_char(0, 1, 0);
        lcd16x2_puts("and push '#'");
        if(Key!='F')                                                 //키패드를 입력받은 경우
        {          
            new_password_in(Key);                                           //새 비밀번호 입력함수1에 전달
            password_index++;                                               //다음 자릿수 입력
            if(Key=='#') {mode_Password_Change=2; password_index=0;}        //'#'입력받은 경우 (입력끝) 다음 모드로 전환
            Key='F';
        }
    }
    if(mode_Password_Change==2)////////////////////////////////새 비밀번호 입력2
    {
        delay_m();
        printf("push the new password one more. and push '#'\n");
        lcd16x2_clrscr();
        lcd16x2_put_custom_char(0, 0, 0);
        lcd16x2_puts("push once more");                            //LCD출력
        lcd16x2_put_custom_char(0, 1, 0);
        lcd16x2_puts("and push '#'");
        if(Key!='F')                                                 //키패드를 입력받은 경우
        {          
            new_password_in2(Key);                                           //새 비밀번호 입력함수2에 전달
            password_index2++;                                               //다음 자릿수 입력
            if(Key=='#') {mode_Password_Change=3; password_index2=0;}        //'#'입력받은 경우 (입력끝) 다음 모드로 전환
            Key='F';
        }
    }
    if(mode_Password_Change==3)/////////////////////////////////새 비밀번호 확인모드
    {
        delay_m();
        if((new_password[0]==new_password2[0])                      //입력받은 두 비밀번호가 같은 경우
            &&(new_password[1]==new_password2[1])
            &&(new_password[2]==new_password2[2])
            &&(new_password[3]==new_password2[3]))
            mode_Password_Change=4;                                 //다음 모드로 전환
        else                                                        //입력받은 두 비밀번호가 다를 경우
        {
            printf("not correct!\n");
            lcd16x2_clrscr();
            lcd16x2_put_custom_char(0, 0, 0);
            lcd16x2_puts("incorrect P/W");                                       //LCD출력
            DelayMs(1000);
            mode_Password_Change=0;                                              //모드 초기화
        }
    }
    if(mode_Password_Change==4)///////////////////////////////////비밀번호 변경 모드
    {
        delay_m();
        int i;
        if(Room[0]=='1'&& Room[1]=='0'&&Room[2]=='1')               //101호일 경우
        {
            for(i=0;i<4;i++)
                {
                    Password_correct_101[i]=new_password[i];            //101호 비밀번호 변경
                    mode_Password_Change=5;                             //다음 모드로 전환
                }
        }
        else if(Room[0]=='1'&& Room[1]=='0'&&Room[2]=='2')           //102호일 경우
        {
            for(i=0;i<4;i++)
                {
                    Password_correct_102[i]=new_password[i];
                    mode_Password_Change=5;
                }
        }
        else if(Room[0]=='1'&& Room[1]=='0'&&Room[2]=='3')           //103호일 경우
        {
            for(i=0;i<4;i++)
                {
                    Password_correct_103[i]=new_password[i];
                    mode_Password_Change=5;
                }
        }
        else                                                        //104호일 경우
        {
            for(i=0;i<4;i++)
                {
                    Password_correct_104[i]=new_password[i];
                    mode_Password_Change=5;
                }
        }
    }
    if(mode_Password_Change==5)////////////////////////////비밀번호 변경 완료 모드
    {
        delay_m();
        printf("complete Password change\n");
        lcd16x2_clrscr();
        lcd16x2_put_custom_char(0, 0, 0);
        lcd16x2_puts("change the P/W");             //LCD 출력
        DelayMs(1000);
        mode_Password_Change=0;                     //모드 초기화
    }
            
}