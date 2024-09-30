import customtkinter as ctk
from pyfirmata2 import Arduino, OUTPUT
import time

# -------------------- GUI INITIAL FRAME -------------------- #
ctk.set_appearance_mode("System")

# Create window
window = ctk.CTk()
window.title("iGEM")
window.configure(fg_color="#18181c")

# Header Frame
header_frame = ctk.CTkFrame(window, fg_color="#18181c", corner_radius=0)
header_frame.pack(fill="x")  # Fill horizontally
header_label = ctk.CTkLabel(header_frame,
                            text="Microfluidic Pump Control Panel",
                            font=("Arial", 35, "bold"),
                            fg_color="#18181c")
header_label.pack(expand=True, fill="both", padx=20, pady=30)

# Initial Connection Frame
connection_frame = ctk.CTkFrame(window, fg_color="#2d2d30")
connection_frame.pack(expand=True, fill="both")
board_name_label = ctk.CTkLabel(connection_frame, text="Board Name:", font=("Arial", 20))
board_name_label.grid(row=0, column=0, padx=(45, 15), pady=20)
board_name_entry = ctk.CTkEntry(connection_frame, placeholder_text="e.g. /dev/ttyACM0", font=("Arial", 15))
board_name_entry.grid(row=0, column=1, padx=0, pady=20)

# --------------- ARDUINO SETUP --------------- #
def connect_to_board():
    global board, DIR_PIN, STEP_PIN, MICROSTEP_PINS, STEPS_PER_REVOLUTION, curStep, curDir
    board_name = board_name_entry.get()
    try:
        board = Arduino(board_name)
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
            board.digital[pin].write(1)  # Set microstepping to maximum

        # Switch to control panel
        connection_frame.pack_forget()
        control_panel_frame.pack(expand=True, fill="both")

    except Exception as e:
        print(f"Error connecting to board: {e}")

# -------------------- GUI CONTROL FRAME -------------------- #
# Create a button to trigger the connection
connect_button = ctk.CTkButton(connection_frame, text="Connect", command=connect_to_board, font=("Arial", 20))
connect_button.grid(row=0, column=2, padx=(150, 40), pady=20)

# Control Panel Frame
control_panel_frame = ctk.CTkFrame(window, fg_color="#2d2d30")  # Initially hidden
segmented_button = ctk.CTkSegmentedButton(control_panel_frame,
                                          values=["Off", "Pump Out", "Pump In", "Mixing"],
                                          font=("Arial", 30),
                                          selected_color="#924DBF",
                                          selected_hover_color="#924DBF")
segmented_button.pack(expand=True, fill="both", padx=20, pady=20)
segmented_button.set("Off")  # Set initial selection

# -------------------- ARDUINO MOTOR CONTROL -------------------- #
def run_motor():
    global curStep, curDir
    if segmented_button.get() == "Mixing":
        for _ in range(STEPS_PER_REVOLUTION):
            board.digital[STEP_PIN].write(1)
            time.sleep(0.0003)  # 300 microseconds delay 
            board.digital[STEP_PIN].write(0)
            time.sleep(0.0003) 
        curStep += 1
        if curStep == 33:
            curDir = not curDir
            curStep = 1
            board.digital[DIR_PIN].write(curDir)

    elif segmented_button.get() == "Pump In":
        board.digital[DIR_PIN].write(1) 
        for _ in range(STEPS_PER_REVOLUTION):
            board.digital[STEP_PIN].write(0)
            time.sleep(0.0003) 
            board.digital[STEP_PIN].write(1)
            time.sleep(0.0003) 
        curStep += 1
        if curStep == 33: 
            curStep = 1
            segmented_button.set("Off") 

    elif segmented_button.get() == "Pump Out":
        board.digital[DIR_PIN].write(0)  
        for _ in range(STEPS_PER_REVOLUTION):
            board.digital[STEP_PIN].write(0)
            time.sleep(0.0003) 
            board.digital[STEP_PIN].write(1)
            time.sleep(0.0003)
        curStep += 1
        if curStep == 33: 
            curStep = 1
            segmented_button.set("Off") 

    elif segmented_button.get() == "Off":
        board.digital[STEP_PIN].write(0) 

# -------------------- MAIN LOOP -------------------- #
board = None  # Initialize board to None (not connected)
while True:
    if board is not None:
        run_motor()
    window.update_idletasks()
    window.update()
