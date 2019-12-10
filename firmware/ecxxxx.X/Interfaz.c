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
    /*LCD_Comando(0x02); //regresar cursor a casa
    __delay_ms(1.64);
    LCD_Cursor(13, 1);
    LCD_EscribirStr("#3: Menu Principal");*/
    LCD_Display(23);
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
                LCD_EscribirStr("#1: Alarma #2: Ventilacion");
                LCD_Display(26);
                Manual_Automatico(1);
                y = 1;
                while (w == 0) {
                    while (n == ' ') {
                    }
                    switch (n) {
                        case'1':
                            n = ' ';
                            LCD_Comando(0x01); // Limpiar Display
                            LCD_EscribirStr("    Alarma:");
                            LCD_Comando(0x02);
                            LCD_Cursor(0,2);
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
                                        LCD_EscribirStr("   Alarma On");
                                        PORTCbits.RC6 = 1; //Salida del detector de Humo en 0 logico por defecto
                                        Delay_ms(3000);
                                        z = 1;
                                        n = ' ';
                                        break;
                                    case'2':
                                        n = ' ';
                                        LCD_Comando(0x01); // Limpiar Display
                                        LCD_EscribirStr("   Alarma Off");
                                        PORTCbits.RC6 = 0; //Salida del detector de Humo en 0 logico por defecto
                                        Delay_ms(3000);
                                        z = 1;
                                        n = ' ';
                                        break;
                                    case'#': // Menu principal
                                        LCD_Comando(0x01); // Limpiar Display
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
                                        TRISCbits.TRISC2 = 0; // el pin CCP2 como entrada ( pwm apagado por defecto) 
                                        Delay_ms(3000);
                                        x = 1;
                                        n = ' ';
                                        break;
                                    case'2':
                                        n = ' ';
                                        LCD_Comando(0x01); // Limpiar Display
                                        LCD_EscribirStr(" Ventilacion Off");
                                        TRISCbits.TRISC2 = 1; // el pin CCP2 como entrada ( pwm apagado por defecto) 
                                        Delay_ms(3000);
                                        x = 1;
                                        n = ' ';
                                        break;
                                    case'#': // Menu principal
                                        LCD_Comando(0x01); // Limpiar Display
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
                        case'#': // Menu principal
                            LCD_Comando(0x01); // Limpiar Display
                            w = 1;
                            n = ' ';
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
                Manual_Automatico(0);
                y = 1;
                n = ' ';
                Delay_ms(3000);
                break;
            case'#': // Menu principal
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
    char y;

    n = ' ';
    y = 0;

    LCD_Comando(0x01); // Limpiar Display
    LCD_EscribirStr("Umbrales de actuadores:");
    LCD_Cursor(-23, 2);
    LCD_EscribirStr("#1: Temp  #2: Por defecto");
    LCD_Display(24);
    while (y == 0) {
        while (n == ' ') {
        }
        switch (n) {
            case'1':
                n = ' ';
                LCD_Comando(0x01); // Limpiar Display
                LCD_EscribirStr("  Umbral Temp.");
                LCD_Comando(0x02);
                LCD_Cursor(0,2);
                Umbral_Temp();
                Delay_ms(3000);
                y = 1;
                n = ' ';
                break;
            case'2':
                n = ' ';
                LCD_Comando(0x01); // Limpiar Display
                LCD_EscribirStr(" Umbral Defecto");
                UT = 30;
                LCD_Comando(0x02);
                LCD_Cursor(0,2);
                LCD_EscribirStr("    Temp. 30C   ");
                Delay_ms(3000);
                y = 1;
                n = ' ';
                break;
            case'#':
                LCD_Comando(0x01); // Limpiar Display
                y = 1;
                break;
            default:
                y = 0;
                n = ' ';
                break;
        }
    }
}

void INTERFACE_Datos(void) {
    char y;

    n = ' ';
    y = 0;

    LCD_Comando(0x01); // Limpiar Display
    LCD_EscribirStr("#1: Temperatura");
    LCD_Comando(0x02);
    LCD_Cursor(0,2);
    LCD_EscribirStr("#2: Humo ");
    LCD_EscribirStr("#3: Lumenes");
    LCD_Display(19);
    while (y == 0) {
        while (n == ' ') {
        }
        switch (n) {
            case'1':
                LCD_Comando(0x01); // Limpiar Display
                LCD_Comando(0x02);
                LCD_Cursor(0,2);
                LCD_EscribirStr("Humedad: 36%");
                Temperatura();
                Delay_ms(3000);
                y = 1;
                break;
            case'2':
                LCD_Comando(0x01); // Limpiar Display
                LCD_EscribirStr("Nivel de CO: 15%");
                LCD_Cursor(-16, 2);
                Delay_ms(3000);
                y = 1;
                break;
            case'3':
                LCD_Comando(0x01); // Limpiar Display
                Fotocelda();
                //__delay_ms(5000);
                y = 1;
                break;
            case'#':
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
    char y;

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

    char t = 3, i = 1, x;
 
    LCD_Comando(0x01); // Limpiar Display
    LCD_Cursor(3, 1); // 3---> Numero de cuadros del cursor que se desea desplazar hacia la derecha - 63 la primera lina, para la simulacion - 40 la primera linea para el montaje
    // 1---> Arriba, 2 Abajo
    LCD_EscribirStr("BIENVENIDO");

    char j = '0';
    n = ' ';
    for (i = 1; (i <= t)&&(n == ' '); i++) {

        LCD_Comando(0x02); //regresar cursor a casa
        LCD_Cursor(8, 2);
        
        j = i + '0';
        LCD_Escribir(j);
        
        
        for (x = 0; (x < 100)&&(n == ' '); x++) {
            __delay_ms(5);
        }
    }
    //Delay_ms(500);
    LCD_Comando(0x01); // Limpiar Display
    n = ' ';
}