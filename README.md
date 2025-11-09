# Simulación de robots EDACup 2025

## Integrantes del Grupo

- Francisco Paredes Alonso
- Santiago Resnik
- Juan Ignacio Fogolin Lagares
- Rocco Diaz Parisi

## Compilacion del codigo

Cuando se compila el codigo, se genera un archivo ejecutable "move_example.exe" dentro del directorio ".\\out\\build\\x64-Debug"
la ruta de este 

## Instalar el simulador


3. Configura el archivo de configuración:

  * Abre el archivo `edacup.json` en un editor de texto.
  * Configura el campo `accessToken` con el token correspondiente a tu grupo.
  * Establece el campo `team1Binary` con la ruta al binario generado en el paso anterior.
  * (Opcional) Configura `team2Binary` con la misma ruta si deseas controlar ambos equipos con el binario de ejemplo.

## Ejecutar el simulador

1. En la línea de comandos, navega a la carpeta que contiene el archivo `README.md`.

2. Inicia el simulador con el siguiente comando:

    node edacup/edacup.mjs

3. Abre un navegador y accede a https://www.openreality.app/ para visualizar la simulación.

4. Para reanudar el juego, usa el comando "p" en la terminal simulador. Puedes detener el juego con el comando "s", y reiniciar los robots con el comando "r".
