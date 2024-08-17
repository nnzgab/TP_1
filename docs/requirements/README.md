# CURSO ONLINE DE SISTEMAS EMBEBIDOS - Arm Book - Edición 2024

##### Alumno NUñEZ Gabriel Eduardo  
##### Email: nunezgabrieleduardo@gmail.com

## Definición de Requisitos y Casos de Uso del Trabajo Final.

#### Selección del proyecto a implementar

En la empresa donde trabajo se tienen diferentes proyectos pendientes de realizar, y se evaluaron tres de ellos:
* Proyecto 1: `Teclado de alarma LED.`
* Proyecto 2: `Micro-amperímetro para sensores de bajo consumo.`
* Proyecto 3: `Expansor de zonas para alarma.`

Los aspectos analizados para la selección del proyecto a implementar fueron los siguientes:
•	Disponibilidad de Hardware en el momento de implementación.
•	Utilidad del proyecto.
•	Tiempo de implementación.

La decisión final para la elección del proyecto a implementar se basará en la Tabla 1, donde se han ponderado los diferentes aspectos de cada proyecto.

| Proyectos     |                   | Disponibilidad de HW (Peso: 10) | Utilidad del Proyecto (Peso: 8) | Tiempo de implementación (Peso: 8) | Peso Final |
|---------------|-------------------|---------------------------------|---------------------------------|------------------------------------|------------|
| Proyecto 1    | Puntaje           |4                                |6                                |6                                   |     -      |
| Proyecto 1    | Puntaje Ponderado |20                               |48                               |60                                  |287         |
| Proyecto 2    | Puntaje           |8                                |7                                |8                                   |     -      |
| Proyecto 2    | Puntaje Ponderado |40                               |56                               |80                                  |250         |
| Proyecto 3    | Puntaje           |6                                |5                                |5                                   |     -      |
| Proyecto 3    | Puntaje Ponderado |30                               |40                               |50                                  |250         |

_Tabla 1: Comparación de puntajes ponderados de los proyectos candidatos para trabajo final_

Disponibilidad de hardware: Si bien los tres proyectos son factibles de realizar con los recursos disponibles a mediano plazo, el Proyecto 2 presenta la ventaja de poder ser iniciado de inmediato, dado que los componentes necesarios ya se encuentran en stock. 

Tiempo de implementación: El Proyecto 2 presenta un equilibrio entre complejidad y duración, lo que permite obtener resultados tangibles en un plazo razonable, en comparación con los otros proyectos.

Utilidad inmediata: El microamperímetro es una herramienta esencial para el control de calidad en la producción de los dispositivos actuales, lo que garantiza un impacto directo y positivo en los procesos productivos de la empresa. A diferencia de los Proyectos 1 y 3, que aún se encuentran en etapa de prototipo, el Proyecto 2 responde a una necesidad concreta y urgente.

### _Descripción del proyecto Micro-amperímetro para sensores bajo consumo._

### Objetivo:
Desarrollar un micro amperímetro para medir el consumo de corriente en sensores PIR y magnéticos de bajo consumo desarrollados en la empresa donde trabajo, con el fin de establecer un control de calidad, verificando si el consumo de cada sensor se encuentra dentro de los límites predefinidos, asegurando así la optimización energética de los mismos.
### Resultados Esperados:
Este proyecto permitirá obtener un dispositivo capaz de medir con exactitud el consumo de corriente de sensores inalámbricos, facilitando la identificación de aquellos que no cumplen con los parámetros establecidos. A través de una interfaz intuitiva con indicadores LED y un display LCD, el usuario podrá verificar rápidamente el estado de cada sensor.
### Análisis e Implementación:
Se busca con el dispositivo visualizar en pantalla el valor de corriente medido en tiempo real, tanto en forma numérica como a través de una representación más intuitiva con LEDs que indican de forma clara si el consumo del sensor se encuentra dentro de los límites preestablecidos:
LED verde: El consumo del sensor está dentro de los límites normales, indicando un correcto funcionamiento.
LED rojo: El consumo del sensor está fuera de los límites establecidos, señalando una posible falla o anomalía en el sensor.
Además, incluirá una opción para desactivar la pantalla y utilizar solo los LEDs, brindando versatilidad en diferentes entornos.

