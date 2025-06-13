import time
import smtplib
from email.message import EmailMessage
import serial

# Configurações do Gmail
REMETENTE = 'meuarduino2025@gmail.com'              # substitua pelo seu e-mail Gmail
SENHA_APP = 'xfnv fiiw ddll khvh'          # substitua pela senha do app gerada no Google
DESTINATARIO = 'arduinotest500@maildrop.cc'    # substitua pelo e-mail do destinatário

# Configura porta serial do Arduino
arduino = serial.Serial('COM5', 9600)

def enviar_email():
    assunto = 'ALERTA'
    corpo_email = 'porta aberta'

    msg = EmailMessage()
    msg['From'] = REMETENTE
    msg['To'] = DESTINATARIO
    msg['Subject'] = assunto
    msg.set_content(corpo_email)

    try:
        with smtplib.SMTP('smtp.gmail.com', 587) as smtp:
            smtp.ehlo()
            smtp.starttls()
            smtp.login(REMETENTE, SENHA_APP)
            smtp.send_message(msg)
        print('Email enviado com sucesso.')
    except Exception as e:
        print('Erro ao enviar email:', e)

def main():
    while True:
        if arduino.in_waiting:
            msg = arduino.readline().decode().strip()
            print("Recebido do Arduino:", msg)
            if msg == "ATIVADO":
                arduino.write(b'CONFIRMADO\n')
                print("Enviado CONFIRMADO")
                enviar_email()
        time.sleep(0.1)

if __name__ == '__main__':
    main()

