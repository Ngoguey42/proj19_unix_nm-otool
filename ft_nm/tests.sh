
launch(){
	./ft_nm $1 >mine 2>/dev/null
	nm -mp $1 > ref
	diff ref mine | head -n 40
	file $1
}

#binaries:
launch "/sbin/mount_acfs"
launch "/usr/bin/agvtool"
launch "/usr/libexec/nsurlsessiond"
launch "/Applications/BetterTouchTool.app/Contents/Resources/relaunch"
launch "/usr/libexec/nsurlsessiond"
launch "/usr/bin/unzip"
launch "/sbin/autodiskmount"
launch "./o/srcs/bin_handle.o"


# launch $1
