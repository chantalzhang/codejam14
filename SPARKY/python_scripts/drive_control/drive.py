import serial
import time

# Open serial connection
ser = serial.Serial('COM3', 9600, timeout=1)
time.sleep(2)  # Allow time for connection to establish and stabilize before sending commands

def forward(duration):
    """Send forward command"""
    print("Sending: F")
    ser.write(b"F\n")
    time.sleep(duration)
    stop()

def backward(duration):
    """Send backward command"""
    print("Sending: B")
    ser.write(b"B\n")
    time.sleep(duration)
    stop()

def turn_left(duration):
    """Send turn left command"""
    print("Sending: L")
    ser.write(b"L\n")
    time.sleep(duration)
    stop()

def turn_right(duration):
    """Send turn right command"""
    print("Sending: R")
    ser.write(b"R\n")
    time.sleep(duration)
    stop()

def stop():
    """Send stop command"""
    print("Sending: S")
    ser.write(b"S\n")
    time.sleep(0.5)

# Test sequence
try:
    print("Starting test sequence...")
    forward(5)
except Exception as e:
    print(f"Error: {e}")
finally:
    ser.close()
    print("Serial port closed")
