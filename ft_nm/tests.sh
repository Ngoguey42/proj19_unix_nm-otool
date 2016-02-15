
launch(){
	file $1 | head -n 1
	./ft_nm $1 >mine 2>/dev/null
	nm -mp $1 >ref 2>/dev/null
	diff ref mine | head -n 3
	# echo ""
}



#archive

launch '../libft/libft.a'
launch '1txt.a'
launch '2obj.a'
launch '0txt.a'
launch '1obj.a'
launch '/nfs/zfs-student-4/users/ngoguey/.brew/Cellar/camlp4/4.02.3+6/lib/ocaml/camlp4/camlp4fulllib.a'
launch '/nfs/zfs-student-4/users/ngoguey/.brew/Cellar/ocaml/4.02.3/lib/ocaml/libasmrun.a'

echo ''
#dylibs
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


#fat
# launch '/usr/share/examshell/venv/lib/python2.7/site-packages/_cffi_backend.so'
# launch '/usr/lib/system/libsystem_trace.dylib'
# launch '/usr/lib/system/libdyld.dylib'
# launch '/usr/lib/system/libsystem_c.dylib'
# launch '/usr/lib/libobjc.A.dylib'
# launch '/usr/lib/crt1.10.6.o'
# launch '/usr/lib/crt1.o'
# launch '/usr/lib/dyld'
# launch '/usr/lib/lazydylib1.o'
# launch '/usr/lib/libc++.1.dylib'
# launch '/usr/lib/libextension.dylib'
# launch '/usr/lib/libgmalloc.dylib'
# launch '/usr/lib/libiconv.2.4.0.dylib'
# launch '/usr/bin/audiodevice'
# launch '/usr/lib/bundle1.o'


echo ''
#binaries:
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
launch o/srcs/build_sections_vector.o
launch o/srcs/endianness.o
launch o/srcs/env.o
launch o/srcs/env_make.o
launch o/srcs/file.o
launch o/srcs/file_make.o
launch o/srcs/file_processpath.o
launch o/srcs/file_release.o
launch o/srcs/filename.o
launch o/srcs/ft_arg.o
launch o/srcs/handle_file.o
launch o/srcs/main.o
launch o/srcs/mmap_file.o
launch o/srcs/obj_buildindices.o
launch o/srcs/obj_buildsections.o
launch o/srcs/obj_handle.o
launch o/srcs/obj_printsym.o
launch o/srcs/processpath.o



# launch $1
