# Ardunio_Auto_Pet_Feeder_Esp32
An DIY Auto Pet Feeder that had three functions.
## Hardware
For the completion of this assignment the following materials had been used:  
- ESP32s
- Pyro-electric Infrared Detector (PIR,HC-SR501)
- LED *1
- Real Time Clock (RTC,DS1302)
- Servo Motor (MG90S)
- Buzzer
- Dupont line
## Tinkercad Connection Diagram
![image](https://github.com/ridegeart/Ardunio_Auto_Pet_Feeder_Esp32/assets/73794853/6ef55a80-463a-46fd-8c17-88c962549f57)
## Function
1. Timing Auto Feeder：Servo Motor+RTC
   - Switch on the Morto to put feed in the bowl with RTC controlled. 
2. Pet Eating Monitoring：PIR+LED+Buzzer
   - Detect whether the cat is near the feeder with PIR sensor, and use the LED and Buzzer to guide the cat to eat.
3. Line Notify:RTC+WiFi
   - Connect the mobile phone through Line Notify to notify user that 1)food has been delivered and 2)the cat is eating.
## Flow Chart
1) Setting feeding Time.
  (when the time comes)
2) Motor start up -> Feed poured out & buzzer ring
4) Sending Message to user through Line Notify.【Feed Finished】
5) Detected that pet is eating (PIR) -> LED Lighting
6) Sending Message to user through Line Notify.【Your caat is eating】  
### Flow
```
                                                                                                                                                          】


                                                      +--------------+                                                         +---------------+
                                                 +--->| buzzer ring  |                                                     +---+ LED Lighting  |
                                                 |    +--------------+                     +-----------------------+       |   +---------------+
                                                 |                                         |                       |       |
+-----------+ when time comes   +-------------+  |    +------------------+                 | Whether pet is eating | Yes   |
| set time  +------------------>| Motor start +--+--->|  Feed poured out +---------------->|     (PIR sensor)      +------>|
+-----------+                   +-------------+  |    +------------------+                 |                       |       |   +---------------------+
                                                 |                                         +-----------------------+       |   | Sending Line Notify.|
                                                 |    +---------------------+                                              +---+                     |
                                                 +--->| Sending Line Notify.|                                                  |  【 pet is eating】   |
                                                      |                     |                                                  +---------------------+
                                                      |【 Feed Finished】     |
                                                      +---------------------+
```
