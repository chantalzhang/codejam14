import serial
import numpy as np
import cv2
from ultralytics import YOLO
import time


#receives video stream from sender on ports (COM6 from virtual serial port driver in our case)

# Configuration for video feed
port = "COM6"  # Replace with the matching virtual serial port
baud_rate = 115200
width = 320  # Must match the sender's settings
height = 240
frame_size = width * height * 2  # RGB565 (2 bytes per pixel)

# Configuration for signaling port
SIGNAL_PORT = "COM7"  # Configure this later
SIGNAL_BAUD = 9600    # Can be adjusted based on needs
last_signal_time = 0
SIGNAL_COOLDOWN = 1.0  # Minimum seconds between signals

# Load YOLO model
model = YOLO('yolov8n.pt')

# Open Serial connections
ser = serial.Serial(port, baud_rate, timeout=1)
try:
    signal_ser = serial.Serial(SIGNAL_PORT, SIGNAL_BAUD, timeout=1)
    print(f"Opened signaling port on {SIGNAL_PORT}")
except:
    print(f"Warning: Could not open signaling port on {SIGNAL_PORT}")
    signal_ser = None

def detect_phones_yolo(frame):
    """
    Detect phones using YOLO and draw bounding boxes.
    Returns the frame and whether a phone was detected.
    """
    global last_signal_time
    current_time = time.time()
    
    phone_detected = False
    results = model(frame)
    
    for result in results:
        boxes = result.boxes
        for box in boxes:
            if box.cls == 67:  # Cell phone class
                phone_detected = True
                x1, y1, x2, y2 = box.xyxy[0]
                cv2.rectangle(frame, 
                            (int(x1), int(y1)), 
                            (int(x2), int(y2)), 
                            (0, 255, 0), 2)
                cv2.putText(frame, 
                          f'Phone {box.conf[0]:.2f}', 
                          (int(x1), int(y1)-10), 
                          cv2.FONT_HERSHEY_SIMPLEX, 
                          0.9, 
                          (0, 255, 0), 
                          2)
    
    # Send signal if phone detected and cooldown has elapsed
    if phone_detected and signal_ser is not None:
        if current_time - last_signal_time >= SIGNAL_COOLDOWN:
            try:
                signal_ser.write(b'1')
                print("Phone detected - Signal sent!")
                last_signal_time = current_time
            except:
                print("Failed to send signal")
    
    return frame

def decode_rgb565_to_bgr(raw_data, width, height):
    """
    Convert RGB565 raw data to BGR format for OpenCV and apply fixed shift.
    """
    # Interpret the raw data as 16-bit unsigned integers (RGB565)
    frame = np.frombuffer(raw_data, dtype=np.uint16).reshape((height, width))

    # Extract R, G, B channels with proper bit shifts
    r = ((frame & 0xF800) >> 11) * 255 // 31    # Red: bits 11-15
    g = ((frame & 0x07E0) >> 5) * 255 // 63     # Green: bits 5-10
    b = (frame & 0x001F) * 255 // 31            # Blue: bits 0-4

    # Stack channels into a BGR image (OpenCV format)
    bgr_frame = np.dstack((b, g, r)).astype(np.uint8)
    
    # Apply fixed 128-pixel shift
    shifted_frame = np.roll(bgr_frame, -128, axis=1)  # Negative for left shift
    
    return shifted_frame

def read_frame(serial_port, frame_size):
    """Read a frame of the specified size from the serial port."""
    data = serial_port.read(frame_size)
    if len(data) != frame_size:
        print("Incomplete frame received.")
        return None
    return data

try:
    print("Starting video feed monitoring...")
    while True:
        raw_frame = read_frame(ser, frame_size)
        if raw_frame is None:
            continue
        
        bgr_image = decode_rgb565_to_bgr(raw_frame, width, height)
        bgr_image = detect_phones_yolo(bgr_image)
        
        cv2.imshow("Emulated OV7670 Feed", bgr_image)
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

except KeyboardInterrupt:
    print("Stopped receiving.")
finally:
    ser.close()
    if signal_ser is not None:
        signal_ser.close()
    cv2.destroyAllWindows()
