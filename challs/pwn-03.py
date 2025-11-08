#!/usr/bin/python3
from pwn import *

p = process("./03-uaf")


def read_addr():
    line = p.recvline().strip().decode()
    print(line)
    return int(line.split(": ")[1], 0)


system_addr = read_addr()
worker_addr = read_addr()


def do_use():
    print(p.recvuntil(b"Choice: ").decode())
    p.send(b"1\n")


def do_allocate(size, data):
    print(p.recvuntil(b"Choice: ").decode())
    p.send(b"2\n")
    p.send(str(size).encode() + b"\n")
    p.sendline(data)


def do_free():
    print(p.recvuntil(b"Choice: ").decode())
    p.send(b"3\n")


# TODO
do_use()
do_allocate(8, b"abcd")
do_free()

p.interactive()
