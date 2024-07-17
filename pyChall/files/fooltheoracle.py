from Crypto.Cipher import ChaCha20
from Crypto.Random import get_random_bytes
from pwn import *
import json, base64

host = connect('130.192.5.212', 6541)

compare = 15
flag = ''
firstBlock = b'0'*16
secondBlock = b'0'*compare
found = False

while len(flag) < 36:

    while(not found):

        host.recvuntil(b'this menu again\n> ')

        host.sendline(b'enc')

        host.recvuntil(b'> ')

        host.sendline(firstBlock.hex() + secondBlock.hex())
        encrypted = bytes.fromhex(host.recvline().decode().strip())

        #get just from the 17th byte to the 32th byte of encrypted 
        secondBlockToCompare = encrypted[16:32]
        if(secondBlockToCompare == firstBlock):
            # get just the last character of the second block
            flag += chr(encrypted[31])
            found = True
        else:
            #go to the next character
            firstBlock = bytes([firstBlock[15] + 1])
    
    found = False
    compare -= 1
    secondBlock = b'0'*compare
    firstBlock = b'0'*16

print(flag)



    