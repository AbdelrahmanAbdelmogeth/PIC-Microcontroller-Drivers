/* 
 * File:   mcal_interrupt_manager.c
 * Author: hp
 *
 * Created on 26 ?????, 2023, 03:46 ?
 */

#include "mcal_interrupt_manager.h"

static volatile uint8 RB4_Flag = 1;
static volatile uint8 RB5_Flag = 1;
static volatile uint8 RB6_Flag = 1;
static volatile uint8 RB7_Flag = 1;

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
void __interrupt() InterruptManagerHigh(void){
    if((INTCONbits.INT0IE == INTERRUPT_ENABLE) && (INTCONbits.INT0IF == INTERRUPT_OCCUR)){
        INT0_ISR();
    }
    if((INTCON3bits.INT2IE == INTERRUPT_ENABLE) && (INTCON3bits.INT2IF == INTERRUPT_OCCUR)){
        INT2_ISR();
    }
    
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCUR) && 
       (PORTBbits.RB4 == GPIO_HIGH) && (RB4_Flag == 1)){
        RB4_Flag = 0;
        RB4_ISR(GPIO_HIGH);
    }
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCUR) && 
       (PORTBbits.RB4 == GPIO_LOW) && (RB4_Flag == 0)){
        RB4_Flag = 1;
        RB4_ISR(GPIO_LOW);
    }
    
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCUR) && 
       (PORTBbits.RB5 == GPIO_HIGH) && (RB5_Flag == 1)){
        RB5_Flag = 0;
        RB5_ISR(GPIO_HIGH);
    }
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCUR) && 
       (PORTBbits.RB5 == GPIO_LOW) && (RB5_Flag == 0)){
        RB5_Flag = 1;
        RB5_ISR(GPIO_LOW);
    }
    
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCUR) && 
       (PORTBbits.RB6 == GPIO_HIGH) && (RB6_Flag == 1)){
        RB6_Flag = 0;
        RB6_ISR(GPIO_HIGH);
    }
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCUR) && 
       (PORTBbits.RB6 == GPIO_LOW) && (RB6_Flag == 0)){
        RB6_Flag = 1;
        RB6_ISR(GPIO_LOW);
    }
    
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCUR) && 
       (PORTBbits.RB7 == GPIO_HIGH) && (RB7_Flag == 1)){
        RB7_Flag = 0;
        RB7_ISR(GPIO_HIGH);
    }
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCUR) && 
       (PORTBbits.RB7 == GPIO_LOW) && (RB7_Flag == 0)){
        RB7_Flag = 1;
        RB7_ISR(GPIO_LOW);
    }
}    
void __interrupt(low_priority) InterruptManagerLow(void){
    if((INTCON3bits.INT1IE == INTERRUPT_ENABLE) && (INTCON3bits.INT1IF == INTERRUPT_OCCUR)){
        INT1_ISR();
    }
}
#else
void __interrupt() InterruptManager(void){
    if((INTCONbits.INT0IE == INTERRUPT_ENABLE) && (INTCONbits.INT0IF == INTERRUPT_OCCUR)){
        INT0_ISR();
    }
    if((INTCON3bits.INT1IE == INTERRUPT_ENABLE) && (INTCON3bits.INT1IF == INTERRUPT_OCCUR)){
        INT1_ISR();
    }
    if((INTCON3bits.INT2IE == INTERRUPT_ENABLE) && (INTCON3bits.INT2IF == INTERRUPT_OCCUR)){
        INT2_ISR();
    }
    else{/*nothing*/}
    
     /* ADC Interrupt*/
    if((PIE1bits.ADIE == INTERRUPT_ENABLE) && (PIR1bits.ADIF == INTERRUPT_OCCUR)){
        ADC_ISR();
    }
    else{/*nothing*/}
    
    /* Timer0 Interrupt*/
    if((INTCONbits.T0IE == INTERRUPT_ENABLE) && (INTCONbits.T0IF == INTERRUPT_OCCUR)){
        TMR0_ISR();
    }
    else{/*nothing*/}
    
    /* Timer1 Interrupt*/
    if((PIE1bits.TMR1IE == INTERRUPT_ENABLE) && (PIR1bits.TMR1IF == INTERRUPT_OCCUR)){
        TMR1_ISR();
    }
    else{/*nothing*/}
    
    /* Timer2 Interrupt*/
    if((PIE1bits.TMR2IE == INTERRUPT_ENABLE) && (PIR1bits.TMR2IF == INTERRUPT_OCCUR)){
        TMR2_ISR();
    }
    else{/*nothing*/}
    
    /* Timer3 Interrupt*/
    if((PIE2bits.TMR3IE == INTERRUPT_ENABLE) && (PIR2bits.TMR3IF == INTERRUPT_OCCUR)){
        TMR3_ISR();
    }
    else{/*nothing*/}
    
    /* CCP1  Interrupt*/
    if((PIE1bits.CCP1IE == INTERRUPT_ENABLE) && (PIR1bits.CCP1IF == INTERRUPT_OCCUR)){
        CCP1_ISR();
    }
    else{/*nothing*/}
    
    /* CCP2  Interrupt*/
    if((PIE2bits.CCP2IE == INTERRUPT_ENABLE) && (PIR2bits.CCP2IF == INTERRUPT_OCCUR)){
        CCP2_ISR();
    }
    else{/*nothing*/}
    
    /* EUSART_TX  Interrupt*/
    if((PIE1bits.TXIE == INTERRUPT_ENABLE) && (PIR1bits.TXIF == INTERRUPT_OCCUR)){
        EUSART_TX_ISR();
    }
    else{/*nothing*/}
    
    /* EUSART_RX  Interrupt*/
    if((PIE1bits.RCIE == INTERRUPT_ENABLE) && (PIR1bits.RCIF == INTERRUPT_OCCUR)){
        EUSART_RX_ISR();
    }
    else{/*nothing*/}
    
#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    /* MSSP_I2C Interrupt */
    if((PIE1bits.SSPIE == INTERRUPT_ENABLE) && (PIR1bits.SSPIF == INTERRUPT_OCCUR)){
        MSSP_I2C_ISR();
    }
    else{/*nothing*/}
    
    /* MSSP_I2C Bus Collision Interrupt */
    if((PIE2bits.BCLIE == INTERRUPT_ENABLE) && (PIR2bits.BCLIF == INTERRUPT_OCCUR)){
        MSSP_I2C_BC_ISR();
    }
    else{/*nothing*/}
#endif  
    
    /* MSSP_I2C Interrupt */
    if((PIE1bits.SSPIE == INTERRUPT_ENABLE) && (PIR1bits.SSPIF == INTERRUPT_OCCUR)){
        MSSP_SPI_ISR();
    }
    else{/*nothing*/}
}
#endif