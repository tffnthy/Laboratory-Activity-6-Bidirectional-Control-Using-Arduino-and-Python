import serial
import time

arduino_port = 'COM6'  # Replace with your Arduino port
baud_rate = 9600

try:
    ser = serial.Serial(arduino_port, baud_rate, timeout=0.1)
    time.sleep(2)  # Wait for Arduino to reset

    print(f"Connected to {arduino_port}")
    print("Press the buttons on your Arduino...")

    while True:
        if ser.in_waiting > 0:
            # Read a full line sent by Arduino
            incoming_data = ser.readline().decode('utf-8').strip()  # strip removes newline

            if incoming_data == 'R':
                print("Received 'R' from Button 1 -> Sending '1'")
                ser.write(b'1')
            elif incoming_data == 'G':
                print("Received 'G' from Button 2 -> Sending '2'")
                ser.write(b'2')
            elif incoming_data == 'B':
                print("Received 'B' from Button 3 -> Sending '3'")
                ser.write(b'3')

        time.sleep(0.01)

except serial.SerialException:
    print("Could not open serial port. Please check your COM port.")
except KeyboardInterrupt:
    print("Program stopped by user.")
    if 'ser' in locals():
        ser.close()

