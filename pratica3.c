//pratica 3 - aplicacao de microprocessadores

// pinos utilizados para comunica��o com o display LCD
sbit LCD_RS at LATB4_bit; // pino 4 do PORTB interligado ao RS do display
sbit LCD_EN at LATB5_bit; // pino 5 do PORTB " " ao EN do display
sbit LCD_D4 at LATB0_bit; // pino 0 do PORTB ao D4
sbit LCD_D5 at LATB1_bit;  // " "
sbit LCD_D6 at LATB2_bit;  // " "
sbit LCD_D7 at LATB3_bit;  // " "

// dire��o do fluxo de dados nos pinos selecionados
sbit LCD_RS_Direction at TRISB4_bit;  // dire��o do fluxo de dados do pino RB4
sbit LCD_EN_Direction at TRISB5_bit;  // " "
sbit LCD_D4_Direction at TRISB0_bit;
sbit LCD_D5_Direction at TRISB1_bit;
sbit LCD_D6_Direction at TRISB2_bit;
sbit LCD_D7_Direction at TRISB3_bit;
ADC_init();


//definicao de constantes do microcontrolador
ADCON0 = 00000001;   //conversor ativado
ADCON1 = 00011011;   //ref+ = an3, vref- = 0, an0 - an3 = analogico, resto digital.

TRISA.RA0 = 1;  // setando os pinos an0 - an3 como entradas
TRISA.RA1 = 1;
TRISA.RA2 = 1;
TRISA.RA3 = 1;


void main(){
  Lcd_Init();                        //Inicializa display no modo 4 bits
  Lcd_Cmd(_LCD_CLEAR);               //Apaga display
  Lcd_Cmd(_LCD_CURSOR_OFF);          //Desliga cursor
  Lcd_Out(1,1,"V: ");              arrumar isso!!
  Lcd_Out(2,1,"Temp: ");   





}