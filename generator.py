import random

zakres = 10
n = 1000

poprzednia = 1

f = open("duzy_plik.txt", "w")
for i in range(1,n):
    nastepna = random.randint(1,zakres)
    f.write(f"({poprzednia}->{nastepna}: {random.randint(1,zakres)*1.0}), \n")
    poprzednia = nastepna
f.write(f"({poprzednia}->1: 1.0) \n")