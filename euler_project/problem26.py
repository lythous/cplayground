d_max = 1;
len_max = 1;

for d in range(1, 1000):
    rs = []
    r = 10%d
    while True:
        rs.append(r)
        r = (r*10)%d
        if r in rs:
            if len(rs)>len_max:
                len_max = len(rs)
                d_max = d
            break

print(d_max)
print(len_max)
