# Mini Vehicle - Robotic Pet Project

Un proyecto de mascota robótica inteligente basado en Arduino que simula diferentes comportamientos de un perro con múltiples modos de operación, detección de obstáculos y navegación autónoma.

## 🐕 Características Principales

- **4 Modos de Comportamiento**: Cambia entre diferentes personalidades con solo presionar un botón
- **Detección de Obstáculos**: Utiliza sensores ultrasónicos e infrarrojos para navegar
- **Detección de Movimiento**: Sensor PIR para vigilancia y alerta
- **Control de Motores**: Sistema de tracción de 4 ruedas con motor driver
- **Alertas Visuales y Sonoras**: LED y buzzer para notificaciones

## 🔧 Componentes Hardware

### Microcontrolador

- Arduino (Uno/Nano compatible)

### Sensores

- **Sensor Ultrasónico HC-SR04** (Pines 11-12): Detección de distancia frontal
- **2x Sensores Infrarrojos** (Pines 5-6): Detección de obstáculos laterales
- **Sensor PIR** (Pin 13): Detección de movimiento

### Actuadores

- **Motor Driver** (Pines 7-10): Control de 4 motores DC
- **LED de Alerta** (Pin 2): Indicador visual
- **Buzzer** (Pin 3): Alertas sonoras

### Control

- **Pulsador** (Pin 4): Cambio de modos de operación

## 🎮 Modos de Operación

### 1. Estado Base (Explorador Autónomo)

- Navegación libre evitando obstáculos
- Gira automáticamente al detectar barreras
- Mantiene distancia de seguridad (40cm)

### 2. Perrito Faldero (Seguidor)

- Sigue a una persona manteniendo distancia óptima (30cm)
- Se acerca si está muy lejos
- Retrocede si está muy cerca
- Ajusta dirección según sensores laterales

### 3. Perrito Vigilancia (Modo Guardia)

- Permanece estático monitoreando el entorno
- Activa alarma (LED + buzzer) al detectar movimiento
- Ideal para seguridad de espacios

### 4. Perrito Guardián (Patrullaje)

- Combina exploración autónoma con vigilancia
- Patrulla el área de forma inteligente
- Alerta ante detección de movimiento durante el recorrido
- Evita obstáculos mientras vigila

## 📋 Esquema de Conexiones

```text
Arduino Uno/Nano
├── Pin 2  → LED de Alerta
├── Pin 3  → Buzzer
├── Pin 4  → Pulsador (modo)
├── Pin 5  → Sensor IR Izquierdo
├── Pin 6  → Sensor IR Derecho
├── Pin 7  → Motor Driver IN1
├── Pin 8  → Motor Driver IN2
├── Pin 9  → Motor Driver IN3
├── Pin 10 → Motor Driver IN4
├── Pin 11 → Trigger (HC-SR04)
├── Pin 12 → Echo (HC-SR04)
└── Pin 13 → Sensor PIR
```

## 🚀 Instalación y Uso

1. **Conecta los componentes** según el esquema de conexiones
2. **Carga el código** `sketch_apr23a.ino` en tu Arduino
3. **Alimenta el sistema** (recomendado: batería externa para motores)
4. **Presiona el pulsador** para cambiar entre modos:
   - 1 vez: Modo Explorador
   - 2 veces: Modo Seguidor  
   - 3 veces: Modo Vigilancia
   - 4 veces: Modo Guardián

## 💡 Funcionamiento del Código

### Funciones Principales

- `estadoBase()`: Lógica de navegación autónoma
- `perritoFaldero()`: Comportamiento de seguimiento
- `perritoVigilancia()`: Modo de vigilancia estática
- `perritoGuardian()`: Patrullaje con detección

### Funciones de Movimiento

- `avanzar(tiempo)`: Movimiento hacia adelante
- `retroceder(tiempo)`: Movimiento hacia atrás
- `giroDerecha(tiempo)`: Giro a la derecha
- `giroIzquierda(tiempo)`: Giro a la izquierda
- `parar()`: Detener todos los motores

### Sensores

- `medirDistancia()`: Calcula distancia con sensor ultrasónico
- Lectura digital de sensores IR y PIR

## 🔧 Personalización

Puedes ajustar los siguientes parámetros en el código:

- **Distancias de seguridad**: Modifica los valores de comparación (30cm, 40cm)
- **Tiempos de movimiento**: Ajusta los delays en las funciones de movimiento
- **Sensibilidad**: Cambia los umbrales de los sensores
- **Sonidos de alerta**: Modifica la frecuencia del buzzer

## 🎯 Proyectos Futuros

- [ ] Control remoto vía Bluetooth/WiFi
- [ ] Integración con cámara para reconocimiento visual
- [ ] Modos de comportamiento adicionales
- [ ] Interface móvil para control y monitoreo
- [ ] Sistema de aprendizaje básico

## 📚 Recursos Adicionales

Este proyecto es ideal para:

- Aprender programación Arduino
- Entender sistemas embebidos
- Iniciarse en robótica móvil
- Proyectos educativos STEM

## 🤝 Contribuciones

¡Las contribuciones son bienvenidas! Siéntete libre de:

- Reportar bugs
- Sugerir nuevas características
- Mejorar la documentación
- Añadir nuevos modos de comportamiento

---

**¡Disfruta de tu mascota robótica!** 🐕🤖
