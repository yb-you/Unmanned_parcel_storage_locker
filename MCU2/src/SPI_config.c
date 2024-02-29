#include "stm32f10x.h"
#include "SPI_define.h"
/*
   SPI 관련 설정.
   SPI는 Master와 Slave로 나뉘는 통신 방식.
   SPI는 2개의 선을 갖는 FullDuplex임을 기억. 즉, 최대 2Line FullDuplex 사용 가능.
*/
/*      SPI_InitTypeDef SPI_InitStructure;

        void SPIy_Master_Configuration()
        {
    /* SPIy Config -------------------------------------------------------------*/
/*           SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
            SPI_InitStructure.SPI_Mode = SPI_Mode_Master;	//마스터모드셋팅
            SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
            SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
            SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
            SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
            SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
            SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_LSB;
            SPI_InitStructure.SPI_CRCPolynomial = 7;
            SPI_Init(SPIy, &SPI_InitStructure);			//SPIy를 마스터로

            /* SPIz Config -------------------------------------------------------------*/
            //SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;
            //SPI_Init(SPIz, &SPI_InitStructure);			//SPIz를 마스터로

    /* Enable SPIy */
/*    SPI_Cmd(SPIy, ENABLE);
            /* Enable SPIz */
            //SPI_Cmd(SPIz, ENABLE);

        

/*void SPIz_Slave_Configuration()
        {
            /* SPIz Config -------------------------------------------------------------*/
/*           SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
            SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;	//마스터모드셋팅
            SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
            SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
            SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
            SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
            SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
            SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_LSB;
            SPI_InitStructure.SPI_CRCPolynomial = 7;
            SPI_Init(SPIz, &SPI_InitStructure);			//SPIy를 마스터로

            /* SPIz Config -------------------------------------------------------------*/
            //SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;
            //SPI_Init(SPIz, &SPI_InitStructure);			//SPIz를 마스터로

            /* Enable SPIy */
            //SPI_Cmd(SPIy, ENABLE);
            /* Enable SPIz */
/*           SPI_Cmd(SPIz, ENABLE);

        }



        //SPIy의 Buffer값(Tx,Rx) 비교할때 사용
        TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength)
        {
            while (BufferLength--)
            {
                if (*pBuffer1 != *pBuffer2)
                {
                return FAILED;
                }

                pBuffer1++;
                pBuffer2++;
            }

            return PASSED;
        }
*/