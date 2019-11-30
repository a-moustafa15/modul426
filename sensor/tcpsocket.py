from _thread import start_new_thread
from socket import *

def accept_sensor():
    
    HOST = '10.102.100.34'  # Standard loopback interface address (localhost)
    PORT = 5567        # Port to listen on (non-privileged ports are > 1023)
    try:
        
        with socket(AF_INET, SOCK_STREAM) as s:
            s.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
            s.bind((HOST, PORT))
            s.listen()
            conn, addr = s.accept()
            with conn:
                while True:
                    data = conn.recv(1)
                    print(data)                     
                s.close()
    except Exception:
        print("Error")
        import traceback
        print (traceback.format_exc())

def start_listening():
    start_new_thread(accept_sensor, ())
    