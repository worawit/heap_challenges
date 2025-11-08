#!/usr/bin/python3
from pwn import *

p = process('./01-chunks')

print(p.recvuntil(b'Your data: ').decode())

# TODO modify data
data = b'\x00'*144
p.send(data)

print(p.recv().decode())

