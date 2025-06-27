import time
import smtplib
import email.message
import serial

arduino = serial.Serial('COM6', 9600)  # adjust the COM port as needed

def enviar_email():
    Corpo_email = "porta aberta"

    msg = email.message.Message()
    msg['Subject'] = "ALERTA"
    msg['From'] = 'tndjyeag@guerrillamail.info'
    msg['To'] = 'altair500@maildrop.cc'
    password = ''
    msg.add_header('Content-Type', 'text/html')
    msg.set_payload(Corpo_email)

    s = smtplib.SMTP('smtp.outlook.com', 587)
    s.starttls()
    s.login(msg['From'], password)
    s.sendmail(msg['From'], [msg['To']], msg.as_string().encode('utf-8'))
    s.quit()
    print('Email enviado')

while True:
    if arduino.in_waiting:
        msg = arduino.readline().decode().strip()
        print("Recebido do Arduino:", msg)
        if msg == "ATIVADO":
            # After receiving ATIVADO, confirm to Arduino
            arduino.write(b'CONFIRMADO\n')
            print("Enviado CONFIRMADO")
            enviar_email()
    time.sleep(0.1)
