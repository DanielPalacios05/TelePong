# Proyecto N°1 - Telemática | TelePong.

### Tabla de contenidos.
- [Introducción.](https://github.com/EsteTruji/TelePong/edit/dev/README.md#introduccio%CC%81n)
- [Desarrollo.](https://github.com/EsteTruji/TelePong/edit/dev/README.md#desarrollo)
  - [Descripción de aspectos generales.](https://github.com/EsteTruji/TelePong/edit/dev/README.md#descripci%C3%B3n-de-aspectos-generales-qu%C3%A9-se-hizo)
  - [Descripción de aspectos personalizados/ajustados.](https://github.com/EsteTruji/TelePong/edit/dev/README.md#descripci%C3%B3n-de-aspectos-personalizadosajustados-qu%C3%A9-funcionalides-tiene)
  - [Descripción de tecnologías.](https://github.com/EsteTruji/TelePong/edit/dev/README.md#descripci%C3%B3n-de-tecnolog%C3%ADas-c%C3%B3mo-se-hizo)
  - [Descripción del protocolo.](https://github.com/EsteTruji/TelePong/edit/dev/README.md#descripci%C3%B3n-del-protocolo)
- [Conclusiones.](https://github.com/EsteTruji/TelePong/edit/dev/README.md#conclusiones)
- [Referencias.](https://github.com/EsteTruji/TelePong/edit/dev/README.md#referencias)

## Introducción.

El documento a continuación tiene el propósito de exponer y detallar el trabajo realizado como proyecto N°1 de Telemática. Es importante mencionar que este trabajo fue desarrollado por Daniel Ricardo Palacios Diego, Damian Antonio Duque López y Esteban Trujillo Carmona.
Ahora bien, primero que todo, en este documento se explicará cuál fue el trabajo en cuestión que se desarrolló, cómo se desarrolló, y qué funcionalidades tiene el producto final.
Posteriormente, se pasará a explicar de forma detallada cómo fue el diseño e implementación del protocolo necesario para la comunicación entre el servidor y el cliente, cuál es el vocabulario de mensajes usados, y su flujo de trabajo.
Finalmente, se brindarán algunas conclusiones acerca del trabajo realizado, de la experiencia de desarrollo, de los retos afrontados, y en general, la experiencia con el trabajo, seguido de las referencias correspondientes. 

## Desarrollo.

### Descripción de aspectos generales. ¿Qué se hizo?
El trabajo realizado consiste en el desarrollo de un juego de _Pong_, el cual nombramos para efectos de la práctica como _TelePong_. El juego de Pong tiene como fin conseguir la mayor cantidad de puntos en un determinado tiempo, o conseguir primero determinada cantidad de puntos. Para este propósito, es necesario procurar que el oponente realice la menor cantidad de puntos evitando que la pelota entre a la _"portería"_ propia usando la raqueta asignada, de tal forma que rebote en ella y se dirija a la portería del oponente para realizar punto. 

### Descripción de aspectos personalizados/ajustados. ¿Qué funcionalides tiene?
Partiendo de la base general de lo que significa y establece el juego clásico de _Pong_, se realizaron determinados ajustes y cambios personalizados, de tal manera que el juego pueda ser distinguido y cumpla además con los requerimientos adicionales de este proyecto. Tales aspectos son los siguientes:

- Con el fin de aumentar la dificultad del juego a medida que pasa el tiempo desde que se inició la partida, se va aumentando gradualmente la velocidad de la pelota, de tal forma que será más difícil interceptarla y evitar que el oponente haga puntos.

### Descripción de tecnologías. ¿Cómo se hizo?
En cumplimiento con lo requerido en la práctica, el juego se desarrolló siguiendo la arquitectura **Cliente-Servidor**, donde se estableció un **servidor** programado en el lenguaje C, y un **cliente** programado en el lenguaje Python. Además, se partió del eje fundamental de los sockets, los cuales posibilitan la comunicación y el envío de mensajes entre el cliente y el servidor, y viceversa. Para ello, se hizo uso de la **API de sockets Berkeley en C**. y de la **librería socket en Python**.

Un aspecto muy importante en este sentido es que no se realizó la importación de tales librerías directamente en el servidor y el cliente, respectivamente, sino que, exclusivamente para el posiblitamiento de la comunicación entre ambos y con el fin de establecer un bajo acoplamiento en este sentido, se estableció un protocolo de comunicación basado en texto en C y en Python (ver [Descripción del protocolo](https://github.com/EsteTruji/TelePong/edit/dev/README.md#descripci%C3%B3n-del-protocolo)). Así, el servidor incluye el protocolo en C, y el cliente importa el protocolo en Python.

Por otro lado, para poder implementar lo relacionado con la concurrencia, es decir, la conexión simultánea de múltiples clientes al juego, de tal manera que todos puedan jugar con su respectivo oponente, se hizo uso de los hilos en el servidor (```#include <pthread.h>```). De tal forma que el servidor esté en la capacidad de atender y responder a las _requests_ que le realizan los diferentes clientes que están jugando.

Ahora, con relación al cliente, se hizo uso de la librería Pygame de Python, para establecer la estructura, lógica, y vistas del juego, basándose fuertemente en la POO (Programación Orientada a Objetos) con el fin de realizar un mejor manejo de los diferentes elementos del juego. De manera adicional, se usaron otras librerías como **os (```import os```)**  **time (```import time```)**

### Descripción del protocolo.

## Conclusiones.
## Referencias. 

https://www.geeksforgeeks.org/tcp-server-client-implementation-in-c/
https://www.geeksforgeeks.org/how-to-create-a-text-input-box-with-pygame/
