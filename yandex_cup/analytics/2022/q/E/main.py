import math

class Gauss:
    def __init__(self, mu, sigma):
        self.mu = mu;
        self.sigma = sigma


def cdf(gauss, x):
    return 0.5 * (1 + math.erf((x - gauss.mu) / (math.sqrt(gauss.sigma * 2))))

def integral(gauss, a, b):
    return cdf(gauss, b) - cdf(gauss, a)

distr = [Gauss(150, 80), Gauss(310, 60), Gauss(450, 70), Gauss(550, 70), Gauss(730, 85), Gauss(900, 90)]

res = 0
for i in range(100, 901):
    j = i + 200
    while j <= 900:
        sq = 0
        for g in distr:
            sq += integral(g, i - 100, i + 100)
            sq += integral(g, j - 100, j + 100)
        if sq > res:
            print("Value = " + str(sq))
            print("{} {}".format(i, j))
            res = sq
        j = j + 1