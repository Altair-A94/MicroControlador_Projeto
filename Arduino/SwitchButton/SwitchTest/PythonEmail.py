import smtplib
from email.message import EmailMessage

def enviar_email():
    remetente = 'meuarduino2025@gmail.com'       # seu email Gmail
    senha = 'xfnv fiiw ddll khvh'
    destinatario = 'arduinotest500@maildrop.cc'  # email do destinatário
    assunto = 'ALERTA'
    corpo_email = 'porta aberta'

    msg = EmailMessage()
    msg['From'] = remetente
    msg['To'] = destinatario
    msg['Subject'] = assunto
    msg.set_content(corpo_email)

    try:
        with smtplib.SMTP('smtp.gmail.com', 587) as smtp:
            smtp.ehlo()
            smtp.starttls()
            smtp.login(remetente, senha)
            smtp.send_message(msg)
        print('Email enviado com sucesso.')
    except Exception as e:
        print('Erro ao enviar email:', e)

if __name__ == '__main__':
    enviar_email()
