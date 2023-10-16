# Proyecto N°1 - Telemática | TelePong.

### Tabla de contenidos.
- [Introducción.](#introduccion)
- [Desarrollo.](#desarrollo)
  - [Descripción de aspectos generales.](#descripci%C3%B3n-de-aspectos-generales-qu%C3%A9-se-hizo)
  - [Descripción de aspectos personalizados/ajustados.](#descripci%C3%B3n-de-aspectos-personalizadosajustados-qu%C3%A9-funcionalides-tiene)
  - [Descripción de tecnologías.](#descripci%C3%B3n-de-tecnolog%C3%ADas-c%C3%B3mo-se-hizo)
  - [Descripción del protocolo.](#descripci%C3%B3n-del-protocolo)
- [Conclusiones.](#conclusiones)
- [Referencias.](#referencias)

<a name="introduccion"></a>
## Introducción.

El documento a continuación tiene el propósito de exponer y detallar el trabajo realizado como proyecto N°1 de Telemática. Es importante mencionar que este trabajo fue desarrollado por Daniel Ricardo Palacios Diego, Damian Antonio Duque López y Esteban Trujillo Carmona.
Ahora bien, primero que todo, en este documento se explicará cuál fue el trabajo en cuestión que se desarrolló, cómo se desarrolló, y qué funcionalidades tiene el producto final.
Posteriormente, se pasará a explicar de forma detallada cómo fue el diseño e implementación del protocolo necesario para la comunicación entre el servidor y el cliente, cuál es el vocabulario de mensajes usados, y su flujo de trabajo.
Finalmente, se brindarán algunas conclusiones acerca del trabajo realizado, de la experiencia de desarrollo, de los retos afrontados, y en general, la experiencia con el trabajo, seguido de las referencias correspondientes. 

<a name="desarrollo"></a>
## Desarrollo.

### Descripción de aspectos generales. ¿Qué se hizo?
El trabajo realizado consiste en el desarrollo de un juego de _Pong_, el cual nombramos para efectos de la práctica como _TelePong_. El juego de Pong tiene como fin conseguir la mayor cantidad de puntos en un determinado tiempo, o conseguir primero determinada cantidad de puntos. Para este propósito, es necesario procurar que el oponente realice la menor cantidad de puntos evitando que la pelota entre a la _"portería"_ propia usando la raqueta asignada, de tal forma que rebote en ella y se dirija a la portería del oponente para realizar punto. 

### Descripción de aspectos personalizados/ajustados. ¿Qué funcionalides tiene?
Partiendo de la base general de lo que significa y establece el juego clásico de _Pong_, se realizaron determinados ajustes y cambios personalizados, de tal manera que el juego pueda ser distinguido y cumpla además con los requerimientos adicionales de este proyecto. Tales aspectos son los siguientes:

- El juego requiere de forma inicial, antes de empezar a jugar, tres elementos fundamentales, de los cuales los dos últimos serán brindados oportunamente a los usuarios. Dichos elementos son el **_nickname_ del usuario** que se desea conectar (con el cual será identificado en toda la partida), la **dirección IP del servidor** (para poder conectarse a este), y el **puerto en el cual estará escuchando el servidor**. Estos dos últimos elementos componen el _socket_ del servidor, y serán usados precisamente para saber dónde debe enviar los mensajes correspondientes.
- Con el fin de aumentar la dificultad del juego a medida que pasa el tiempo desde que se inició la partida, se va aumentando gradualmente la velocidad de la pelota, de tal forma que será más difícil interceptarla y evitar que el oponente haga puntos.
- Con el fin posibilitar la conexión de múltiples clientes de forma simultánea en el juego, y para permitir que el servidor sea capaz de atender de manera oportuna las solicitudes y mensajes de los clientes conectados, se implementaron los hilos, basándose en el concepto de _multi-threading_. Así, el juego es capaz de soportar a varios jugadores al mismo tiempo, con el propósito de brindar un servicio que pueda ser accedido por múltiples usuarios simultáneamente.


### Descripción de tecnologías. ¿Cómo se hizo?
En cumplimiento con lo requerido en la práctica, el juego se desarrolló siguiendo la arquitectura **Cliente-Servidor** y **TCP/IP**, donde se estableció un **servidor** programado en el lenguaje C, y un **cliente** programado en el lenguaje Python. Además, se partió del eje fundamental de los sockets, los cuales posibilitan la comunicación y el envío de mensajes entre el cliente y el servidor, y viceversa. Para ello, se hizo uso de la **API de sockets Berkeley en C**. y de la **librería socket en Python**.

Un aspecto muy importante en este sentido es que no se realizó la importación de tales librerías directamente en el servidor y el cliente, respectivamente, sino que, exclusivamente para el posiblitamiento de la comunicación entre ambos y con el fin de establecer un bajo acoplamiento en este sentido, se estableció un protocolo de comunicación basado en texto en C y en Python (ver [Descripción del protocolo](https://github.com/EsteTruji/TelePong/edit/dev/README.md#descripci%C3%B3n-del-protocolo)). Así, el servidor incluye el protocolo en C, y el cliente importa el protocolo en Python.

También cabe destacar que, después de deliberar y discutir en el grupo de trabajo, se optó por trabajar con los **sockets de tipo UDP**. Tales motivos se enuncian a continuación:
1. Dado el contexto del proyecto, el cual corresponde a un "videojuego" y no a una aplicación donde es crucial que no haya pérdida de información, se consideró la opción de trabajar sobre sockets UDP. 
2. Los sockets UDP posibilitan una comunicación más rápida entre el cliente y el servidor y viceversa, lo que se traduce en una latencia más baja en comparación sockets TCP.
3. La aplicación funcionará en tiempo real, por lo que las latencias, o a lo sumo, las latencias considerables, no pueden ser aceptadas, ya que acabaría por completo con el sentido y la usabilidad de esta.
4. Como los sockets UDP son sin conexión, hay una menor sobrecarga de datos ya que no es necesario tener que establecer esa conexión antes de enviar cualquier mensaje o _request_. Esto beneficia también a la velocidad del juego, en comparación (nuevamente) con _sockets_ TCP.

Por otro lado, para poder implementar lo relacionado con la concurrencia, es decir, la conexión simultánea de múltiples clientes al juego, de tal manera que todos puedan jugar con su respectivo oponente, se hizo uso de los hilos en el servidor (```#include <pthread.h>```). De tal forma que el servidor esté en la capacidad de atender y responder a las _requests_ que le realizan los diferentes clientes que están jugando.

Ahora, con relación al cliente, se hizo uso de la librería Pygame de Python, para establecer la estructura, lógica, y vistas del juego, basándose fuertemente en la POO (Programación Orientada a Objetos) con el fin de realizar un mejor manejo de los diferentes elementos del juego. De manera adicional, se usaron otras librerías como **os (```import os```)** y **time (```import time```)** con el fin de brindar otras herramientas necesarias para el funcionamiento del cliente.

### Descripción del protocolo.
Con relación al protocolo, cabe mencionar que se desarrolló con el fin posbilitar el bajo acoplamiento entre el cliente, el servidor y la librería de _sockets_. De esta forma, así como se tiene implementado, basta con que el cliente y el servidor importen o incluyan al protocolo en su lenguaje correspondiente. Por lo tanto, el protocolo se definió basado en texto, de tal manera que la comunicación entre el cliente-protocolo y servidor-protocolo es a través de una cadena de texto que incluye la información necesaria para poder realizar determinada acción del lado del protocolo, usando los _sockets_. El protocolo recibe entonces la cadena que le envía el servidor o el cliente y realiza un parseo de la misma, con el fin de extraer la información necesaria. De tal 

## Conclusiones.
## Referencias. 

https://www.geeksforgeeks.org/tcp-server-client-implementation-in-c/
https://www.geeksforgeeks.org/how-to-create-a-text-input-box-with-pygame/
