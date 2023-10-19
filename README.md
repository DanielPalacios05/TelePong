# Proyecto N°1 - Telemática | TelePong.

### Tabla de contenidos.
- [Introducción.](#introduccion)
- [Desarrollo.](#desarrollo)
  - [Requerimientos previos.](#requerimientos-previos)
  - [Acciones iniciales.](#acciones-iniciales-qu%C3%A9-debo-hacer-para-jugar)
  - [Descripción de aspectos generales.](#descripci%C3%B3n-de-aspectos-generales-qu%C3%A9-se-hizo)
  - [Descripción de aspectos personalizados/ajustados.](#descripci%C3%B3n-de-aspectos-personalizadosajustados-qu%C3%A9-funcionalides-tiene)
  - [Flujo del juego.](#flujo-del-juego-c%C3%B3mo-funciona)
  - [Descripción de tecnologías.](#descripci%C3%B3n-de-tecnolog%C3%ADas-c%C3%B3mo-se-hizo)
  - [Descripción del protocolo.](#descripci%C3%B3n-del-protocolo)
    - [Vocabulario de mensajes usado.](#vocabulario-de-mensajes-usado)
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

### Requerimientos previos.
Para poder ejecutar y jugar sin problema a TelePong, es necesario que el dispositivo (computador) donde se va a ejecutar cumpla con los siguientes requerimientos:
- **Sistema Operativo (o WSL en su defecto):** Linux.
- **Lenguaje:** C, y su compilador respectivo instalados - Python.
- **Librerías:** Requiere de la instalación previa de **Pygame** (```pip install pygame```).
- **Acceso a Internet:** Requiere de un computador con acceso a Internet.
- **Editor de código:** Preferiblemente, tener instalado Visual Studio Code.

### Acciones iniciales. ¿Qué debo hacer para jugar?
Una vez se cumplan todos los requerimientos previamente indicados, a cada usuario que desee jugar a TelePong, se le compartirá una carpeta comprimida con los archivos correspondientes al cliente. Estos son TelePongClient.py, myPongProtocol.py, y getInfoWindow.py. El archivo myPongProtocol.py corresponde al responsable de la comunicación a través de sockets entre el cliente y el servidor desplegado. El archivo getInfoWindow.py corresponde a un módulo de la aplicación que se encarga de desplegar una ventana donde se da la bienvenida al juego, y se reciben de parte del usuario la información mínima necesaria para jugar, es decir su _nickname_, la _dirección IP del servidor_, y el _puerto del servidor_. Finalmente, el archivo TelePongClient.py corresponde al archivo de cliente que debe ser ejecutado por el usuario, ya que acá se encuentra el juego como tal. Para ejecutar ese archivo, primero debe descomprimir la carpeta .zip recibida, después abrir dicha carpeta en el editor de código (Visual Studio Code), y ejecutar por la consola el siguiente comando: ```python3 TelePongClient.py```. De esta forma, se abrirá inmediatamente después la ventana donde se dará la bienvenido y se pedirá la información previamente mencionada.


### Descripción de aspectos generales. ¿Qué se hizo?
El trabajo realizado consiste en el desarrollo de un juego de _Pong_, el cual nombramos para efectos de la práctica como _TelePong_. El juego de Pong tiene como fin conseguir la mayor cantidad de puntos en un determinado tiempo, o conseguir primero determinada cantidad de puntos. Para este propósito, es necesario procurar que el oponente realice la menor cantidad de puntos evitando que la pelota entre a la _"portería"_ propia usando la raqueta asignada, de tal forma que rebote en ella y se dirija a la portería del oponente para realizar punto. Con relación al movimiento de las raquetas, se tiene que este es solo de manera vertical (arriba o abajo), y con el fin de generar tal movimiento se tiene establecido el uso de las teclas arriba y abajo del teclado (flecha arriba y flecha abajo).

### Descripción de aspectos personalizados/ajustados. ¿Qué funcionalides tiene?
Partiendo de la base general de lo que significa y establece el juego clásico de _Pong_, se realizaron determinados ajustes y cambios personalizados, de tal manera que el juego pueda ser distinguido y cumpla además con los requerimientos adicionales de este proyecto. Tales aspectos son los siguientes:

- El juego requiere de forma inicial, antes de empezar a jugar, tres elementos fundamentales (tal y como se indicó en la sección de [Acciones iniciales](#acciones-iniciales-qu%C3%A9-debo-hacer-para-jugar)), de los cuales los dos últimos serán brindados oportunamente a los usuarios. Esta información debe ser escrita en la ventana de bienvenida de TelePong, donde habrán tres espacios destinados para ellos respectivamente. Dichos elementos son el **_nickname_ del usuario** que se desea conectar (con el cual será identificado en toda la partida), la **dirección IP del servidor** (para poder conectarse a este), y el **puerto en el cual estará escuchando el servidor**. Estos dos últimos elementos componen el _socket_ del servidor, y serán usados precisamente para saber dónde debe enviar los mensajes correspondientes.
- Con el fin de aumentar la dificultad del juego a medida que pasa el tiempo desde que se inició la partida, se va aumentando gradualmente la velocidad de la pelota, de tal forma que será más difícil interceptarla y evitar que el oponente haga puntos.
- Con el fin posibilitar la conexión de múltiples clientes de forma simultánea en el juego, y para permitir que el servidor sea capaz de atender de manera oportuna las solicitudes y mensajes de los clientes conectados, se implementaron los hilos, basándose en el concepto de _multi-threading_. Así, el juego es capaz de soportar a varios jugadores al mismo tiempo, con el propósito de brindar un servicio que pueda ser accedido por múltiples usuarios simultáneamente.

### Flujo del juego. ¿Cómo funciona?
De tal forma, el flujo del juego es el siguiente:
- El servidor, encendido, escucha constantemente por mensajes del cliente.
- El cliente se inicia, y envía un mensaje de inicialización del juego junto al Nick del jugador y demas informacion relevante.
- El servidor recibe ese mensaje, y lo compara para verificar que sí sea un mensaje de inicialización, o es un mensaje durante la partida.
  - Una vez se verifica que es un mensaje de inicialización el servidor toma el _nickname_ y la dirección IP junto con el puerto del jugador, crea un jugador con esa información, lo agrega al arreglo de jugadores y pasa a verificar en qué partida o sala puede ubicar a ese jugador.
  - El servidor verifica, recorriendo cada sala, cuál tiene espacio para este jugador. En este caso se pueden presentar tres escenarios en cada sala:
    - Si la sala está vacía, entonces agrega ese jugador a esa sala siendo el jugador 1, y le asigna al jugador la información del id de esa sala y su número de jugador (1).
    - Si la sala tiene solo un jugador, entonces agrega ese jugador a esa sala siendo el jugador 2, y le asigna al jugador la información del id de esa sala y su número de jugador (2).
    - Si la sala está llena, es decir, tiene los dos jugadores, entonces pasa a verificar la siguiente sala, y así sucesivamente hasta que encuentre una sala donde pueda ingresar.
  - Después de haberlo asignado a una sala, le envía al cliente la información de su número de jugador (1 o 2) y el id de la sala.
  - El cliente recibe esa información y la guarda, y espera a recibir a su oponente.
  - Pasado esto, el servidor verifica si el jugador que acaba de añadir al juego es el número 2.
    - En caso de que sea, el servidor le enviará a ambos jugadores de esa sala el _nickname_ de su respectivo oponente.
    - El cliente recibirá entonces el _nickname_ de su oponente y procederá a crear ambos jugadores en su propia instancia del juego sigiuendo la información que recibió (número de jugador propio y _nickname_ del oponente) y a iniciar el juego.
- Como se había indicado al principio, el servidor sigue ahora escuchando constantemente de nuevo.
- Lo que sigue acá de parte del cliente es enviar los mensajes de los movimientos correspondientes **UP**, **DOWN** y **NONE**, dependiendo de qué es lo que haga ese cliente, y esperar la recepción del movimiento del oponente.
- El servidor recibe el mensaje y lo compara para verificar si es un mensaje de inicialización.
  - Como esta vez no es un mensaje de inicialización, sino uno durante la partida, el servidor va a pasar ese mensaje junto con su _socket_ a un hilo, el cual llamará a la función threadBody, quien se encargará de atender ese mensaje y darle la respuesta correspondiente.
    - En este caso, la respuesta será enviarle ese movimiento que recibió al oponente del jugador que envió el mensaje.
    - Como cada cliente estaba esperando el movimiento de su oponente, y ya cada uno lo envió a quien correspondía, ambos lo reciben y reflejan su movimiento y el del oponente en el juego.
    - Así se hará con cada movimiento que realicen los clientes durante todo el juego.
    - Finalmente, Una vez el cliente identefique que alguno de los 2 jugadores ha llegado a los cinco puntos, este enviara un mensaje al servidor anunciando el ganador.
    - El servidor procedera a enviar este mensaje al oponente y una vez este confirme la recepcion de este ultimo mensaje se procedera a terminar el juego.
    - Para terminar el juego simplemente se cambiara la vista del cliente y se le mostrara a ambos jugadores el nombre del ganador de la partida.

Este flujo del juego se puede repetir tantas veces como se desee, ya que el servidor, mientras esté encendido, estará escuchando los mensajes de potenciales clientes, y de los ya conectados y activos.

### Diagrama ilustrativo del flujo del juego
![DiagramaFlujoTelePong drawio](https://github.com/EsteTruji/TelePong/assets/94024545/8e133d32-e87e-4623-9372-7eab71757e47)


### Descripción de tecnologías. ¿Cómo se hizo?
Además, en cumplimiento con lo requerido en la práctica, el juego se desarrolló siguiendo la arquitectura **Cliente-Servidor** y **TCP/IP**, donde se estableció un **servidor** programado en el lenguaje C, y un **cliente** programado en el lenguaje Python, a los cuales se les asignaron los nombres de **TelePongServer.c** y **TelePongClient.py**, respectivamente.. Además, se partió del eje fundamental de los sockets, los cuales posibilitan la comunicación y el envío de mensajes entre el cliente y el servidor, y viceversa. Para ello, se hizo uso de la **API de sockets Berkeley en C**. y de la **librería socket en Python**.

Un aspecto muy importante en este sentido es que no se realizó la importación de tales librerías directamente en el servidor y el cliente, respectivamente, sino que, exclusivamente para el posiblitamiento de la comunicación entre ambos y con el fin de establecer un bajo acoplamiento en este sentido, se estableció un protocolo de comunicación basado en texto en C y en Python (ver [Descripción del protocolo](#descripci%C3%B3n-del-protocolo)). Así, el servidor incluye el protocolo en C, y el cliente importa el protocolo en Python.

También cabe destacar que, después de deliberar y discutir en el grupo de trabajo, se optó por trabajar con los **sockets de tipo UDP**. Tales motivos se enuncian a continuación:
1. Dado el contexto del proyecto, el cual corresponde a un "videojuego" y no a una aplicación donde es crucial que no haya pérdida de información, se consideró la opción de trabajar sobre sockets UDP. 
2. Los sockets UDP posibilitan una comunicación más rápida entre el cliente y el servidor y viceversa, lo que se traduce en una latencia más baja en comparación sockets TCP.
3. La aplicación funcionará en tiempo real, por lo que las latencias, o a lo sumo, las latencias considerables, no pueden ser aceptadas, ya que acabaría por completo con el sentido y la usabilidad de esta.
4. Como los sockets UDP son sin conexión, hay una menor sobrecarga de datos ya que no es necesario tener que establecer esa conexión antes de enviar cualquier mensaje o _request_. Esto beneficia también a la velocidad del juego, en comparación (nuevamente) con _sockets_ TCP.

Por otro lado, para poder implementar lo relacionado con la concurrencia, es decir, la conexión simultánea de múltiples clientes al juego, de tal manera que todos puedan jugar con su respectivo oponente, se hizo uso de los hilos en el servidor (```#include <pthread.h>```). De tal forma que el servidor esté en la capacidad de atender y responder a las _requests_ que le realizan los diferentes clientes que están jugando.

Ahora, con relación al cliente, se hizo uso de la librería Pygame de Python, para establecer la estructura, lógica, y vistas del juego, basándose fuertemente en la POO (Programación Orientada a Objetos) con el fin de realizar un mejor manejo de los diferentes elementos del juego. De manera adicional, se usaron otras librerías como **os (```import os```)** y **time (```import time```)** con el fin de brindar otras herramientas necesarias para el funcionamiento del cliente.

### Descripción del protocolo.
Con relación al protocolo, cabe mencionar que se desarrolló con el fin posibilitar el bajo acoplamiento entre el cliente, el servidor y la librería de _sockets_. De esta forma, así como se tiene implementado, basta con que el cliente y el servidor importen o incluyan al protocolo en su lenguaje correspondiente, siendo así el protocolo en C **myPongProtocol.c** y el protocolo en Python **myPongProtocol.py**. Por lo tanto, el protocolo se definió basado en texto, de tal manera que la comunicación entre el cliente-protocolo y servidor-protocolo es a través del llamado a una función general, que recibe como argumento una cadena de texto que incluye la información necesaria para poder realizar determinada acción del lado del protocolo, usando los _sockets_ (valga aclara que, para el caso del protocolo en Python, se hizo la excepción de enviar también como argumento al socket del cliente debido a las complicaciones que presentaba en este lenguaje para convertirlo a cadena de texto). El protocolo recibe entonces la cadena que le envía el servidor o el cliente y realiza un parseo de la misma, con el fin de extraer la información necesaria e identificar cuál es la acción que posteriormente debe ejecutar. Con relación a los mensajes usados para la comunicación, se estableció que se utilizarían dos prefijos o palabras iniciales de reconocimiento, las cuales serían **PLAYER** y **SERVER**, y que de ahí en adelante se seguiría una jerarquía, siendo **PLAYER** y **SERVER** el nivel principal, el siguiente nivel correspondiendo a la instrucción propiamente, y finalmente teniendo los argumentos necesarios para la ejecución de tal comando. Así, pues, se tiene el siguiente conjunto de mensajes, los cuales son utilizados por el servidor y el cliente de la manera que a continuación se enuncia. 

#### Vocabulario de mensajes usado.
Con relación al prefijo **PLAYER**:
- PLAYER CREATE_SOCKET: Permite la creación del _socket_ del cliente, el cual será utilizado durante todo el juego para el envío y recepción de mensajes.
- PLAYER CREATE <ins>_NICKNAME_</ins>: Permite la creación de un nuevo jugador, tomando como _nickname_ el mandado en el espacio correspondiente.
- PLAYER RECEIVE <ins>_SOCKET_</ins>: Permite la rececepción de un nuevo jugador para posteriormente asignarlo a una sala o _game_ junto con la información necesaria para jugar, usando el _socket_ del servidor, tomándolo del espacio <ins>_SOCKET_</ins>.
- PLAYER SEND_OPP <ins>_SOCKET_</ins> <ins>_NICKNAME_</ins> <ins>_PLAYER_ADD_</ins>: Permite el envío de la información requiere un jugador con relación a quién es su oponente (<ins>_NICKNAME_</ins>), usando el _socket_ del servidor (<ins>_SOCKET_</ins>), y la dirección IP junto con el puerto (<ins>_PLAYER_ADD_</ins>) del jugador que va a recibir a su oponente
- PLAYER RECEIVE_OPP <ins>_SOCKET_</ins>: Permite la recepción del _nickname_ del oponente que le corresponde al jugador, después de que el servidor hizo la distribución necesaria de los jugadores entrantes en las salas disponibles, usando el _socket_ del cliente que se encuentra en el espacio correspondiente de la instrucción.
- PLAYER SEND_MSG <ins>_SOCKET_</ins> <ins>_MESSAGE_</ins>: Permite enviar un determinado mensaje (<ins>_MESSAGE_</ins>), usando el _socket_ del cliente (<ins>_SOCKET_</ins>)
- PLAYER SEND_MOVE <ins>_SOCKET_</ins> <ins>_MESSAGE_</ins>: Permite que el cliente pueda enviar al servidor un mensaje (<ins>_MESSAGE_</ins>) que está relacionado con el movimiento que este realiza en el juego usando su _socket_ (<ins>_SOCKET_</ins>).
- PLAYER MOVE <ins>_GAME_ID_</ins> <ins>_PLAYER_NUM_</ins> <ins>_MOVEMENT_</ins>: Permite que el servidor pueda conocer qué jugador realizó qué movimiento a partir de la información incluida en el mensaje completo, dónde se puede obtener qué número de jugador (<ins>_PLAYER_NUM_</ins>) de qué juego o partida (<ins>_GAME_ID_</ins>) realizó determinado movimiento (<ins>_MOVEMENT_</ins>).
- PLAYER SEND_MOVE_OPP <ins>_MOVEMENT_</ins> <ins>_SOCKET_</ins> <ins>_PLAYER_ADD_</ins>: Permite que el servidor envíe un movimiento que realizó un jugador de determinada partida a la dirección IP del oponente. Esto se logra usando el _socket_ del servidor (<ins>_SOCKET_</ins>), el movimiento que realizó el jugador (<ins>_MOVEMENT_</ins>), y la dirección IP junto con el puerto (<ins>_PLAYER_ADD_</ins>) del oponente respectivo.
- PLAYER DELETE <ins>_GAME_ID_</ins> <ins>_PLAYER_NUM_</ins>: Permite la eliminación de un jugador que se encuentra en el juego con id <ins>_GAME_ID_</ins> y con el número de juagdor <ins>_PLAYER_NUM_</ins>.

Con relación al prefijo **SERVER**:
- SERVER CREATE_SOCKET: Permite la creación del socket del servidor, el cual será utilizado durante todo el juego para el envío hacia y recepción de mensajes de parte de los diferentes clientes conectados.
- SERVER LISTEN_MSG <ins>_SOCKET_</ins>: Permite que el servidor escuche por un posible mensaje entrante de parte de algún cliente conectado, usando su _socket_ (<ins>_SOCKET_</ins>).
- SERVER GAME_INFO <ins>_SOCKET_</ins> <ins>_PLAYER_NUM_</ins> <ins>_GAME_ID_</ins> <ins>_PLAYER_ADD_</ins>: Permite el envío de la información necesaria de la partida para poder jugar. Ahí se incluye el _socket_ del servidor (<ins>_SOCKET_</ins>) para poder enviar la información correspondiente, el número del jugador (<ins>_PLAYER_NUM_</ins>) y el id del juego o partida en la que se encuentra el jugador (<ins>_PLAYER_NUM_</ins>) a la dirección IP junto con el puerto (<ins>_PLAYER_ADD_</ins>) del jugador que la va a recibir.

## Conclusiones.
A manera de conclusiones podemos destacar las siguientes:
1. Consideramos este proyecto como una práctica bastante importante debido a los temas y elementos con los que aquí se trabajaron. Estos constituyen tópicos fundamentales en nuestra carrera como Ingenieros de Sistemas, no solo por la amplia aplicación de los mismos en múltiples áreas, sino también por el desarrollo de habilidades y manejo de los mismos a la hora de usarlos y aplicarlos en este proyecto.
2. Consideramos este proyecto como una oportunidad para darnos cuenta de cuáles son algunos de los elementos que van detrás de arquitecturas como Cliente-Servidor, donde pudimos evidenciar las aplicaciones de otras arquitecturas como TCP/IP, y el uso de herramientas tan cruciales para estas arquitecturas, tales como los sockets, en el manejo de la comunicación entre cliente y servidor y viceversa.
3. Consideramos que los sockets son elementos fundamentales en una amplia gama de desarrollos debido a su gran utilidad y su labor crucial para el posibilitamiento de una comunicación y envío de mensajes entre diferentes actores, sean servidores o clientes, o ambos. Además, dentro de este aspecto, consideramos que es muy valiosa la posibilidad que estos sockets brindan al ofrecer un socket específico según las necesidades puntuales del proyecto en cuestión; estos tipos son UDP y TCP, donde ambos poseen ventajas con relación al otro, y donde es de crucial importancia realizar un apropiado balance de las necesidades y requerimientos básicos del proyecto para decidir con relación a cuál usar.
4. Consideramos que el uso de los hilos es demasiado importante en proyectos donde se requiere manejar apropiadamente la concurrencia de usuarios y peticiones de los mismos. Estos hilos posibilitan que el servidor pueda estar atendiendo y respondiendo a las diferentes _requests_ y mensajes que los clientes le envíen, y esto es crucial en momentos donde mensajes son enviadas al mismo tiempo. Así el servidor puede recibir el mensaje y delegar la respuesta del mismo a un hilo puntual. 

## Referencias. 

- GeeksforGeeks. (2023). Create a pong game in Python PyGame. GeeksforGeeks. https://www.geeksforgeeks.org/create-a-pong-game-in-python-pygame/
- GeeksforGeeks. (2021). How to create a text input box with PyGame. GeeksforGeeks. https://www.geeksforgeeks.org/how-to-create-a-text-input-box-with-pygame/
- GeeksforGeeks. (2022). TCP Server Client Implementation in C. GeeksforGeeks. https://www.geeksforgeeks.org/tcp-server-client-implementation-in-c/
- Greyrat, R. (2022, 5 julio). ¿Cómo dibujar un rectángulo con esquina redondeada en PyGame? – Barcelona Geeks. https://barcelonageeks.com/como-dibujar-un-rectangulo-con-esquina-redondeada-en-pygame/
