import csv

headers = ['4','8','16','32','64','128','256','512','1024','2048','4096','8192','16384','32768','65536']
runs = {h: [] for h in headers}

with open('worst.csv') as f:
    r = csv.reader(f)
    for row in r:
        runs[row[0]].append((row[1], row[2]))

print('metric,' + ','.join(headers))
for i in range(len(next(iter(runs.values())))):
    cycles = [runs[h][i][0] for h in headers]
    rates = [runs[h][i][1] for h in headers]
    print('cycles,' + ','.join(cycles))
    print('rate,' + ','.join(rates))

with open('worst_out.csv', 'w', newline='') as out:
    w = csv.writer(out)
    w.writerow(headers)
    for i in range(len(next(iter(runs.values())))):
        w.writerow([runs[h][i][0] for h in headers])
        w.writerow([runs[h][i][1] for h in headers])
