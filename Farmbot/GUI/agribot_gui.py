from logging import exception
from time import sleep, time
import tkinter.font
from wsgiref import headers
import requests
import cv2
import os
import urllib.request
from datetime import datetime
from serial import Serial
from tkinter import *
from tkinter import ttk
from tkinter import messagebox as msg
from threading import *
from gtexttospeech import TextToSpeech
from getData import DataArduino, GetData, query

"""""
SETUP
"""""

Farmbot = '1'   

serialPort = "/dev/ttyACM0"
# serialPort = "/dev/ttyUSB0"

path = os.path.dirname(os.path.abspath(__file__))
baudRate = 9600
print(path)

# path = '/home/pi/Documents/Farmbot/'
# path = ''

try:  
  ser = Serial(serialPort, baudRate, timeout=0, writeTimeout=0)
except:
  print('Serial Not Available')  

camPort = 1


"""""
SETUP
"""""

url_get = 'http://farmbot.belajarobot.com/farm/bot/' + Farmbot
url_post  = 'http://farmbot.belajarobot.com/sensor/' + Farmbot

headers = {
  'user-agent': 'Mozilla/5.0 (Linux; Android 6.0; Nexus 5 Build/MRA58N) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/101.0.4951.54 Mobile Safari/537.36'
}

root = Tk()
changefont = tkinter.font.Font(font="montserrat_bold", size=18)
textfont = tkinter.font.Font(font="montserrat_bold", size=14)
root.title("Agribot")
root.geometry("800x480")
root.attributes('-zoomed', False)

# dynamic variable
suhu = StringVar()
kelembapan = StringVar()
intensitas = StringVar()
kelembapan_tanah = StringVar()
internet_status = StringVar()
serBuffer = ''
state = False
laststate = False
imgAvailable = False

frame1 = Frame(root)
frame2 = Frame(root)

frame1.grid(row=0, column=0, sticky='nsew')
frame2.grid(row=0, column=0, sticky='nsew')

# ========================FRAME 1================================
bckg = PhotoImage(file=path + "/window 1/background2.png")
lbl_bg = Label(frame1, image=bckg).pack()

btnext = PhotoImage(file=path + "/window 1/next.png")
lbl_btnext = Button(frame1, image=btnext, background='#FFFFFF',
                    command=lambda:[showframe(frame2), UpdateTanaman()])
lbl_btnext.place(x=757, y=197)

# dynamic label untuk diisi dari data serial
l_suhu = Label(frame1, text='', textvariable=suhu,
               font=changefont, bg='#C6E9FC').place(x=640, y=156)
l_kelembapan = Label(frame1, text='', textvariable=kelembapan,
                     font=changefont, bg='#F2F2F2').place(x=640, y=214)
l_intensitas = Label(frame1, text='', textvariable=intensitas,
                     font=textfont, bg='#C6E9FC').place(x=640, y=272)
l_kelembapan_tanah = Label(frame1, text='', textvariable=kelembapan_tanah,
                           font=textfont, bg='#F2F2F2').place(x=640, y=328)
l_internet_status = Label(frame1, text='', textvariable=internet_status,
                           font=textfont, bg='#C6E9FC').place(x=550, y=386)

# dynamic image untuk dirubah dari data serial
img = PhotoImage(file=path + "/emoji/1.png")
lbl_img = ttk.Label(frame1, image=img, background='#FFFFFF')
lbl_img.place(x=35, y=115)


# ========================FRAME 2================================
bckg2 = PhotoImage(file=path + "/window 2/bg.png")
lbl_bg2 = Label(frame2, image=bckg2).pack()

btnext2 = PhotoImage(file=path + "/window 2/back.png")
lbl_btnext2 = Button(frame2, image=btnext2,
                     background='#FFFFFF', command=lambda: showframe(frame1))
lbl_btnext2.place(x=43, y=20)

# # source image untuk pot
planted = PhotoImage(file=path + "/window 2/planted.png")
unplanted = PhotoImage(file=path + "/window 2/empty.png")

