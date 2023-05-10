import csv

kelembapan = "Sasti"
suhu = "Widyasari"

fieldnames = ['first_name', 'last_name']
data = {}
with open('names.csv', 'r', newline='') as csvfile:
    csv_reader = csv.reader(csvfile)
    rows = list(csv_reader)
    rows.append([kelembapan,suhu])
    with open('names.csv', 'w', newline='') as csvfile:
        fieldnames = ['first_name', 'last_name']
        writer = csv.DictWriter(csvfile, fieldnames=fieldnames)
        for row in rows:
            writer.writerow({'first_name': row[0], 'last_name': row[1]})