En la Figura 1 se observa un diagrama de bloques del sistema.
![Fig 1 Diagrama en bloques del Micro-amperimetro](https://github.com/nnzgab/TP_1/blob/TPF/docs/requirements/data/Diagrama_bloques.PNG)
_Figura 1: Diagrama en bloques del Micro-amperimetro_


### Elicitación de requisitos y casos de uso

En la tabla 2 se comparan dos instrumentos para medir corrientes del orden de los microamperes.

| Característica           | WDCU30001                                 | DT132A                                    |
|--------------------------|-------------------------------------------|-------------------------------------------|
| Fuente de alimentación   | 7-24 V CC                                 | 9 V CC                                    |
| Rango de corriente DC    | 1 uA-100 mA                                 | 40 µA / 400 µA / 4 mA / 40 mA / 400 mA         |
| Rango de tension DC      | 1 uV-30 V                                   | 400 mV /4 V / 40 V / 400 V / 600 V            |
| Alarma de intervalo      | Si                                        | Si                                        |
| Forma de conexion        | Baterías AA                               | Sin batería (transformador a 220V)        |
| Tamaño del producto      | 79 x 43 x 33 mm.                          | 145 x 70 x 35 mm.                         |
| Display                  | Si                                        | no                                        |
| Precio                   | 42,28 USD + IVA                           | 52,8 USD + IVA                            |

_Tabla 2: Comparación entre dos productos de medición de microamperes disponibles en el mercado_

El microamperímetro WDCU30001 es muy similar a lo que se busca lograr, por que mide corrientes muy pequeñas y tiene un avisador para saber cuandose alcanza determinado limite, tambien pero realiza otras mediciones que no son importantes para este desarrollo, por lo que se buscará un dispositivo que mida solo microamperes en el orden preestablecido y los indique tanto con un display como leds para el estado.

 Links:
* [WDCU30001 ]([https://www.agrofy.com.ar/pluviometro-omixom-omx-rain-modelo-gprs.html](https://es.aliexpress.com/item/1005006378956430.html))
* [DT132A]([https://www.donagro.com.ar/estacion-meteorologica-daza-dzwh-2900-wifi-solar-remota-1820.html](https://articulo.mercadolibre.com.ar/MLA-1131139873-multimetro-digital-autorrango-capacimetro-temp-true-rms-l9-_JM#polycard_client=search-nordic&position=2&search_layout=grid&type=item&tracking_id=65034891-ddb5-48ba-bf3f-628254b05d48))

La Tabla 3 presenta los requerimientos del proyecto.

| Grupo de Requerimiento | ID de Requerimiento | Descripción |
|---|---|---|
| Funcionalidad | 1.1 | Medir corrientes eléctricas DC en el rango de 1 uA a 100 uA. |
| Funcionalidad | 1.2 | Indicar en tiempo real si la corriente medida está dentro o fuera de los límites preestablecidos. |
| Funcionalidad | 1.3 | Mostrar el valor de la corriente medida en un display. |
| Hardware | 2.1 | Incorporar un display LCD de 16x2 caracteres. |
| Hardware | 2.2 | Utilizar LEDs indicadores (verde y rojo) para señalizar si la medición está dentro o fuera de los límites preestablecidos. |
| Hardware | 2.3 | El sistema se conectará al dispositivo bajo prueba con pinzas cocodrilo. |
| Hardware | 2.4 | El sistema tendrá una llave de encendido. |
| Hardware | 2.5 | El sistema tendrá una llave para poder apagar el display con llave on/off. |
| Alimentación | 3.1 | El dispositivo debe ser alimentado con baterías CR123A. |
| Alimentación | 3.2 | Implementar un sistema de bajo consumo para prolongar la vida útil de la batería. |
| Alimentación | 3.3 | No incluye cargador de batería. |
| Alimentación | 3.4 | No incluye detección de nivel de batería. |
| Tiempo de ejecución | 4.1 | El proyecto se entregará antes del 17 de Septiembre de 2024. |
| Manual de uso y Documentación | 5.1 | El código del sistema embebido estará disponible en un repositorio Git, acompañado de un informe detallado con lista de partes, diagramas de conexión, requerimientos cumplidos, forma de uso y conclusiones. |
| Costo | 6.1 | El costo será menor a 35 dólares. |

_Tabla 3: Requerimientos del sistema_

#### Casos de uso

| Elemento de Caso de Uso | Definición |
|---|------|
| Disparador | El usuario necesita visualizar el consumos de sus sensores en funcionamiento en tiempo real |
| Precondición | El sistema está encendido y con baterías cargadas. El selector del display está en on|
| Flujo Básico | El usuario conecta el dispositivo bajo prueba al sistema. El usuario enciende el sistema. El sistema muestra en el display el valor en tiempo real de la corriente. El sistema enciende el led verde o rojo de acuerdo si el valor de corriente está dentro o fuera del límite preestablecido. |
| Flujo Alternativo | **1.a** no se muestra la medición en el display pero si en los leds. En este caso la llave selectora del display podría estar en off. <br><br> **1.b** no se muestra lectura en el display ni encienden los leds. En este caso el sistema podría estar apagado y se debería encender el sistema. <br><br> **1.c** no se muestra lectura en el display ni encienden los leds y el sistema está en on. en este caso se debería cambiar las baterías que podrían estar descargadas. |

_Tabla 4: Diagrama de caso de uso número 1. Medición de corriente en tiempo real_


| Elemento de Caso de Uso | Definición |
|---|------|
| Disparador | El usuario necesita visualizar si el consumo esta dentro o fuera del rango establecido |
| Precondición | El sistema está encendido y con baterías cargadas. El selector del display está en off|
| Flujo Básico | El usuario conecta el dispositivo bajo prueba al sistema. El usuario pone el dispositivo bajo prueba en bajo consumo. El usuario enciende el sistema. El sistema enciende el led verde o rojo de acuerdo si el valor de corriente está dentro o fuera del limite preestablecido. |
| Flujo Alternativo | **2.a** no se enciende ninguno de los leds. el sistema podría estar apagado. <br><br> **2.b** No se enciende ninguno de los leds y el sistema está en ON. En este caso puede encender el display para determinar el consumo por esta lectura. <br><br> **2.c** no se enciende ninguno de los leds y el sistema está en ON y el display está en ON y no tengo lectura. en este caso se debería cambiar las baterías que podrían estar descargadas.|

Tabla 5: Diagrama de caso de uso número 1. Determinar si el consumo está dentro o fuera del rango establecido_
