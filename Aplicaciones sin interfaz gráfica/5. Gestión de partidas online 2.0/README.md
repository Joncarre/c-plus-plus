

<!--Creado por Jonathan Carrero -->

**Gestor de partidas online 2.0**
==============
----------

**Nueva funcionalidad**

En esta segunda versión nos encontramos con principalmente tres nuevas funcionalidades:

- Las partidas con más de 30 días sin actividad se cerrarán automáticamente al apagar la aplicación, dando por ganador al jugador que no tiene el turno (obvio).

- Las partidas terminadas se van a ir guardando en un archivo denominado historico.txt.

- Pueden consultarse estadícticas por adversarios, que mostará para cada uno contra los que se ha jugador, el número de partidas ganadas, perdidas y empatadas.

**Cambios en diseño**

Se han modificado e implementado nuevos cambios en esta segunda versión. Lo más importantes se describen a continuación:

- La lista de acceso a las partidas en curso no forma parte del usuario. Por lo tanto, no se requiere el módulo ListaAccesoPartidas.

- Se ha añadido al gestor un campo del tipo tListaAccesoPartidas para mantener la lista de accesos a las partidas en curso del usuario de la sesión.

- La lista de usuarios pasa a ser un array de tamaño dinámico, de forma que cuando se llene el array será reemplazado por otro de más capacidad.

- La lista de partidas pasa a ser un array de datos dinámico. Al insertar un usuario, si la lista está llena, se redimensionará para poder insertarlo.

- La lista de acceso a las partidas en curso en lugar de contener el índice o posición de cada partida en la lista de partidas del gestor, guardará la dirección de memoria (puntero) de las partidas.


