def map(value, in_min, in_max, out_min, out_max):
    return int((value-in_min) * (out_max - out_min) / (in_max - in_min) + out_min)

value = map(20000,26500,6000,0,100)

string = "{}{}C".format(10,chr(176))
print(string)