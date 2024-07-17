from pwn import *



ADDRESS = #we do not care the actual address

PORT = 12342

SECRET_LEN = 16


#################################################

r = connect(ADDRESS, PORT)

secret = ""

block_size = AES.block_size

'''
here is the message: -> first block
+
one block of A
+ 
here is the secret:? -> third block
+
A*(16-len(secret))
+
here is the secret:S
+
ECRET0000000
'''
preM = "here is the message:"
postM = "here is the secret:"

for i in range (16):
msg = b'A'*(17-i)
found = false
for char in string.printable:
toSend = preM + msg + postM + secret + char.encode()
r.sendline(toSend)
received = bytes.fromhex(r.receiveline().strip().decode())
if( received[32:48] == received[48:64] )
{
guessed += char.encode()
print(guessed)
found = true
break
}

if( !found ) print("char not found")




