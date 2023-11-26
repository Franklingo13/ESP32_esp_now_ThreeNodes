# Proyecto de Ejemplo para ESP32

Este proyecto de ejemplo demuestra la integración de ESP-NOW para la comunicación entre dos nodos ESP32. En este caso, un nodo transmisor envía datos a un nodo receptor a través de ESP-NOW, y el nodo receptor muestra la información en una pantalla OLED.

## Objetivo del Proyecto

El objetivo de este proyecto es proporcionar un punto de partida para desarrollar aplicaciones que utilizan la funcionalidad ESP-NOW de los microcontroladores ESP32. Además, se utiliza una pantalla OLED para visualizar los datos recibidos.

## Configuración del Proyecto

Este proyecto ha sido probado en los siguientes objetivos:
- ESP32

## Estructura del Proyecto

El contenido principal del proyecto se encuentra en el directorio `main`, con la siguiente estructura:

```
├── CMakeLists.txt
├── main
│   ├── CMakeLists.txt
│   └── main.c
└── README.md                  // Este archivo
```

- `CMakeLists.txt`: Este archivo contiene la configuración del sistema de construcción CMake para el proyecto.

- `main`: Este directorio contiene el código fuente principal del proyecto.

    - `main.c`: Este archivo contiene el código fuente principal que implementa la lógica del proyecto.

## Cómo Utilizar el Ejemplo

Se recomienda a los usuarios utilizar este ejemplo como plantilla para nuevos proyectos. Se pueden seguir las instrucciones detalladas en la [página de documentación](https://docs.espressif.com/projects/esp-idf/en/latest/api-guides/build-system.html#start-a-new-project) para iniciar un nuevo proyecto.

## Funcionalidades Principales

- Comunicación bidireccional entre dos nodos ESP32 utilizando ESP-NOW.
- Visualización de datos recibidos en una pantalla OLED.
- Uso de la infraestructura de construcción ESP-IDF basada en CMake.

## Configuración del Nodo Receptor

El nodo receptor está configurado para mostrar datos específicos en la pantalla OLED según la dirección MAC del nodo transmisor. En el código, se identifica al nodo transmitido por su dirección MAC y se muestra información específica en la pantalla OLED.

## Configuración del Nodo Transmisor

El nodo transmisor lee datos de un sensor (por ejemplo, un ADC) y los transmite al nodo receptor a través de ESP-NOW. El mensaje transmitido contiene la lectura del sensor.

## Notas Adicionales

- Este proyecto utiliza ESP-IDF y está configurado para construirse con CMake.
- El código ha sido comentado para facilitar la comprensión y posible modificación.

Este proyecto proporciona una base sólida para desarrollar aplicaciones que involucren la comunicación inalámbrica entre nodos ESP32 y la visualización de datos en una pantalla OLED. Se recomienda revisar la documentación de ESP-IDF para obtener más detalles sobre la configuración y el desarrollo de proyectos.