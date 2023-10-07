import socket

SERVER_IP = '127.0.0.1'  # Replace with the actual IP address of the server
SERVER_PORT = 12345

def create_socket():
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect((SERVER_IP, SERVER_PORT))
    return client_socket

def getMovement(client_socket, movement):
    # Remove extra spaces and newline characters from the input
    user_input = movement.strip()

    # Send user input to the server
    client_socket.sendall(user_input.encode())

    # Receive updated game state from the server
    response = client_socket.recv(1024).decode()
    print("Server response: ", response)
    return response

    # Process game state and update the game display
    # ...



# Close the socket
#client_socket.close()