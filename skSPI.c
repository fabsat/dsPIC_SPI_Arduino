
#include <xc.h>
#include "skSPI.h"
#define FCY     1920000UL
#include <libpic30.h>

/*******************************************************************************
*  SPI_Init(void)                                                      *
*    ＳＰＩモードの設定と初期化を行う処理                                        *
*******************************************************************************/
void SPI_Init(void)
{   
    //SPIレジスタ設定
    SPI1CONbits.MSTEN = 1;          //マスターモードセット
    SPI1STATbits.SPIROV = 0;        //オーバーフローは発生せず
    SPI1CONbits.CKE = 0;            //IDLEクロック状態→アクティブ状態でシリアル出力データが変化
    SPI1CONbits.CKP = 1;            //クロックのIDLE状態はHighレベルでアクティブ状態はLow
    SPI1CONbits.DISSDO = 0;         //SDOピンはモジュールにより制御
    SPI1CONbits.FRMEN = 0;          //フレーム化SPIサポート無効化
    SPI1CONbits.MODE16 = 0;         //8ビット送信
    SPI1CONbits.SMP = 0;            //データ出力時間の中央で入力データをサンプルする
    SPI1CONbits.SSEN = 0;           //SSピンをポートレジスタとして制御される
    SPI1CONbits.PPRE = 0;           //第1プリスケール1/64
    SPI1CONbits.SPRE = 7;           //第2プリスケール1/1
    SPI1STATbits.SPIEN = 1;         //SPI有効
 }

      
/*******************************************************************************
*  ans = SPI_transfer(dt)                                                      *
*    ＳＰＩ通信でのデータ送信とデータ受信を行う処理                            *
*                                                                              *
*    dt  : ８ビットの送信するデータを指定します                                *
*******************************************************************************/
char SPI_transfer(SPI_m mode, char dt)
{
    
    IFS0bits.SPI1IF = 0;                    //SPI割り込みフラグをクリア
    
    //マスターモード
    if(mode == SPI_master){
        LATBbits.LATB2 = 0;                  //SSピンをLOWに
        SPI1BUF = dt;                        // データの送信
        while(IFS0bits.SPI1IF == 0){};       // 受信待ち
        IFS0bits.SPI1IF = 0;                 //SPI割り込みフラグをクリア
        LATBbits.LATB2 = 1;                  //SSピンをLOWに
    }
    
    //スレーブモード
    if(mode == SPI_slave){
        SPI1BUF = dt;                      // データの送信
        while(IFS0bits.SPI1IF == 0){};       // 受信待ち
        IFS0bits.SPI1IF = 0;
    }
    
    return SPI1BUF;                    // データの受信
}
