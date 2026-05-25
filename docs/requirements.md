# Requerimientos del Proyecto — MiniCraibot

# Descripción del Proyecto

MiniCraibot es un asistente robótico interactivo desarrollado como proyecto de la asignatura Sistemas Embebidos de la Universidad EIA.

El sistema está diseñado para interactuar con usuarios mediante sensores táctiles, expresiones visuales en pantalla OLED, movimiento motorizado de cabeza y servicios de inteligencia artificial basados en reconocimiento de voz y generación automática de respuestas.

La arquitectura del firmware está basada en una Máquina de Estados Finitos (FSM), permitiendo un diseño modular, escalable y mantenible.

El objetivo del proyecto es simular un flujo de desarrollo cercano a un entorno profesional de sistemas embebidos, incluyendo:

- Arquitectura de firmware
- Manejo de requerimientos
- Trazabilidad
- Testing
- Manejo de errores
- Documentación técnica
- Logging estructurado
- Control de versiones con GitHub

---

# Funcionalidades Implementadas Actualmente

Actualmente el sistema implementa:

- Arquitectura FSM (Finite State Machine)
- Detección de interacción mediante sensor touch
- Animaciones emocionales en pantalla OLED SSD1306
- Movimiento de cabeza mediante motor paso a paso
- Grabación de audio mediante micrófono I2S
- Comunicación WiFi
- Comunicación HTTP con servidor FastAPI
- Integración con servicios de inteligencia artificial
- Generación automática de respuestas
- Reproducción de respuestas mediante TTS
- Organización modular del firmware
- Logging serial UART para debugging
- Manejo de transiciones de estado
- Integración de sensores y actuadores
- Flujo colaborativo usando GitHub

---

# Requerimientos Funcionales

| ID | Requerimiento |
|----|----------------|
| RF-001 | El robot debe detectar interacción del usuario mediante sensor touch. |
| RF-002 | El robot debe mostrar animaciones emocionales en pantalla OLED SSD1306. |
| RF-003 | El robot debe mover la cabeza usando un motor paso a paso. |
| RF-004 | El sistema debe implementar una arquitectura FSM. |
| RF-005 | El robot debe pasar de estado IDLE a DESPERTANDO mediante interacción touch. |
| RF-006 | El sistema debe ingresar al estado ESCUCHANDO después del despertar. |
| RF-007 | El sistema debe grabar audio mediante micrófono I2S. |
| RF-008 | El sistema debe enviar audio a un servidor FastAPI usando HTTP. |
| RF-009 | El sistema debe procesar audio utilizando servicios de inteligencia artificial. |
| RF-010 | El sistema debe generar respuestas automáticas mediante IA. |
| RF-011 | El sistema debe reproducir respuestas mediante TTS. |
| RF-012 | El sistema debe retornar automáticamente al estado IDLE después de finalizar la interacción. |
| RF-013 | El sistema debe conectarse a una red WiFi. |
| RF-014 | El sistema debe generar logs UART para debugging y validación. |
| RF-015 | El sistema debe implementar comunicación modular entre periféricos y módulos de firmware. |
| RF-016 | El sistema debe mostrar diferentes expresiones visuales según el estado actual de la FSM. |

---

# Requerimientos No Funcionales

| ID | Requerimiento |
|----|----------------|
| RNF-001 | El firmware debe ser modular y mantenible. |
| RNF-002 | El proyecto debe organizarse usando archivos separados .c y .h. |
| RNF-003 | El sistema debe usar GitHub para control de versiones y trabajo colaborativo. |
| RNF-004 | El sistema debe funcionar mediante alimentación externa estable. |
| RNF-005 | El sistema debe mantener una arquitectura escalable para futuras integraciones. |
| RNF-006 | El sistema debe permitir depuración mediante logs UART estructurados. |
| RNF-007 | El sistema debe utilizar protocolos estándar de comunicación embebida. |
| RNF-008 | El firmware debe permitir integración futura de nuevos sensores y actuadores. |
| RNF-009 | El sistema debe mantener tiempos de respuesta adecuados para interacción en tiempo real. |

---

# Arquitectura del Sistema

El firmware se encuentra dividido en módulos independientes:

- Módulo FSM
- Módulo OLED
- Módulo SSD1306
- Módulo de control del motor
- Módulo de sensores touch
- Módulo WiFi
- Módulo de comunicación con servidor
- Módulo de audio
- Módulo TTS
- Módulo de bitmaps
- Módulo de logging

Esta arquitectura permite:

- Escalabilidad
- Mantenibilidad
- Facilidad de integración
- Depuración modular
- Separación de responsabilidades

---

# Protocolos de Comunicación

| Protocolo | Uso |
|-----------|-----|
| I2C | Comunicación con pantalla OLED SSD1306 |
| UART | Logging serial y debugging |
| I2S | Comunicación con micrófono y reproducción de audio |
| HTTP | Comunicación ESP32 ↔ servidor FastAPI |
| WiFi | Comunicación inalámbrica del sistema |

---

# Estados de la FSM

- IDLE
- DESPERTANDO
- ESCUCHANDO
- PROCESANDO
- HABLANDO

---

# Testing y Validación

Los casos de prueba y validación del sistema se encuentran documentados en:

- `TC_Robot_EIA.docx`

Las pruebas realizadas incluyen:

- Validación de transiciones FSM
- Validación de comunicación WiFi
- Validación de comunicación HTTP
- Validación de reproducción TTS
- Validación de captura de audio
- Validación de animaciones OLED
- Validación de movimiento del motor
- Validación de interacción touch

---

# Control de Versiones

El proyecto es mantenido mediante GitHub utilizando commits colaborativos realizados por todos los integrantes del equipo.

El repositorio contiene:

- Código fuente
- Documentación técnica
- Evidencia de pruebas
- Diagramas
- Arquitectura de firmware
- Matriz SRTM
- Casos de prueba
- Requerimientos funcionales y no funcionales

---
