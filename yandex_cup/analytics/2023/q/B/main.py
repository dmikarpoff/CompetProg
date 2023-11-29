import csv
from datetime import datetime

class Rec:
  def __init__(self):
    self.vis = None
    self.pay = None
    
last_date = None

users = {}

with open('data.csv') as csv_file:
    csv_reader = csv.reader(csv_file, delimiter=',')
    cnt = 0
    for row in csv_reader:
      cnt += 1
      if cnt == 1:
        continue
      d = datetime.strptime(row[1], "%Y-%m-%d")
      if last_date is None or d > last_date:
        last_date = d
        
      if not (row[0] in users):
        users[row[0]] = Rec()
      if users[row[0]].vis is None or users[row[0]].vis > d:
        users[row[0]].vis = d
        
      if row[2] == 'True' and (users[row[0]].pay is None or users[row[0]].pay > d):
        users[row[0]].pay = d
        
cnt = 0
m = {}

print(last_date)

for i, rec in users.items():
  if rec.vis is None:
    print("Fuck !!!!")
  if rec.pay is None:
    continue
  if (rec.pay - rec.vis).days >= 90:
    continue
  cnt += 1
  fd = rec.vis.replace(day=1)
  if not (fd in m):
    m[fd] = 0
  m[fd] += 1
  
l = []
for a, b in m.items():
  l.append((a, b))
  
l.sort()
for (a, b) in l:
  x = a.strftime("%Y-%m-%d")
  print("{0},{1}".format(x, b))