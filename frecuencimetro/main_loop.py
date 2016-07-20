# -*- coding: utf-8 -*-

import RPi.GPIO as GPIO
import time

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)
GPIO.setup(4, GPIO.OUT)
GPIO.setup(17, GPIO.OUT)
GPIO.setup(27, GPIO.OUT)

GPIO.setup(21, GPIO.IN)
GPIO.setup(20, GPIO.IN)

state = True

cycle = 0.1

led_task = 10
led_state = False
read_task = 1
# endless loop, on/off for 1 second
try:

  while True:

     if(GPIO.input(21)):
        GPIO.output(4,True)   
     else:
        GPIO.output(4,False)

     if(GPIO.input(20)):
        GPIO.output(27,True)
     else:
        GPIO.output(27,False)

     if(led_task == 0):
        led_state = not led_state
        GPIO.output(17,led_state)
        led_task = 10
     else:
        GPIO.output(17,False)
     led_task-=1

     time.sleep(cycle)
except KeyboardInterrupt:
     GPIO.cleanup()
