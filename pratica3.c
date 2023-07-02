// Pratica 3 - aplicacao de microprocessadores

// Configuracao de pinos do LCD (PORTB)
// Pinos utilizados para comunicacao com o display LCD
sbit LCD_RS at LATB4_bit;           // Pino 4 do PORTB interligado ao RS do display
sbit LCD_EN at LATB5_bit;           // Pino 5 do PORTB interligado ao EN do display
sbit LCD_D4 at LATB0_bit;           // Pino 0 do PORTB interligado ao D4 do display
sbit LCD_D5 at LATB1_bit;           // Pino 1 do PORTB interligado ao D5 do display
sbit LCD_D6 at LATB2_bit;           // Pino 2 do PORTB interligado ao D6 do display
sbit LCD_D7 at LATB3_bit;           // Pino 3 do PORTB interligado ao D7 do display
// Direcao do fluxo de dados nos pinos selecionados
sbit LCD_RS_Direction at TRISB4_bit;// Direcao do fluxo de dados do pino RB4
sbit LCD_EN_Direction at TRISB5_bit;// Direcao do fluxo de dados do pino RB5
sbit LCD_D4_Direction at TRISB0_bit;// Direcao do fluxo de dados do pino RB0
sbit LCD_D5_Direction at TRISB1_bit;// Direcao do fluxo de dados do pino RB1
sbit LCD_D6_Direction at TRISB2_bit;// Direcao do fluxo de dados do pino RB2
sbit LCD_D7_Direction at TRISB3_bit;// Direcao do fluxo de dados do pino RB3

 char Tensao[10];                   // String onde será colocado o valor da tensao a ser posto no display
 char Temp[8];                      // String onde será colocado o valor da temperatura a ser posto no display
 int Va;                            // Variavel numerica que armazenará a tensao corvertida pelo ADC
 int Ta;                            // Variavel numerica que armazenará a temperatura corvertida pelo LM35
 int Vmax = 500;                    // Valor maximo de tensao a ser colocado no display
 int Tmax = 999;                    // Valor maximo de temperatura a ser colocado no display

// Inicio do programa
void main() {

 // Configuracao inicial de pinos, entrada, saida e registradores ADC
 TRISA.RA0 = 1;                     // Pino RA0 como entrada (canal analogico AN0)
 TRISE.RE1 = 1;                     // Pino RE1 como entrada (canal analogico AN6)
 ADCON0 = 0B00000001;               // AN0 -> AD ligado, leitura deslig., canal AN0
 ADCON2 = 0B10101010;               // Justificativa para direita, FOSC/32 (tempo entre 2 e 25 us)
                                    //... e 12 TAD (tempo de conversao de cada bit + 2 TAD)
 #ifdef P18F45K22                   // Utilizando um PIC18F45k22
 ANSELA.B0 = 1;                     // Somente bit 0 ("B0") do PORTA sera usado como analogico
 ANSELB = 0;                        // PORTB = 0, isto e, como I/O digital,  pois nao sera usado como analogico
 ADCON1 = 0B00000000;               // tensoes de ref. internas = VDD e Vss
 VREFCON0 = 0B00010000;             // Vref+ interna ajustada para 1,024V
 #endif
 #ifdef P18F4550                    // Utilizando um PIC18F4550
 ADCON1=0B00001000;                 // Tensao de ref interna, canais AN6-AN0 como analogico
 #endif

 // Configuracao do modulo ADC
 ADC_init();
 // Configuracao do modulo LCD
 Lcd_Init();                        // Inicializa o display no modo 4 bits
 Lcd_Cmd(_LCD_CLEAR);               // Apago o display
 Lcd_Cmd(_LCD_CURSOR_OFF);          // Desliga o cursor
 Lcd_Out(1,1,"Tensao:       V ");   // Escrita no LCD
 Lcd_Out(2,1," Temp.:        oC");  // Escrita no LCD
 
 while(1) {
 
  // Valor de tensao
  Va = ADC_Read(0);                 //Leitura da entrada analogica 0
  Va = Va * (Vmax/1023.);           //Modulacao da entrada analogica no intervalo desejado
  Tensao[0] = (Va/100)%10 + '0';    //Separacao do valor encontrado para transformar em uma string que
  Tensao[1] = '.';                  //... possa ser exposta no display
  Tensao[2] = (Va/10)%10 + '0';
  Tensao[3] = (Va/1)%10 + '0';
  LCD_Out(1,9,Tensao);              // Apresenta o valor da tensao na linha 1 e coluna 9 do display LCD
  Delay_ms(20);                     // Delay para permitir a atualizacao do LCD
  
  // Valor de temperatura
  Ta = ADC_Read(6);                 //Leitura da entrada analogica 6
  Ta = Ta * (Tmax/1023.);           //Modulacao da entrada analogica nos intervalos desejados
  Temp[0] = (Ta/100)%10 + '0';      //Separacao do valor encontrado para transformar em uma string que
  Temp[1] = (Ta/10)%10 + '0';
  Temp[2] = '.';                    //... possa ser exposta no display
  Temp[3] = (Ta)%10 + '0';
  Temp[4] = 0;
  Lcd_Out(2,9,Temp);                // Apresenta o valor da temperatura na linha 2 e coluna 9 do display LCD
  Delay_ms(20);                     // Delay para permitir a atualizacao do LCD
  
 }                                  // Fim de "while(1)"
}                                   // Fim de "void main()"