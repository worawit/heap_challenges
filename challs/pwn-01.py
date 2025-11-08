#!/usr/bin/python3
from pwn import *

p = process("./01-overflow")


def read_addr():
    line = p.recvline().strip().decode()
    print(line)
    return int(line.split(": ")[1], 0)


system_addr = read_addr()
name_addr = read_addr()
worker_addr = read_addr()

print(p.recv().decode())
# TODO modify name
name = b"my world\n"
p.send(name)

# p.interactive()
print(p.recvline().decode())
