import random, sys
seed = int(sys.argv[1])
binCapacity = int(sys.argv[2])
itemsRange = int(sys.argv[3])
numberOfItems = int(sys.argv[4])
random.seed(seed)

print numberOfItems
print binCapacity
for i in range(1,numberOfItems+1):
    print random.randint(1,itemsRange)
