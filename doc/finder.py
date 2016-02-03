

import os
import re
import subprocess


value = "[0-9a-f\s]*"

typeparent = "(\(.*\))"

info1 = "(\[[^\]]*\]|\s*)"

linkage = "(external|non\-external|weak external|non-external \(was a private external\))"

identchars = "[_0-9a-zA-Z\.\$]"
normalsymbol = identchars + "+"
objcsymbol = identchars + "*" + "[\+\-]\[.*\]" + identchars + "*"
symbol = "(" + objcsymbol + "|" + normalsymbol + ")"

where = "\s*(\([^)]*\)|\s*)"

pattern = value+typeparent+"\s*"+info1+"\s*"+linkage+"\s*"+symbol+where+"$"

if __name__ == "__main__":

	for root, dirs, files in os.walk("/usr/bin"):
		path = root.split('/')
		# print root
		# print dirs
		# print files
		# print path, 'lol'
		# print (len(path) - 1) *'---' , os.path.basename(root)
		for file in files:
			fpath = "%s/%s" %(root, file)
			p = subprocess.Popen(['nm', '-m', fpath]
								 , stdout=subprocess.PIPE, stderr=subprocess.PIPE)
			out, err = p.communicate()
			if len(out) == 0 and len(err) == 0:
				continue
			print fpath, "------->"
			if len(err) != 0:
				print err
				if re.match(".*Permission denied.*", err) != None:
					continue
				assert(len(err) == 0)
			lines = out.splitlines()
			# print pattern
			for line in lines:
				if len(line) == 0 or re.match("^(.*)\:$", line, re.M) != None:
					continue
				grps = re.match(pattern, line, re.M)
				print "line: \"%s\"" %(line)
				if grps == None:
					# print re.match(value+typeparent+"\s*"+info1+"\s*"+linkage+"\s*"+symbol+where+"$", line, re.M)
					print grps
					print "failed in: ", fpath
					assert(False)
				# print "0:", grps.group(0)
				# print "1:", grps.group(1)
				# print "2:", grps.group(2)
				# print "3:", grps.group(3)
				# print "4:", grps.group(4)
				# print "5:", grps.group(5)
				# print "truc:", grps.start(), grps.end()
					# print 'truc:', i
					# print grps.group(i)

				# print "MATCHKLOL"
				# print grps
				# assert(False)

			# print "%s/%s" %(root, file)
			# print len(path)*'---', file
