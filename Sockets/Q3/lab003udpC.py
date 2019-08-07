import socket

cli = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)

addr = ('127.0.0.1',11116)

msg = "what"
while True:
	msg = raw_input("Enter message : ")
	cli.sendto(msg,addr)
	if(msg == 'x'):
		break
	print(cli.recvfrom(1024))

print("\nConnection closed")
cli.close()
