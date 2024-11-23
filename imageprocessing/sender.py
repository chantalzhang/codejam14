import serial
import numpy as np
import cv2
import time

# Simulated OV7670 camera.
# Takes in webcam input and converts it to RGB565 format for the receiver, which is expecting an OV7670 video stream
# Serializes to port COM5, replace with port on your machine
# Uses virtual serial port driver https://www.virtual-serial-port.org/vspd-post-download.html.

# Configuration
port = "COM5"  # Replace with your serial port
baud_rate = 115200
width = 320  # Emulated OV7670 resolution
height = 240
frame_size = width * height * 2  # RGB565 (2 bytes per pixel)

# Open Serial connection
ser = serial.Serial(port, baud_rate, timeout=1)

def bgr_to_rgb565(frame):
    """
    Convert a BGR frame (from OpenCV) to RGB565 format.
    """
    # Resize the frame to match the desired resolution
    frame_resized = cv2.resize(frame, (width, height))

    # Extract B, G, R channels
    b = frame_resized[:, :, 0].astype(np.uint16) >> 3  # Blue (5 bits)
    g = frame_resized[:, :, 1].astype(np.uint16) >> 2  # Green (6 bits)
    r = frame_resized[:, :, 2].astype(np.uint16) >> 3  # Red (5 bits)

    # Combine into RGB565 format: [RRRRRGGG][GGGBBBBB]
    rgb565 = ((r << 11) | (g << 5) | b)

    # Return raw bytes in little-endian order
    return rgb565.astype(np.uint16).tobytes()



def send_frame(serial_port, frame_data):
    """
    Send a frame over the serial port.
    """
    serial_port.write(frame_data)
    print(f"Sent frame of size {len(frame_data)} bytes.")

def generate_dummy_frame(width, height):
    """
    Generate a dummy frame with random RGB565 data.
    (This can be used if the webcam is not available.)
    """
    return np.random.randint(0, 65536, size=(height, width), dtype=np.uint16).tobytes()

def main():
    # Try to open the webcam
    cap = cv2.VideoCapture(0)
    
    # Add webcam configuration
    cap.set(cv2.CAP_PROP_FRAME_WIDTH, width)
    cap.set(cv2.CAP_PROP_FRAME_HEIGHT, height)
    cap.set(cv2.CAP_PROP_FPS, 30)

    if not cap.isOpened():
        print("Error: Could not open webcam. Falling back to dummy data.")
        use_webcam = False
    else:
        print("Webcam successfully opened.")
        use_webcam = True

    try:
        print("Press 'q' to quit.")
        while True:
            if use_webcam:
                # Capture a frame from the webcam
                ret, frame = cap.read()
                if not ret:
                    print("Error: Could not read frame from webcam.")
                    print("Attempting to reinitialize camera...")
                    cap.release()
                    time.sleep(1)
                    cap = cv2.VideoCapture(0)
                    continue

                # Convert the frame to RGB565
                frame_data = bgr_to_rgb565(frame)

                # Show the frame locally for debugging
                cv2.imshow("Webcam (Emulating OV7670)", cv2.resize(frame, (width, height)))
            else:
                # Generate a dummy frame if webcam is unavailable
                frame_data = generate_dummy_frame(width, height)

            # Send the frame over serial
            send_frame(ser, frame_data)

            # Exit on 'q' key
            if use_webcam and cv2.waitKey(1) & 0xFF == ord('q'):
                break

            # Add a small delay to prevent overwhelming the serial connection
            time.sleep(0.033)  # ~30 FPS

    except KeyboardInterrupt:
        print("Stopped by user.")
    finally:
        # Release resources
        if use_webcam:
            cap.release()
        ser.close()
        cv2.destroyAllWindows()

if __name__ == "__main__":
    main()
