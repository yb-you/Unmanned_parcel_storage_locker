#include "stm32f10x.h"
//#include "SPI_define.h"     // SPI1, SPI2�� ���� ����� �� �ֵ��� ������ �κ�
//#include "USART_define.h"

#include <stdio.h>
extern uint8_t Send_data = 11;
extern uint8_t Receive_data = 0;
extern int position;

extern int motor_on;
extern int usart_seg1;
extern int usart_seg2;
extern int usart_seg3;
extern int usart_seg4;
extern int usart_num;

extern int usart_PS1;
extern int usart_PS2;
extern int usart_PS3;
extern int usart_PS4;
extern int usart_PS_num;
extern int count;
void usart_data(void)
{
        if((Receive_data==11)||(Receive_data==10)||(Receive_data==21)||(Receive_data==20)||         //����� �����ų� ������� 
            (Receive_data==31)||(Receive_data==30)||(Receive_data==41)||(Receive_data==40))
            {
                printf("Receive_data=%d\n",Receive_data);
              //  count=0;
                delay_m();
                position=Receive_data;
                usart_seg1=0;usart_seg2=0;usart_seg3=0;usart_seg4=0;usart_num=0;            //���� �ʱ�ȭ
                usart_PS1=0;usart_PS2=0;usart_PS3=0;usart_PS4=0;usart_PS_num=0;
                                                               
                delay_m();
                Receive_data=0;
            }
        else if(Receive_data==48||Receive_data==49||Receive_data==50||Receive_data==51||Receive_data==52    //Ű�е�� �� ȣ�� �Է� ���� ���
            ||Receive_data==53||Receive_data==54||Receive_data==55||Receive_data==56||Receive_data==57)
            {
                //motor_on=0;
                usart_PS1=0;usart_PS2=0;usart_PS3=0;usart_PS4=0;usart_PS_num=0;
                printf("Receive_data=%d\n",Receive_data);
                if(usart_num==0)                                                        //�� ȣ�� �Է�1
                    {
                        usart_seg1=(Receive_data-47);                              //���׸�Ʈ ǥ��
                        delay_m();delay_m();//delay_m();delay_m();delay_m();
                        Receive_data=0;
                        
                        printf("usart_seg1=%d\n",usart_seg1);
                        usart_num++;                                            //���� ���׸�Ʈ�� �̵�
                    }
                else if(usart_num==1)                                                   //�� ȣ�� �Է�2
                    {
                        usart_seg2=(Receive_data-47);                             //���׸�Ʈ ǥ��
                        Receive_data=0;
                        delay_m();delay_m();//delay_m();delay_m();delay_m();
                        printf("usart_seg2=%d\n",usart_seg2);
                        usart_num++;
                    }
                else if(usart_num==2)                                                   //�� ȣ�� �Է�3
                    {
                        usart_seg3=(Receive_data-47);
                        Receive_data=0;
                        delay_m();delay_m();//delay_m();delay_m();delay_m();
                        printf("usart_seg3=%d\n",usart_seg3);
                        usart_num++;
                    }
                else if(usart_num==3)                                                    //�� ȣ�� �Է�4
                    {
                        usart_seg4=(Receive_data-47);
                        Receive_data=0;
                        delay_m();delay_m();//delay_m();delay_m();delay_m();
                        printf("usart_seg4=%d\n",usart_seg4);
                        usart_num++;
                    }
            }
        else if(Receive_data==123)                                                      //���׸�Ʈ ǥ�� ���� ���
            {
                printf("123\n");
                usart_seg1=0;usart_seg2=0;usart_seg3=0;usart_seg4=0;usart_num=0;        //���׸�Ʈ off�� ���� �ʱ�ȭ
                usart_PS1=0;usart_PS2=0;usart_PS3=0;usart_PS4=0;usart_PS_num=0;
                GPIO_4digit_segment_DIG_off();                                          
                Receive_data=0;
            }
        else if(Receive_data==100)                                                      //Ű�е�� �� ��й�ȣ �Է��� ���
            { 
               // motor_on=0;
                usart_seg1=0;usart_seg2=0;usart_seg3=0;usart_seg4=0;usart_num=0;
                if(usart_PS_num==0)                                                     //�� ��й�ȣ�Է�1
                {
                    usart_PS1=1;                                                     //ù��° ���׸�Ʈ -��� ���
                    Receive_data=0;
                    delay_m();delay_m();//delay_m();delay_m();delay_m();
                    usart_PS_num++;                                                 //���� ��й�ȣ �Է��� ���� ���� ����
                }
                else if(usart_PS_num==1)                                                    //�� ��й�ȣ�Է�2
                {
                    usart_PS2=1;                                                     //�ι�° ���׸�Ʈ -��� ���
                    Receive_data=0;
                    delay_m();delay_m();//delay_m();delay_m();delay_m();
                    usart_PS_num++;
                }
                else if(usart_PS_num==2)                                                    //�� ��й�ȣ�Է�3
                {
                    usart_PS3=1;
                    Receive_data=0;
                    delay_m();delay_m();//delay_m();delay_m();delay_m();
                    usart_PS_num++;
                }
                else if(usart_PS_num==3)                                                    //�� ��й�ȣ�Է�4
                {
                    usart_PS4=1;
                    Receive_data=0;
                    delay_m();delay_m();//delay_m();delay_m();delay_m();
                    usart_PS_num++;
                }
                
            }
}