# static image. pot baris 1 (p11-p16)
p11 = Label(frame2, image=unplanted, background='#FFFFFF')
p11.place(x=117, y=32)
p12 = Label(frame2, image=unplanted, background='#FFFFFF')
p12.place(x=225, y=32)
p13 = Label(frame2, image=unplanted, background='#FFFFFF')
p13.place(x=333, y=32)
p14 = Label(frame2, image=unplanted, background='#FFFFFF')
p14.place(x=441, y=32)
p15 = Label(frame2, image=unplanted, background='#FFFFFF')
p15.place(x=549, y=32)
p16 = Label(frame2, image=unplanted, background='#FFFFFF')
p16.place(x=657, y=32)
# static image. pot baris 1 (p21-p26)
p21 = Label(frame2, image=unplanted, background='#FFFFFF')
p21.place(x=117, y=134)
p22 = Label(frame2, image=unplanted, background='#FFFFFF')
p22.place(x=225, y=134)
p23 = Label(frame2, image=unplanted, background='#FFFFFF')
p23.place(x=333, y=134)
p24 = Label(frame2, image=unplanted, background='#FFFFFF')
p24.place(x=441, y=134)
p25 = Label(frame2, image=unplanted, background='#FFFFFF')
p25.place(x=549, y=134)
p26 = Label(frame2, image=unplanted, background='#FFFFFF')
p26.place(x=657, y=134)
# static image. pot baris 1 (p31-p36)
p31 = Label(frame2, image=unplanted, background='#FFFFFF')
p31.place(x=117, y=236)
p32 = Label(frame2, image=unplanted, background='#FFFFFF')
p32.place(x=225, y=236)
p33 = Label(frame2, image=unplanted, background='#FFFFFF')
p33.place(x=333, y=236)
p34 = Label(frame2, image=unplanted, background='#FFFFFF')
p34.place(x=441, y=236)
p35 = Label(frame2, image=unplanted, background='#FFFFFF')
p35.place(x=549, y=236)
p36 = Label(frame2, image=unplanted, background='#FFFFFF')
p36.place(x=657, y=236)
# static image. pot baris 1 (p41-p46)
p41 = Label(frame2, image=unplanted, background='#FFFFFF')
p41.place(x=117, y=338)
p42 = Label(frame2, image=unplanted, background='#FFFFFF')
p42.place(x=225, y=338)
p43 = Label(frame2, image=unplanted, background='#FFFFFF')
p43.place(x=333, y=338)
p44 = Label(frame2, image=unplanted, background='#FFFFFF')
p44.place(x=441, y=338)
p45 = Label(frame2, image=unplanted, background='#FFFFFF')
p45.place(x=549, y=338)
p46 = Label(frame2, image=unplanted, background='#FFFFFF')
p46.place(x=657, y=338)


