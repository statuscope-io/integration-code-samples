# A sample Python 3 script to mark a Statuscope task as successful

import requests
import simplejson
import sys

data = {'token':'921b844aa8c9c44740329e121157b9e3', 'status':'OK'}
headers = {'Content-Type':'application/json'}

try:
    r = requests.post('https://www.statuscope.io/tasks/TxyosPiHdwiXrjqH4', data=simplejson.dumps(data), headers=headers)

    # Print only first 100 characters, since successful responses are shorter
    print("Server returned: {}".format(r.text[:100]))

    # Access response fields and values
    if r.json()['result'] == 'OK':
        print('Success')
    else:
        print('Failure')

except requests.exceptions.ConnectionError as ConnErr:
    print("Cannot connect to server")
    sys.exit(-1)

except simplejson.scanner.JSONDecodeError as DecodeErr:
    print("Cannot decode server response")
    sys.exit(-2)

