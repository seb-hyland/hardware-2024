import customtkinter as ctk

ctk.set_appearance_mode("System")  # Modes: system (default), light, dark
ctk.set_default_color_theme("green")  # Themes: blue (default), dark-blue, green

window = ctk.CTk()
window.title("iGEM")
window.configure(fg_color="#18181c")  # Set background color in CustomTkinter

header_frame = ctk.CTkFrame(window,
                            fg_color="#2d2d30",
                            corner_radius=0)
header_frame.grid(row=0,
                  column=0,
                  columnspan=2,
                  sticky="nsew")
header_frame.rowconfigure(0, weight=1)

header_label = ctk.CTkLabel(header_frame,
                            text="Microfluidic Pump Control Panel",
                            font=("Arial", 35, "bold"),
                            fg_color="#2d2d30")
header_label.pack(expand=True,
                  fill="both",
                  padx=20,
                  pady=30)

segmented_button = ctk.CTkSegmentedButton(window, 
                                          values=["Off", "Pump Out", "Pump In", "Mixing"],
                                          font=("Arial", 30),
                                          selected_color="#924DBF",
                                          selected_hover_color="#924DBF"
                                          )
segmented_button.grid(row=1,
                      column=0,
                      columnspan=2,
                      sticky="ew",
                      padx=20,
                      pady=20)
segmented_button.set("Off")  # Set initial selection

window.columnconfigure(0, weight=1)
window.columnconfigure(1, weight=1)
window.rowconfigure(1, weight=1)
window.rowconfigure(2, weight=1)

window.mainloop()
