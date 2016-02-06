

# /Applications/Flux.app/Contents/Frameworks/Sparkle.framework/Versions/A/Sparkle: Mach-O universal binary with 3 architectures
# /Applications/Flux.app/Contents/Frameworks/Sparkle.framework/Versions/A/Sparkle (for architecture ppc):Mach-O dynamically linked shared library ppc
# /Applications/Flux.app/Contents/Frameworks/Sparkle.framework/Versions/A/Sparkle (for architecture i386):Mach-O dynamically linked shared library i386
# /Applications/Flux.app/Contents/Frameworks/Sparkle.framework/Versions/A/Sparkle (for architecture x86_64):Mach-O 64-bit dynamically linked shared library x86_64


import os
import re
import subprocess
from sys import argv

import signal
import sys

typesdict = dict()

def signal_term_handler(signal, frame):
	print 'got SIGINT'

	sys.exit(0)


if __name__ == "__main__":
	signal.signal(signal.SIGINT, signal_term_handler)
	writefile = open("unknown", "w")
	for root, dirs, files in os.walk('/'):
	# for root, dirs, files in os.walk('/usr'):
	# for root, dirs, files in os.walk('/usr/lib/libATCommandStudio.a'):
		for file in files:
			fpath = "%s/%s" %(root, file)
			p1 = subprocess.Popen(['nm', fpath]
								 , stdout=subprocess.PIPE, stderr=subprocess.PIPE)
			out1, err1 = p1.communicate()
			p2 = subprocess.Popen(['./a.out', fpath]
								 , stdout=subprocess.PIPE, stderr=subprocess.PIPE)
			out2, err2 = p2.communicate()
			if len(out1) != 0 and len(out2) == 0:
			# if len(out) != 0:
				writefile.write("%s\n" %(fpath))
				writefile.flush()
				line =  out2.split('\n', 1)[0]

			# 	if (re.search("Mac", line) and line not in typesdict):
				print "'%s', '%s'" %(line, fpath)
			# 		typesdict[line] = fpath
