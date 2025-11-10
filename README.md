# Simulación de robots EDACup 2025

## Integrantes del Grupo

- Francisco Paredes Alonso
- Santiago Resnik
- Juan Ignacio Fogolin Lagares
- Rocco Diaz Parisi

## Compilacion del codigo

Cuando se compila el codigo, se genera un archivo ejecutable "move_example.exe" dentro del directorio ".\\out\\build\\x64-Debug"
la ruta de este 

## Configuracion

3. Configura el archivo de configuración:

  * Abre el archivo `edacup.json` en un editor de texto.
  * Configura el campo `accessToken` con el token correspondiente a tu grupo.
  * Establece el campo `team1Binary` con la ruta al binario generado en el paso anterior.
  * (Opcional) Configura `team2Binary` con la misma ruta si deseas controlar ambos equipos con el binario de ejemplo.

## Comentarios sobre la funcionalidad del codigo

Una implementación necesaria fue la asignación de un rol a cada robot, los cuales pueden ser defensor o atacante. Cada uno cumple el rol designado, en el caso del defensor se mantienen cerca del area recorriendo una trayectoria circular para bloquear posibles disparos del contrincante, y el atacante es quien busca la pelota constantemente intentando marcar goles. Si el defensor es penalizado y queda fuera del juego, el atacante toma su lugar hasta que regrese. Los robots tratan de evitar las faltas, por ejemplo, dejando de seguir la pelota si sale de los limites de la cancha o si entra a algun area.