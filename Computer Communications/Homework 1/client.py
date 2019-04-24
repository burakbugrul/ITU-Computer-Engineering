from socket import AF_INET, socket, SOCK_STREAM
from threading import Thread
import tkinter


class Client:

    def __init__(self, **kwargs):
        self.BUFFER_SIZE = 1024
        self.HOST = kwargs.get('host', '')
        self.PORT = int(kwargs.get('port', 12312))
        self.server = socket(AF_INET, SOCK_STREAM)  # TCP connection
        self.quit_message = "---quit---"
        self.gui = tkinter.Tk()  # tkinter is a default module in python
        self.gui.title("Chat Room")  # Setting window title
        self.messages_frame = tkinter.Frame(self.gui)  #  Message flow frame
        self.message_textfield = tkinter.StringVar()  # Message entry field
        self.scrollbar = tkinter.Scrollbar(self.messages_frame)  # For scrolling old messages
        self.messages = tkinter.Listbox(self.messages_frame, height=30, width=100, yscrollcommand=self.scrollbar.set)
        self.scrollbar.pack(side=tkinter.RIGHT, fill=tkinter.Y)  # Vertical scroll
        self.messages.pack(side=tkinter.LEFT, fill=tkinter.BOTH)  # Message align left
        self.messages.pack()
        self.messages_frame.pack()
        self.entry = tkinter.Entry(self.gui, textvariable=self.message_textfield)
        self.entry.bind("<Return>", self.send)  # Routing messages to 'send' function
        self.entry.pack()
        self.send_button = tkinter.Button(self.gui, text="Send", command=self.send)  # Linking send button
        self.send_button.pack()
        self.gui.protocol("WM_DELETE_WINDOW", self.close_callback)  # A callback for window close event

    def connect(self):
        self.server.connect((self.HOST, self.PORT))

    def receive(self):

        while True:  # Infinite loop for listening incoming messages
            try:
                message = self.server.recv(self.BUFFER_SIZE).decode("utf-8")
                self.messages.insert(tkinter.END, message)
                self.messages.yview(tkinter.END)  # Autoscroll
            except:  # gui or OS error
                break

    def send(self, event=None):

        message = self.message_textfield.get()
        self.message_textfield.set("")  # After sending a message, entry field should be cleared

        self.server.send(bytes(message, "utf-8"))

        if message == self.quit_message:
            self.server.close()
            self.gui.quit()

    def close_callback(self, event=None):
        self.message_textfield.set(self.quit_message)
        self.send()


if __name__ == "__main__":

    host = input("Please enter HOST(leave empty for default): ").strip()

    try:
        port = int(input("Please enter PORT(leave empty for default): "))
    except:
        port = 12312

    client = Client(host=host, port=port)
    client.connect()
    receiver_thread = Thread(target=client.receive)
    receiver_thread.start()
    tkinter.mainloop()