# # static label. text baris 1 (t11-t16)
t11 = Label(frame2, text='-', justify=CENTER, font=changefont,bg="#FFFFFF")
t11.place(x=159, y=122, anchor=CENTER)
t12 = Label(frame2, text='-', justify=CENTER, font=changefont,bg="#FFFFFF")
t12.place(x=267, y=122, anchor=CENTER)
t13 = Label(frame2, text='-', justify=CENTER, font=changefont,bg="#FFFFFF")
t13.place(x=375, y=122, anchor=CENTER)
t14 = Label(frame2, text='-', justify=CENTER, font=changefont,bg="#FFFFFF")
t14.place(x=483, y=122, anchor=CENTER)
t15 = Label(frame2, text='-', justify=CENTER, font=changefont,bg="#FFFFFF")
t15.place(x=591, y=122, anchor=CENTER)
t16 = Label(frame2, text='-', justify=CENTER, font=changefont,bg="#FFFFFF")
t16.place(x=699, y=122, anchor=CENTER)
# static label. text baris 1 (t21-t26)
t21 = Label(frame2, text='-', justify=CENTER, font=changefont,bg="#FFFFFF")
t21.place(x=159, y=224, anchor=CENTER)
t22 = Label(frame2, text='-', justify=CENTER, font=changefont,bg="#FFFFFF")
t22.place(x=267, y=224, anchor=CENTER)
t23 = Label(frame2, text='-', justify=CENTER, font=changefont,bg="#FFFFFF")
t23.place(x=375, y=224, anchor=CENTER)
t24 = Label(frame2, text='-', justify=CENTER, font=changefont,bg="#FFFFFF")
t24.place(x=483, y=224, anchor=CENTER)
t25 = Label(frame2, text='-', justify=CENTER, font=changefont,bg="#FFFFFF")
t25.place(x=591, y=224, anchor=CENTER)
t26 = Label(frame2, text='-', justify=CENTER, font=changefont,bg="#FFFFFF")
t26.place(x=699, y=224, anchor=CENTER)
# static label. text baris 1 (t31-t36)
t31 = Label(frame2, text='-', justify=CENTER, font=changefont,bg="#FFFFFF")
t31.place(x=159, y=326, anchor=CENTER)
t32 = Label(frame2, text='-', justify=CENTER, font=changefont,bg="#FFFFFF")
t32.place(x=267, y=326, anchor=CENTER)
t33 = Label(frame2, text='-', justify=CENTER, font=changefont,bg="#FFFFFF")
t33.place(x=375, y=326, anchor=CENTER)
t34 = Label(frame2, text='-', justify=CENTER, font=changefont,bg="#FFFFFF")
t34.place(x=483, y=326, anchor=CENTER)
t35 = Label(frame2, text='-', justify=CENTER, font=changefont,bg="#FFFFFF")
t35.place(x=591, y=326, anchor=CENTER)
t36 = Label(frame2, text='-', justify=CENTER, font=changefont,bg="#FFFFFF")
t36.place(x=699, y=326, anchor=CENTER)
# static label. text baris 1 (t41-t46)
t41 = Label(frame2, text='-', justify=CENTER, font=changefont,bg="#FFFFFF")
t41.place(x=159, y=428, anchor=CENTER)
t42 = Label(frame2, text='-', justify=CENTER, font=changefont,bg="#FFFFFF")
t42.place(x=267, y=428, anchor=CENTER)
t43 = Label(frame2, text='-', justify=CENTER, font=changefont,bg="#FFFFFF")
t43.place(x=375, y=428, anchor=CENTER)
t44 = Label(frame2, text='-', justify=CENTER, font=changefont,bg="#FFFFFF")
t44.place(x=483, y=428, anchor=CENTER)
t45 = Label(frame2, text='-', justify=CENTER, font=changefont,bg="#FFFFFF")
t45.place(x=591, y=428, anchor=CENTER)
t46 = Label(frame2, text='-', justify=CENTER, font=changefont,bg="#FFFFFF")
t46.place(x=699, y=428, anchor=CENTER)


# =========================SERIAL DATA PROCESS===================

def readSerial():
    while True:
        c = ser.read()
        if len(c) == 0:
            break

        global serBuffer
        global p_status, p_suhu, p_kelembapan, p_kelembapan_tanah, p_intensitas

        if c == '\r':
            c = ''

        if c == b'\n':
            serBuffer += "\n"
            print(serBuffer)

            nA = serBuffer.index('A')
            nB = serBuffer.index('B')
            nC = serBuffer.index('C')
            nD = serBuffer.index('D')
            nE = serBuffer.index('E')
            nF = serBuffer.index('F')

            p_status = serBuffer[nA+1:nB]
            p_suhu = serBuffer[nB+1:nC]
            p_kelembapan = serBuffer[nC+1:nD]
            p_intensitas = serBuffer[nD+1:nE]
            p_kelembapan_tanah = serBuffer[nE+1:nF]

            # isi dynamic variable
            suhu.set(p_suhu)
            kelembapan.set(p_kelembapan)
            intensitas.set(Lumenlvl(p_intensitas))
            kelembapan_tanah.set(Humlvl(p_kelembapan_tanah))


            # ubah dynamic image
            img = PhotoImage(file=path + "/emoji/" + p_status + ".png")

            lbl_img.configure(image=img)
            lbl_img.image = img

            serBuffer = ""
        else:
            serBuffer += c.decode("utf-8")

    lbl_img.bind("<Button-1>", playsound)        
    root.after(200, readSerial)

def playsound(event):
    if connect():
      TextToSpeech(p_suhu,p_intensitas,p_kelembapan,p_kelembapan_tanah, path)
      print("Clicked at : ", event.x, event.y)

def showframe(frame):
    frame.tkraise()

def CheckTanaman(kolom,baris,data):
  try:
    Tanaman = {
      "id" : "",
      "nama" : "",
    }
    data = GetData(kolom,baris,data)
    data.save()
    if data.plant_id != "0":
      Tanaman['id'] = planted
      Tanaman['nama'] = data.plant_name
    else:
      Tanaman['id'] = unplanted
      Tanaman['nama'] = "Kosong"
    return Tanaman  
  except:
    print("gagal check Tanaman")

