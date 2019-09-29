#include <xc.h>
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config CP = OFF         // FLASH Program Memory Code Protection bits (Code protection off)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low Voltage In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EE Memory Code Protection (Code Protection off)
#pragma config WRT = ON         // FLASH Program Memory Write Enable (Unprotected program memory may be written to by EECON control)

# define _XTAL_FREQ 4000000

#define LCD_RS PORTCbits.RC1
#define LCD_E PORTCbits.RC0
#define LCD_DATO PORTD

void LCD_Escribir(char dato);
void LCD_Comando(char dato);
void LCD_Configuracion_Inicial();
void PIC_Configuracion_Inicial();
void LCD_EscribirStr(char str[]);
void LCD_Cursor(int Horizontal, int Vertical);
void LCD_Display(int Tam, int Hor);
int LCD_Contar(char c[]);

void main()
{
    int Horizontal, Vertical, aux2;
    char aux1[]="Grupo 03: Karlhianna - Jose";
    PIC_Configuracion_Inicial();
    LCD_Configuracion_Inicial();
    
        aux2=LCD_Contar(aux1);
    
        Horizontal = 0; // Numero de cuadros del cursor que se desea desplazar hacia la derecha - 63 la primera lina, para la simulacion - 40 la primera linea para el montaje
        Vertical = 0; // 1 Arriba, 2 Abajo
        LCD_Cursor(Horizontal, Vertical);
        LCD_EscribirStr(aux1);
        
     while(1)
    {   
        LCD_Display(aux2,0);
    }
            
    while(1){
        __delay_ms(500);
        PORTAbits.RA0 = 1;
        __delay_ms(500);        
        PORTAbits.RA0 = 0;
    };//Prueba encendiendo intermitentemente un LED
}
void LCD_Escribir(char dato){
    LCD_RS = 1;
    LCD_DATO = dato;
    LCD_E = 1;
    LCD_E = 0;
    __delay_us(40);
}

void LCD_Comando(char dato){
    LCD_RS = 0;
    LCD_DATO = dato;
    LCD_E = 1;
    LCD_E = 0;
    if(dato <= 3){
      __delay_ms(2);
    }else{
      __delay_us(40);
    }
}
void LCD_Configuracion_Inicial(){
    LCD_E = 0;
    __delay_ms(15);
    LCD_Comando(0x38);
    __delay_ms(5);
    LCD_Comando(0x38);
    __delay_ms(1);
    LCD_Comando(0x38);
    LCD_Comando(0x38);
    LCD_Comando(0x0C);
    LCD_Comando(0x01);//Display clear
    LCD_Comando(0x06);//incrementar el cursor
   
    LCD_Comando(0x0C);//DISPLAY ON/ CURSOR OFF /NO BLINKING
   
}
void PIC_Configuracion_Inicial(){
    TRISD = 0;
    TRISCbits.TRISC0 = 0;
    TRISCbits.TRISC1 = 0;
    TRISA = 0;
    ADCON0=0b00000000; //Configuracion del registro ADCON0
     /*INICIALIZACIÓN DE INTERRUPCIONES*/
    INTCON = 0;//limpiar registro INTCON
    INTCONbits.GIE = 0;//Hab interrupciones
}
void LCD_EscribirStr(char str[])
{
    int i=0;
    while(str[i]!='\0' && i<1000)
    {
        LCD_Escribir(str[i]);
        i++;
    }
}
void LCD_Cursor(int h, int v)
{
    int i;
   
    if(v==1)
    {
        for(i=0;i<h;i++)
        {
            __delay_us(40);
            LCD_Comando(0x14);
        }
    }
  
    if(v==2)
    {
        h=h+40;
        for(i=0;i<h;i++)
        {
            __delay_us(40);
            LCD_Comando(0x14);
        }
    }
   
 }
int LCD_Contar(char c[])
{
    int i=0;
    while(c[i]!='\0' && i<1000)
    {
        i++;
    }
    return i;
}
void LCD_Display(int Tam, int Hor)
{
    int aux1, i;
    __delay_ms(2);
    LCD_Comando(0x02);
    
    __delay_ms(2000);
    if(Tam>16 && Tam<40)
    {
        aux1 = Tam-16;
        for(i=-1;i<aux1;i++)
        {
            __delay_ms(500);
            LCD_Comando(0x1B);
        }
    }
}
