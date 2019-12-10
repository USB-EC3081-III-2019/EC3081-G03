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
    char i;

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

void LCD_Display(int Tam) {
    int aux1, i;

    __delay_ms(2);
    LCD_Comando(0x02);

    __delay_ms(300);
    if (Tam > 16 && Tam < sr) {
        aux1 = Tam - 16;
        n = ' ';
        for (i = -1; (i < aux1) && (n == ' '); i++) {
            __delay_ms(300);
            LCD_Comando(0x1B);
        }
    }
    if (n == ' ') {
        Delay_ms(600);
    }
    __delay_ms(2);
    LCD_Comando(0x02);
    __delay_ms(2);
}