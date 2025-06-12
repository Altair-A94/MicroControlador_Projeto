import serial
import time
import smtplib
import email.message 

arduino = serial.Serial('COM6', 9600)  # ajuste a porta COM

def enviar_email():
    Corpo_email = "porta aberta"

    msg = email.message.Message()
    msg['Subject'] = "ALERTA"
    msg['From'] = f'meuremetente@gmail.com'
    msg['To'] = 'altair500@maildrop.cc'
    password = 'senha do email aqui'
    msg.add_header('Content-Type', 'text/html')
    msg.set_payload(Corpo_email)

    s = smtplib.SMTP('smtp.outlook.com: 587')
    s.starttls()
    # credencias de login para enviar o email
    s.login(msg['From'], password)
    s.sendmail(msg['From'], [msg['To']], msg.as_string().encode('utf-8'))
    print('Email enviado')

while True:
    if arduino.in_waiting:
        msg = arduino.readline().decode().strip()
        print("Recebido do Arduino:", msg)
        if msg == "ATIVADO":
            # Depois de receber ATIVADO, confirma para Arduino
            arduino.write(b'CONFIRMADO\n')
            print("Enviado CONFIRMADO")
            enviar_email()
    time.sleep(0.1)
