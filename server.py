import socket
import matplotlib.pyplot as plt

with open('data.txt', 'w') as f:
    pass

with socket.socket() as sock:
    sock.bind(("", 10001))
    sock.listen()

    while True:
        conn, addr = sock.accept()
        with conn:
            while True:
                data = conn.recv(1024)

                if not data:
                    break

                with open('data.txt', 'a') as f:
                    f.write(data.decode() + '\n')

                print('Adding data to the file...')
