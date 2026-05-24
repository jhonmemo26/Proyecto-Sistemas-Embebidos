# Requerimientos del Proyecto — MiniCraibot

# Descripción del Proyecto

MiniCraibot es un asistente robótico interactivo desarrollado como proyecto de la asignatura Sistemas Embebidos de la Universidad EIA.

El sistema está diseñado para interactuar con usuarios mediante sensores táctiles, expresiones visuales en pantalla OLED, movimiento motorizado de cabeza y futuros servicios de inteligencia artificial basados en voz.

La arquitectura del firmware está basada en una Máquina de Estados Finitos (FSM), permitiendo un diseño modular, escalable y mantenible.

El objetivo del proyecto es simular un flujo de desarrollo cercano a un entorno profesional de sistemas embebidos, incluyendo:
- arquitectura de firmware,
- manejo de requerimientos,
- trazabilidad,
- testing,
- manejo de errores,
- documentación técnica,
- control de versiones con GitHub.

---

# Funcionalidades Implementadas Actualmente

Actualmente el sistema implementa:

- Arquitectura FSM (Finite State Machine)
- Detección de interacción mediante sensor touch
- Animaciones emocionales en pantalla OLED SSD1306
- Movimiento de cabeza mediante motor paso a paso
- Gestión de timeout en estado ESCUCHANDO
- Estado PROCESANDO simulado
- Organización modular del firmware
- Comunicación serial UART para debugging
- Manejo de transiciones de estado
- Integración inicial de sensores y actuadores
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
| RF-007 | El sistema debe detectar una simulación de voz mediante un segundo sensor touch. |
| RF-008 | El sistema debe pasar al estado PROCESANDO después de detectar voz. |
| RF-009 | El sistema debe retornar automáticamente a IDLE mediante timeout. |
| RF-010 | El sistema debe generar logs UART para debugging y validación. |

---

# Requerimientos No Funcionales

| ID | Requerimiento |
|----|----------------|
| RNF-001 | El firmware debe ser modular y mantenible. |
| RNF-002 | El proyecto debe organizarse usando archivos separados .c y .h. |
| RNF-003 | El sistema debe usar GitHub para control de versiones y trabajo colaborativo. |
| RNF-004 | El sistema debe funcionar usando una fuente de alimentación externa. |

---

# Arquitectura del Sistema

El firmware se encuentra dividido en módulos independientes:

- Módulo FSM
- Módulo OLED
- Módulo de control del motor
- Módulo de sensores touch
- Futuro módulo de micrófono
- Futuro módulo de audio/TTS

Esta arquitectura permite:
- escalabilidad,
- mantenibilidad,
- facilidad de integración,
- depuración modular.

---

# Protocolos de Comunicación

| Protocolo | Uso |
|-----------|-----|
| I2C | Comunicación con pantalla OLED SSD1306 |
| UART | Logging serial y debugging |
| I2S | Futuro manejo de micrófono y audio |

---

# Estados Actuales de la FSM

- IDLE
- DESPERTANDO
- ESCUCHANDO
- PROCESANDO
- RESPONDIENDO (en desarrollo)

---

# Testing y Validación

Los casos de prueba y validación del sistema se encuentran documentados en:

- `TC_Robot_EIA.docx`

---

# Control de Versiones

El proyecto es mantenido mediante GitHub utilizando commits colaborativos realizados por todos los integrantes del equipo.

El repositorio contiene:
- código fuente,
- documentación,
- evidencia de pruebas,
- diagramas,
- arquitectura de firmware,
- trazabilidad de requerimientos.

---