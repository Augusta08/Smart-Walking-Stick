# Smart Walking Stick
Design of a Smart Walking Stick using arduino nano, ultrasonic sensors and a vibration motor. 

The smart walking stick functions by continuously scanning the environment for obstacles and holes, then providing real-time feedback to the user through vibration and sound.  

At the front of the stick, an ultrasonic sensor is mounted to detect obstacles within a range of 50 cm. It emits high-frequency sound waves and measures the time it takes for the echo to return after bouncing off an object. Based on
this time, the distance to the object is calculated. If an obstacle is detected within the set range, both a vibration motor and a buzzer are activated. The vibration intensity increases as the obstacle gets closer, and the buzzer beeps more rapidly, giving the user an intuitive sense of how near the object is.  

In addition to obstacle detection, a downward-facing ultrasonic sensor is positioned near the base of the stick to detect holes or sudden drops in the walking surface. When a hole is sensed, the system immediately triggers a continuous buzzer sound, unlike the beeping pattern used for front obstacles.  

This distinct, uninterrupted alert helps the user quickly differentiate between raised obstacles and potentially dangerous drops.  
## Components Used  
Arduino Nano  
Ultrasonic Sensors  
Vibration Motor  
Buzzer  
9V Battery  
Switch  


![Image](https://github.com/user-attachments/assets/ed57a2f8-5841-4466-bcdd-0f2f507ee66a)



