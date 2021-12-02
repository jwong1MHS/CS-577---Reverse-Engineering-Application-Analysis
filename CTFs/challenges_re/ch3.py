# edi
n = 256
print(n)

# mov	edx, edi
# shr	edx
d = (n >> 1)
# or	edx, edi
# mov	eax, edx
a = d | n
print(d,a)


# shr	eax, 2
a = (a >> 2)
# or	eax, edx
# mov	edx, eax
d = a | d
print(a,d)


# shr	edx, 4
d = (d >> 4)
# or	edx, eax
# mov	eax, edx
a = d | a
print(d,a)


# shr	eax, 8
a = (a >> 8)
# or	eax, edx
# mov	edx, eax
d = a | d
print(a,d)

# shr  edx, 16
d = (d >> 4)
# or   edx, eax
d = d | a
print(d)

# imul	eax, edx, 79355661 ; 0x4badf0d
a = (d * 79355661)
# shr	eax, 26
a = (a >> 26)
print(a)
