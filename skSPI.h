#ifndef _SKSPI_H_
#define _SKSPI_H_


#define LOW  0
#define HIGH 1

//SPI1SATAレジスタ設定
#define SPI_on        0x8000
#define IDLE_stop     0x2000
#define OVER_happen   0x0040
#define TRANS_b_data  0x0002
#define RECEP_b_data  0x0001

//SPI1CONレジスタ設定
#define FRLEM_ON       0x4000
#define SS1_input      0x2000
#define SDO1_pin_on    0x0800
#define BIT_16         0x0400
#define MASTER_back_on 0x0200
#define CLOCK_AI       0x0100
#define SS_on          0x0080
#define IDLE_high      0x0040
#define MASTER_on      0x0020

//SPIモードの構造体変数定義
typedef enum{
    SPI_master,
    SPI_slave,
} SPI_m;

void SPI_Init(void);
char SPI_transfer(SPI_m mode, char dt);


#endif
