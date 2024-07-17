from Crypto.Cipher import AES
from Crypto.Util.Padding import pad, unpad
from Crypto.Random import get_random_bytes
from secret import flag
import json, base64

key = get_random_bytes(32)

def get_user_token(name):
    cipher = AES.new(key=key, mode=AES.MODE_ECB)
    token = json.dumps({
        "username": name,
        "admin": False
    })
    enc_token = cipher.encrypt(pad(token.encode(),AES.block_size))
    return f"{base64.b64encode(enc_token).decode()}" # encryption encoded base64


def check_user_token(token):
    cipher = AES.new(key=key, mode=AES.MODE_ECB)
    dec_token = unpad(cipher.decrypt(base64.b64decode(token)),AES.block_size)

    user = json.loads(dec_token) # de-jsonifier of the token as a dictionary
    
    if user.get("admin", False) == True:
        return True
    else:
        return False
    

def get_flag():
    token = input("What is your token?\n> ").strip()
    if check_user_token(token):
        print("You are admin!")
        print(f"This is your flag!\n{flag}")
    else:
        print("HEY! WHAT ARE YOU DOING!?")
        exit(1)


if __name__ == "__main__":
    name = input("Hi, please tell me your name!\n> ").strip()
    token = get_user_token(name)
    print("This is your token: " + token)

    menu = \
        "What do you want to do?\n" + \
        "quit - quit the program\n" + \
        "help - show this menu again\n" + \
        "flag - get the flag\n" + \
        "> "
    while True:
        cmd = input(menu).strip()

        if cmd == "quit":
            break
        elif cmd == "help":
            continue
        elif cmd == "flag":
            get_flag()
