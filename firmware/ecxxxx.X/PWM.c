void PIC_Configuracion_Inicial(void) {
    TRISD = 0;
    TRISCbits.TRISC3 = 1; //Entrada del detector de Humo
    TRISCbits.TRISC6 = 0; //Salida del detector de Humo (actuar)
    PORTCbits.RC6 = 0; //Salida del detector de Humo en 0 logico por defecto

    TRISCbits.TRISC0 = 0; //LCD_E
    TRISCbits.TRISC1 = 0; //LCD_RS
    
    TRISAbits.TRISA1 = 0; //Salida del indicador de Automatico(0 logico)/Manual(1 logico)
    PORTAbits.RA1 = 0; // Configuracion en modo automatico por defecto

    TRISB = 0b11110000;

    //ADCON1bits.PCFG = 0b111110; //A0 será la entrada analógica
    //Perifericos (Iniciar configuraciones analogicas)
    ADCON0bits.ADCS = 0b00; //ADCS1:ADCS0: A/D Conversion Clock Select bits 00 = FOSC/2    
    ADCON0bits.ADON = 1; //Encendemos el modulo analogico
    ADCON1bits.ADFM = 1; //Justificación a la derecha(De esta manera, los bits más significativos se almacenan en ADRESH)
    //ADCON0 = 0b00000000; //Configuracion del registro ADCON0
    /*INICIALIZACIÓN DE INTERRUPCIONES*/
    INTCON = 0; //limpiar registro INTCON
    
    ////////////////////////////////////////////////////////////////////////////
    /////////////////////////INTERUPCION POR TIEMPO/////////////////////////////
    T2CON = 0b00000100; // Timer0 with external freq and 32 as prescaler
    TMR2 = 0; // Load the time value for 1us delayValue can be between 0-256 only
    PR2 = 255;
    TMR2ON = 1; //Enable timer interrupt bit in PIE1 register
    TMR2IE = 1; //Enable timer interrupt bit in PIE1 register
    GIE = 1; //Enable Global Interrupt
    PEIE = 1; //Enable the Peripheral Interrupt
    /////////////////////////INTERUPCION POR TIEMPO/////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    
    ////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////PWM////////////////////////////////////////
    PR2 = 255;
    CCPR1L =    0b00011001;
    CCP1CON =   0b00111100; //    <5:4>   fin del paso 2
    //////////////////////Para Variar el Dcy se varia lo siguiente://////////////////////////////////////////
    CCPR1L =    0b10000000; // 50%
    CCP1CON =   0b00001100 ;////<1:3 = 11xx> colocar el bit 1:3 el 1 es para el modo PWM
    TRISCbits.TRISC2 = 1; // el pin CCP2 como entrada ( pwm apagado por defecto) 
    T1CON = 0b00000110; // Timer2 prescaler de 16