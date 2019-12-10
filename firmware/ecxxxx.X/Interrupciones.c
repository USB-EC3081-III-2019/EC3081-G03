INTCONbits.GIE = 1; //Hab interrupciones Globales
    PORTB = 0;
    RBIF = 0;
    INTCONbits.RBIE = 1; //Port b

    OPTION_REGbits.nRBPU = 0;
}

void Actuar() {
    if (DetectorHumo() == 1) {
        PORTCbits.RC6 = 1;
    } else {
        PORTCbits.RC6 = 0;
    }
    
    if(TEMP>=UT){
        TRISCbits.TRISC2 = 0; //PWM activado
    }else{
        TRISCbits.TRISC2 = 1; //PWM desactivado
    }
}

char DetectorHumo() {
    TRISCbits.TRISC3 = 1;
    //TRISCbits.TRISC4 = 0;
    //PORTCbits.RC4 = 0;
    if (PORTCbits.RC3 == 1) {
        return 0;
    } else {
        return 1;
    }
}

void Fotocelda() {

    n = ' ';
    int valor;
    long lux1;
    int uni, dec, cen, mil;

    while (n == ' ') {
        valor = ADC_Read(0); //Se coloca 0 porque es el canal analogico RA0

        if (valor > 725) {
            lux1 = (-6 * valor + 5010) / 10;

            if (valor > 835)
                lux1 = 0;
        } else {
            lux1 = ((8 * valor / 1000 - 11600 / 1000) * valor) + 4271;
        }

        LCD_EscribirStr("Flujo luminoso:");
        LCD_Cursor(-15, 2);

        if (lux1 < 0) {
            lux1 = -lux1;
        }

        mil = (lux1) / 1000;
        LCD_Escribir('0' + mil);
        cen = (lux1 - mil * 1000) / 100;
        LCD_Escribir('0' + cen);
        dec = (lux1 - mil * 1000 - cen * 100) / 10; // a partir de aqui es el error
        LCD_Escribir('0' + dec);
        uni = lux1 % 10;
        LCD_Escribir('0' + uni);


        __delay_ms(500);
        LCD_Comando(0x02);
    }
}

unsigned int ADC_Read(unsigned char canal) {
    ADCON0 &= 0xC5; //Valor para reiniciar los canales a 0
    ADCON0bits.CHS = canal; //Se elige el canal
    __delay_ms(2); //Espera para el cambio
    GO_nDONE = 1; //Se activa la
    while (GO_nDONE); //Esperamos hasta que terminen
    int X = ADRESH << 8;
    X = X + ADRESL; //Los valores se guardarán en el registro ADRES H(2 mas significativos) L(6 menos significativos)
    return (X);

}

void Delay_ms(int x) {
    //__delay_ms(100);
    n = ' ';
    for (int i = 0; i < x; i++) {
        if (n == ' ') {
            __delay_ms(1);
        }
    }
    n = ' ';
}


void __interrupt(high_priority) Interrupcion(void) {
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

    if (TMR2IF == 1) // Timer has overflown
    {
        TMR2IF = 0; // Clear timer interrupt flag
        count++;
        Actuar();
    }
}

