from pwn import *

r = connect('130.192.5.212',  6531)

for i in range(128):

    r.recvuntil(b'using: ')

    otp = r.recvline().strip().decode()

    r.recvuntil(b'Input: ')

    r.sendline(otp.encode())

    r.recvuntil(b'Output: ')

    result = r.recvline().strip().decode()

    if(result[:32] == result[32:]):
        r.sendline(b'ECB')
    else:
        r.sendline(b'CBC')

r.interactive()


