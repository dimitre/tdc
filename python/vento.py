import requests
import json as json
import pandas as pa
from pandas import json_normalize
from datetime import datetime
from pytz import timezone
import math 

from datetime import datetime
now = datetime.now() # current date and time
hoje = now.strftime("%Y-%m-%d")

url = "http://www.cropnet.us/api/v1/login"
payload = "{\"email\":\"api-client-klabin@zeusagro.com\",\"password\":\"klabin-lNka8i4E8dj\"}"
headers = {
  'Content-Type': 'application/json;charset=UTF-8',
  'Accept': 'application/json, text/plain, */*'
}

response = requests.request("POST", url, headers=headers, data=payload)
login = json.loads(response.text)
token = login['user']['token']
url = 'http://www.cropnet.us/api/v1/pics/4422/monitoring?start=' + hoje + "&end=" + hoje + "&timeZone=-3"

payload={}
headers = {
  'Authorization': token
}
 
response = requests.request("GET", url, headers=headers, data=payload)
# print(json.dumps(response.text, indent=4))

# import sys
# import json
# from pygments import highlight, lexers, formatters

# formatted_json = json.dumps(json.loads(response.text), indent=4)
# colorful_json = highlight(formatted_json, lexers.JsonLexer(), formatters.TerminalFormatter())
# print(colorful_json)

dados = json.loads(response.text)

resultado = {
  # print(math.sin(math.radians(270)));
  'dir' : math.sin(math.radians(dados[0]['windDirectionAverage'])),
  'direction' : dados[0]['windDirectionAverage'],
  'speed' : dados[0]['windSpeedInst'],
  'started': dados[0]['started'],
}

my_json = json.dumps(resultado)
print(my_json)