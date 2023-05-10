from datetime import datetime as dt
from gtts import gTTS
import time
import os


def waktu():
    if dt.now().hour > 5 and dt.now().hour <= 10:
        waktu = "Pagi"
    elif dt.now().hour > 10 and dt.now().hour <= 14:
        waktu = "Siang"
    elif dt.now().hour > 14 and dt.now().hour < 17:
        waktu = "Soree"
    else:
        waktu = "Datang"

    return waktu

def lvlKelembaban(param):
    switcher = {
    '1' : 'Kering',
    '2' : 'Agak Lembab',
    '3' : 'Lembab',
    '4' : 'Sangat Lembab',
    '5' : 'Basah' 
     }
    return switcher.get(param,'nothing')

def lvlIntensitas(param):
    switcher = {
    '1' : 'Rendah',
    '2' : 'Medium',
    '3' : 'Terang',
    '4' : 'Sangat Terang'
     }
    return switcher.get(param,'nothing')

def TextToSpeech(cTemp, lux, humidity, moisture, path):
    try:
        phrase = "Selamat {}, Kondisi Suhu saat ini adalah {} derajat Celcius, Dan kelembapan Udara sebesar {} Persen, Kelembapan Tanah {}.".format(waktu(), int(cTemp), int(humidity), lvlKelembaban(moisture))     
        phrase1 = "Untuk Keterangan Cahaya {} , Terima Kasih".format(lvlIntensitas(lux))
        language = 'id'
    
        output = gTTS(text=phrase + phrase1, lang=language, slow=False)
        output.save(path + "GUI/temp.mp3")
        time.sleep(0.4)
        os.system("mpg123 {}GUI/temp.mp3".format(path))
        return True
    except:
        print("SoundOutput Error")