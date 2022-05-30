================================================================================================
Date: 12 June 2016
Purpose: Instruction Guide for TCT Build/Install/Execution using Address Sanitizer
================================================================================================


=====================================Description================================================
TCT Facilitates executing any itc/ctc/utc module using Address Sanitizer (ASAN).
Tizen 3.0 frameworks are mainly implemented in unmanaged programming languages (C and C++) which do not provide any protection against invalid memory accesses.
Such accesses often result in memory corruption and eventually cause program crashes or other abnormal behavior.
AddressSanitizer (or ASan for short) is a part of Google toolsuite for program quality assurance. The advantages of ASan are 
 - much (~40x) faster than valgrind 
 - actively evolving (in contrast to mudflap which has been recently removed from GCC) 
 - cross-platform (in contrast to Intel MPX) 

Current AddressSanitizer handles the following classes of errors
 - use after free 
 - buffer overruns and wild pointers 
 - use after return / use after end-of-block 
 - initialization order bugs 
================================================================================================
 

=====================Build/Install/Execution Steps for any TCT Module==========================
a) ./scripts/init.sh
b) Build TCT module : 
	$ sudo ./tcbuild build_asan <build_type> <module_name> [arch_type] [device_type]	(for device build)
	$ sudo ./tcbuildsdk build_asan <build_type> <module_name> [arch_type] [device_type]	(for emulator build)
c) Install TCT Module : 
	$ sudo ./tcbuild install_asan<build_type> <module_name> [arch_type] [device_type]	(for device install)
	$ sudo ./tcbuildsdk install_asan <build_type> <module_name> [arch_type] [device_type]	(for emulator install)
		<build_type> = itc|ctc|utc
    	<arch_type> = armv7l/aarch64” (for tcbuild) and “i586/x86_64” (for tcbuildsdk)
    	<device_type> = mobile|wearable|tv
d) Execute using tct-manager tool.

Note:
a.) To build/install all the packages (itc+ctc+utc for all modules), exclude <build_type> and <module_name> from command as mention below: 
    $ sudo ./tcbuild build_asan [arch_type] [device_type] 	(build all for device)
    $ sudo ./tcbuild install_asan [arch_type] [device_type] (install all for device)
b.) To build/install all the packages for specific build_type, (itc or ctc or utc), exclude <module_name> from command as mention below: 
    $ sudo ./tcbuild build_asan <build_type> [ arch_type] [device_type]		(build for specific build_type for device)
    $ sudo ./tcbuild install_asan <build_type> [ arch_type] [device_type]	(install for specific build_type for device)
================================================================================================


=====================================Troubleshooting===============================================
For any troubleshooting, please contact its developer: Satyajit Anand (satyajit.a@samsung.com)
===================================================================================================
