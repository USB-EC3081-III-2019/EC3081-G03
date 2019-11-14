#include <xc.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config CP = OFF         // FLASH Program Memory Code Protection bits (Code protection off)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low Voltage In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EE Memory Code Protection (Code Protection off)
#pragma config WRT = ON         // FLASH Program Memory Write Enable (Unprotected program memory may be written to by EECON control)

#define _XTAL_FREQ 4000000

#define LCD_RS PORTCbits.RC1
#define LCD_E PORTCbits.RC0
#define LCD_DATO PORTD

void LCD_Escribir(char dato);
void LCD_Comando(char dato);
void LCD_Configuracion_Inicial(void);
void PIC_Configuracion_Inicial(void);
void LCD_EscribirStr(char str[]);
void LCD_Cursor(int Horizontal, int Vertical);
void LCD_Display(int Tam);
int LCD_Contar(char c[]);
void INTERFACE_Bienvenida(void);
void INTERFACE_Principal(void);
void INTERFACE_Datos(void);
void INTERFACE_Umbral(void);
void INTERFACE_Manual_Auto(void);

void Fotocelda(void);
unsigned int ADC_Read(unsigned char canal);

void Delay_ms(int x);
unsigned char n = ' ', sr = 40;
unsigned int a = 0, Q = 0;

