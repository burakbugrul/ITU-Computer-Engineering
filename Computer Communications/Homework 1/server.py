from socket import AF_INET, socket, SOCK_STREAM
from threading import Thread
from datetime import datetime


class Server:

    def __init__(self, **kwargs):
        self.clients = {}  # Dictionary for client name
        self.addresses = {}  # Dictionary for client addresses
        self.names = {}
        self.HOST = kwargs.get('host', '')
        self.PORT = kwargs.get('port', 12312)
        self.BUFFER_SIZE = 1024  # Buffer for one data fetch from the socket
        self.server = socket(AF_INET, SOCK_STREAM)  # TCP socket
        self.quit_message = "---quit---"
    
    def serve(self, number=5):
        self.server.bind((self.HOST, self.PORT))
        self.server.listen(number)

    def wait_connections(self):

        print("Waiting for connections...")

        while True:  # Infinitly listening new connections
            client, client_address = self.server.accept()  # A connection occured
            print(client, f'{client_address[0]}:{client_address[1]} has connected')
            client.send(bytes("Welcome, please enter your username", "utf-8"))  # Welcome text
            self.addresses[client] = client_address  # Saving client adress
            Thread(target=self.communicate_client, args=(client,)).start()  # Infinitly wating messages from the client

    def communicate_client(self, client):  # Client listening function

        while True:

            name = client.recv(self.BUFFER_SIZE).decode("utf-8")  # Getting username from the client

            if name not in self.names:  # name is valid
                client.send(bytes(f'Welcome {name}, you can send messages now. For exit, plase type \'---quit---\'', "utf-8"))
                self.broadcast(f'Prepare yourselves, {name} has joined!')  # Announcing new client to everyone
                self.clients[client] = name  # Saving client name
                self.names[name] = True
                break
            else:  # name is not valid, ask for another one
                client.send(bytes(f'Username \'{name}\' is taken, please enter another one', "utf-8"))

        while True:  # Infinite loope for waiting messages of the client

            message = client.recv(self.BUFFER_SIZE).decode("utf-8")  # Wating a message

            if message != self.quit_message:  # Checking whether the client wants to leave the chat
                self.broadcast(name + ": " + message)
            else:
                client.send(bytes("You are out of the chat room now :(", "utf-8"))
                client.close()
                del self.names[self.clients[client]]
                del self.clients[client]  # Deleting client from the room
                self.broadcast(f'{name} has left the chat.')
                break  # Terminating the loop

    def broadcast(self, message):
        for client in self.clients:  # Sending a message to all clients in the room
            client.send(bytes(f"({datetime.now().strftime('%H:%M')}) " + message, "utf-8"))

    def close(self):
        self.server.close()


if __name__ == "__main__":

    host = input("Please enter HOST(leave empty for default): ").strip()

    try:
        port = int(input("Please enter PORT(leave empty for default): "))
    except:
        port = 12312

    try:
        client_limit = int(input("Enter a limit for client number: "))
    except:
        client_limit = 5

    server = Server(host=host, port=port)
    server.serve(client_limit)
    connections = Thread(target=server.wait_connections())
    connections.start()  # Starts the infinite loop.
    connections.join()  # Waiting all thread to end to close the server
    server.close()
