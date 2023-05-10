import telebot
import time
import smbus
import Adafruit_ADS1x15


adc = Adafruit_ADS1x15.ADS1115()
bot = telebot.TeleBot('5634329059:AAEYESfbrhVK47lNBFEaddfaRrH1oUhKXSE')
GAIN = 1

@bot.message_handler(commands=['start'])
def start(message):
    chatid = message.chat.id
    bot.send_message(chatid,'Selamat Datang')
    bot.send_message(chatid,'Command:\n/kondisi\n/photo')

@bot.message_handler(commands=['kondisi'])
def kondisi(message):
    readSHT()
    chatid = message.chat.id
    bot.send_message(chatid,'Suhu : {}{}C \nKelembapan Udara: {}% \nKelembapan Tanah: {}%'.format(int(cTemp),chr(176),int(humidity),int(soil())))

@bot.message_handler(commands=['photo'])
def photo(message):
    chatid = message.chat.id
    bot.send_photo(chatid,open('example.jpg','rb'))

def soil():
    return map(adc.read_adc(0, gain=GAIN),26500,6000,0,100)

def map(value, in_min, in_max, out_min, out_max):
    return int((value-in_min) * (out_max - out_min) / (in_max - in_min) + out_min)

def readSHT():
    global cTemp, fTemp, humidity
    try:
        # Get I2C bus
        bus = smbus.SMBus(1)
        bus.write_i2c_block_data(0x44, 0x2C, [0x06])  # Address 0x44
        time.sleep(0.5)
        data = bus.read_i2c_block_data(0x44, 0x00, 6)

        # Convert the data
        temp = data[0] * 256 + data[1]
        cTemp = -45 + (175 * temp / 65535.0)
        fTemp = -49 + (315 * temp / 65535.0)
        humidity = 100 * (data[3] * 256 + data[4]) / 65535.0

        # print("Temperature in Celsius is : %.2f C" % cTemp)
        # print("Temperature in Fahrenheit is : %.2f F" % fTemp)
        # print("Relative Humidity is : %.2f %%RH" % humidity)

    except:
        print("SHT error")


while True:
    try:
        bot.polling()
    except:
        pass        
