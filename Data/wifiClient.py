import socket

def wifi_client(server_ip, server_port, message):
    try:
        # Create socket
        client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

        print(f"Connecting to {server_ip}:{server_port}...")
        client.connect((server_ip, server_port))
        print("Connected!")

        # Send message
        client.sendall(message.encode('utf-8'))
        print(f"Sent: {message}")

        # Optional: receive response
        response = client.recv(1024)
        print("Received:", response.decode('utf-8'))

        client.close()

    except Exception as e:
        print("Error:", e)


if __name__ == "__main__":
    server_ip = "192.168.50.114"   # <-- change to your server IP
    server_port = 4242            # <-- change to your server port

    while True:
        msg = input("Enter message (or 'exit'): ")
        if msg.lower() == "exit":
            break

        wifi_client(server_ip, server_port, msg)