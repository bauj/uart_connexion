# uart_connexion

Small project to send and receive data through UART, using cpp, multithreaded.

## How-to

Download the latest release available (Linux only). Make it an executable and run it.

`uart_connexion` will only detect UART devices which have the following name pattern :
* `/dev/ttyAMA*`
* `/dev/ttyUSB*`
* `/dev/ttyACM*`

Once selected, choose the right baudrate and hit the connect button.

An arduino sketch is available in the repository. It is a small program that reacts to the reception of instruction (command) such as "ON", "OFF" and "SHINE".

It induces a modification of the builtin LED behaviour of a classical Arduino UNO (or equivalent). Once the instruction is received, the device will send back a message through UART, readable in the Monitoring frame of `uart_connexion`. 
