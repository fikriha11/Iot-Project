
# Importing tkinter module
from tkinter import * 
from tkinter import messagebox as msg      
 

def callback():
    print('Akan Di update')
    status = msg.askyesno('Update', 'Tanaman Akan Di Update')
    if status:
        print('oke')


# Creating a tkinter window
root = Tk()
 
# Initialize tkinter window with dimensions 300 x 250            
root.geometry('300x250')    
 

btnUpdate = Button(root,text='Update',command = callback)
btnUpdate.place(x=200, y=20)
 
root.mainloop()