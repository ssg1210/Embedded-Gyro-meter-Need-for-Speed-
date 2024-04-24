# Embedded-Gyro-meter-Need-for-Speed-
This project was part of an embedded challenge - to built a wearable tech

# Objective 
The objective of this embedded challenge was to build a wearable 
speedometer which can calculate velocity by measuring angular velocities available 
from our built-in gyroscope (L3GD20) - without a GPS. Our gyroscope can 
measure 3-axis angular velocity. Strategically placing the sensor on the legs or feet 
can capture the angular velocities and with a bit of processing is able to convert those 
angular velocities to linear forward velocity and calculate distance traveled (using 
only a gyro!)

# Requirements

1. STM32F429 Discovery Board with built in gyroscope 
2. Power supply/USB power bank 
3. A way to store 20 seconds of velocity data, sampled at 0.5 second intervals 
(Storing in memory is fine)

#Project Approach

Used the STM32F29 discovery kit, it comes with a built-in gyroscope which was 
further used to capture the value for movement of human walk. 
The project was further implemented in the following sequence: - 
1. Placement of Gyroscope: - 
• The microcontroller is placed on the thigh, as the gyroscope collects 
values of only in the angular fashion.  
• Gyroscope sensor is a device that can measure and maintain the 
orientation and angular velocity of an object, that is, it measures the 
tilt and lateral orientation of the object. 
• Human leg tilts from the knee point and the thigh section oscillates in 
the to and from motion, while walking or running. 
• Hence, to get values of the angular velocity of the body (leg) of a 
human being from the gyroscope, we decided to place the gyroscope 
on the upper thigh section.  
2. Gathering values only from x-axis: - 
• As we placed the gyroscope on the upper thigh area of the leg, we 
were able to get values in the 3- directions namely, the x-axis, y-axis, 
and z-axis. 
• While walking, the thigh oscillates in the to and fro direction, i.e., just 
in one direction, which we decided to be as the x-axis. Hence, we got 
a lot of noise in gathering the values from the y-axis and the z-axis, 
which is why, in this project, for walking case, we have just considered 
the values from the x-axis.  
• While running, the legs are sometimes completely lifted at angle of 90o 
from the ground. Hence, in the running case, we have tried to 
implement the values from the 2 directions or two axes viz, the x-axis 
and the y-axis.  
3. Calculating angular velocity: - 
• Angular velocity is defined as the rate of change of the position angle 
of an angle with respect to time. 
• To get the values of the angular velocity of a human leg while covering 
a distance, we implemented the standard formula to calculate the 
total angular velocity, when a human body makes a move.  
• The formula to find the angular velocity of a human body that we 
implemented, is ω = r M g I ω, where r is the distance from the pivot 
to the center of mass of the gyroscope, I is the moment of inertia of 
the gyroscope's spinning disk, M is its mass, and ω is the angular 
frequency of the gyroscope disk. 
• Here, pivot is considered as the knee point of the leg from where the 
knee bends. This pivot point makes an imaginary circle around it and 
the center of mass of the gyroscope lies on the circumference of this 
imaginary circle.  
• In this way, we are able to find the angular velocity of a human body 
in motion which will then effectively help us in finding the linear 
velocity and the total distance travel in the further steps. 
4. Averaging the angular velocity: - 
• While in motion, the gyroscope continuously gauges and calculates 
the values of the angular velocities across all the directions.  
• To get an estimate of all the changing values of the angular velocities, 
we take an average of all the values that the gyroscope has been 
gathering for the last 40 times. 
• In this given project, we are expected to find accurate values for a time 
duration of 20 seconds, over which we have to gather values every half 
a second, hence, we set the ticker to 40, which ultimately collects 40 
data points in all the cases. Once the ticker reaches 40, the counter is 
again set to 0 and the gyroscope restarts gathering all the values all 
over again. 


5. Finding the linear velocity from the angular velocity: - 
• We were done taking the average of all the angular velocities, the next 
task we performed was to calculate the linear velocity of the human 
body, so as to ultimately calculate the total distance covered by it. 
• To do this we calculated the total time taken by a human body to take 
one step at a time and then multiplied the whole thing by the total 
number of steps taken.  
• From the above step, we were able to find the value of ω which 
indicates the value of the total angular displacement of the object. 
• To find the linear velocity from the given angular velocity, we used the 
formula v = rω, where v is linear velocity, r is the radius (the distance 
from the pivot point to the center of mass of the gyroscope), and ω is 
the angular distance traveled.  
• We further integrated ω with respect to dt, that finally gave us the 
value of total angular displacement (l). 
• We then multiplied the angular displacement with the cos function of 
the angle (ie, lcos)  that is being formed due to the pivot which gave 
us the value of the total linear velocity of a human body. 
6. Total distance covered: - 
• After getting the value of the linear velocity, the only task that 
remained was to calculate the total distance traveled by a human 
body in a time span of 20 seconds. 
• Hence, we multiplied the time taken by a human body to take one 
step with the total number of steps walked/ran in the time duration 
of 20 seconds. 
• To complete the math behind this logic, we then further multiplied 
the whole term with the linear velocity as the formula suggests (v x t 
= d), due to which we were able to compute the total distance 
traveled by a human body in 20 seconds of time, which was 
supposedly the objective of this major project. 


# Explain the Graphs

![image](https://github.com/ssg1210/Embedded-Gyro-meter-Need-for-Speed-/assets/167916988/b5a68f92-65a1-460d-8d43-020ea62ccd3b)

• Here from the graphs, the similarity between all the graphs taken at 
different points of angular velocities, is clearly visible. 
• The fluctuation can be observed due the y axis and z axis measurements 
that is why we only consider x axis measurements 


# Testing and Conclusion

We tested the working of our project for around 20-25 steps for about 20 
seconds. 
Following is the output collected by the terminal is:  
When stationary:  

![image](https://github.com/ssg1210/Embedded-Gyro-meter-Need-for-Speed-/assets/167916988/3896a811-b0cb-4be7-92c8-43f30c6d4ad4)

![image](https://github.com/ssg1210/Embedded-Gyro-meter-Need-for-Speed-/assets/167916988/94a98d7f-4c7f-4d93-b334-e5a87b835f06)

![image](https://github.com/ssg1210/Embedded-Gyro-meter-Need-for-Speed-/assets/167916988/44f3bdd0-ccf7-4651-997d-04be18b236c8)

# Code

So there are 4 files in the zip that we are attaching:  
• main.cpp: the main file including the main driver function and logic implementation for our project.  
• gyro_funcs.cpp: This file includes all the gyro functions used in our project like for displaying or calculating angular velocity etc.  
• gyro_funcs.h: This is the header files to access the function used in the project 
• variables_declared: This is the header file that includes all the variables used the project






