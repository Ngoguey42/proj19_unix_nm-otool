# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    finder.py                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/02/03 23:07:20 by ngoguey           #+#    #+#              #
#    Updated: 2016/02/04 00:46:52 by ngoguey          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import os
import re
import subprocess

value = "[0-9a-f\s]*"

typeparen = "\([^()]+\)"

linkage = """\
private external|\
\(alignment \d+\^\d+\) external|\
external|\
non\-external|\
weak external|\
weak private external|\
weak external automatically hidden|\
non\-external \[no dead strip\]|\
non\-external \(was a private external\)|\
\[referenced dynamically\] external \[no dead strip\]|\
external \[no dead strip\]|\
\[referenced dynamically\] external"""

identchars = "[_0-9a-zA-Z\.\$\:]"
identcharsparen = "[()_0-9a-zA-Z\.\$\:]"
normalsymbol = identchars + "+"
objcsymbol = identchars+"*" + "[\+\-\]\["+identcharsparen+"* "+identchars+"*\]" + identchars+"*"
symbol = objcsymbol + "|" + normalsymbol

where = "\([^()]+\)|\s*"

pattern = "^"+value+"("+typeparen+")\s*("+linkage+")\s*("+symbol+")\s*("+where+")$"

if __name__ == "__main__":

	# line = "00002fc0 (__TEXT,__text) non-external +[SSAudioDeviceCenter initialize]"
	# grps = re.search(pattern, line)
	# print grps

	# print grps.group(1)
	# print grps.group(2)
	# print grps.group(3)
	# print grps.group(4)

	# print
	# assert(False)


	typeSet = set() # group(1)
	linkageSet = set() # group(2)
	# whereSet = set() # group(4)
	comboDict = dict() # k=type+linkage+where v=filepath+line
	typeFile = open("types", "wa")
	linkageFile = open("linkages", "wa")
	# for root, dirs, files in os.walk("/usr/share"):
	# for root, dirs, files in os.walk("/nfs/zfs-student-4/users/ngoguey"):
	# for root, dirs, files in os.walk("/nfs/zfs-student-4/users/ngoguey/.brew"):
	for root, dirs, files in os.walk("/usr"):
		path = root.split('/')
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
				elif re.match(".*no name list*", err) != None:
					continue
				elif re.match(".*No such file or directory*", err) != None:
					continue
				assert(len(err) == 0)
			lines = out.splitlines()
			for line in lines:
				if len(line) == 0 or re.match("^(.*)\:$", line, re.M) != None:
					continue
				grps = re.search(pattern, line)
				if grps == None:
					print "line: \"%s\"" %(line)
					print "failed in: ", fpath
					assert(False)
				if grps.group(1) not in typeSet:
					# print "Adding (%s) to typeSet" %(grps.group(1))
					typeFile.write(grps.group(1) + "\n")
					typeFile.flush()
					typeSet.add(grps.group(1))
				if grps.group(2) not in linkageSet:
					# print "Adding (%s) to linkageSet" %(grps.group(2))
					linkageFile.write(grps.group(2) + "\n")
					linkageFile.flush()
					linkageSet.add(grps.group(2))
				k = (grps.group(1), grps.group(2))
				if k not in comboDict:
					print "Adding (\n%s\n%s\n) to comboDict" %(fpath, line)
					comboDict[k] = (fpath, line)
	typeFile.close()
	linkageFile.close()
