from random import randint

T = [10, 50, 100, 10000]


def test(tid, n):
    with open("tests%d.in" % tid, "w") as f:
        f.write("%d" % n)
        f.write("\n")
        for j in range(n):
            f.write("%d " % randint(1, 10000))
        f.write("\n")
        for j in range(n):
            f.write("%d " % randint(1, 10000))


for i, t in enumerate(T):
    test(i, t)
