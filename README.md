# ESP32_esp_now_ThreeNodes

Este repositorio contiene tres nodos ESP32 que utilizan la tecnología ESP-NOW para la comunicación entre ellos. Cada nodo tiene su propia carpeta en el repositorio: `espnow_ADC_TX`, `esp-now_RTC_TX`, y `esp-now_RX`. Estos nodos están diseñados para realizar funciones específicas y pueden ser probados individualmente.

## Estructura del Repositorio

1. **espnow_ADC_TX:** Este nodo transmite datos del conversor analógico a digital (ADC) utilizando ESP-NOW.

2. **esp-now_RTC_TX:** Este nodo transmite la fecha y hora actual desde un módulo RTC (Real-Time Clock) mediante ESP-NOW.

3. **esp-now_RX:** Este nodo actúa como receptor para recibir datos transmitidos por los otros nodos a través de ESP-NOW.

## Configuración y Uso

Para probar cada nodo, sigue estos pasos:

1. Crea un nuevo proyecto en ESP-IDF utilizando la plantilla de ejemplo correspondiente a cada nodo.

2. Copia la carpeta `components` del nodo respectivo en la raíz del nuevo proyecto. Esta carpeta contiene las librerías necesarias para el funcionamiento del nodo.

3. Copia el código principal de cada nodo en el nuevo proyecto.

4. Consulta los diagramas de conexión ubicados en la carpeta `Imagenes` para asegurarte de que los componentes estén conectados correctamente. Por ejemplo, "Imagenes/diagrama_conexion_nodoRX_OLED_esp32.jpg" muestra cómo conectar la pantalla OLED al ESP32, y "Imagenes/ESP32-with-DS3231-RTC-Module-schematic-diagram.jpg" muestra cómo conectar el RTC DS3231 al ESP32.

## Detalles de los Nodos

### espnow_ADC_TX

Este nodo transmite datos del ADC mediante ESP-NOW. Asegúrate de configurar correctamente los pines y la conexión del ADC.

### esp-now_RTC_TX

Transmite la fecha y hora actual desde un módulo RTC a través de ESP-NOW. Asegúrate de conectar el módulo RTC según el diagrama proporcionado.

### esp-now_RX

Este nodo actúa como receptor para recibir datos transmitidos por los otros nodos. Asegúrate de configurar correctamente la recepción de datos y las conexiones necesarias.

## Imágenes de Referencia

La carpeta `Imagenes` contiene diagramas de conexión que te guiarán en la correcta conexión de componentes. Revísalos antes de implementar cada nodo.

---

**Nota:** Asegúrate de tener configurado correctamente el entorno de desarrollo de ESP-IDF antes de probar estos nodos. Puedes consultar la documentación oficial de [ESP-IDF](https://docs.espressif.com/projects/esp-idf/en/latest/) para obtener instrucciones detalladas.

Si tienes alguna pregunta o necesitas más detalles, no dudes en preguntar. ¡Buena suerte!