void main(void) {

    PIC_Configuracion_Inicial();
    LCD_Configuracion_Inicial();
    TRISAbits.TRISA1 = 0;
    PORTAbits.RA1 = 0; // Configuracion en modo automatico

    //RBIE = 0;

    n = ' ';
    while (1) {
        INTERFACE_Bienvenida();
        Q = 1;
        while (Q == 1) {
            INTERFACE_Principal();
        }
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////Libreria INTERFACE///////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

void INTERFACE_Manual_Auto(void) {
    int w, x, y, z;

    n = ' ';
    w = 0;
    x = 0;
    y = 0;
    z = 0;

    LCD_Comando(0x01); // Limpiar Display
    LCD_EscribirStr("#1: Manual");
    LCD_Cursor(-10, 2);
    LCD_EscribirStr("#2: Automatico (defecto)");
    LCD_Comando(0x02); //regresar cursor a casa
    __delay_ms(1.64);
    LCD_Cursor(13, 1);
    LCD_EscribirStr("#3: Menu Principal");
    LCD_Display(31);
    while (y == 0) {
        while (n == ' ') {
        }
        switch (n) {
            case'1':
                n = ' ';
                LCD_Comando(0x01); // Limpiar Display
                LCD_Cursor(2, 1);
                LCD_EscribirStr("AjusteManual");
                PORTAbits.RA1 = 1;
                LCD_Cursor(-14, 2);
                LCD_EscribirStr("#1: Luminaria #2: Ventilacion");
                LCD_Display(29);
                y = 1;
                while (w == 0) {
                    while (n == ' ') {
                    }
                    switch (n) {
                        case'1':
                            n = ' ';
                            LCD_Comando(0x01); // Limpiar Display
                            LCD_EscribirStr("   Luminaria:");
                            LCD_Cursor(-13, 2);
                            LCD_EscribirStr("#1: On   #2: Off");
                            w = 1;
                            n = ' ';
                            while (n == ' ') {
                            }
                            while (z == 0) {
                                while (n == ' ') {
                                }
                                switch (n) {
                                    case'1':
                                        n = ' ';
                                        LCD_Comando(0x01); // Limpiar Display
                                        LCD_EscribirStr("  Luminaria On");
                                        Delay_ms(3000);
                                        z = 1;
                                        n = ' ';
                                        break;
                                    case'2':
                                        n = ' ';
                                        LCD_Comando(0x01); // Limpiar Display
                                        LCD_EscribirStr("  Luminaria Off");
                                        Delay_ms(3000);
                                        z = 1;
                                        n = ' ';
                                        break;
                                    default:
                                        z = 0;
                                        n = ' ';
                                        break;

                                }
                            }//aqui muere el switch 3 luminaria
                            break;
                        case'2':
                            n = ' ';
                            LCD_Comando(0x01); // Limpiar Display
                            LCD_EscribirStr("  Ventilacion:");
                            LCD_Cursor(-14, 2);
                            LCD_EscribirStr("#1: On   #2: Off");
                            w = 1;
                            n = ' ';
                            while (n == ' ') {
                            }
                            while (x == 0) {
                                while (n == ' ') {
                                }
                                switch (n) {
                                    case'1':
                                        n = ' ';
                                        LCD_Comando(0x01); // Limpiar Display
                                        LCD_EscribirStr(" Ventilacion On");
                                        Delay_ms(3000);
                                        x = 1;
                                        n = ' ';
                                        break;
                                    case'2':
                                        n = ' ';
                                        LCD_Comando(0x01); // Limpiar Display
                                        LCD_EscribirStr(" Ventilacion Off");
                                        Delay_ms(3000);
                                        x = 1;
                                        n = ' ';
                                        break;
                                    default:
                                        x = 0;
                                        n = ' ';
                                        break;
                                }//aqui muere el switch 4 ventilacion
                            }
                            break;
                        default:
                            w = 0;
                            n = ' ';
                            break;
                    }//aqui muere el switch 2 - Ajuste manual, luminaria o ventilacion?
                }
                break;
            case'2': // Automatico
                n = ' ';
                LCD_Comando(0x01); // Limpiar Display
                LCD_EscribirStr("   AjusteAuto");
                PORTAbits.RA1 = 0;
                LCD_Cursor(-13, 2);
                LCD_EscribirStr("Conf por defecto");
                y = 1;
                n = ' ';
                __delay_ms(3000);
                break;
            case'3': // Menu principal
                LCD_Comando(0x01); // Limpiar Display
                y = 1;
                n = ' ';
                break;
            default:
                y = 0;
                n = ' ';
                break;
        }
    }
}

void INTERFACE_Umbral(void) {
    int y;

    n = ' ';
    y = 0;

    LCD_Comando(0x01); // Limpiar Display
    LCD_EscribirStr("Umbrales de actuadores:");
    LCD_Cursor(-23, 2);
    LCD_EscribirStr("#1: Temp  #2:CO  #3: Lumenes");
    LCD_Display(28);
    while (y == 0) {
        while (n == ' ') {
        }
        switch (n) {
            case'1':
                n = ' ';
                LCD_Comando(0x01); // Limpiar Display
                LCD_EscribirStr("  Umbral Temp.");
                LCD_Cursor(-14, 1);
                __delay_ms(3000);
                y = 1;
                n = ' ';
                break;
            case'2':
                n = ' ';
                LCD_Comando(0x01); // Limpiar Display
                LCD_EscribirStr("   Umbral CO.");
                LCD_Cursor(-13, 1);
                __delay_ms(3000);
                y = 1;
                n = ' ';
                break;
            case'3':
                n = ' ';
                LCD_Comando(0x01); // Limpiar Display
                LCD_EscribirStr(" Umbral Lumenes");
                LCD_Cursor(-15, 1);
                __delay_ms(3000);
                y = 1;
                n = ' ';
                break;
            default:
                y = 0;
                n = ' ';
                break;
        }
    }
}

void INTERFACE_Datos(void) {
    int y;

    n = ' ';
    y = 0;

    LCD_Comando(0x01); // Limpiar Display
    LCD_EscribirStr("#1: Temperatura");
    LCD_Cursor(-15, 2);
    LCD_EscribirStr("#2: CO");
    LCD_Cursor(3, 1);
    LCD_EscribirStr("#3: Lumenes");
    LCD_Display(20);
    while (y == 0) {
        while (n == ' ') {
        }
        switch (n) {
            case'1':
                LCD_Comando(0x01); // Limpiar Display
                LCD_EscribirStr("Temp: 25 C");
                LCD_Cursor(-10, 2);
                LCD_EscribirStr("Humedad: 36%");
                __delay_ms(5000);
                y = 1;
                break;
            case'2':
                LCD_Comando(0x01); // Limpiar Display
                LCD_EscribirStr("Nivel de CO: 15%");
                LCD_Cursor(-16, 2);
                __delay_ms(5000);
                y = 1;
                break;
            case'3':
                LCD_Comando(0x01); // Limpiar Display
                Fotocelda();
                //__delay_ms(5000);
                y = 1;
                break;
            case'4':
                LCD_Comando(0x01); // Limpiar Display
                y = 1;
                n = ' ';
                break;
            default:
                y = 0;
                n = ' ';
                break;
        }
    }
}

void INTERFACE_Principal(void) {
    int y;

    n = ' ';
    y = 0;

    LCD_Comando(0x01); // Limpiar Display
    LCD_EscribirStr("#1: Datos");
    LCD_Cursor(3, 1);
    LCD_EscribirStr("#2: Umbral");
    LCD_Cursor(-22, 2);
    LCD_EscribirStr("#3: Man / Auto");
    LCD_Display(22);
    while (y == 0) {
        while (n == ' ') {
        }
        switch (n) {
            case'1':
                INTERFACE_Datos();
                y = 1;
                n = ' ';
                break;
            case'2':
                INTERFACE_Umbral();
                y = 1;
                n = ' ';
                break;
            case'3':
                INTERFACE_Manual_Auto();
                y = 1;
                n = ' ';
                break;
            case'#':
                Q = 0;
                y = 1;
                n = ' ';
                break;
            default:
                y = 0;
                n = ' ';
                break;
        }
    }
}

void INTERFACE_Bienvenida(void) {

    int aux2, aux3, t = 3, i;
    n = ' ';
    LCD_Comando(0x01); // Limpiar Display
    aux2 = LCD_Contar("BIENVENIDO");
    LCD_Cursor(3, 1); // 3---> Numero de cuadros del cursor que se desea desplazar hacia la derecha - 63 la primera lina, para la simulacion - 40 la primera linea para el montaje
    // 1---> Arriba, 2 Abajo
    LCD_EscribirStr("BIENVENIDO");
    aux3 = -(aux2 + 3);
    LCD_Cursor(aux3 + 8, 2);

    char j = '0';
    for (i = 1; i <= t; i++) {
        j = i + '0';
        __delay_ms(1000);
        LCD_Escribir(j);
        __delay_ms(1.64);
        LCD_Comando(0x02); //regresar cursor a casa
        __delay_ms(1.64);
        LCD_Cursor(8, 2);
    }
    __delay_ms(1000);
    LCD_Comando(0x01); // Limpiar Display
    __delay_ms(1.64);
    n = ' ';
}
////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////Libreria INTERFACE///////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////Libreria LCD/////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
void LCD_Escribir(char dato) {
    LCD_RS = 1;
    LCD_DATO = dato;
    LCD_E = 1;
    LCD_E = 0;
    __delay_us(40);
}

void LCD_Comando(char dato) {
    LCD_RS = 0;
    LCD_DATO = dato;
    LCD_E = 1;
    LCD_E = 0;
    if (dato <= 3) {
        __delay_ms(2);
    } else {
        __delay_us(40);
    }
}

void LCD_Configuracion_Inicial(void) {
    LCD_E = 0;
    __delay_ms(15);
    LCD_Comando(0x38);
    __delay_ms(5);
    LCD_Comando(0x38);
    __delay_ms(1);
    LCD_Comando(0x38);
    LCD_Comando(0x38);
    LCD_Comando(0x0C);
    LCD_Comando(0x01); //Display clear
    LCD_Comando(0x06); //incrementar el cursor

    LCD_Comando(0x0C); //DISPLAY ON/ CURSOR OFF /NO BLINKING

}

void LCD_EscribirStr(char str[]) {
    int i = 0;
    while (str[i] != '\0' && i < 1000) {
        LCD_Escribir(str[i]);
        i++;
    }
}

void LCD_Cursor(int h, int v) {
    int i;

    if (v == 1) {
        for (i = 0; i < h; i++) {
            __delay_us(40);
            LCD_Comando(0x14);
        }
    }

    if (v == 2) {
        h = h + sr;
        for (i = 0; i < h; i++) {
            __delay_us(40);
            LCD_Comando(0x14);
        }
    }

}

int LCD_Contar(char c[]) {
    int i = 0;
    while (c[i] != '\0' && i < 1000) {
        i++;
    }
    return i;
}

void LCD_Display(int Tam) {
    int aux1, i;
    
    __delay_ms(2);
    LCD_Comando(0x02);

    __delay_ms(300);
    if (Tam > 16 && Tam < sr) {
        aux1 = Tam - 16;
        n = ' ';
        for (i = -1; (i < aux1) && (n == ' '); i++) {
            __delay_ms(400);
            LCD_Comando(0x1B);
        }
    }
    if(n == ' '){
        __delay_ms(1300);
    }
    __delay_ms(2);
    LCD_Comando(0x02);
    __delay_ms(2);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////Libreria LCD/////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

void PIC_Configuracion_Inicial(void) {
    TRISD = 0;
    TRISCbits.TRISC0 = 0;
    TRISCbits.TRISC1 = 0;
    TRISB = 0b11110000;
    
    ADCON1bits.PCFG = 0b111110; //A0 será la entrada analógica
    //Perifericos (Iniciar configuraciones analogicas)
    ADCON0bits.ADCS = 0b00;     //ADCS1:ADCS0: A/D Conversion Clock Select bits 00 = FOSC/2    
    ADCON0bits.ADON = 1;        //Encendemos el modulo analogico
    ADCON1bits.ADFM = 1;        //Justificación a la derecha(De esta manera, los bits más significativos se almacenan en ADRESH)
    //ADCON0 = 0b00000000; //Configuracion del registro ADCON0
    /*INICIALIZACIÓN DE INTERRUPCIONES*/
    
    INTCON = 0; //limpiar registro INTCON
    INTCONbits.GIE = 1; //Hab interrupciones Globales
    PORTB = 0;
    RBIF = 0;
    INTCONbits.RBIE = 1; //Port b

    OPTION_REGbits.nRBPU = 0;
}

void Fotocelda() {
    n = ' ';
    while (n == ' ') {
        float valor = ADC_Read(0), aux4; //Se coloca 0 porque es el canal analogico RA0
        float voltaje = (valor * 5) / 1023; //voltajes a lumenes
        int aux1, aux2, aux3;
        int lux1;

        valor = voltaje;

        //////////////////////////
        aux1 = valor;
        aux2 = aux1 * 10;
        aux4 = valor * 10;
        aux3 = aux4 - aux2;
        /////////////////////////

        lux1 = ((60.386 * (pow(valor, 4))) - (944.04 * (pow(valor, 3))) + (5496.2 * (pow(valor, 2))) - (14252 * valor) + (14092));

        if (lux1 < 0) {
            lux1 = -lux1;
        }

        char var[16];
        LCD_Comando(0x01);
        LCD_EscribirStr("Flujo luminoso:");
        LCD_Cursor(-15,2);
        sprintf(var, "%d Lm", lux1);
        //LCD_Comando(0x02);
        //__delay_ms(500);
        LCD_EscribirStr(var);
        __delay_ms(100);

         /*LCD_Comando(0x01);
         LCD_EscribirStr(" V: ");
         LCD_Escribir('0'+aux1);
         LCD_EscribirStr(".");
         LCD_Escribir('0'+aux3);
         //__delay_ms(200);*/
         
         LCD_Comando(0x02);
    }
}

unsigned int ADC_Read(unsigned char canal) {
    ADCON0 &= 0xC5;                     //Valor para reiniciar los canales a 0
    ADCON0bits.CHS = canal;             //Se elige el canal
    __delay_ms(2);                      //Espera para el cambio
    GO_nDONE = 1;                       //Se activa la
    while (GO_nDONE);                   //Esperamos hasta que terminen
    int X = ADRESH << 8;
    X = X + ADRESL;                     //Los valores se guardarán en el registro ADRES H(2 mas significativos) L(6 menos significativos)
    return (X);

}

void Delay_ms(int x) {
    __delay_ms(100);
    n = ' ';
    for (int i = 0; i < x; i++) {
        if (n == ' ') {
            __delay_ms(1);
        }
    }
}
void __interrupt() Interrupcion(void) {
    if (RBIF) //Si hay cambio de estado en PORTB
    {
        char a = 0, b = 1, c = 1, i = 1, k = 1;
        while (k == 1) {
            PORTBbits.RB3 = a;
            PORTBbits.RB2 = b;
            PORTBbits.RB1 = c;


            if ((PORTBbits.RB7 == 0)&&(PORTBbits.RB3 == 0)) //Código de atención de la interrupción
            {
                //LCD_Comando(0x01); //Display clear
                __delay_ms(2);
                //LCD_Escribir('*');
                n = '*';
                k = 0;
                __delay_ms(100);

            }
            if ((PORTBbits.RB7 == 0)&&(PORTBbits.RB2 == 0))//Código de atención de la interrupción
            {
                //LCD_Comando(0x01); //Display clear
                __delay_ms(2);
                //LCD_Escribir('0');
                n = '0';
                k = 0;
                __delay_ms(100);
            }
            if ((PORTBbits.RB7 == 0)&&(PORTBbits.RB1 == 0))//Código de atención de la interrupción
            {
                __delay_ms(2);
                //LCD_Escribir('#');
                n = '#';
                k = 0;
                __delay_ms(100);
            }
            if ((PORTBbits.RB6 == 0)&&(PORTBbits.RB3 == 0)) //Código de atención de la interrupción
            {
                //LCD_Comando(0x01); //Display clear
                __delay_ms(2);
                //LCD_Escribir('7');
                n = '7';
                k = 0;
                __delay_ms(100);

            }
            if ((PORTBbits.RB6 == 0)&&(PORTBbits.RB2 == 0))//Código de atención de la interrupción
            {
                //LCD_Comando(0x01); //Display clear
                __delay_ms(2);
                //LCD_Escribir('8');
                n = '8';
                k = 0;
                __delay_ms(100);
            }
            if ((PORTBbits.RB6 == 0)&&(PORTBbits.RB1 == 0))//Código de atención de la interrupción
            {
                //LCD_Comando(0x01); //Display clear
                __delay_ms(2);
                //LCD_Escribir('9');
                n = '9';
                k = 0;
                __delay_ms(100);
            }
            //
            if ((PORTBbits.RB5 == 0)&&(PORTBbits.RB3 == 0)) //Código de atención de la interrupción
            {
                //LCD_Comando(0x01); //Display clear
                __delay_ms(2);
                //LCD_Escribir('4');
                n = '4';
                k = 0;
                __delay_ms(100);
            }
            if ((PORTBbits.RB5 == 0)&&(PORTBbits.RB2 == 0))//Código de atención de la interrupción
            {
                //LCD_Comando(0x01); //Display clear
                __delay_ms(2);
                //LCD_Escribir('5');
                n = '5';
                k = 0;
                __delay_ms(100);
            }
            if ((PORTBbits.RB5 == 0)&&(PORTBbits.RB1 == 0))//Código de atención de la interrupción
            {
                //LCD_Comando(0x01); //Display clear
                __delay_ms(2);
                //LCD_Escribir('6');
                n = '6';
                k = 0;
                __delay_ms(100);
            }
            //
            if ((PORTBbits.RB4 == 0)&&(PORTBbits.RB3 == 0)) //Código de atención de la interrupción
            {
                //LCD_Comando(0x01); //Display clear
                __delay_ms(2);
                //LCD_Escribir('1');
                n = '1';
                k = 0;
                __delay_ms(100);
            }
            if ((PORTBbits.RB4 == 0)&&(PORTBbits.RB2 == 0))//Código de atención de la interrupción
            {
                //LCD_Comando(0x01); //Display clear
                __delay_ms(2);
                //LCD_Escribir('2');
                n = '2';
                k = 0;
                __delay_ms(100);
            }
            if ((PORTBbits.RB4 == 0)&&(PORTBbits.RB1 == 0))//Código de atención de la interrupción
            {
                //LCD_Comando(0x01); //Display clear
                __delay_ms(2);
                //LCD_Escribir('3');
                n = '3';
                k = 0;
                __delay_ms(100);
            }

            if (i == 1) {
                a = 1;
                b = 0;
                c = 1;
            }
            if (i == 2) {
                a = 1;
                b = 1;
                c = 0;
                //i=-1;
            }
            if (i == 3) {
                k = 0;
                i = -1;
            }
            i++;
        }
        PORTB = 0;
        RBIF = 0; //Desactivar bandera...

        //INTCONbits.RBIF==0;
    }

}
