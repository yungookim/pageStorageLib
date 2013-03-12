import sys
import re

if not sys.argv[1:]:
    print >>sys.stderr, "Usage: %s <bio file>"
    sys.exit(0)

filename = sys.argv[1]
name = None
bio = []

def clean(s):
    return re.sub(r'[^a-z ]+', '', s.lower()).strip()

with open(filename, 'r') as f:
    for line in f.xreadlines():
        if line.startswith('NM:'):
            if name and bio:
                print name
                print " ".join(bio)
            name = line[3:].strip()
            bio = []
        if line.startswith('BG:'):
            bio.append(clean(line[3:]))

if name and bio:
    print name
    print " ".join(bio)