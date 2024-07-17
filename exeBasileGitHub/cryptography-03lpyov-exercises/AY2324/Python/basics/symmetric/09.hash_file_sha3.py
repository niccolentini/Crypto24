from Crypto.Hash import SHA3_256


hash_gen = SHA3_256.new()

with open(__file__) as f_input:
    hash_gen.update(f_input.read().encode()) #by default the file is open as text, so we need to encode it to bytes

print(hash_gen.digest())
print(hash_gen.hexdigest())


hash_gen = SHA3_256.new()
with open(__file__,"rb") as f_input:
    hash_gen.update(f_input.read())

print(hash_gen.digest())
print(hash_gen.hexdigest())
