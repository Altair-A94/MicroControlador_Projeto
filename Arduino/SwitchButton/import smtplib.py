   import smtplib

   smtp_server = "smtp.office365.com"
   port = 587  # Para TLS
   sender_email = "seu_email@exemplo.com"
   password = "sua_senha"

   with smtplib.SMTP(smtp_server, port) as server:
       server.starttls()  # Segurança
       server.login(sender_email, password)
       # Enviar e-mail...
   