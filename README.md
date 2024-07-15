***
# NUñEZ Gabriel Eduardo  
Email: nunezgabrieleduardo@gmail.com

# TP1
**Test de teclado de Alarma**
*El teclado led de alarma cuenta de salidas digitales que controlan leds indicadores de Zonas, de estado de sistema, de iluminación de Teclas, entradas de analógicas de Zona y de sensor de batería, entradas digitales para ingreso de teclas, salida digital para indicador auditivo, puerto de comunicación UART.*
*El objetivo proncipal es desarrollar un programa que permita testear el hardware de un teclado led de alarma.*

## Hardware a testear en esta entrega:
* Leds de sistema.
  * LedArm.
  * LedReady.
  * LedSystem. 

* Entrada de teclas.
  * Tecla 1.
  * Tecla 2.
  * Tecla 3.
    
* Salida de audio por buzzer.

* Entrada analogica (medicion voltaje potenciometro).
  * Representa el sensado de nivel de bateria o zona de teclado.  
  
* Puerto de comunicacion Uart.
  * La utilizacion de este puerto nos ifdica que esta operativo.

> ## Procedimiento:
> El programa arranca encendiendo secuencialmente los leds Arm, Ready y System una y otra ves.
> El el monitor serie se va indicando como seguir el test.
> Se arranca el test pulsando tecla 1 + tecla 2.
> Luego se va probanto el ingreso secuencial de cada tecla 1, 2 y 3.
> Luego se pruba los leds, seguido el buzzer y por ultimo se hace una medicion ADC.
> Se avanza secuencialmentea pulsando la tecla 1.
> Se indica por el terminal tanto el inicio como el final del test.
> Existe un timeout que de superarlo termina el testeo.
> Los 3 led encendiendo de forma secuencial indica que aun no empezó el test.
> Los 3 led intermitentes indican que el test finalizo.

### Conexionado:
![esquemaConexion](https://github.com/nnzgab/TP1/blob/main/conexion.PNG)

### Salida monitor Serial:
![SalidaMonitorSerial](https://github.com/nnzgab/TP1/blob/main/salida%20monitor%20serie.PNG)
***




