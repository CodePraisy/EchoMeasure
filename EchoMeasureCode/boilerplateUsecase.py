import serial
import json

PORT = "COM7"       # change this
BAUD = 115200

with serial.Serial(PORT, BAUD, timeout=1) as ser:
    while True:
        line = ser.readline().decode("utf-8").strip()
        if not line:
            continue
        try:
            print(json.loads(line))
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        except json.JSONDecodeError:
            pass