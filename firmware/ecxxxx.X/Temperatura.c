void Temperatura(){
    int aux1, aux2;
    char UTAux = 0;
    n = ' ';
    while (UTAux == 0) {
        while (n == ' ') {
            LCD_Comando(0x02);
            LCD_EscribirStr("Temp: ");
            aux1 = TEMP / 10;
            LCD_Escribir(aux1 + '0');
            aux2 = TEMP % 10;
            LCD_Escribir(aux2 + '0');
        }
        switch (n) {
            case '2':
                TEMP = TEMP + 1;
                LCD_Comando(0x02);
                LCD_EscribirStr("Temp: ");
                aux1 = TEMP / 10;
                LCD_Escribir(aux1 + '0');
                aux2 = TEMP % 10;
                LCD_Escribir(aux2 + '0');
                n = ' ';
                break;
            case '8':
                TEMP = TEMP - 1;
                LCD_Comando(0x02);
                LCD_EscribirStr("Temp: ");
                aux1 = TEMP / 10;
                LCD_Escribir(aux1 + '0');
                aux2 = TEMP % 10;
                LCD_Escribir(aux2 + '0');
                n = ' ';
                break;
            case '#':
                UTAux = 1;
                break;
            default:
                n = ' ';
                break;
        }
    }
}

void Umbral_Temp(void) {
    int aux1, aux2;
    char UTAux = 0;
    n = ' ';
    while (UTAux == 0) {
        while (n == ' ') {
            LCD_Comando(0x02);
            LCD_Cursor(0, 2);
            LCD_EscribirStr("Temp: ");
            aux1 = UT / 10;
            LCD_Escribir(aux1 + '0');
            aux2 = UT % 10;
            LCD_Escribir(aux2 + '0');
        }
        switch (n) {
            case '2':
                UT = UT + 1;
                LCD_Comando(0x02);
                LCD_Cursor(0, 2);
                LCD_EscribirStr("Temp: ");
                aux1 = UT / 10;
                LCD_Escribir(aux1 + '0');
                aux2 = UT % 10;
                LCD_Escribir(aux2 + '0');
                n = ' ';
                break;
            case '8':
                UT = UT - 1;
                LCD_Comando(0x02);
                LCD_Cursor(0, 2);
                LCD_EscribirStr("Temp: ");
                aux1 = UT / 10;
                LCD_Escribir(aux1 + '0');
                aux2 = UT % 10;
                LCD_Escribir(aux2 + '0');
                n = ' ';
                break;
            case '#':
                UTAux = 1;
                break;
            default:
                n = ' ';
                break;
        }
    }
}
