from Crypto.Cipher import ChaCha20
from Crypto.Random import get_random_bytes
from pwn import *
import json, base64

host = connect('130.192.5.212', 6561)

host.recvuntil(b'initialize me!\n> ')

seed = 0
random.seed(seed)
nonce = random.getrandbits(12*8)

host.sendline(str(seed).encode())
host.recvuntil(b'encrypted secret!\n')

ciphertext = bytes.fromhex(host.recvline().decode().strip())

host.recvuntil(b'(y/n)')
host.sendline(b'y')

host.recvuntil(b'message? ')
msg = b"A"*46 
host.sendline(msg)

ciphertext2 = bytes.fromhex(host.recvline().decode().strip())

# obtain keystream by XORing the plaintext and ciphertext
keystream = b''
for i in range(len(ciphertext2)):
    keystream += bytes([ciphertext2[i] ^ msg[i]])

#retrieve the flag from ciphertext using the keystream
flag = b''
for i in range(len(ciphertext)):
    flag += bytes([ciphertext[i] ^ keystream[i]])

print(flag)







