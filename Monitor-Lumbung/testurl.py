from email import header
import requests

headers = {
  'user-agent': 'Mozilla/5.0 (Linux; Android 6.0; Nexus 5 Build/MRA58N) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/101.0.4951.54 Mobile Safari/537.36'
}

def InsertSensor():
  url = 'http://mlj.belajarobot.com/sensor/1'
  name_img = 'picture.png'
  img = open(name_img, 'rb')

  data = {
    'moist': 88,
    'lumen': 12874,
    'temp': 38,
    'humid': 72
  } 

  # files = {'image':img}
  files = {'image': (name_img,img,'images/png')}

  try:
    res = requests.post(url, data=data, files=files, headers=headers)
    print(res.text)
  except Exception as error:
    print(error)


def PostSensor():
  header = {}
  # header['Content-Type'] = 'application/x-www-form-urlencoded'
  header['Content-Type'] = 'application/application/json'
  url = 'https://mio.ptmdr.co.id/Themomi/uploadData'
  data = {
    'lokasi_id' : 2,
    'suhu' : 15,
    'Kelembaban' : 55,
  }
  try:
    # res = requests.post(url, data=data, headers=header)
    res = requests.post(url, data=data)
    print(res)
  except Exception as error:
    print(error)  


PostSensor()
# InsertSensor()