from Crypto.Hash import SHA256


hash_object = SHA256.new()
hash_object.update(b'Beginning of the message to hash...')
hash_object.update(b'...and some more data')

print(hash_object.digest()) # returns the hash as bytes
print(hash_object.hexdigest()) # returns the hash as a string of hexadecimal digits


hash_object = SHA256.new(data=b'First part of the message. ' ) # here is passed already the first piece of data to hash
hash_object.update(b'Second part of the message. ')
hash_object.update(b'Third and last.')

print(hash_object.digest())
print(hash_object.hexdigest())
