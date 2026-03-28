
## Descripción

El presente documento tiene como objetivo definir los requisitos funcionales y no funcionales del sistema a desarrollar, los cuales servirán como base para su diseño e implementación. Estos requisitos permiten establecer de manera clara las funcionalidades esperadas y los criterios de calidad del sistema.

Asimismo, se incluye un plan de pruebas orientado a verificar el cumplimiento de dichos requerimientos, junto con el diseño de una plantilla para la elaboración de casos de prueba (*test cases*), que facilitará la organización y ejecución del proceso de testing.

---

## Requisitos Funcionales

| Código | Nombre | Descripción |
|--------|--------|------------|
| **RF-01** | Inicia interacción con el usuario por detección de sensor touch | El sistema debe detectar el toque del usuario en la carcasa o cabeza del robot mediante los pines capacitivos del ESP32 y transicionar del estado IDLE (inactivo) al estado SALUDANDO (activo) en menos de 500 ms. *Criterio de aceptación: al tocar la carcasa, el robot inicia el saludo en ≤ 500 ms medidos desde el contacto.* |
| **RF-02** | Saludo de bienvenida | Al detectar el toque, el sistema debe reproducir un mensaje de saludo por el parlante y mostrar una animación en la pantalla OLED simultáneamente, seguido de la pregunta “¿En qué te puedo ayudar?”. *Criterio de aceptación: el audio de saludo y la animación ocurren de forma simultánea y sin delay perceptible.* |
| **RF-03** | Grabación de voz del usuario | Luego del saludo, el sistema debe activar el micrófono y grabar la pregunta del usuario. La grabación finaliza automáticamente cuando se detecta silencio continuo por más de 1.5 segundos. *Criterio de aceptación: el sistema captura correctamente el audio y lo cierra por detección de silencio.* |
| **RF-04** | Transcripción de voz a texto | El sistema debe enviar el audio grabado al servidor local vía WiFi y recibir el texto transcrito en español mediante Whisper en menos de 5 segundos. *Criterio de aceptación: coincidencia ≥ 80%.* |
| **RF-05** | Búsqueda de keywords | Se busca en la base de datos preestablecida una coincidencia con las keywords. *Criterio de aceptación: respuesta correcta ≥ 80% de casos.* |
| **RF-06** | Síntesis y reproducción de respuesta | El sistema debe sintetizar en audio la respuesta mediante Piper TTS y reproducirla por el parlante. *Criterio de aceptación: audio sin interrupciones.* |
| **RF-07** | Actualización de OLED | La pantalla OLED debe reflejar el estado actual del sistema (IDLE, SALUDANDO, PENSANDO, RESPONDIENDO). *Criterio de aceptación: actualización correcta en cada transición.* |
| **RF-08** | Movimiento de actuadores | Movimientos sincronizados con el audio. *Criterio de aceptación: movimiento visible y continuo.* |
| **RF-09** | Verificación al usuario | El sistema debe confirmar si la respuesta fue adecuada o solicitar repetir la pregunta. |
| **RF-10** | Retorno a IDLE | El sistema vuelve a estado IDLE si no hay más preguntas. |

---

## Requisitos No Funcionales

| Código | Nombre | Descripción |
|--------|--------|------------|
| **RNF-01** | Actuadores | Tiempo de respuesta < 200 ms con control de torque. *Criterio: medición con osciloscopio.* |
| **RNF-02** | Audio | THD < 5% y ≥ 70 dB a 1 m. *Criterio: medición de sonido.* |
| **RNF-03** | Procesamiento | Latencia total ≤ 5 s en ESP32. *Criterio: pruebas consecutivas.* |
| **RNF-04** | Alimentación | Fuente externa 5V ±5%, sin batería. *Criterio: operación ≥ 1 hora.* |
| **RNF-05** | Componentes | Componentes comerciales y reemplazables. |
| **RNF-06** | Fabricación | Carcasa en impresión 3D modular. |
| **RNF-07** | Dimensiones | Máx: 24 × 18 × 20 cm. |
| **RNF-08** | Estética | Sin componentes visibles, peso < 2 kg. |
| **RNF-09** | Protección | Resistencia tipo IP4X e IPX2. |
| **RNF-10** | Conectividad | WiFi con reconexión automática < 10 s. |

---


