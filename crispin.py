import serial
import time
from datetime import datetime

# Configuración del puerto serial
arduino_port = "COM4"
baud_rate = 9600

# Inicia la conexión serial
try:
    ser = serial.Serial(arduino_port, baud_rate, timeout=1)
    print(f"Conectado a {arduino_port}")
    time.sleep(2)  # Espera a que Arduino esté listo
except Exception as e:
    print(f"No se pudo conectar a {arduino_port}: {e}")
    exit()

# Envío de la fecha actual
while True:
    try:
        # Obtén la fecha actual
        current_date = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        
        # Envía la fecha por el puerto serial
        ser.write(current_date.encode('utf-8'))
        print(f"Enviando: {current_date}")
        
        # Espera una respuesta del Arduino
        response = ser.readline().decode('utf-8').strip()
        if response == "OK":
            print("Arduino respondió OK. Finalizando.")
            break
        else:
            print(f"Respuesta del Arduino: {response}")
        
        time.sleep(5)  # Espera antes de volver a enviar
    except KeyboardInterrupt:
        print("Proceso interrumpido por el usuario.")
        break
    except Exception as e:
        print(f"Error: {e}")
        break

# Cierra la conexión serial
ser.close()
