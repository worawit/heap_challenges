#!/usr/bin/python3
from pwn import *

p = process("./07-double-free")


def read_addr():
    line = p.recvline().strip().decode()
    print(line)
    return int(line.split(": ")[1], 0)


key_value = read_addr()
key_addr = read_addr()


def create_note(data):
    print(p.recvuntil(b"Choice: ").decode())
    p.send(b"1\n")
    p.sendline(data)
    print(p.recvline().strip().decode())


def read_note(idx):
    print(p.recvuntil(b"Choice: ").decode())
    p.send(b"2\n")
    p.send(f"{idx}\n".encode())
    return p.recvline()[:-1]


def update_note(idx, data):
    print(p.recvuntil(b"Choice: ").decode())
    p.send(b"3\n")
    p.send(f"{idx}\n".encode())
    p.sendline(data)


def delete_note(idx):
    print(p.recvuntil(b"Choice: ").decode())
    p.send(b"4\n")
    p.send(f"{idx}\n".encode())


def exit_note():
    print(p.recvuntil(b"Choice: ").decode())
    p.send(b"0\n")


# TODO
create_note(b"test")
data = read_note(0)
update_note(0, data)
delete_note(0)
exit_note()


try:
    while True:
        print(p.recvline().decode(), end="")
except Exception:
    pass
