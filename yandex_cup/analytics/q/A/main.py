import datetime
import operator


class Session:
    def __init__(self, id, t):
        self.id = id
        self.t = t


f = open('log.csv', 'r')
session_count = 0
active_session = []
event_interval = []
max_event = 0
time_of_max_event = datetime.datetime(2000, 1, 1)
img_upload = {}
for line in f:
    columns = line.strip('\n').split(',')
    if columns[0] == 'date':
        continue
    user_id = int(columns[1])
    action_timestamp = datetime.datetime.strptime(columns[0], '%Y-%m-%d_%H:%M:%S')
    session_found = False
    for s in active_session:
        if s.id == user_id and (action_timestamp - s.t).total_seconds() < 1800:
            session_found = True
            s.t = action_timestamp
    if not session_found:
        if datetime.date(2020, 4, 11) == action_timestamp.date():
            session_count += 1
            active_session.append(Session(user_id, action_timestamp))
    active_session = [s for s in active_session if (action_timestamp - s.t).total_seconds() < 1800]
    param = columns[3]
    event = int(columns[2])
    if event == 3 and param == 'picture':
        if not action_timestamp.date() in img_upload:
            img_upload[action_timestamp.date()] = 0
        img_upload[action_timestamp.date()] += 1
    event_interval = [t for t in event_interval if (action_timestamp - t).total_seconds() < 600]
    event_interval.append(action_timestamp)
    if len(event_interval) >= max_event:
        max_event = len(event_interval)
        time_of_max_event = event_interval[0]

print("Session num = {}".format(session_count))
max_uploads = max(img_upload.items(), key=operator.itemgetter(1))
print("Max uploads = {}".format(max_uploads))
print("Max event {} in {}".format(max_event, time_of_max_event))