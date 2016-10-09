import matplotlib.pyplot as plt
import numpy as np

plotValues = open("./DataSet1/plotValues.txt")
sensorValues = open("./DataSet1/heelStrikes.txt")
footFlat = open("./DataSet1/footflat.txt")
midSwing = open("./DataSet1/midSwing.txt")
footRaised = open("./DataSet1/footRaised.txt")
midStance = open("./DataSet1/midStance.txt")

zSensor = []
ySensor = []
gyroValsY = []
xAxis = []

xVals = []
yVals = []
zVals = []

flatX = []
flatY = []

midStanceX = []
midStanceY = []

footRaisedX=[]
footRaisedY=[]

midSwingX = []
midSwingY = []

a = 0
b = 0

count = 0

with plotValues as f:
    for line in f:
        a, b, c = line.split()
        zSensor.append(c)
        ySensor.append(b)
        gyroValsY.append(a)
        xAxis.append(count)
        count = count+1
        

plt.plot(xAxis, zSensor, label="Z Values")
plt.plot(xAxis, ySensor, label="Y Values")
plt.plot(xAxis, gyroValsY)

with sensorValues as f:
    for line in f:
        a, b, c = line.split()
        xVals.append(a)
        yVals.append(b)
        zVals.append(c)

plt.scatter(xVals, yVals, marker='o', s=100, c='red', alpha=.5, label='Y HeelStrike Avg Value')
plt.scatter(xVals, zVals, marker='o', s=100, c='yellow', alpha=.5, label='Z HeelStrike Avg Value')

with midStance as f:
    for line in f:
        a, b = line.split()
        midStanceX.append(a)
        midStanceY.append(b)

plt.scatter(midStanceX, midStanceY, marker='+', s =100, c='grey', label='Midstance Region')

with footFlat as f:
    for line in f:
        a, b = line.split()
        flatX.append(a)
        flatY.append(b)

plt.scatter(flatX, flatY, marker='+', s =100, c='purple', label='Foot Flat Regions')

with footRaised as f:
    for line in f:
        a, b = line.split()
        footRaisedX.append(a)
        footRaisedY.append(b)

plt.scatter(footRaisedX, footRaisedY, marker=',', s=100, c='yellow', alpha=.5, label='Z FootRaised Avg Value')

with midSwing as f:
    for line in f:
        a, b = line.split()
        midSwingX.append(a)
        midSwingY.append(b)

plt.scatter(midSwingX, midSwingY, marker='+', s =100, c='orange', label='Midswing Regions')

plt.grid()

legend = plt.legend(loc='upper right', shadow=True)

# The frame is matplotlib.patches.Rectangle instance surrounding the legend.
frame = legend.get_frame()
frame.set_facecolor('0.90')

# Set the fontsize
for label in legend.get_texts():
    label.set_fontsize('small')

for label in legend.get_lines():
    label.set_linewidth(1.5)  # the legend line width

plt.show()

