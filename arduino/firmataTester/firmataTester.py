import customtkinter as ctk
from pyfirmata2 import Arduino, OUTPUT
import time

# -------------------- ARDUINO SETUP -------------------- #
board = Arduino('/dev/ttyACM0')  # Always connect to /dev/ttyACM0
print("Board successfully connected")

# Define pin numbers
DIR_PIN = 3
STEP_PIN = 2
MICROSTEP_PINS = [8, 9, 10]
STEPS_PER_REVOLUTION = 1600
curStep = 0
curDir = True

# Set pin modes
board.digital[DIR_PIN].mode = OUTPUT
board.digital[STEP_PIN].mode = OUTPUT
for pin in MICROSTEP_PINS:
    board.digital[pin].mode = OUTPUT
    board.digital[pin].write(1)  # Set microstepping

# -------------------- GUI SETUP -------------------- #
ctk.set_appearance_mode("System")
window = ctk.CTk()
window.title("Motor Control")
window.configure(fg_color="#18181c")

# Switch variable
switch_var = ctk.BooleanVar(value=False)  # Start with the switch off

# Function to perform one motor step
def motor_step():
    global curStep, curDir
    if switch_var.get():  # Only step if the switch is ON
        board.digital[STEP_PIN].write(1)
        time.sleep(0.0003)
        board.digital[STEP_PIN].write(0)
        time.sleep(0.0003)
        curStep += 1
        if curStep == 33:
            curDir = not curDir
            curStep = 1
            board.digital[DIR_PIN].write(curDir)

# Function to toggle motor (not directly used in this case)
def toggle_motor():
    # You might not need this function anymore if you're 
    # directly controlling the motor in the main loop
    pass 

# Create the On/Off switch
switch = ctk.CTkSwitch(window, text="Motor", variable=switch_var, command=toggle_motor)
switch.pack(pady=20)

# -------------------- MAIN LOOP -------------------- #
while True:
    motor_step() # Execute one motor step if the switch is ON
    window.update_idletasks()
    window.update()
    time.sleep(0.001) # Adjust delay as needed 
