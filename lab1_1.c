/*
 * File:   main.c
 * Author: Ogureckiy,Murashko
 *
 * Created on 13 ôåâðàëÿ 2019 ã., 9:58
 * 
 * Ðåàëèçîâàíî:
 * 2)ïðè íàæàòèè íà ëåâóþ êíîïêó, ïîäêëþ÷åííîé ê RA4 äèîä ìèãàåò, äèíàìèê çâó÷èò  
 */

// PIC18F4525 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1H
#pragma config OSC = HSPLL      // Oscillator Selection bits (HS oscillator, PLL enabled (Clock Frequency = 4 x FOSC1))
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bits (Brown-out Reset enabled and controlled by software (SBOREN is enabled))
#pragma config BORV = 3         // Brown Out Reset Voltage bits (Minimum setting)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = PORTC   // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<4:0> pins are configured as digital I/O on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-003FFFh) not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (004000-007FFFh) not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (008000-00BFFFh) not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-003FFFh) not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (004000-007FFFh) not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (008000-00BFFFh) not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot Block (000000-0007FFh) not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-003FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (004000-007FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (008000-00BFFFh) not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot Block (000000-0007FFh) not protected from table reads executed in other blocks)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.


#include <xc.h> //cannot find <alloca.h>
#define _XTAL_FREQ 40000000
#define DYNAMIC_STATE LATCbits.LATC0 //ñîñòîÿíèå äèíàìèêà (1 - âèáðèðóåò, 2 - íå âèáðèðóåò)
#define DIOD_STATE LATBbits.LATB3 //ñîñòîÿíèå äèîäà (1 - ãîðèò, 2 - íå ãîðèò)
#define LEFT_BUTTON_STATE !PORTAbits.RA4 //ëåâàÿ êíîïêà (1-íàæàòà,0-îòæàòà)

void main(void) 
{
    TRISB3=0; //äèîä
    TRISB0=1;//êíîïêà ïðàâàÿ, åñëè ñìîòðåòü ñî ñòîðîíû , ãäå êíîïêè ñíèçó
    TRISA4=1;//êíîïêà ëåâàÿ, åñëè ñìîòðåòü ñî ñòîðîíû , ãäå êíîïêè ñíèçó
    TRISC0=0;//äèíàìèê
    unsigned int counter=0;//êîëè÷åñòâî  ïîëíûõ ïåðèîäîâ ìåàíäðà, ïîäàíîãî íà äèíàìèê 
 

    while (1) 
    {   
        if(LEFT_BUTTON_STATE)  //ïðè íàæàòèè íà êíîïêó ñîñòîÿíèå áèòà ðîí 
            //RA4 ñòàíîâèòñÿ 0 è â ðåãèñòð B3 çàïèñûâàåòñÿ 1  è çàãîðàåòñÿ ëàìïà
        {   // óñëîâèå âûïîëíÿåòñÿ

                   //ïîäà÷à ìåàíäðà íà çâóêîâîé âûõîä (time=166ìêñ)
                  __delay_ms(0.083);
                  DYNAMIC_STATE = 1;
                  __delay_ms(0.083);   
                  DYNAMIC_STATE = 0;

                  //ìèãàíèå ñâåòîäèîäà
                  if(counter>=1205) //êàæäûå 1205*166 ìêñ = 200 ìñ ñâåòîäèîä ìåíÿåò ñîñòîÿíèå 
                  {
                    DIOD_STATE = !DIOD_STATE ;
                    counter = 0;
                  }
                  counter++;
        }
        else
        {
            DIOD_STATE = 0; //ãàñèì äèîä
        }
    }
}
 
