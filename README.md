# Invernadero Inteligente
 El proyecto consiste en diseñar un invernadero inteligente. Un [invernadero](https://grupomsc.com/blog/invernadero/que-es-y-como-funciona-un-invernadero) es un recinto en el que se mantienen condiciones ambientales adecuadas para favorecer el cultivo de plantas. En un invernadero inteligente se monitorean, a través de sensores, las condiciones ambientales (humedad, luminosidad, temperatura, aireación) en las que se encuentra la planta, esta información es interpretada por un microcontrolador el cual dará la señal a una serie de actuadores para que se activen de ser necesario. La intención es automatizar el sistema que controlada las distintas variables que intervienen en este sistema, con el fin de aumentar su eficiencia, es decir, conseguir los mejores resultados en el menor tiempo posible.

## Integrantes del equipo
* 15-11517 José Villalobos 
* 15-10596 Karlhianna González

# Sensores
¿Qué es un sensor?
Un sensor es un dispositivo capaz de captar magnitudes físicas (variaciones de luz, temperatura, sonido, etc.) u otras condiciones de su entorno. Un sensor de temperatura es un dispositivo capaz de transformar los cambios de temperatura en señales eléctricas para ser interpretadas por otro dispositivo eléctrico o electrónico.

## Sensores a utilizar

 * FOTOCELDA [LDR](https://protosupplies.com/product/ldr-light-dependent-resistor-12mm/) 
 
  > Las fotoresistencias, también conocidas como resistencias dependientes de la luz (LDR), son dispositivos sensibles a la luz que se utilizan con mayor frecuencia para indicar la presencia o ausencia de luz, o para medir la intensidad de la luz. En la oscuridad, su resistencia es muy alta, a veces hasta 1MΩ, pero cuando el sensor LDR está expuesto a la luz, la resistencia disminuye drásticamente, incluso hasta unos pocos ohmios, dependiendo de la intensidad de la luz. Los LDRs tienen una sensibilidad que varía con la longitud de onda de la luz aplicada y son dispositivos no lineales. Se utilizan en muchas aplicaciones, pero a veces son obsoletos por otros dispositivos como fotodiodos y fototransistores. [Fuente](http://www.resistorguide.com/photoresistor/)
 <img src="https://raw.githubusercontent.com/USB-EC3081-III-2019/EC3081-G03/master/docs/ldr.png">
 
* FAN COOLER

* SENSOR DE TEMPERATURA [LM35](https://www.mouser.com/ProductDetail/Texas-Instruments/LM35DZ-NOPB?qs=sGAEpiMZZMvu8NZDyZ4K0WAoLK%252Bhc60t)
 
 > El LM35 es un circuito electrónico sensor que puede medir temperatura. Su salida es analógica, es decir, te proporciona un voltaje proporcional a la temperatura. El sensor tiene un rango desde −55°C a 150°C. Su popularidad se debe a la facilidad con la que se puede medir la temperatura. Incluso no es necesario de un microprocesador o microcontrolador para medir la temperatura. Dado que el sensor LM35 es analógico, basta con medir con un multímetro, el voltaje a salida del sensor.
 Para convertir el voltaje a la temperatura, el LM35 proporciona 10mV por cada grado centígrado. También cabe señalar que ese sensor se puede usar sin offset, es decir que si medimos 20mV a la salida, estaremos midiendo 2°C. [Fuente](https://hetpro-store.com/TUTORIALES/lm35/)
 <img src="https://github.com/USB-EC3081-III-2019/EC3081-G03/blob/master/docs/lm35%20image.jpg" width="300" height="300">
 
* SENSOR DE HUMEDAD Y TEMPERATURA [DHT11](https://github.com/USB-EC3081-III-2019/EC3081-G03/blob/master/docs/DHT11%20Image.jpg) 
 
 <img src="https://github.com/USB-EC3081-III-2019/EC3081-G03/blob/master/docs/DHT11%20Image.jpg" width="300" height="300">
 
 # Actuadores
 ¿Qué es un actuador?
Un actuador es un dispositivo capaz de transformar energía hidráulica, neumática o eléctrica en la activación de un proceso con la finalidad de generar un efecto sobre un sistema automatizado. Este recibe la orden de un regulador o controlador y en función a ella genera la señal para activar un elemento final de control. [–Fuente]( https://es.wikipedia.org/wiki/Actuador)



## Estructura del repositorio
### docs/
En la carpeta docs/ se colocan todos los archivos de soporte que necesite para la documentación del proyecto: .pdf, imágenes, documentos, etc. También todas las imagenes o resultados que vayan a utilizarse como adjuntos en la WIKI. La estructura interna de la carpeta docs/ puede contener tantos directorios como ustedes lo requieran.
### firmware/
En la carpeta firmware/ deben colocarse los archivos relevantes del código que debe ejecutarse en el microcontrolador. Si el IDE utilizado para el desarrollo del firmware genera un árbol de carpetas asociadas al proyecto, incluya todos los directorios necesarios. Procure solo incluir los archivos y directorios necesarios para compilar correctamente el firmware y no incluya los archivos intermedios que se generan durante la compilación. 
#### Caso MPLAB


#### Caso CODEWARRIOR

### Software/
En el caso de que el proyecto incluya desarrollo de software para PC (MATLAB, Python, LabVIEW, etc) el código/proyecto respectivo debe ir dentro de este directorio.

## Instrucciones para usar la plantilla
* Haga click sobre la opción 'use this template' en la parte superior del repositorio.
* Aparecera la ventana para crear un repositorio basado en esta plantilla.
* Debe crear el repositorio dentro de la organización correspondiente a la materia y no dentro de su cuenta personal de GitHub.
* El nombre del repositorio debe ser ECXXXX-GXX.
* Edite el README.md de su repositorio según los datos de su materia y grupo.

