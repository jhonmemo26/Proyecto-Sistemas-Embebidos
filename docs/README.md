# Requisitos del Sistema

## 2. Requisitos Funcionales

| Código | Nombre | Descripción |
|--------|--------|------------|
| **RF-01** | Inicia interacción con el usuario por detección de sensor touch | El sistema debe detectar el toque del usuario en la carcasa o cabeza del robot mediante los pines capacitivos del ESP32 y transicionar del estado IDLE (inactivo) al estado SALUDANDO (activo) en menos de 500 ms. Criterio de aceptación: al tocar la carcasa, el robot inicia el saludo en ≤ 500 ms medidos desde el contacto. |
| **RF-02** | Saludo de bienvenida (emite saludo y pregunta para el usuario) | Al detectar el toque, el sistema debe reproducir un mensaje de saludo por el parlante y mostrar una animación en la pantalla OLED simultáneamente, seguido de la pregunta “¿En qué te puedo ayudar?”. Criterio de aceptación: el audio de saludo y la animación ocurren de forma simultánea y sin delay perceptible entre sí. |
| **RF-03** | Grabación de voz del Usuario | Luego del saludo, el sistema debe activar el micrófono y grabar la pregunta del usuario. La grabación finaliza automáticamente cuando se detecta silencio continuo por más de 1.5 segundos. Criterio de aceptación: el sistema captura correctamente el audio y lo cierra por detección de silencio. |
| **RF-04** | Transcripción de voz a texto | El sistema debe enviar el audio grabado al servidor local vía WiFi y recibir el texto transcrito en español mediante Whisper en menos de 5 segundos. Criterio de aceptación: el texto transcrito coincide con la pregunta hablada en al menos el 80%. |
| **RF-05** | Búsqueda de Keywords para dar respuesta lógica | Se busca en la base de datos preestablecida una coincidencia con las keywords. Criterio de aceptación: el sistema retorna una respuesta correcta en ≥ 80% de preguntas del conjunto de prueba. |
| **RF-06** | Síntesis y reproducción de respuesta | El sistema debe sintetizar en audio la respuesta de texto mediante Piper TTS y reproducirla por el parlante a través del amplificador (estado RESPONDIENDO). Criterio de aceptación: el audio se reproduce sin interrupciones según el texto generado. |
| **RF-07** | El OLED se actualiza para cada estado | La pantalla OLED debe reflejar el estado actual del sistema (IDLE, SALUDANDO, PENSANDO y RESPONDIENDO) (error en caso de alguno). Criterio de aceptación: la OLED actualiza el mensaje correctamente en cada transición de estado. |
| **RF-08** | Movimiento de actuadores | Para cada estado se tendrán unos movimientos predefinidos y sincronizados con la reproducción de audio. Criterio de aceptación: los actuadores se mueven durante la respuesta y el movimiento es visible y continuo. |
| **RF-09** | Verificación de Pregunta al Usuario | El sistema debe de asegurarse (preguntar) si la respuesta es lo que esperaba y en caso de que no se le pide repetir la pregunta. Criterio de aceptación: Se tendra un texto establecido para la respuesta del usuario y reproducirlo |
| **RF-10** | Volver al estado IDLE | Luego de responder, si la pregunta fue resuelta correctamente vuelve y pregunta si hay otra pregunta; en caso de que no el sistema vuelve al estado IDLE. Criterio de aceptación: Dependiendo de la respuesta del usuario el sistema reproduce texto establecido y vuelve al estado IDLE |

---

## 3. Requisitos No Funcionales

| Código | Nombre | Descripción |
|--------|--------|------------|
| **RNF-01** | Actuadores | Los actuadores del sistema deben presentar tiempos de respuesta inferiores a 200 ms desde la orden del firmware, con movimientos suaves y limitación de torque para garantizar la seguridad del usuario. Criterio de aceptación: Medir con osciloscopio el tiempo entre comando PWM y el movimiento (debe ser ≤ 200 ms en 5 pruebas) |
| **RNF-02** | Audio | El sistema de audio debe garantizar claridad en la reproducción de voz con distorsión total armónica (THD) menor al 5% y nivel sonoro mínimo de 70 dB medido a 1 metro del parlante. No se requiere salida estéreo. Criterio de aceptación: Reproducir fragmento de prueba y medir el número sonoro. |
| **RNF-03** | Procesamiento | El sistema deberá ejecutar algoritmos eficientes de procesamiento de voz y respuesta, con latencia total de respuesta ≤ 5 segundos y uso optimizado de recursos del microcontrolador (ESP32). Criterio de aceptación: Cronometrar diferentes ciclos completos como pruebas consecutivas. |
| **RNF-04** | Alimentación | El sistema debe operar mediante una fuente externa regulada de 5V ±5%, compatible con cargadores comerciales tipo USB, sin uso de batería interna. La fuente debe ser diferente a la del laboratorio. Criterio de aceptación: El sistema completo debe de operar correctamente conectado a una fuente externa al menos una hora sin falla. |
| **RNF-05** | Componentes | Todos los componentes electrónicos y mecánicos del sistema deben ser comerciales, identificables por referencia de fabricante y disponibles para reemplazo individual. Criterio de aceptación: Lista de materiales con su referencia comercial y disponibilidad nacional principalmente. |
| **RNF-06** | Fabricación | La carcasa del robot debe ser fabricada mediante impresión 3D con acabado profesional y permitir el ensamblaje modular para facilitar el acceso a componentes internos. Criterio de aceptación: Inspección del acabado superficial y demostración del montaje y desmontaje sin complicaciones mayores. |
| **RNF-07** | Dimensiones | El robot no debe exceder las dimensiones de 24 cm (alto) × 18 cm (ancho) × 20 cm (profundidad). Debe ser estable en superficie plana horizontal sin soporte adicional. |
| **RNF-08** | Estética | Ningún componente electrónico debe ser visible desde el exterior del robot. El diseño debe ser amigable e interactivo. El peso total no debe superar 2 kg. Criterio de aceptación: Inspección visual 360 y medición por báscula. |
| **RNF-09** | Protección | El sistema debe resistir polvo ambiental en condiciones normales de interior (equivalente a IP4X) y salpicaduras leves de agua (equivalente a IPX2), dado que operará en un entorno de biblioteca universitaria. Criterio de aceptación: Pruebas de salpicaduras leves sin afectar su funcionamiento. |
| **RNF-10** | Conectividad | El sistema debe soportar conectividad WiFi de forma obligatoria para comunicación con el servidor local. La conexión debe restablecerse automáticamente ante desconexiones sin reinicio manual del sistema. Criterio de aceptación: Desconectar y reconectar el WiFi en menos de 10 s y continuar operando. |


