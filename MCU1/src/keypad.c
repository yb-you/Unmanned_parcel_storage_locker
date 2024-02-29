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
void Key_in_Room(uint8_t Key)////////////////////�Է�ȣ�� ���� �Լ�///////////////////////
{
    Room[Room_index]=Key;
}

void new_password_in(uint8_t Key)////////////////////�� ��й�ȣ ���� �Լ�///////////////////////
{
    new_password[password_index]=Key;
}
void new_password_in2(uint8_t Key)////////////////////�� ��й�ȣ ���� �Լ�2///////////////////////
{
    new_password2[password_index2]=Key;
}
void password_in(uint8_t Key)//////////////////////��й�ȣ Ȯ�� �Լ�////////////////////////
{
    if(Room[0]=='1'&& Room[1]=='0'&&Room[2]=='1')           //�� ȣ���� 101ȣ �� ���
        {
            position_102=position_103=position_104=0;
            Password_in_101[position_101]= Key;                 //101ȣ ��й�ȣ Ȯ�� ������ ����
        }
    else if(Room[0]=='1'&& Room[1]=='0'&&Room[2]=='2')      //�� ȣ���� 102ȣ �� ���
        {
            position_101=position_103=position_104=0;   
            Password_in_102[position_102]= Key;                 //102ȣ ��й�ȣ Ȯ�� ������ ����
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

void Keypad_password(void)////////////////////////Ű�е� �Է� �Լ�///////////////////////////////////////////
{
    mode_Password_Change=0;

    if(mode_Password_Room==0)//////////�ʱ�
    {
        //USART_SendData(USART3, 0);
        delay_m();
        while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
            USART_SendData(USART3, 123);                                //���׸�Ʈ�� �� ��
        DelayMs(300);
        while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
            USART_SendData(USART3, 0);                                  //��� ���� �ʱ�ȭ
        lcd16x2_clrscr();
        lcd16x2_put_custom_char(0, 0, 0);
        lcd16x2_puts("Operating lock");                 //LCD ���
        lcd16x2_put_custom_char(0, 1, 0);
        lcd16x2_puts("push '*'");
        if(Key=='*') {mode_Password_Room=1;   Key='F';}                 //'*'�� ���� ��� ���� ���� ��ȯ
    }
    if(mode_Password_Room==1)/////////////////////////////////////�� ȣ�� �Է¸��
    {
        delay_m();
        printf("push the Room.no and push '*'\n");          
        lcd16x2_clrscr();
        lcd16x2_put_custom_char(0, 0, 0);
        lcd16x2_puts("push the Room.No");               //LCD���
        lcd16x2_put_custom_char(0, 1, 0);
        lcd16x2_puts("and push '*'");
        if(Key!='F')                                                    //Ű�е� �Է��� ���� ���
        {
            delay_m();
            Key_in_Room(Key);                                                   //�Է� ȣ�� ����
            while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
                USART_SendData(USART3, Key);                                    //�Է� ȣ�� ��� ����
            DelayMs(300);                                                       //��� ��
            while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
                USART_SendData(USART3, 0);                                      //��ź��� �ʱ�ȭ
            Room_index++;                                                       //���� ��ȣ�� �Է�
            if(Key=='*')                                                        //'*'�� ���� ��� (�Է� ��)
            {
                delay_m();
                while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
                    USART_SendData(USART3, 123);                                     //���׸�Ʈ�� �� ��
                DelayMs(300);
                while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
                    USART_SendData(USART3, 0);                                       //��� ���� �ʱ�ȭ
                mode_Password_Room=2; Room_index=0;                                  //���� ��� ��ȯ
            }
            Key='F';
        }
    }
    if(mode_Password_Room==2)////////////////////////////////////�� ��й�ȣ �Է¸��
    {
        delay_m();
        if(Room[0]=='1'&& Room[1]=='0'&&Room[2]=='1')               //�� ȣ���� 101ȣ �� ���
        {
            printf("push the password Room1. and push '#'\n");
            lcd16x2_clrscr();
            lcd16x2_put_custom_char(0, 0, 0);
            lcd16x2_puts("push P/W Room1");                         //LCD���
            lcd16x2_put_custom_char(0, 1, 0);
            lcd16x2_puts("and push '#'");
            if(Key!='F')                                            //Ű�е带 �Է� ���� ���
            {
                delay_m();
                while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
                    USART_SendData(USART3, 100);                                //�� ��й�ȣ �Է¹޾Ҵٴ� ���� 100 ����
                DelayMs(300);
                while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
                    USART_SendData(USART3, 0);
                password_in(Key);                                               //�� ��й�ȣ �Է� �Լ��� ����
                position_101++;                                                 //101ȣ �Է� ��й�ȣ �迭 �ε��� ����
                if(Key=='#')                                                    //'#'�� ���� ��� (�Է� ��)
                    {
                        delay_m();
                        while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
                            USART_SendData(USART3, 123);                        //���׸�Ʈ�� �� ��
                        DelayMs(300);
                        while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
                            USART_SendData(USART3, 0);                          //��� ���� �ʱ�ȭ
                        mode_Password_Room=3;                                   //���� ���� ��ȯ
                        position_101=0;
                    }
                Key='F';
            }
        }
        else if(Room[0]=='1'&& Room[1]=='0'&&Room[2]=='2')          //102ȣ�� ��� (101ȣ�� ���� ���)
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
        else if(Room[0]=='1'&& Room[1]=='0'&&Room[2]=='3')          //103ȣ�� ��� (101ȣ�� ���� ���)
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
        else if(Room[0]=='1'&& Room[1]=='0'&&Room[2]=='4')          //104ȣ�� ��� (101ȣ�� ���� ���)
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
        else                                                //��ȣ���� �������� ���� ���
        {
            delay_m();
            while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
                USART_SendData(USART3, 123);
            DelayMs(300);
            while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
                USART_SendData(USART3, 0);
            printf("Not exist Room.no\n");                  //LCD ���
            lcd16x2_clrscr();
            lcd16x2_put_custom_char(0, 0, 0);
            lcd16x2_puts("Not exist");
            DelayMs(1000);
            mode_Password_Room=1;                           //���� ���� ���ư�
        }
     }
    if(mode_Password_Room==3)/////////////////////////////////���й�ȣ Ȯ�θ��
    {
        if(Room[0]=='1'&& Room[1]=='0'&&Room[2]=='1')                   //101ȣ�� ���
            {
                if((Password_in_101[0]==Password_correct_101[0])            //101ȣ�� ���� ��й�ȣ�� �Է� ��й�ȣ�� ��� ���� ���
                    &&(Password_in_101[1]==Password_correct_101[1])
                    &&(Password_in_101[2]==Password_correct_101[2])
                    &&(Password_in_101[3]==Password_correct_101[3]))
                {
                    printf("open Room.101!\n");
                    lcd16x2_clrscr();
                    lcd16x2_put_custom_char(0, 0, 0);
                    lcd16x2_puts("open Room.101");                                      //LCD ���
                    delay_m();
                    while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
                        USART_SendData(USART3, 11);                                     //101ȣ  ���� ���� 11 ����
                        DelayMs(300);                                                   //��� ���� �ð��� �� ��
                    while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
                            USART_SendData(USART3, 0);                                  //��� ���� �ʱ�ȭ
                    DelayMs(1000);                 
                    
                    locking=1;                                                          //����� ����
                    mode_Password_Room=0;                                               //��� �ʱ�ȭ
                }
                else                                                        //��й�ȣ�� Ʋ�� ���
                {
                    printf("not correct\n");
                    lcd16x2_clrscr();
                    lcd16x2_put_custom_char(0, 0, 0);
                    lcd16x2_puts("incorrect P/W");                          //LCD���
                    DelayMs(1000);
                    mode_Password_Room=0;                                   //��� �ʱ�ȭ
                }
             }
        else if(Room[0]=='1'&& Room[1]=='0'&&Room[2]=='2')             //102ȣ�� ���(101ȣ�� ����)
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
        else if(Room[0]=='1'&& Room[1]=='0'&&Room[2]=='3')             //103ȣ�� ���(101ȣ�� ����)
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
        else                                                                 //104ȣ�� ���(101ȣ�� ����)
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

void password_change()//////////////////////��й�ȣ ���� �Լ�////////////////////////
{
    mode_Password_Room=0;
    if(mode_Password_Change==0)/////////////////////////�ʱ� ���
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
        if(Key=='#') {mode_Password_Change=1; password_index=0; password_index2=0; Key='F';}    //'#'�� ���� ��� ���� ���� ��ȯ
        if(Key=='0') {                                                                          //'0'�� ���� ��� ����� ����
            locking=0;                                                          //����� �۵�
                if(Room[0]=='1'&& Room[1]=='0'&&Room[2]=='1')                           //101ȣ�� ���
                {
                    delay_m();
                    while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
                        USART_SendData(USART3, 10);                                     //101ȣ ���� ���� 10 ���� 
                        DelayMs(500);                                                   //��� ���� �ð� ������
                    while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
                            USART_SendData(USART3, 0);                                  //��� ���� �ʱ�ȭ
                }
                else if(Room[0]=='1'&& Room[1]=='0'&&Room[2]=='2')                           //102ȣ�� ���
                {
                    delay_m();
                    while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
                        USART_SendData(USART3, 20);                                     //102ȣ ���� ���� 20 ���� 
                        DelayMs(500);
                    while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
                            USART_SendData(USART3, 0);
                }
                else if(Room[0]=='1'&& Room[1]=='0'&&Room[2]=='3')                           //103ȣ�� ���
                {
                    delay_m();
                    while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
                        USART_SendData(USART3, 30);
                        DelayMs(500);
                    while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
                            USART_SendData(USART3, 0);
                }
                else                                                                         //104ȣ�� ���
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
    if(mode_Password_Change==1)/////////////////////////////////////�� ��й�ȣ �Է¸��
    {
        delay_m();
        printf("push the new password. and push '#'\n");
        lcd16x2_clrscr();
        lcd16x2_put_custom_char(0, 0, 0);
        lcd16x2_puts("push the newP/W");                            //LCD���
        lcd16x2_put_custom_char(0, 1, 0);
        lcd16x2_puts("and push '#'");
        if(Key!='F')                                                 //Ű�е带 �Է¹��� ���
        {          
            new_password_in(Key);                                           //�� ��й�ȣ �Է��Լ�1�� ����
            password_index++;                                               //���� �ڸ��� �Է�
            if(Key=='#') {mode_Password_Change=2; password_index=0;}        //'#'�Է¹��� ��� (�Է³�) ���� ���� ��ȯ
            Key='F';
        }
    }
    if(mode_Password_Change==2)////////////////////////////////�� ��й�ȣ �Է�2
    {
        delay_m();
        printf("push the new password one more. and push '#'\n");
        lcd16x2_clrscr();
        lcd16x2_put_custom_char(0, 0, 0);
        lcd16x2_puts("push once more");                            //LCD���
        lcd16x2_put_custom_char(0, 1, 0);
        lcd16x2_puts("and push '#'");
        if(Key!='F')                                                 //Ű�е带 �Է¹��� ���
        {          
            new_password_in2(Key);                                           //�� ��й�ȣ �Է��Լ�2�� ����
            password_index2++;                                               //���� �ڸ��� �Է�
            if(Key=='#') {mode_Password_Change=3; password_index2=0;}        //'#'�Է¹��� ��� (�Է³�) ���� ���� ��ȯ
            Key='F';
        }
    }
    if(mode_Password_Change==3)/////////////////////////////////�� ��й�ȣ Ȯ�θ��
    {
        delay_m();
        if((new_password[0]==new_password2[0])                      //�Է¹��� �� ��й�ȣ�� ���� ���
            &&(new_password[1]==new_password2[1])
            &&(new_password[2]==new_password2[2])
            &&(new_password[3]==new_password2[3]))
            mode_Password_Change=4;                                 //���� ���� ��ȯ
        else                                                        //�Է¹��� �� ��й�ȣ�� �ٸ� ���
        {
            printf("not correct!\n");
            lcd16x2_clrscr();
            lcd16x2_put_custom_char(0, 0, 0);
            lcd16x2_puts("incorrect P/W");                                       //LCD���
            DelayMs(1000);
            mode_Password_Change=0;                                              //��� �ʱ�ȭ
        }
    }
    if(mode_Password_Change==4)///////////////////////////////////��й�ȣ ���� ���
    {
        delay_m();
        int i;
        if(Room[0]=='1'&& Room[1]=='0'&&Room[2]=='1')               //101ȣ�� ���
        {
            for(i=0;i<4;i++)
                {
                    Password_correct_101[i]=new_password[i];            //101ȣ ��й�ȣ ����
                    mode_Password_Change=5;                             //���� ���� ��ȯ
                }
        }
        else if(Room[0]=='1'&& Room[1]=='0'&&Room[2]=='2')           //102ȣ�� ���
        {
            for(i=0;i<4;i++)
                {
                    Password_correct_102[i]=new_password[i];
                    mode_Password_Change=5;
                }
        }
        else if(Room[0]=='1'&& Room[1]=='0'&&Room[2]=='3')           //103ȣ�� ���
        {
            for(i=0;i<4;i++)
                {
                    Password_correct_103[i]=new_password[i];
                    mode_Password_Change=5;
                }
        }
        else                                                        //104ȣ�� ���
        {
            for(i=0;i<4;i++)
                {
                    Password_correct_104[i]=new_password[i];
                    mode_Password_Change=5;
                }
        }
    }
    if(mode_Password_Change==5)////////////////////////////��й�ȣ ���� �Ϸ� ���
    {
        delay_m();
        printf("complete Password change\n");
        lcd16x2_clrscr();
        lcd16x2_put_custom_char(0, 0, 0);
        lcd16x2_puts("change the P/W");             //LCD ���
        DelayMs(1000);
        mode_Password_Change=0;                     //��� �ʱ�ȭ
    }
            
}