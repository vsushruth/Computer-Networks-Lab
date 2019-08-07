import socket

cli = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
print("Client socket created")

port = 11115
cli.connect(('127.0.0.1',port))

sndm = raw_input("Enter message :")
cli.send(sndm)
msg = "what"

while(sndm != 'x' and msg != 'x'):
	msg = cli.recv(1024)
        print(msg)
	sndm = raw_input("Enter message: ")
	cli.send(sndm)

cli.close()
