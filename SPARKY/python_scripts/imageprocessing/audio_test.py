import time
from playsound import playsound
import os

# Get the absolute path to the audio directory
current_dir = os.path.dirname(os.path.abspath(__file__))
audio_dir = os.path.join(current_dir, "audio")

# List of audio files
audio_files = [
    os.path.join(audio_dir, "n_aggressive.mp3"),
    os.path.join(audio_dir, "n_sparky.mp3"),
    os.path.join(audio_dir, "n_get_off_phone.mp3"),
    os.path.join(audio_dir, "n_meow.mp3")
]

def play_all_files():
    for audio_file in audio_files:
        print(f"Playing: {os.path.basename(audio_file)}")
        playsound(audio_file)
        time.sleep(0.5)  # Half second delay between files

if __name__ == "__main__":
    print("Playing audio files...")
    try:
        while True:
            play_all_files()
    except KeyboardInterrupt:
        print("\nPlayback stopped by user")
