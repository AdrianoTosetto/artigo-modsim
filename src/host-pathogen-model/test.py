import random
import math
import time
import matplotlib.pyplot as plt

def mapRange(number):
    output_start = -5
    output_end = 5
    input_start = 0
    input_end = 10000
    output = output_start + ((output_end - output_start) / (input_end - input_start)) * (number - input_start)

    return output

aliveCells = 223
totalSites = 10000
sites = ( totalSites ) * [0]
aliveIndexes = random.sample(range(1, totalSites), aliveCells)

for i in range(0, aliveCells):
    sites[aliveIndexes[i]] = 1

x = []
y = []

def sigmoid(number):
    return 1 / (1 + math.exp(-number))

for i in range(0, 3000):
    x.append(i)
    aliveCells = len(list(filter(lambda site: site == 1, sites)))
    occupiedSpace = totalSites - aliveCells
    y.append(aliveCells)
    prob = 0

    nextSites = sites
    for k in range(0, totalSites):
        if sites[k] == 0:
            #prob = sigmoid(mapRange(aliveCells))
            newIndividuals = 0.005 * aliveCells * (1 - aliveCells / totalSites)
            emptySites = totalSites - aliveCells
            prob = newIndividuals / emptySites
            draw = random.uniform(0.0, 1.0)

            if draw <= prob:
                nextSites[k] = 1
        elif sites[k] == 1:
            draw = random.uniform(0.0, 1.0)
            if draw <= 0.0004:
                nextSites[k] = 0
                pass
    sites = nextSites

#print(x)
#print(y)

print(sigmoid(mapRange(6000)))

plt.plot(x, y)
plt.show()