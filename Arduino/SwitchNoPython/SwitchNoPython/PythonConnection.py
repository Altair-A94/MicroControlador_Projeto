import serial
import time

# Ajuste a porta serial conforme seu sistema operacional:
# Windows: algo como 'COM3'
# Linux/Mac: algo como '/dev/ttyACM0' ou '/dev/ttyUSB0'
PORTA = 'COM13'  
BAUD_RATE = 9600

try:
    arduino = serial.Serial(PORTA, BAUD_RATE, timeout=1)
    time.sleep(2)  # Dá tempo para a conexão estabilizar

    print("Conectado ao Arduino na porta", PORTA)

    while True:
        if arduino.in_waiting > 0:
            linha = arduino.readline().decode('utf-8').strip()
            print("Recebido do Arduino:", linha)

            if linha == "ATIVADO":
                print("Enviando CONFIRMADO para Arduino...")
                arduino.write(b"CONFIRMADO\n")

except serial.SerialException:
    print("Não foi possível conectar na porta serial.")
except KeyboardInterrupt:
    print("Programa interrompido pelo usuário.")
finally:
    if 'arduino' in locals() and arduino.is_open:
        arduino.close()
        print("Conexão serial encerrada.")
