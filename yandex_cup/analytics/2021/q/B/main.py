import re

users = {}

for i in range(1, 21):
    fname = f'feature_files\\feature_{i}.csv'
    with open(fname, 'r') as fdescr:
        for ln in fdescr.readlines():
            columns = ln.split(',')
            user_id = int(columns[0])
            feature = (columns[1] if len(columns) > 1 else '')
            if re.search(r'\d', feature):
                try:
                    users[user_id] += 1
                except KeyError:
                    users[user_id] = 1

count = 0
for k, v in users.items():
    if v >= 10:
        count += 1

print(count)