def UpdateTanaman():
  global p11,p12,p13,p14,p15,p16,p21,p22,p23,p24,p25,p26,p31,p31,p32,p33,p34,p35,p36,p41,p42,p43,p44,p45,p46
  global t11,t12,t13,t14,t15,t16,t21,t22,t23,t24,t25,t26,t31,t31,t32,t33,t34,t35,t36,t41,t42,t43,t44,t45,t46
  global frame2

  try:
    p11.config(image=G11['id'])
    t11.config(text = "")
    t11.config(text=G11['nama'])
    p12.config(image=G12['id'])
    t12.config(text = "")
    t12.config(text=G12['nama'])
    p13.config(image=G13['id'])
    t13.config(text = "")
    t13.config(text=G13['nama'])
    p14.config(image=G14['id'])
    t14.config(text = "")
    t14.config(text=G14['nama'])
    p15.config(image=G15['id'])
    t15.config(text = "")
    t15.config(text=G15['nama'])
    p16.config(image=G16['id'])
    t16.config(text = "")
    t16.config(text=G16['nama'])

    p21.config(image=G21['id'])
    t21.config(text = "")
    t21.config(text=G21['nama'])
    p22.config(image=G22['id'])
    t22.config(text = "")
    t22.config(text=G22['nama'])
    p23.config(image=G23['id'])
    t23.config(text = "")
    t23.config(text=G23['nama'])
    p24.config(image=G24['id'])
    t24.config(text = "")
    t24.config(text=G24['nama'])
    p25.config(image=G25['id'])
    t25.config(text = "")
    t25.config(text=G25['nama'])
    p26.config(image=G26['id'])
    t26.config(text = "")
    t26.config(text=G26['nama'])

    p31.config(image=G31['id'])
    t31.config(text = "")
    t31.config(text=G31['nama'])
    p32.config(image=G32['id'])
    t32.config(text = "")
    t32.config(text=G32['nama'])
    p33.config(image=G33['id'])
    t33.config(text = "")
    t33.config(text=G33['nama'])
    p34.config(image=G34['id'])
    t34.config(text = "")
    t34.config(text=G34['nama'])
    p35.config(image=G35['id'])
    t35.config(text = "")
    t35.config(text=G35['nama'])
    p36.config(image=G36['id'])
    t36.config(text = "")
    t36.config(text=G36['nama'])

    p41.config(image=G41['id'])
    t41.config(text = "")
    t41.config(text=G41['nama'])
    p42.config(image=G42['id'])
    t42.config(text = "")
    t42.config(text=G42['nama'])
    p43.config(image=G43['id'])
    t43.config(text = "")
    t43.config(text=G43['nama'])
    p44.config(image=G44['id'])
    t44.config(text = "")
    t44.config(text=G44['nama'])
    p45.config(image=G45['id'])
    t45.config(text = "")
    t45.config(text=G45['nama'])
    p46.config(image=G46['id'])
    t46.config(text = "")
    t46.config(text=G46['nama'])
  except:
    print("failde Update Frame Tanaman")  
  
def GetDatabase(data):
  global G11,G12,G13,G14,G15,G16,G21,G22,G23,G24,G25,G26,G31,G31,G32,G33,G34,G35,G36,G41,G42,G43,G44,G45,G46
  G11 = CheckTanaman(1,1,data)
  G12 = CheckTanaman(1,2,data)
  G13 = CheckTanaman(1,3,data)
  G14 = CheckTanaman(1,4,data)
  G15 = CheckTanaman(1,5,data)
  G16 = CheckTanaman(1,6,data)

  G21 = CheckTanaman(2,1,data)
  G22 = CheckTanaman(2,2,data)
  G23 = CheckTanaman(2,3,data)
  G24 = CheckTanaman(2,4,data)
  G25 = CheckTanaman(2,5,data)
  G26 = CheckTanaman(2,6,data)

  G31 = CheckTanaman(3,1,data)
  G32 = CheckTanaman(3,2,data)
  G33 = CheckTanaman(3,3,data)
  G34 = CheckTanaman(3,4,data)
  G35 = CheckTanaman(3,5,data)
  G36 = CheckTanaman(3,6,data)

  G41 = CheckTanaman(4,1,data)
  G42 = CheckTanaman(4,2,data)
  G43 = CheckTanaman(4,3,data)
  G44 = CheckTanaman(4,4,data)
  G45 = CheckTanaman(4,5,data)
  G46 = CheckTanaman(4,6,data)



