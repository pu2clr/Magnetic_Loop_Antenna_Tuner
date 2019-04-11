#  Simple python program to test the Antenna Tuner Controller 

This Python program can be useful to test the communication of the Arduino prototype via Bluetooth.

If you are using an Unix system operator the Bluetooth / Serial connection be made as shown below.
```python
atu = serial.Serial(
port='/dev/tty.HC-05-DevB', 
        baudrate=9600,
        parity=serial.PARITY_ODD,
        stopbits=serial.STOPBITS_TWO,
        bytesize=serial.SEVENBITS
)
```
You should know what __/dev/tty*__ your bluetooth device is connected to your Unix computer.


If you are using Microsoft Windows the Bluetooth / Serial connection can be made as shown below.

```python
atu = serial.Serial(
        port='COM5',
        baudrate=9600,
        parity=serial.PARITY_ODD,
        stopbits=serial.STOPBITS_TWO,
        bytesize=serial.SEVENBITS
)
```

You should know what __COM*__ your bluetooth device is connected to your Windows computer.
