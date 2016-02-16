
launch(){
	# ls -ld $1
	# file $1

	file $1 | head -n 1
	./ft_nm $1 >mine 2>/dev/null
	nm -mp $1 >ref 2>/dev/null
	diff ref mine
	# diff ref mine | head -n 70
	# echo ""
}

# /usr/lib/bundle1.o: Mach-O universal binary with 2 architectures
# /usr/lib/bundle1.o (for architecture x86_64):Mach-O 64-bit object x86_64
# /usr/lib/bundle1.o (for architecture i386):Mach-O object i386
# cpu16777223 subcpu3 off4096 size520 align12
# cpu7 subcpu3 off8192 size608 align12

# /usr/bin/audiodevice: Mach-O universal binary with 2 architectures
# /usr/bin/audiodevice (for architecture ppc):Mach-O executable ppc
# /usr/bin/audiodevice (for architecture i386):Mach-O executable i386
# cpu18 subcpu0 off4096 size29532 align12
# cpu7 subcpu3 off36864 size33412 align12

# /usr/lib/libgmalloc.dylib: Mach-O universal binary with 2 architectures
# /usr/lib/libgmalloc.dylib (for architecture x86_64):Mach-O 64-bit dynamically linked shared library x86_64
# /usr/lib/libgmalloc.dylib (for architecture i386):Mach-O dynamically linked shared library i386
# cpu16777223 subcpu3 off4096 size43168 align12
# cpu7 subcpu3 off49152 size42512 align12

#fat
echo "=============FATS:============"
# launch '/usr/lib/system/libsystem_c.dylib'
# launch '/usr/lib/libc++.1.dylib'
# launch '/usr/bin/audiodevice'  #2arch no x86_64

#small diffs:
# launch '/usr/lib/bundle1.o'
# launch '/usr/lib/lazydylib1.o'
# launch '/usr/lib/libobjc.A.dylib'
# launch '/usr/lib/crt1.o'
exit


launch '/usr/share/examshell/venv/lib/python2.7/site-packages/_cffi_backend.so'
launch '/usr/lib/system/libsystem_trace.dylib'
launch '/usr/lib/system/libdyld.dylib'
launch '/usr/lib/crt1.10.6.o'
launch '/usr/lib/dyld'
launch '/usr/lib/libextension.dylib'
launch '/usr/lib/libgmalloc.dylib'
launch '/usr/lib/libiconv.2.4.0.dylib'




echo ''
#archive
echo "=============ARCH:============"

launch '../libft/libft.a'
launch '1txt.a'
launch '2obj.a'
launch '0txt.a'
launch '1obj.a'
launch '/nfs/zfs-student-4/users/ngoguey/.brew/Cellar/camlp4/4.02.3+6/lib/ocaml/camlp4/camlp4fulllib.a'
launch '/nfs/zfs-student-4/users/ngoguey/.brew/Cellar/ocaml/4.02.3/lib/ocaml/libasmrun.a'

echo ''
#dylibs
echo "=============DYLB:============"
launch '/usr/lib/libATCommandStudioDynamic.dylib'
launch '/usr/lib/libAccountPolicyTranslation.dylib'
launch '/usr/lib/libBSDPClient.A.dylib'
launch '/usr/lib/libBSDPClient.dylib'
launch '/usr/lib/libDHCPServer.A.dylib'
launch '/usr/lib/libDHCPServer.dylib'
launch '/usr/lib/libIASUnifiedProgress.dylib'
launch '/usr/lib/libQMIParserDynamic.dylib'
launch '/usr/lib/libTelephonyUtilDynamic.dylib'
launch '/usr/lib/libUniversalAccess.dylib'
launch '/usr/lib/libXSEvent.dylib'
launch '/usr/lib/libdns_services.dylib'
launch '/usr/lib/libecpg.6.5.dylib'
launch '/usr/lib/libecpg.6.dylib'
launch '/usr/lib/libecpg.dylib'
launch '/usr/lib/libecpg_compat.3.5.dylib'
launch '/usr/lib/libecpg_compat.3.dylib'
launch '/usr/lib/libecpg_compat.dylib'
launch '/usr/lib/libipconfig.dylib'
launch '/usr/lib/libktrace.dylib'
launch '/usr/lib/libodmodule.dylib'
launch '/usr/lib/libpgtypes.3.4.dylib'
launch '/usr/lib/libpgtypes.3.dylib'
launch '/usr/lib/libpgtypes.dylib'
launch '/usr/lib/libpmenergy.dylib'
launch '/usr/lib/libpmsample.dylib'
launch '/usr/lib/libpq.5.6.dylib'
launch '/usr/lib/libpq.5.dylib'
launch '/usr/lib/libpq.dylib'
launch '/usr/lib/libprequelite.dylib'
launch '/usr/lib/libquit.dylib'
launch '/usr/lib/libspindump.dylib'
launch '/usr/lib/libsysmon.dylib'
launch '/usr/lib/libsystemstats.dylib'
launch '/usr/lib/ssh-keychain.dylib'

# launch '/usr/lib/libnetsnmp.5.2.1.dylib'
# launch '/usr/lib/libnetsnmp.5.dylib'
# launch '/usr/lib/libnetwork.dylib'
# launch '/usr/lib/libxcselect.dylib'

echo ''
#binaries:
echo "=============OBJS:============"
launch '/usr/share/rbx/gems/gems/rubysl-bigdecimal-2.0.2/ext/rubysl/bigdecimal/bigdecimal.o'
launch '/usr/bin/iscsictl'
launch /sbin/mount_acfs
launch /usr/bin/agvtool
launch /Applications/BetterTouchTool.app/Contents/Resources/relaunch
launch /usr/libexec/nsurlsessiond
launch /usr/bin/unzip
launch /sbin/autodiskmount
launch '/sbin/mount_smbfs'
launch '/sbin/fsck_udf'
launch '/usr/share/rbx/gems/gems/rubysl-openssl-2.1.0/ext/rubysl/openssl/ossl.o'

launch o/srcs/bin_handle.o
launch o/srcs/bin_readmagic.o
launch o/srcs/env_make.o
launch o/srcs/file_make.o
launch o/srcs/file_processpath.o
launch o/srcs/file_release.o
launch o/srcs/main.o
launch o/srcs/obj_buildindices.o
launch o/srcs/obj_handle.o
launch o/srcs/obj_printsym.o



# launch $1
