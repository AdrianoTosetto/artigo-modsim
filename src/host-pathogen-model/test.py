import random
import math
import matplotlib.pyplot as plt

aliveCells = 3
totalSites = 100
sites = ( totalSites ) * [0]
aliveIndexes = random.sample(range(1, totalSites), aliveCells)

x = []
y = []

def sigmoid(number):
    return 1 / (1 + math.exp(-number))

for i in range(0, 8000):
    x.append(i)
    nextSites = sites
    for k in range(0, totalSites):
        if sites[k] == 0:
            prob = 100 * sigmoid(-i / 10000)
            #print(prob)
            draw = random.randint(0, 100)
            #print(draw)
            if draw <= prob:
                nextSites[k] = 1
        if sites[k] == 1:
            draw = random.randint(0, 100)
            if draw <= 4:
                nextSites[k] = 0
                pass
    aliveCells = len(list(filter(lambda site: site == 1, sites)))
    sites = nextSites
    y.append(aliveCells)

#print(x)    
#print(y)    

plt.plot(x, y)
plt.show()