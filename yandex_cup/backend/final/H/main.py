import json
import base64
import requests
import random
import string

def predict(line): 
    data = json.loads(line)
    msg = data["message"]
    num = data["number"]
    str_num = str(num)
    output_json = {"key_1": ((num * 4) & (2 ** 63 - 1)) if ((num * 4) & (2 ** 63)) == 0 else (((num * 4) & (2 ** 63 - 1)) - 2 ** 63),
                   "key_2": str_num[0:2] + '%',
                   "key_3": int(''.join(sorted(str_num))),
                   "key_4": chr(bytes(msg, 'utf-8')[num % len(bytes(msg, 'utf-8'))]),
                   "key_5": len(bytes(msg, 'utf-8')),
                   "space_6": msg.count(' '),
                   "const_7": "0x40",
                   "key_8": "{0:b}".format(bytes(msg, 'utf-8')[0])
    }
    str_json = json.dumps(output_json, ensure_ascii=False)
    #print(str_json)
    return base64.b64encode(bytes(str_json, 'utf-8')).decode('utf-8')
    
def acquire(line):
    r = requests.post('https://functions.yandexcloud.net/d4ebbsb4j7aoid25o0r5?integration=raw', data=line.encode('utf-8'))
    return r.text    

kTarget = 'est'

if kTarget == 'test':
    for i in range(0, 10):
        l = random.randint(1, 10)
        russian = u'йцукенгшщзхъфывапролджэячсмитьбюёЁЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭЯЧСМИТЬБЮ'
        symbols = u'!@#$%^&*(),. '
        message = ''.join(random.choice(string.ascii_lowercase + string.digits + russian + symbols) for _ in range(0, l))
        num = random.randint(1001, 2 ** 63 - 1)
        req = f'{{"message": "{message}", "number": {num}}}'
        predicted = predict(req)
        acquired = acquire(req)
        if predicted != acquired:
            print("FAILURE !!!!!!!!!!!!!!")
            print(req)
            print(predicted)
            print(acquired)
else:
    line = input()
    print(predict(line))
