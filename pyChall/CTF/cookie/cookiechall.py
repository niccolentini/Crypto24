from Crypto.Cipher import ChaCha20
from Crypto.Random import get_random_bytes
from pwn import *
import json, base64

'''
prima crei un plaintext qualsiasi, poi quando ricevi il token (cifratura di plaintext e nonce) fai known plaintext attack per ottener il keystream

Forgi il cookie come "admin : true" e lo cifri con il keystream ottenuto e il nonce di prima e poi glielo mandi come token
'''

host = connect('130.192.5.212', 6521)
host.recvuntil(b'Hi, please tell me your name!\n> ')

host.sendline(b'admin')
host.recvuntil(b'This is your token: ')
received = host.recvline().decode().strip()

nonce = base64.b64decode(received.split('.')[0])
ciphertext = base64.b64decode(received.split('.')[1])

plaintext = json.dumps({
    "username" : "admin"
}).encode()

#obtain keystream by XORing the plaintext and ciphertext

keystream = b''
for i in range(len(ciphertext)):
    keystream += bytes([ciphertext[i] ^ plaintext[i]])


new_plaintext = json.dumps({
    "admin" : True
}).encode()

#obtain the new ciphertext by XORing the new plaintext and the keystream (keystream reuse vulnerability)

new_ciphertext = b''
for i in range(len(new_plaintext)):
    new_ciphertext += bytes([new_plaintext[i] ^ keystream[i]])

new_token = base64.b64encode(nonce).decode() + '.' + base64.b64encode(new_ciphertext).decode()

host.recvuntil(b'> ')
host.sendline(b'flag')
host.recvuntil(b'What is your token?\n> ')
host.sendline(new_token)

host.interactive()



