print("Введите коэффициенты переменных: ")
k1 = int(input("x = "))
k2 = int(input("y = "))
k3 = int(input("C = "))
n = 1
dots = {k3: {}}
_ = 0
while _ < len(dots):
    l = list(dots.keys())[_]
    for i in 0, 1:
        for j in 0, 1:
            left_fr = bin(abs(k1 * i + k2 * j))[2:-1]
            left_re = bin(abs(l))[2:-1]
            if left_fr == "":
                left_fr = "0"
            if left_re == "":
                left_re = "0"
            if k1 * i + k2 * j < 0:
                if l < 0:
                    right = -1 * int(bin(abs(k1 * i + k2 * j))[-1], 2) + -1 * int(bin(abs(l))[-1], 2)
                    left = -1 * int(left_fr, 2) + -1 * int(left_re, 2)
                else:
                    right = -1 * int(bin(abs(k1 * i + k2 * j))[-1], 2) + int(bin(abs(l))[-1], 2)
                    left = -1 * int(left_fr, 2) + int(left_re, 2)
            else:
                if l < 0:
                    right = int(bin(abs(k1 * i + k2 * j))[-1], 2) + -1 * int(bin(abs(l))[-1], 2)
                    left = int(left_fr, 2) + -1 * int(left_re, 2)
                else:
                    right = int(bin(abs(k1 * i + k2 * j))[-1], 2) + int(bin(abs(l))[-1], 2)
                    left = int(left_fr, 2) + int(left_re, 2)
            if right >= 2:
                left += 1
                right -= 2
            if right == -1 or right == -2:
                left -= 1
                right += 2
            if left not in dots.keys():
                dots[left] = {}
            if left in dots[l].keys():
                dots[l][left].append(str(i) + str(j) + ":" + str(right))
            else:
                dots[l][left] = [str(i) + str(j) + ":" + str(right)]
    _ += 1

i = 0
all_keys = []
print("\nВсе состояния:")
for key0, d0 in dots.items():
    all_keys.append(key0)
    if key0 < 0:
        key0 = "-" + bin(key0)[3:]
    else:
        key0 = "+" + bin(key0)[2:]
    print(f"q{i}({key0}) ", end = " ")
    i += 1
print()
i = 0
for key0, d0 in dots.items():
    if key0 < 0:
        key0 = "-" + bin(key0)[3:]
    else:
        key0 = "+" + bin(key0)[2:]
    print(f"\nИз состояния q{i}({key0}) в")
    for key1, value in d0.items():
        index = all_keys.index(key1)
        if key1 < 0:
            key1 = "-" + bin(key1)[3:]
        else:
            key1 = "+" + bin(key1)[2:]
        print(f"q{index}({key1}): ", end = "")
        [print(_, end="\t") for _ in value]
        print()
    i += 1