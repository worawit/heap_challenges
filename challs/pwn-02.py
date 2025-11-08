#!/usr/bin/python3
from pwn import *

p = process("./02-overflow")


def read_addr():
    line = p.recvline().strip().decode()
    print(line)
    return int(line.split(": ")[1], 0)


key_value = read_addr()
key_addr = read_addr()
msg_addr = read_addr()
msg_s_addr = read_addr()
arr_addr = read_addr()
arr_data_addr = read_addr()

# TODO modify msg
msg = b"my world\n"
p.send(msg)

# TODO modify idx and val
idx = 1
val = 2
p.send(f"{idx} {val}\n".encode())

try:
    while True:
        print(p.recvline().decode(), end="")
except Exception:
    pass
