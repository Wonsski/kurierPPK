import random

zakres = 10
n = 300

poprzednia = 1

f = open("duzy_plik.txt", "w")
for i in range(1,n):
    klientB = random.randint(1,zakres)
    klientA = random.randint(1,zakres)

    czyJednokierunkowa = random.randint(1,zakres)%2==0

    if czyJednokierunkowa:
        f.write(f"({klientA}->{klientB}: {random.randint(1,zakres)*1.0}), \n")
    else:
        f.write(f"({klientA}-{klientB}: {random.randint(1,zakres)*1.0}), \n")