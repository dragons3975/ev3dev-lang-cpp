#!/usr/bin/env python3

import socket

client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
addr = ("127.0.0.1", 8080)

client_socket.sendto(bytearray.fromhex('0A00FF7FBE0101010101'), addr)
data, server = client_socket.recvfrom(1024)
for i in range (data[0]):
    print(data[i])
