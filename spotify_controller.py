import spotipy
from spotipy.oauth2 import SpotifyOAuth
import serial
import time
import sys

SPOTIPY_CLIENT_ID = ''
SPOTIPY_CLIENT_SECRET = ''
SPOTIPY_REDIRECT_URI = 'http://127.0.0.1:8888/callback'

SERIAL_PORT = 'COM3'
BAUD_RATE = 9600

scope = 'user-read-playback-state user-read-currently-playing'
sp = spotipy.Spotify(auth_manager=SpotifyOAuth(
    client_id=SPOTIPY_CLIENT_ID,
    client_secret=SPOTIPY_CLIENT_SECRET,
    redirect_uri=SPOTIPY_REDIRECT_URI,
    scope=scope
))

try:
    arduino = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
    time.sleep(2)
except Exception as e:
    print(f"Could not open serial port {SERIAL_PORT}: {e}")
    sys.exit(1)

def send_to_arduino(line1, line2):
    line1 = line1[:48].ljust(48)
    line2 = line2[:48].ljust(48)
    try:
        arduino.write((line1 + line2 + '\n').encode('utf-8'))
    except Exception as e:
        print(f"Error sending to Arduino: {e}")

def get_current_playback():
    try:
        current = sp.current_playback()
        if not current or not current['is_playing']:
            return "Not Playing", ""
        item = current['item']
        if item is None:
            return "Not Playing", ""
        name = item['name']
        artists = ', '.join([a['name'] for a in item['artists']])
        duration_ms = item['duration_ms']
        progress_ms = current['progress_ms']
        def format_time(ms):
            minutes = ms // 60000
            seconds = (ms % 60000) // 1000
            return f"{minutes}:{seconds:02}"
        time_info = f"{format_time(progress_ms)} / {format_time(duration_ms)}"
        line2 = f"{artists} - {time_info}"
        def clean_text(s):
            return ''.join(c if 32 <= ord(c) <= 126 else ' ' for c in s)
        return clean_text(name), clean_text(line2)
    except Exception as e:
        print(f"Spotify error: {e}")
        return "Error", ""

print("Spotify Display Running...")
last_title = ""
try:
    while True:
        title, info = get_current_playback()
        send_to_arduino(title, info)
        last_title = title
        time.sleep(1)
except KeyboardInterrupt:
    print("Exiting...")
    arduino.close()
    sys.exit(0)
