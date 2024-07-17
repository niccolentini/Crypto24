from Crypto.Random import get_random_bytes
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad, unpad

if __name__ == "__main__":
    IV = get_random_bytes(AES.block_size) # size of the IV is the size of the block in the algorithm

    key = get_random_bytes(AES.key_size[2])

    plaintext = b'These are the data to encrpyt !!'

    cipher_enc = AES.new(key, AES.MODE_CBC, IV) # here we initialize the object of the encryption

    ciphertext = cipher_enc.encrypt(plaintext) # we perform the cipher by calling the obect above and use the encrypt method
    print(ciphertext)

    cipher_dec = AES.new(key, AES.MODE_CBC, IV)
    decrypted_text = cipher_dec.decrypt(ciphertext)
    print(decrypted_text)

    # other example = now the plaintext will become unaligned string

    plaintext = b'Unaligned string...'
    cipher_enc = AES.new(key, AES.MODE_CBC, IV)
    padded_data = pad(plaintext, AES.block_size)
    print(padded_data)
    ciphertext = cipher_enc.encrypt(padded_data) # here you need to pass the aligned data padded!!!
    print(ciphertext)

    cipher_dec = AES.new(key, AES.MODE_CBC, IV)
    decrypted_text = cipher_dec.decrypt(ciphertext)
    unpadded = unpad(decrypted_text, AES.block_size)
    print(unpadded)


