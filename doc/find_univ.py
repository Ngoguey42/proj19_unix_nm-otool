

import re
import os
import subprocess

if __name__ == "__main__":
	nlinesSet = set()
	fatsStream = open("fats.sh", "a")
	for root, dirs, files in os.walk('/usr'):
		for file in files:
			path = "%s/%s" %(root, file)
			p1 = subprocess.Popen(['file', path]
								  , stdout=subprocess.PIPE, stderr=subprocess.PIPE)
			out1, err1 = p1.communicate()
			if (re.search("universal binary", out1) != None):
				lines =  out1.split('\n')
				nlines = len(lines)
				if nlines not in nlinesSet:
					# nlinesSet.add(nlines)
					print path
					fatsStream.write("file '" + str(path) + "'\n")
					fatsStream.flush()

	fatsStream.close()
