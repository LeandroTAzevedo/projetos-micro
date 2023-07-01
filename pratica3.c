//pratica 3 - aplicacao de microprocessadores

// pinos utilizados para comunica??o com o display LCD
sbit LCD_RS at LATB4_bit; // pino 4 do PORTB interligado ao RS do display
sbit LCD_EN at LATB5_bit; // pino 5 do PORTB " " ao EN do display
sbit LCD_D4 at LATB0_bit; // pino 0 do PORTB ao D4
sbit LCD_D5 at LATB1_bit;  // " "
sbit LCD_D6 at LATB2_bit;  // " "
sbit LCD_D7 at LATB3_bit;  // " "

// dire??o do fluxo de dados nos pinos selecionados
sbit LCD_RS_Direction at TRISB4_bit;  // dire??o do fluxo de dados do pino RB4
sbit LCD_EN_Direction at TRISB5_bit;  // " "
sbit LCD_D4_Direction at TRISB0_bit;
sbit LCD_D5_Direction at TRISB1_bit;
sbit LCD_D6_Direction at TRISB2_bit;
sbit LCD_D7_Direction at TRISB3_bit;

char Tensao[10]; // Display LCD - tipo char - int 8 bits
char Temp[10];
int Va;
int Ta;
int Vmax = 500;
int Tmax = 999;

void main(){

// Configuracao inicial (pinos, entrada, saida e registradores ADC)
TRISA.RA0 = 1; // Pino RA0 como entrada (canal analogico AN0)
TRISE.RE1 = 1; // Pino RE1 como entrada (canal analogico AN6)
//PORTA.RA0 = 1; // opcional
ADCON0 = 0B00000001; // AN0 -> AD ligado, leitura deslig., canal AN0
ADCON2 = 0B10101010; // Justificativa para direita, FOSC/32 (tempo entre 2 e 25 us)
//... e 12 TAD (tempo de conversao de cada bit + 2 TAD)
#ifdef P18F45K22 // Utilizando um PIC18F45k22
ANSELA.B0 = 1; // Somente bit 0 ("B0") do PORTA sera usado (ou seja: RA0/AN0) como analogico
ANSELB = 0; // PORTB = 0, isto e, como I/O digital,  pois nao sera usado como analogico
ADCON1 = 0B00000000; // tensoes de ref. internas = VDD e Vss
VREFCON0 = 0B00010000; // Vref+ interna ajustada para 1,024V
TRISA.RA2 = 1;
TRISA.RA3 = 1;
#endif

#ifdef P18F4550 // Utilizando um PIC18F4550
ADCON1 = 0B00011011;   //ref+ = an3, vref- = 0, an0 - an3 = analogico, resto digital. Ta diferente do q vc fez pedro
TRISA.RA1 = 1;
TRISA.RA2 = 1;
TRISA.RA3 = 1;
#endif

ADC_init();




Lcd_Init();                        //Inicializa display no modo 4 bits
Lcd_Cmd(_LCD_CLEAR);               //Apaga display
Lcd_Cmd(_LCD_CURSOR_OFF);          //Desliga cursor
Lcd_Out(1,6,"V");
Lcd_Out(2,7,"C");

while(1){
  Va = ADC_Read(0);
  Va = Va * (Vmax/1023.);
  Tensao[0] = (Va/1000) + '0';
  Tensao[1] = (Va/100)%10 + '0';
  Tensao[2] = '.';
  Tensao[3] = (Va/10)%10 + '0';
  Tensao[4] = (Va)%10 + '0';
  Tensao[5] = 0;
  Lcd_Out(1,1,Tensao); // Mostra os valores no display
  Delay_ms(20); // Delay para permitir a atualizacao do LCD


//temp:

Ta = ADC_Read(1);
Ta = Ta * (Tmax/1023.);
Temp[0] = (Ta/100)%10 + '0';
Temp[1] = (Ta/10)%10 + '0';
Temp[2] = '.';
Temp[3] = (Ta)%10 + '0';
Temp[4] = 0;
Lcd_Out(2,1, Temp);
Delay_ms(20);
  }
} // Fim de "void main()"