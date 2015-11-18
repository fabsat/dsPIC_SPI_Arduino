/* 
 * File:   newmain.c
 * Author: Tetsuya
 *
 * Created on 2015/09/28, 16:26
 *            2015/11/13, 17:55
 */

#include <xc.h>
#include <p30F6014A.h>

#define FCY     1920000UL

#include <libpic30.h>
#include "skSPI.h"

#define SDI1 PORTFbits.RF7
#define SDO1 PORTFbits.RF8
#define SCK1 PORTFbits.RF6

/*コンフィグレーションの設定*/
// FOSC
#pragma config FOSFPR = FRC        // Oscillator (FRC w/PLL 4x)
#pragma config FCKSMEN = CSW_FSCM_OFF   // Clock Switching and Monitor (Sw Disabled, Mon Disabled)
// FWDT
#pragma config FWPSB = WDTPSB_16        // WDT Prescaler B (1:16)
#pragma config FWPSA = WDTPSA_512       // WDT Prescaler A (1:512)
#pragma config WDT = WDT_OFF             // Watchdog Timer (Enabled)
// FBORPOR
#pragma config FPWRT = PWRT_64          // POR Timer Value (64ms)
#pragma config BODENV = NONE            // Brown Out Voltage (Reserved)
#pragma config BOREN = PBOR_ON          // PBOR Enable (Enabled)
#pragma config MCLRE = MCLR_DIS          // Master Clear Enable (Disabled)
// FBS
#pragma config BWRP = WR_PROTECT_BOOT_OFF// Boot Segment Program Memory Write Protect (Boot Segment Program Memory may be written)
#pragma config BSS = NO_BOOT_CODE       // Boot Segment Program Flash Memory Code Protection (No Boot Segment)
#pragma config EBS = NO_BOOT_EEPROM     // Boot Segment Data EEPROM Protection (No Boot EEPROM)
#pragma config RBS = NO_BOOT_RAM        // Boot Segment Data RAM Protection (No Boot RAM)
// FSS
#pragma config SWRP = WR_PROT_SEC_OFF   // Secure Segment Program Write Protect (Disabled)
#pragma config SSS = NO_SEC_CODE        // Secure Segment Program Flash Memory Code Protection (No Secure Segment)
#pragma config ESS = NO_SEC_EEPROM      // Secure Segment Data EEPROM Protection (No Segment Data EEPROM)
#pragma config RSS = NO_SEC_RAM         // Secure Segment Data RAM Protection (No Secure RAM)
// FGS
#pragma config GWRP = GWRP_OFF          // General Code Segment Write Protect (Disabled)
#pragma config GCP = GSS_OFF            // General Segment Code Protection (Disabled)
// FICD
#pragma config ICS = ICS_PGD            // Comm Channel Select (Use PGC/EMUC and PGD/EMUD)

/*メイン*/
int main(void) {
    
    TRISA  = 0x00 ;                     // 1で入力 0で出力 RA0-RA7全て出力に設定
    TRISF  = 0b0000000010000000 ;       // 1:in 0:out SDI1(RF7:in) SDO1(RF8:out) SCK1(RF6:out)
    TRISBbits.TRISB2 = 0 ;              //SS(RB2:out)
    PORTA  = 0x00 ;                     // 出力ピンの初期化(全てLOWにする)
    PORTF  = 0x0000 ;                   // 出力ピンの初期化(全てLOWにする)
    
    LATAbits.LATA7 = 1;     //LED点灯
    __delay_ms(1000);       //１秒待つ
    LATAbits.LATA7 = 0;     //LED消灯

    //SPI通信の設定関数
    SPI_Init();
    
    while(1){
        //SPI通信の送信関数
        SPI_transfer(SPI_master, 0x12);
    }

    return 0;
}

