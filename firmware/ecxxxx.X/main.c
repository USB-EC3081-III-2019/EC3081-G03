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
    int Horizontal, Vertical, aux2, aux3;
    char aux1[]="Grupo 03: KYJ";
    char aux0[]="->";
    PIC_Configuracion_Inicial();
    LCD_Configuracion_Inicial();
   
        aux2 = LCD_Contar(aux1);
   
        Horizontal = 0; // Numero de cuadros del cursor que se desea desplazar hacia la derecha - 63 la primera lina, para la simulacion - 40 la primera linea para el montaje
        Vertical = 1; // 1 Arriba, 2 Abajo
        LCD_Cursor(Horizontal, Vertical);
        LCD_EscribirStr(aux1);
       
     /*while(1)
    {  
        LCD_Display(aux2,0);
    }*/
    /////////////////////////////////////
       
        aux3=LCD_Contar(aux0);
       
        Horizontal = -aux2; // Numero de cuadros del cursor que se desea desplazar hacia la derecha - 63 la primera lina, para la simulacion - 40 la primera linea para el montaje
        Vertical = 2; // 1 Arriba, 2 Abajo
        LCD_Cursor(Horizontal, Vertical);
        LCD_EscribirStr(aux0);
        while(1){};
    /*while(1)
    {  
        LCD_Display(aux3,0);
    }*/
       
    /*while(1){
        __delay_ms(500);
        PORTAbits.RA0 = 1;
        __delay_ms(500);        
        PORTAbits.RA0 = 0;
    };//Prueba encendiendo intermitentemente un LED*/
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
    TRISB = 0b11110000;
    ADCON0=0b00000000; //Configuracion del registro ADCON0
     /*INICIALIZACIÓN DE INTERRUPCIONES*/
    INTCON = 0;//limpiar registro INTCON
    INTCONbits.GIE = 1;//Hab interrupciones Globales
    PORTB = 0;
    RBIF = 0;
    INTCONbits.RBIE = 1;//Port b
   
    OPTION_REGbits.nRBPU = 0;
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
void interrupt Interrupcion(void)
{
if(RBIF) //Si hay cambio de estado en PORTB
{  
    int a=1,b=1,c=1,i=0,k=1;
    while(k==1)
    {
        PORTBbits.RB3 = a;
        PORTBbits.RB2 = b;
        PORTBbits.RB1 = c;
       
           
        if((PORTBbits.RB7 == 0)&&(PORTBbits.RB3 == 0)) //Código de atención de la interrupción
        {
            //LCD_Comando(0x01); //Display clear
            __delay_ms(2);
            LCD_Escribir('*');
            k=0;
       
        }
        if((PORTBbits.RB7 == 0)&&(PORTBbits.RB2 == 0))//Código de atención de la interrupción
        {
            //LCD_Comando(0x01); //Display clear
            __delay_ms(2);
            LCD_Escribir('0');
            k=0;
        }
        if((PORTBbits.RB7 == 0)&&(PORTBbits.RB1 == 0))//Código de atención de la interrupción
        {
            //LCD_Comando(0x01); //Display clear
            __delay_ms(2);
            LCD_Escribir('#');
            k=0;
        }
        if((PORTBbits.RB6 == 0)&&(PORTBbits.RB3 == 0)) //Código de atención de la interrupción
        {
            //LCD_Comando(0x01); //Display clear
            __delay_ms(2);
            LCD_Escribir('7');
            k=0;
       
        }
        if((PORTBbits.RB6 == 0)&&(PORTBbits.RB2 == 0))//Código de atención de la interrupción
        {
            //LCD_Comando(0x01); //Display clear
            __delay_ms(2);
            LCD_Escribir('8');
            k=0;
        }
        if((PORTBbits.RB6 == 0)&&(PORTBbits.RB1 == 0))//Código de atención de la interrupción
        {
            //LCD_Comando(0x01); //Display clear
            __delay_ms(2);
            LCD_Escribir('9');
            k=0;
        }
        //
        if((PORTBbits.RB5 == 0)&&(PORTBbits.RB3 == 0)) //Código de atención de la interrupción
        {
            //LCD_Comando(0x01); //Display clear
            __delay_ms(2);
            LCD_Escribir('4');
            k=0;
       
        }
        if((PORTBbits.RB5 == 0)&&(PORTBbits.RB2 == 0))//Código de atención de la interrupción
        {
            //LCD_Comando(0x01); //Display clear
            __delay_ms(2);
            LCD_Escribir('5');
            k=0;
        }
        if((PORTBbits.RB5 == 0)&&(PORTBbits.RB1 == 0))//Código de atención de la interrupción
        {
            //LCD_Comando(0x01); //Display clear
            __delay_ms(2);
            LCD_Escribir('6');
            k=0;
        }
        //
        if((PORTBbits.RB4 == 0)&&(PORTBbits.RB3 == 0)) //Código de atención de la interrupción
        {
            //LCD_Comando(0x01); //Display clear
            __delay_ms(2);
            LCD_Escribir('1');
            k=0;
       
        }
        if((PORTBbits.RB4 == 0)&&(PORTBbits.RB2 == 0))//Código de atención de la interrupción
        {
            //LCD_Comando(0x01); //Display clear
            __delay_ms(2);
            LCD_Escribir('2');
            k=0;
        }
        if((PORTBbits.RB4 == 0)&&(PORTBbits.RB1 == 0))//Código de atención de la interrupción
        {
            //LCD_Comando(0x01); //Display clear
            __delay_ms(2);
            LCD_Escribir('3');
            k=0;
        }
       
       
   
        if(i==0)
        {
            a=0;
            b=1;
            c=1;
        }
        if(i==1)
        {
            a=1;
            b=0;
            c=1;
        }
        if(i==2)
        {
            a=1;
            b=1;
            c=0;
            i=-1;
        }
        i++;
    }
           
RBIF = 0; //Desactivar bandera...
 
//INTCONbits.RBIF==0;
}

}
