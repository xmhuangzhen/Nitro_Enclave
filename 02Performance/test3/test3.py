import time

while True:
    ans = 0
    startTime = time.time()
    for i in range(1,10000):
        for j in range(1,10000):
            ans = ans+1
    endTime = time.time()
    print(endTime - startTime)