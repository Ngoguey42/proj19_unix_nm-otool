# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    compare_dir.py                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/02/17 11:25:41 by ngoguey           #+#    #+#              #
#    Updated: 2016/02/17 11:35:07 by ngoguey          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import os
import re
import subprocess
from sys import argv

if __name__ == "__main__":

	for dirpath in argv[1:]:
		outFile = open("diffs_" + dirpath.replace('/', '-') + ".txt", "w")
		for root, dirs, files in os.walk(dirpath):
			for file in files:
				fpath = "%s/%s" %(root, file)
				ref = subprocess.Popen(['nm', '-pm', fpath]
									 , stdout=subprocess.PIPE, stderr=subprocess.PIPE)
				refout, referr = ref.communicate()
				mine = subprocess.Popen(['./ft_nm', '-pm', fpath]
									 , stdout=subprocess.PIPE, stderr=subprocess.PIPE)
				mineout, mineerr = mine.communicate()
				if mineout != refout:
					print "diff over %s" %(fpath)
					outFile.write("diff '%s;\n" %(fpath))
					outFile.flush()
		out.close()
