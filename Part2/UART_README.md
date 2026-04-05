**What UART is and where it is used ?**

UART is a method used to send data one bit at a time from one device to another. It is used in laptop to/from microcontroller.

**Frame format (start bit, data bits, parity, stop bit) ?**

 Start Bit (1 bit):- It indicates beginning of data transmission ;
 Data Bits (usually 8 bits):- The data which is to be send;
 Parity Bit (optional):- it is used for simple error detection ;
 Stop Bit (1 or 2 bits):- It indicates end of transmission

**Baud rate and its significance?**

Baud rate is the rate at which data or bit is send. Both sender and receiver should have the same baud rate otherwise the output becomes garbage.

 **Asynchronous communication concept?**

UART doesn’t have a shared clock. So both devices fix a baud rate and starts syncing after the the start bit. So after start bit the sender and receiver both at fixed intervals given by the baud rate.

Registers used for UART configuration are  USART_CR1( Control register), USART_BRR (Baud rate register), USART_SR (Status register),USART_DR (Data register ,Used to send data )

**Baud rate calculation?**

Baud Rate = Clock Frequency / USARTDIV

We want a Baud Rate of 9600, so we take a USARTDIV of  (16x106/9600)=1667 or 0x0683

 **Steps involved in transmitting data?**

Steps involved