def captureImage():
  global imgAvailable
  try:
    cap = cv2.VideoCapture(camPort)
    result, image = cap.read()
    if result:
        imgAvailable = True
        cv2.imwrite(path + "picture.png", image)
        cap.release()
    else:
        imgAvailable = False
        print("No image detected. Please! try again")   
  except:
    print("check Camera")


def SendSerial():
  try:
    getData = query(url_get,headers)
    GetDatabase(getData)
    if(updateParameter(6,30) or updateParameter(14,15)):
      ser.write(bytes('stop','utf-8'))
      sleep(3)
      Data = '*' + DataArduino(getData) + '#'
      ser.write(bytes(Data,'utf-8'))
      print(Data)
      print('Updated')

    if not connect():
      print('failed post databases')    

  except Exception as error:
    print('failed post databases')        

def updateSerial():
  try:
    ser.write(bytes('stop','utf-8'))
    sleep(1)
    status = msg.askyesno('Update', 'Tanaman Akan Di Update') 
    if status:
      getData = query(url_get,headers)
      GetDatabase(getData)
      Data = '*' + DataArduino(getData) + '#'
      ser.write(bytes(Data,'utf-8'))
      print(Data)
    else:
      ser.write(bytes('lanjut','utf-8'))
      msg.showinfo('update', 'update canceled')
  except:
    ser.write(bytes('lanjut','utf-8'))
    print('failed Update Serial')

def UpdateDatabase():
  captureImage()
  try:

    if imgAvailable:
      name_img = path + 'picture.png'
    else:
      name_img = path + 'noImage.jpeg'

    img = open(name_img, 'rb')
    data = {
      'moist': p_kelembapan_tanah,
      'lumen': p_intensitas,
      'temp': p_suhu,
      'humid': p_kelembapan,
    }
    files = {'image': (name_img,img,'images/png')}

    res = requests.post(url_post, data=data, files=files, headers=headers)
    print(res.text) 

  except Exception as error:
    print("Update Database Error")

def Lumenlvl(param):
  switcher = {
    '1' : 'Low',
    '2' : 'Medium',
    '3' : 'High',
    '4' : 'Direct Sun'  
  }

  return switcher.get(param,'nothing')

def Humlvl(param):
  switcher = {
    '1' : 'Dry',
    '2' : 'Slight Wet',
    '3' : 'Moist',
    '4' : 'Very Moist',
    '5' : 'Soaked' 
  }
  return switcher.get(param,'nothing')


def updateParameter(hours, minutes,):   

    global state
    global laststate

    minute = int (datetime.now().strftime('%M'))
    hour = int (datetime.now().strftime('%H'))

    if minute == minutes and hour == hours:
        state = True
    else:
        state = laststate = False

    if state != laststate:
        laststate = state 
        return True 

    return False

def connect(host = 'http://google.com'):
    try:
        urllib.request.urlopen(host)
        return True
    except:
        return False  

def statusInternet():
  if connect():
    internet_status.set("Internet Connected")
  else:
    internet_status.set("Internet Disconnect")

  root.after(1000,statusInternet) 

    

def thread_get():
  t1 = Thread(target=SendSerial)
  t1.start()
  root.after(60000, thread_get)

def thread_post():
  t1 = Thread(target=UpdateDatabase)
  t1.start()
  root.after(60000, thread_post)


# Button Update
btnUpdate = Button(frame1,text='Update Data',background='#FFFFFF',
            borderwidth=2,command= updateSerial)
btnUpdate.place(x=400, y=384)

# 30 menit = 600.000 ms
showframe(frame1)

# First Update Frame Tanaman
try:
  getData = query(url_get,headers)
  GetDatabase(getData)
except Exception as error:
  print('internet not connected')

root.after(200, readSerial)
root.after(1000,statusInternet)
root.after(60000, thread_get)
root.after(60000, thread_post)
root.mainloop()
