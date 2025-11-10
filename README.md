# Simulación de robots EDACup 2025

## Integrantes del Grupo

- Rocco Diaz Parisi
- Juan Ignacio Fogolin Lagares
- Francisco Paredes Alonso
- Santiago Resnik



## Compilacion del codigo

Se debe utilizar "node ./edacup.mjs" para ejecutarlo. 
Cuando se compila el codigo, se genera un archivo ejecutable "move_example.exe" dentro del directorio ".\\out\\build\\x64-Debug".

## Comentarios sobre la funcionalidad del codigo

### Estructura General
El código implementa un sistema de control para dos robots en un juego de fútbol robótico, donde cada robot tiene un rol específico y comportamientos asociados. La implementación se basa en un sistema de roles dinámicos que permite a los robots adaptarse a si el defensor ya no se encuentra en al cancha (penalizado), el atacante cambie de rol y tome su lugar.

### Comportamiento del Defensor
- **Posicionamiento**: Mantiene una trayectoria circular alrededor del área de su equipo.
- **Radio de Acción**: Utiliza `DEFENDER_CIRCLE_RADIUS` para mantener una distancia óptima.
- **Seguimiento de Pelota**: Siempre se orienta hacia la pelota (`getAngle()`).
- **Acción de Despeje**: Activa el kicker cuando la pelota está dentro de su rango.


### Comportamiento del Atacante
1. **Posicionamiento Ofensivo**:
   - Si está detrás de la pelota: Se coloca a una distancia `ATTACKER_SHOOT_DISTANCE` para tomar impulso
   - Si tiene la pelota: Activa el dribbler y se dirige hacia la portería rival
   - Si está delante de la pelota: Se mueve hacia la posición de la pelota

2. **Control de Pelota**:
   - Usa el dribbler cuando tiene posesión
   - Calcula ángulos óptimos de aproximación hacia el arco rival

### Sistema de Recuperación
- Si el defensor es penalizado (fuera de juego), el atacante asume el rol defensivo
- El sistema mantiene la posición del robot penalizado en modo AFK hasta su retorno
- Se implementa un sistema de verificación de altura (`MAX_HEIGHT`) para detectar robots fuera de juego

### Prevención de Faltas
- Verificación de límites del campo (`offLimitsCheck`)
- Control de distancias y posiciones para evitar infracciones
- Manejo de situaciones especiales cuando la pelota está fuera de los límites
