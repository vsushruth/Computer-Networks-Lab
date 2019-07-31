import socket 
import select 
import sys
from thread import *

soc = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print("Server socket created")

port = 11225
soc.bind(('',port))
print("Server binded to port")

soc.listen(100)
print("Server is listening")



