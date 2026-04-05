What a timer is in a microcontroller ?

It is a timer built in the STM-32. We use the clock inside the STM-32 to time our tasks.

Why hardware timers are preferred over software delays?

Delay using looping is very hard to control and won’t be accurate to more than an extend where as hardware timers are very accurate. One more advantage of using Hardware timers over Software delays is that it is independent of the Compiler.

Basic working concept (counter, prescaler, auto-reload)?

Counter: -It is used to count the numbers…

Prescaler: -It is used to scale the amount the we take in one counting. Like we don’t count upto a large value since clock speed is in Mhz, We take the ‘n’ terms to increase the count by one using the Prescaler

Auto-reload: - It is a measure upto which value it should count. After that it resets the count to 0.

Which timer was used? 

The Timer used is TIM2.It is a general-purpose timer available in STM32.



Prescaler (PSC) value and why it was chosen?

Prescaler Value: 15999

The clock speed of STM32 is 16MHz. So, if we want to count each ms , we have to count each 16x106/1000=16000. So, we have to take prescaler: (16000-1) =15999. Basically, it’s like count the next term after ignoring the prescaler number of numbers.

 Auto-reload register (ARR) value calculation?

Auto reload register is the value upto which it should count. Since it has to blink every 2 seconds and it counts very ms, ARR = 2/10-3= 2000. Hence,  it will count until 2000.

 Control and status registers involved?

 We use CR1 as control register and SR as status register.CR1 is used to start or control how the timer works  and SR tells if you need to count or ARR is reached.
 
 How the update flag is used for timing?
 
Update flag is used like if ARR is reached it becomes 1 and tells to stop counting and reset to zero. 
 
