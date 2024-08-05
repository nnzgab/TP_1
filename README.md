# CURSO ONLINE DE SISTEMAS EMBEBIDOS - Arm Book - Edición 2024

# TRABAJO PRACTICO N°2

#### Funcionalidades de la segunda entrega que corresponde al TP N°2 incluye:

* **Teclado Matricial
* **Maquina de estados finitos
* **Modularizacion en archivos
* 
***
## Alumno NUñEZ Gabriel Eduardo  
## Email: nunezgabrieleduardo@gmail.com

## Teclado de Alarma: Firmware de Prueba Funcional.

### Introducción.

Los teclados de alarma son componentes cruciales en los sistemas de seguridad, ya que permiten a los usuarios interactuar con el sistema y controlar sus funciones. Es fundamental garantizar que estos teclados funcionen correctamente para asegurar la protección adecuada de los hogares o negocios. La implementación de un firmware de prueba funcional en los teclados de alarma durante el proceso de producción puede ayudar a identificar y corregir fallas temprano, antes de que lleguen a los clientes.

### Objetivo principal.

El objetivo principal de este proyecto es desarrollar e implementar un firmware que permita realizar una prueba funcional completa de los teclados de alarma durante la etapa de producción. Este firmware debe evaluar todos los componentes del teclado, incluyendo:

* **Teclado matricial:** Verificar la correcta respuesta de cada tecla al ser presionada, detectando posibles fallos en los contactos o la matriz de teclas.
* **LEDs:** Asegurar que los 9 LEDs (6 para zonas y 3 para sistema) funcionen correctamente, indicando los estados correspondientes de manera precisa.
* **Buzzer:** Probar el funcionamiento del buzzer, generando sonidos de alerta y notificaciones según lo especificado en el diseño del teclado.
* **Entradas analógicas:** Interpretar los valores analógicos leídos para determinar el estado de la batería y las zonas del teclado.
* **Puerto de comunicación UART:** Validar la correcta comunicación entre el teclado y el panel de alarma, enviando y recibiendo mensajes de prueba.

### Diagrama en bloque.
![Diagrama en bloque](https://raw.githubusercontent.com/nnzgab/TP_1/nnzgab-patch-1/diagrama_bloque.PNG)

### Descripción del programa de prueba de teclado.

>#### Inicio y cuenta regresiva.
>
>* El programa comienza con una cuenta regresiva de 6 segundos visible en el monitor serial.
>* Durante este tiempo, tres LEDs de sistema se encenderán secuencialmente.
>
>#### Inicio del test.
>
>* Para iniciar el test, el usuario debe presionar una combinación específica de dos teclas (por ejemplo, '#' y '1') dentro del período de la cuenta regresiva.
>* Si se inicia el test correctamente, se mostrará el mensaje "INICIO DE TEST" en el monitor serial.
>
>#### Prueba de ingreso de teclas.
>
>* El programa solicitará al usuario que ingrese cada tecla del teclado de manera secuencial.
>* Cada vez que se ingrese una tecla correcta, se avanzará a la siguiente.
>
>#### Prueba de LEDs.
>
>* Una vez finalizada la prueba de ingreso de teclas, se procederá a evaluar el funcionamiento de cada LED, encendiéndolos secuencialmente.
>* Para avanzar a la siguiente prueba, el usuario debe presionar la tecla '#'.
>
>#### Prueba de buzzer y entradas analógicas.
>
>* Seguidamente, se evaluarán el buzzer y las entradas analógicas del teclado.
>
>#### Finalización del test.
>
>* El test concluirá con el mensaje "FINAL DEL TEST" en el monitor serial.
>* La finalización del test se verá con todos los leds parpadeando intermitentemente.
>* Durante la ejecución del test, si el usuario no pasa al siguiente estado dentro de un período de 6 segundos, el test se finalizará automáticamente.
>




