import csv
import matplotlib.pyplot as plt
import turtle
import math

line = []

with open('path.csv') as csv_file:
    csv_reader = csv.reader(csv_file, delimiter=',')
    cnt = 0
    for row in csv_reader:
      cnt += 1
      if cnt == 1:
        continue
      if cnt == 9:
        continue
      if cnt == 22 or cnt == 23 or cnt == 24:
        continue
      if cnt == 29:
        continue
      if cnt == 47:
         continue
      if cnt == 75:
        continue
      line.append((float(row[0]), float(row[1])))

l = 0.0
for i in range(0, len(line) - 1):
  x0, y0 = line[i]
  x1, y1 = line[i + 1]
  d = math.sqrt((x1 - x0) ** 2 + (y1 - y0) ** 2)
  j = i + 2
  print(f"{i}: {d}")
  l += d
print(l)

turtle.screensize(1800, 600)
turtle.penup()
turtle.goto((0.0, 0.0))

turtle.pendown()

x0, y0 = line[0]

for x, y in line:
  turtle.goto((x - x0, y - y0))

turtle.hideturtle()
turtle.exitonclick()