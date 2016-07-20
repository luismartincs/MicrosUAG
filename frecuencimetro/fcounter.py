# -*- coding: utf-8 -*-

import RPi.GPIO as GPIO
import time

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)

#Pines

D1 = 17
D2 = 4
D3 = 3
D4 = 2

LED1 = 16
LED2 = 12
LED3 = 25

BTN = 24

INPUT = 23

#Transistores
GPIO.setup(2, GPIO.OUT)
GPIO.setup(3, GPIO.OUT)
GPIO.setup(4, GPIO.OUT)
GPIO.setup(17, GPIO.OUT)

#Segmentos
GPIO.setup(26, GPIO.OUT) #g
GPIO.setup(19, GPIO.OUT) #f
GPIO.setup(13, GPIO.OUT) #a
GPIO.setup(6, GPIO.OUT)  #b
GPIO.setup(5, GPIO.OUT)  #e
GPIO.setup(21, GPIO.OUT) #d
GPIO.setup(20, GPIO.OUT) #c

#Leds
GPIO.setup(LED1,GPIO.OUT)
GPIO.setup(LED2,GPIO.OUT)
GPIO.setup(LED3,GPIO.OUT)

#Button
GPIO.setup(BTN,GPIO.IN)

#Input

GPIO.setup(INPUT,GPIO.IN)

#Task Counters

LED1_TASK = 500
LED2_TASK = 1000
LED3_TASK = 250

BTN_TASK = 50

S1 = 1
S2 = 2
S3 = 4
S4 = 3

CT = 100

cycle = 0.001

#Variables

LBTN_ST = 1
CBTN_ST = 1
ON_HOLD = False
IN_ST = 1
CIN_ST = 1

COUNT = 0
F = 0


#Segmentos

#f,g,a,b,e,c,d
n_pines = [26,19,13,6,5,21,20]

n0 = [False,True,False,False,False,False,False]
n1 = [True,True,True,False,True,False,True]
n2 = [True,False,False,False,False,True,False]
n3 = [True,False,False,False,True,False,False]
n4 = [False,False,True,False,True,False,True]
n5 = [False,False,False,True,True,False,False]
n6 = [False,False,False,True,False,False,False]
n7 = [True,True,False,False,True,False,True]
n8 = [False,False,False,False,False,False,False]
n9 = [False,False,False,False,True,False,False]

numbers = [n0,n1,n2,n3,n4,n5,n6,n7,n8,n9]


def show_display_number(display,number):
   show_number(number)
   GPIO.output(D1,False)
   GPIO.output(D2,False)
   GPIO.output(D3,False)
   GPIO.output(D4,False)   
   GPIO.output(display,True)

def show_number(number):
   segments = numbers[number]
   for idx,pin in enumerate(n_pines):
      GPIO.output(pin,segments[idx])
   

  
# endless loop, on/off for 1 second
try:

  while True:
     
     if LED1_TASK == 0:
        if ON_HOLD:
	   GPIO.output(LED1,True)
        LED1_TASK = 500
     else:
        GPIO.output(LED1,False)

     if LED2_TASK == 0:
        GPIO.output(LED2,True)
        LED2_TASK = 1000
     else:
        GPIO.output(LED2,False)

     if LED3_TASK == 0:
        if not ON_HOLD:
	   GPIO.output(LED3,True)
        LED3_TASK = 250
     else:
        GPIO.output(LED3,False)

     CBTN_ST = GPIO.input(BTN)

     if CBTN_ST != LBTN_ST:
	if CBTN_ST == 0:
           ON_HOLD = not ON_HOLD

     CIN_ST = GPIO.input(INPUT)
       
     if CIN_ST != IN_ST:
     	COUNT += 1

     if S1 == 0:
        show_display_number(D1,COUNT/1000)
        S1 = 1
     if S2 == 0:
        F = COUNT % 1000
        show_display_number(D2,F/100)
        S2 = 2
     if S3 == 0:
        F = F % 100
        show_display_number(D3,F/10)
        S3 = 4
     if S4 == 0:
        F = F % 10
        show_display_number(D4,F)
	S4 = 3
	
     IN_ST = CIN_ST
     LBTN_ST = CBTN_ST
     LED1_TASK -= 1 
     LED2_TASK -= 1  
     LED3_TASK -= 1   
     S1 -= 1
     S2 -= 1
     S3 -= 1
     S4 -= 1
     CT -= 1
     time.sleep(cycle)
except KeyboardInterrupt:
     GPIO.cleanup()
