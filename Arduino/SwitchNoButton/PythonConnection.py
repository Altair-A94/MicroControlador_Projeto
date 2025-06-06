import serial
import time

arduino = serial.Serial('COM13', 9600)  # ajuste a porta COM

while True:
    if arduino.in_waiting:
        msg = arduino.readline().decode().strip()
        print("Recebido do Arduino:", msg)
        if msg == "ATIVADO":
            # Depois de receber ATIVADO, confirma para Arduino
            arduino.write(b'CONFIRMADO\n')
            print("Enviado CONFIRMADO")
    time.sleep(0.1)
