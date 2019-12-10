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