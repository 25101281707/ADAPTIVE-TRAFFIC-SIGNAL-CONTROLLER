# ADAPTIVE-TRAFFIC-SIGNAL-CONTROLLER
Adaptive traffic signal controller using a priority queue (max-heap) with aging. A C++ program on the laptop picks the next green lane from Arduino sensor data. Priority = 2 × vehicle count + waiting time.
 Fixed-timer signals waste time on empty lanes. Our controller gives the green light to the lane with the highest priority score, calculated as 2 × vehicle count + 1 × waiting time. Because waiting time is part of the score, a lane with few vehicles still gets its turn (aging), so no lane is starved. The Arduino reads IR sensors and controls the LEDs. The C++ program on the laptop makes the decisions, and the two talk over USB serial at 9600 baud. The green time depends on the vehicle count, from 5 to 30 seconds.

