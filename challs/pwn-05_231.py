#!/usr/bin/python3
from pwn import *

p = process(["./ld-231.so", "./05-tcache-uaf_231"], env={"LD_PRELOAD": "./libc-231.so"})
# p = gdb.debug(["./ld-231.so", "./05-tcache-uaf_231"], env={"LD_PRELOAD": "./libc-231.so"})


def read_addr():
    line = p.recvline().strip().decode()
    print(line)
    return int(line.split(": ")[1], 0)


shell_addr = read_addr()
op_addr = read_addr()


def create_note():
    print(p.recvuntil(b"Choice: ").decode())
    p.send(b"1\n")


def read_note():
    print(p.recvuntil(b"Choice: ").decode())
    p.send(b"2\n")
    return p.recvline()[:-1]


def update_note(data):
    print(p.recvuntil(b"Choice: ").decode())
    p.send(b"3\n")
    p.sendline(data)


def delete_note():
    print(p.recvuntil(b"Choice: ").decode())
    p.send(b"4\n")


def exit_note():
    print(p.recvuntil(b"Choice: ").decode())
    p.send(b"0\n")


# TODO
create_note()
data = read_note()
update_note(data)
delete_note()
exit_note()


p.interactive()
