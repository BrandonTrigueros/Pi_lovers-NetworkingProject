# NOTE: this is a GNU Makefile.  You must use "gmake" rather than "make".
#
# Makefile for the threads assignment.  The threads assignment must
#  be done first!
#
# Copyright (c) 1992 The Regents of the University of California.
# All rights reserved.  See copyright.h for copyright notice and limitation 
# of liability and disclaimer of warranty provisions.

DEFINES = -DTHREADS
INCPATH = -I../threads -I../machine
HFILES = $(THREAD_H)
CFILES = $(THREAD_C)
C_OFILES = $(THREAD_O)

include ../Makefile.common
include ../Makefile.dep
#-----------------------------------------------------------------
# DO NOT DELETE THIS LINE -- make depend uses it
# DEPENDENCIES MUST END AT END OF FILE
main.o: ../threads/main.cc /usr/include/stdc-predef.h \
 ../threads/copyright.h ../threads/utility.h ../machine/sysdep.h \
 ../threads/copyright.h /usr/include/c++/13/stdlib.h \
 /usr/include/c++/13/cstdlib \
 /usr/include/c++/13/x86_64-redhat-linux/bits/c++config.h \
 /usr/include/bits/wordsize.h \
 /usr/include/c++/13/x86_64-redhat-linux/bits/os_defines.h \
 /usr/include/features.h /usr/include/features-time64.h \
 /usr/include/bits/timesize.h /usr/include/sys/cdefs.h \
 /usr/include/bits/long-double.h /usr/include/gnu/stubs.h \
 /usr/include/gnu/stubs-64.h \
 /usr/include/c++/13/x86_64-redhat-linux/bits/cpu_defines.h \
 /usr/include/c++/13/pstl/pstl_config.h /usr/include/stdlib.h \
 /usr/include/bits/libc-header-start.h \
 /usr/lib/gcc/x86_64-redhat-linux/13/include/stddef.h \
 /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h \
 /usr/include/bits/floatn.h /usr/include/bits/floatn-common.h \
 /usr/include/bits/types/locale_t.h /usr/include/bits/types/__locale_t.h \
 /usr/include/sys/types.h /usr/include/bits/types.h \
 /usr/include/bits/typesizes.h /usr/include/bits/time64.h \
 /usr/include/bits/types/clock_t.h /usr/include/bits/types/clockid_t.h \
 /usr/include/bits/types/time_t.h /usr/include/bits/types/timer_t.h \
 /usr/include/bits/stdint-intn.h /usr/include/endian.h \
 /usr/include/bits/endian.h /usr/include/bits/endianness.h \
 /usr/include/bits/byteswap.h /usr/include/bits/uintn-identity.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/types/sigset_t.h /usr/include/bits/types/__sigset_t.h \
 /usr/include/bits/types/struct_timeval.h \
 /usr/include/bits/types/struct_timespec.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/thread-shared-types.h \
 /usr/include/bits/pthreadtypes-arch.h \
 /usr/include/bits/atomic_wide_counter.h /usr/include/bits/struct_mutex.h \
 /usr/include/bits/struct_rwlock.h /usr/include/alloca.h \
 /usr/include/bits/stdlib-float.h /usr/include/c++/13/bits/std_abs.h \
 /usr/include/stdio.h \
 /usr/lib/gcc/x86_64-redhat-linux/13/include/stdarg.h \
 /usr/include/bits/types/__fpos_t.h /usr/include/bits/types/__mbstate_t.h \
 /usr/include/bits/types/__fpos64_t.h /usr/include/bits/types/__FILE.h \
 /usr/include/bits/types/FILE.h /usr/include/bits/types/struct_FILE.h \
 /usr/include/bits/types/cookie_io_functions_t.h \
 /usr/include/bits/stdio_lim.h /usr/include/string.h \
 /usr/include/strings.h ../threads/system.h ../machine/interrupt.h \
 ../threads/list.h ../threads/scheduler.h ../threads/list.h \
 ../threads/thread.h ../machine/stats.h ../machine/timer.h \
 ../threads/utility.h
scheduler.o: ../threads/scheduler.cc /usr/include/stdc-predef.h \
 ../threads/copyright.h ../threads/scheduler.h ../threads/list.h \
 ../threads/utility.h ../machine/sysdep.h ../threads/copyright.h \
 /usr/include/c++/13/stdlib.h /usr/include/c++/13/cstdlib \
 /usr/include/c++/13/x86_64-redhat-linux/bits/c++config.h \
 /usr/include/bits/wordsize.h \
 /usr/include/c++/13/x86_64-redhat-linux/bits/os_defines.h \
 /usr/include/features.h /usr/include/features-time64.h \
 /usr/include/bits/timesize.h /usr/include/sys/cdefs.h \
 /usr/include/bits/long-double.h /usr/include/gnu/stubs.h \
 /usr/include/gnu/stubs-64.h \
 /usr/include/c++/13/x86_64-redhat-linux/bits/cpu_defines.h \
 /usr/include/c++/13/pstl/pstl_config.h /usr/include/stdlib.h \
 /usr/include/bits/libc-header-start.h \
 /usr/lib/gcc/x86_64-redhat-linux/13/include/stddef.h \
 /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h \
 /usr/include/bits/floatn.h /usr/include/bits/floatn-common.h \
 /usr/include/bits/types/locale_t.h /usr/include/bits/types/__locale_t.h \
 /usr/include/sys/types.h /usr/include/bits/types.h \
 /usr/include/bits/typesizes.h /usr/include/bits/time64.h \
 /usr/include/bits/types/clock_t.h /usr/include/bits/types/clockid_t.h \
 /usr/include/bits/types/time_t.h /usr/include/bits/types/timer_t.h \
 /usr/include/bits/stdint-intn.h /usr/include/endian.h \
 /usr/include/bits/endian.h /usr/include/bits/endianness.h \
 /usr/include/bits/byteswap.h /usr/include/bits/uintn-identity.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/types/sigset_t.h /usr/include/bits/types/__sigset_t.h \
 /usr/include/bits/types/struct_timeval.h \
 /usr/include/bits/types/struct_timespec.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/thread-shared-types.h \
 /usr/include/bits/pthreadtypes-arch.h \
 /usr/include/bits/atomic_wide_counter.h /usr/include/bits/struct_mutex.h \
 /usr/include/bits/struct_rwlock.h /usr/include/alloca.h \
 /usr/include/bits/stdlib-float.h /usr/include/c++/13/bits/std_abs.h \
 /usr/include/stdio.h \
 /usr/lib/gcc/x86_64-redhat-linux/13/include/stdarg.h \
 /usr/include/bits/types/__fpos_t.h /usr/include/bits/types/__mbstate_t.h \
 /usr/include/bits/types/__fpos64_t.h /usr/include/bits/types/__FILE.h \
 /usr/include/bits/types/FILE.h /usr/include/bits/types/struct_FILE.h \
 /usr/include/bits/types/cookie_io_functions_t.h \
 /usr/include/bits/stdio_lim.h /usr/include/string.h \
 /usr/include/strings.h ../threads/thread.h ../threads/system.h \
 ../machine/interrupt.h ../threads/list.h ../machine/stats.h \
 ../machine/timer.h ../threads/utility.h
synch.o: ../threads/synch.cc /usr/include/stdc-predef.h \
 ../threads/copyright.h ../threads/synch.h ../threads/thread.h \
 ../threads/utility.h ../machine/sysdep.h ../threads/copyright.h \
 /usr/include/c++/13/stdlib.h /usr/include/c++/13/cstdlib \
 /usr/include/c++/13/x86_64-redhat-linux/bits/c++config.h \
 /usr/include/bits/wordsize.h \
 /usr/include/c++/13/x86_64-redhat-linux/bits/os_defines.h \
 /usr/include/features.h /usr/include/features-time64.h \
 /usr/include/bits/timesize.h /usr/include/sys/cdefs.h \
 /usr/include/bits/long-double.h /usr/include/gnu/stubs.h \
 /usr/include/gnu/stubs-64.h \
 /usr/include/c++/13/x86_64-redhat-linux/bits/cpu_defines.h \
 /usr/include/c++/13/pstl/pstl_config.h /usr/include/stdlib.h \
 /usr/include/bits/libc-header-start.h \
 /usr/lib/gcc/x86_64-redhat-linux/13/include/stddef.h \
 /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h \
 /usr/include/bits/floatn.h /usr/include/bits/floatn-common.h \
 /usr/include/bits/types/locale_t.h /usr/include/bits/types/__locale_t.h \
 /usr/include/sys/types.h /usr/include/bits/types.h \
 /usr/include/bits/typesizes.h /usr/include/bits/time64.h \
 /usr/include/bits/types/clock_t.h /usr/include/bits/types/clockid_t.h \
 /usr/include/bits/types/time_t.h /usr/include/bits/types/timer_t.h \
 /usr/include/bits/stdint-intn.h /usr/include/endian.h \
 /usr/include/bits/endian.h /usr/include/bits/endianness.h \
 /usr/include/bits/byteswap.h /usr/include/bits/uintn-identity.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/types/sigset_t.h /usr/include/bits/types/__sigset_t.h \
 /usr/include/bits/types/struct_timeval.h \
 /usr/include/bits/types/struct_timespec.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/thread-shared-types.h \
 /usr/include/bits/pthreadtypes-arch.h \
 /usr/include/bits/atomic_wide_counter.h /usr/include/bits/struct_mutex.h \
 /usr/include/bits/struct_rwlock.h /usr/include/alloca.h \
 /usr/include/bits/stdlib-float.h /usr/include/c++/13/bits/std_abs.h \
 /usr/include/stdio.h \
 /usr/lib/gcc/x86_64-redhat-linux/13/include/stdarg.h \
 /usr/include/bits/types/__fpos_t.h /usr/include/bits/types/__mbstate_t.h \
 /usr/include/bits/types/__fpos64_t.h /usr/include/bits/types/__FILE.h \
 /usr/include/bits/types/FILE.h /usr/include/bits/types/struct_FILE.h \
 /usr/include/bits/types/cookie_io_functions_t.h \
 /usr/include/bits/stdio_lim.h /usr/include/string.h \
 /usr/include/strings.h ../threads/list.h ../threads/system.h \
 ../machine/interrupt.h ../threads/list.h ../threads/scheduler.h \
 ../machine/stats.h ../machine/timer.h ../threads/utility.h
system.o: ../threads/system.cc /usr/include/stdc-predef.h \
 ../threads/system.h ../threads/copyright.h ../machine/interrupt.h \
 ../threads/copyright.h ../threads/list.h ../threads/utility.h \
 ../machine/sysdep.h /usr/include/c++/13/stdlib.h \
 /usr/include/c++/13/cstdlib \
 /usr/include/c++/13/x86_64-redhat-linux/bits/c++config.h \
 /usr/include/bits/wordsize.h \
 /usr/include/c++/13/x86_64-redhat-linux/bits/os_defines.h \
 /usr/include/features.h /usr/include/features-time64.h \
 /usr/include/bits/timesize.h /usr/include/sys/cdefs.h \
 /usr/include/bits/long-double.h /usr/include/gnu/stubs.h \
 /usr/include/gnu/stubs-64.h \
 /usr/include/c++/13/x86_64-redhat-linux/bits/cpu_defines.h \
 /usr/include/c++/13/pstl/pstl_config.h /usr/include/stdlib.h \
 /usr/include/bits/libc-header-start.h \
 /usr/lib/gcc/x86_64-redhat-linux/13/include/stddef.h \
 /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h \
 /usr/include/bits/floatn.h /usr/include/bits/floatn-common.h \
 /usr/include/bits/types/locale_t.h /usr/include/bits/types/__locale_t.h \
 /usr/include/sys/types.h /usr/include/bits/types.h \
 /usr/include/bits/typesizes.h /usr/include/bits/time64.h \
 /usr/include/bits/types/clock_t.h /usr/include/bits/types/clockid_t.h \
 /usr/include/bits/types/time_t.h /usr/include/bits/types/timer_t.h \
 /usr/include/bits/stdint-intn.h /usr/include/endian.h \
 /usr/include/bits/endian.h /usr/include/bits/endianness.h \
 /usr/include/bits/byteswap.h /usr/include/bits/uintn-identity.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/types/sigset_t.h /usr/include/bits/types/__sigset_t.h \
 /usr/include/bits/types/struct_timeval.h \
 /usr/include/bits/types/struct_timespec.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/thread-shared-types.h \
 /usr/include/bits/pthreadtypes-arch.h \
 /usr/include/bits/atomic_wide_counter.h /usr/include/bits/struct_mutex.h \
 /usr/include/bits/struct_rwlock.h /usr/include/alloca.h \
 /usr/include/bits/stdlib-float.h /usr/include/c++/13/bits/std_abs.h \
 /usr/include/stdio.h \
 /usr/lib/gcc/x86_64-redhat-linux/13/include/stdarg.h \
 /usr/include/bits/types/__fpos_t.h /usr/include/bits/types/__mbstate_t.h \
 /usr/include/bits/types/__fpos64_t.h /usr/include/bits/types/__FILE.h \
 /usr/include/bits/types/FILE.h /usr/include/bits/types/struct_FILE.h \
 /usr/include/bits/types/cookie_io_functions_t.h \
 /usr/include/bits/stdio_lim.h /usr/include/string.h \
 /usr/include/strings.h ../threads/scheduler.h ../threads/list.h \
 ../threads/thread.h ../machine/stats.h ../machine/timer.h \
 ../threads/utility.h ../threads/preemptive.h
thread.o: ../threads/thread.cc /usr/include/stdc-predef.h \
 ../threads/copyright.h ../threads/thread.h ../threads/utility.h \
 ../machine/sysdep.h ../threads/copyright.h /usr/include/c++/13/stdlib.h \
 /usr/include/c++/13/cstdlib \
 /usr/include/c++/13/x86_64-redhat-linux/bits/c++config.h \
 /usr/include/bits/wordsize.h \
 /usr/include/c++/13/x86_64-redhat-linux/bits/os_defines.h \
 /usr/include/features.h /usr/include/features-time64.h \
 /usr/include/bits/timesize.h /usr/include/sys/cdefs.h \
 /usr/include/bits/long-double.h /usr/include/gnu/stubs.h \
 /usr/include/gnu/stubs-64.h \
 /usr/include/c++/13/x86_64-redhat-linux/bits/cpu_defines.h \
 /usr/include/c++/13/pstl/pstl_config.h /usr/include/stdlib.h \
 /usr/include/bits/libc-header-start.h \
 /usr/lib/gcc/x86_64-redhat-linux/13/include/stddef.h \
 /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h \
 /usr/include/bits/floatn.h /usr/include/bits/floatn-common.h \
 /usr/include/bits/types/locale_t.h /usr/include/bits/types/__locale_t.h \
 /usr/include/sys/types.h /usr/include/bits/types.h \
 /usr/include/bits/typesizes.h /usr/include/bits/time64.h \
 /usr/include/bits/types/clock_t.h /usr/include/bits/types/clockid_t.h \
 /usr/include/bits/types/time_t.h /usr/include/bits/types/timer_t.h \
 /usr/include/bits/stdint-intn.h /usr/include/endian.h \
 /usr/include/bits/endian.h /usr/include/bits/endianness.h \
 /usr/include/bits/byteswap.h /usr/include/bits/uintn-identity.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/types/sigset_t.h /usr/include/bits/types/__sigset_t.h \
 /usr/include/bits/types/struct_timeval.h \
 /usr/include/bits/types/struct_timespec.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/thread-shared-types.h \
 /usr/include/bits/pthreadtypes-arch.h \
 /usr/include/bits/atomic_wide_counter.h /usr/include/bits/struct_mutex.h \
 /usr/include/bits/struct_rwlock.h /usr/include/alloca.h \
 /usr/include/bits/stdlib-float.h /usr/include/c++/13/bits/std_abs.h \
 /usr/include/stdio.h \
 /usr/lib/gcc/x86_64-redhat-linux/13/include/stdarg.h \
 /usr/include/bits/types/__fpos_t.h /usr/include/bits/types/__mbstate_t.h \
 /usr/include/bits/types/__fpos64_t.h /usr/include/bits/types/__FILE.h \
 /usr/include/bits/types/FILE.h /usr/include/bits/types/struct_FILE.h \
 /usr/include/bits/types/cookie_io_functions_t.h \
 /usr/include/bits/stdio_lim.h /usr/include/string.h \
 /usr/include/strings.h ../threads/switch.h ../threads/synch.h \
 ../threads/list.h ../threads/system.h ../machine/interrupt.h \
 ../threads/list.h ../threads/scheduler.h ../machine/stats.h \
 ../machine/timer.h ../threads/utility.h
utility.o: ../threads/utility.cc /usr/include/stdc-predef.h \
 ../threads/copyright.h ../threads/utility.h ../machine/sysdep.h \
 ../threads/copyright.h /usr/include/c++/13/stdlib.h \
 /usr/include/c++/13/cstdlib \
 /usr/include/c++/13/x86_64-redhat-linux/bits/c++config.h \
 /usr/include/bits/wordsize.h \
 /usr/include/c++/13/x86_64-redhat-linux/bits/os_defines.h \
 /usr/include/features.h /usr/include/features-time64.h \
 /usr/include/bits/timesize.h /usr/include/sys/cdefs.h \
 /usr/include/bits/long-double.h /usr/include/gnu/stubs.h \
 /usr/include/gnu/stubs-64.h \
 /usr/include/c++/13/x86_64-redhat-linux/bits/cpu_defines.h \
 /usr/include/c++/13/pstl/pstl_config.h /usr/include/stdlib.h \
 /usr/include/bits/libc-header-start.h \
 /usr/lib/gcc/x86_64-redhat-linux/13/include/stddef.h \
 /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h \
 /usr/include/bits/floatn.h /usr/include/bits/floatn-common.h \
 /usr/include/bits/types/locale_t.h /usr/include/bits/types/__locale_t.h \
 /usr/include/sys/types.h /usr/include/bits/types.h \
 /usr/include/bits/typesizes.h /usr/include/bits/time64.h \
 /usr/include/bits/types/clock_t.h /usr/include/bits/types/clockid_t.h \
 /usr/include/bits/types/time_t.h /usr/include/bits/types/timer_t.h \
 /usr/include/bits/stdint-intn.h /usr/include/endian.h \
 /usr/include/bits/endian.h /usr/include/bits/endianness.h \
 /usr/include/bits/byteswap.h /usr/include/bits/uintn-identity.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/types/sigset_t.h /usr/include/bits/types/__sigset_t.h \
 /usr/include/bits/types/struct_timeval.h \
 /usr/include/bits/types/struct_timespec.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/thread-shared-types.h \
 /usr/include/bits/pthreadtypes-arch.h \
 /usr/include/bits/atomic_wide_counter.h /usr/include/bits/struct_mutex.h \
 /usr/include/bits/struct_rwlock.h /usr/include/alloca.h \
 /usr/include/bits/stdlib-float.h /usr/include/c++/13/bits/std_abs.h \
 /usr/include/stdio.h \
 /usr/lib/gcc/x86_64-redhat-linux/13/include/stdarg.h \
 /usr/include/bits/types/__fpos_t.h /usr/include/bits/types/__mbstate_t.h \
 /usr/include/bits/types/__fpos64_t.h /usr/include/bits/types/__FILE.h \
 /usr/include/bits/types/FILE.h /usr/include/bits/types/struct_FILE.h \
 /usr/include/bits/types/cookie_io_functions_t.h \
 /usr/include/bits/stdio_lim.h /usr/include/string.h \
 /usr/include/strings.h
threadtest.o: ../threads/threadtest.cc /usr/include/stdc-predef.h \
 /usr/include/unistd.h /usr/include/features.h \
 /usr/include/features-time64.h /usr/include/bits/wordsize.h \
 /usr/include/bits/timesize.h /usr/include/sys/cdefs.h \
 /usr/include/bits/long-double.h /usr/include/gnu/stubs.h \
 /usr/include/gnu/stubs-64.h /usr/include/bits/posix_opt.h \
 /usr/include/bits/environments.h /usr/include/bits/types.h \
 /usr/include/bits/typesizes.h /usr/include/bits/time64.h \
 /usr/lib/gcc/x86_64-redhat-linux/13/include/stddef.h \
 /usr/include/bits/confname.h /usr/include/bits/getopt_posix.h \
 /usr/include/bits/getopt_core.h /usr/include/bits/unistd_ext.h \
 /usr/include/linux/close_range.h ../threads/copyright.h \
 ../threads/system.h ../machine/interrupt.h ../threads/copyright.h \
 ../threads/list.h ../threads/utility.h ../machine/sysdep.h \
 /usr/include/c++/13/stdlib.h /usr/include/c++/13/cstdlib \
 /usr/include/c++/13/x86_64-redhat-linux/bits/c++config.h \
 /usr/include/c++/13/x86_64-redhat-linux/bits/os_defines.h \
 /usr/include/c++/13/x86_64-redhat-linux/bits/cpu_defines.h \
 /usr/include/c++/13/pstl/pstl_config.h /usr/include/stdlib.h \
 /usr/include/bits/libc-header-start.h /usr/include/bits/waitflags.h \
 /usr/include/bits/waitstatus.h /usr/include/bits/floatn.h \
 /usr/include/bits/floatn-common.h /usr/include/bits/types/locale_t.h \
 /usr/include/bits/types/__locale_t.h /usr/include/sys/types.h \
 /usr/include/bits/types/clock_t.h /usr/include/bits/types/clockid_t.h \
 /usr/include/bits/types/time_t.h /usr/include/bits/types/timer_t.h \
 /usr/include/bits/stdint-intn.h /usr/include/endian.h \
 /usr/include/bits/endian.h /usr/include/bits/endianness.h \
 /usr/include/bits/byteswap.h /usr/include/bits/uintn-identity.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/types/sigset_t.h /usr/include/bits/types/__sigset_t.h \
 /usr/include/bits/types/struct_timeval.h \
 /usr/include/bits/types/struct_timespec.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/thread-shared-types.h \
 /usr/include/bits/pthreadtypes-arch.h \
 /usr/include/bits/atomic_wide_counter.h /usr/include/bits/struct_mutex.h \
 /usr/include/bits/struct_rwlock.h /usr/include/alloca.h \
 /usr/include/bits/stdlib-float.h /usr/include/c++/13/bits/std_abs.h \
 /usr/include/stdio.h \
 /usr/lib/gcc/x86_64-redhat-linux/13/include/stdarg.h \
 /usr/include/bits/types/__fpos_t.h /usr/include/bits/types/__mbstate_t.h \
 /usr/include/bits/types/__fpos64_t.h /usr/include/bits/types/__FILE.h \
 /usr/include/bits/types/FILE.h /usr/include/bits/types/struct_FILE.h \
 /usr/include/bits/types/cookie_io_functions_t.h \
 /usr/include/bits/stdio_lim.h /usr/include/string.h \
 /usr/include/strings.h ../threads/scheduler.h ../threads/list.h \
 ../threads/thread.h ../machine/stats.h ../machine/timer.h \
 ../threads/utility.h ../threads/diningph.h ../threads/synch.h
diningph.o: ../threads/diningph.cc /usr/include/stdc-predef.h \
 ../threads/diningph.h ../threads/synch.h ../threads/copyright.h \
 ../threads/thread.h ../threads/utility.h ../machine/sysdep.h \
 ../threads/copyright.h /usr/include/c++/13/stdlib.h \
 /usr/include/c++/13/cstdlib \
 /usr/include/c++/13/x86_64-redhat-linux/bits/c++config.h \
 /usr/include/bits/wordsize.h \
 /usr/include/c++/13/x86_64-redhat-linux/bits/os_defines.h \
 /usr/include/features.h /usr/include/features-time64.h \
 /usr/include/bits/timesize.h /usr/include/sys/cdefs.h \
 /usr/include/bits/long-double.h /usr/include/gnu/stubs.h \
 /usr/include/gnu/stubs-64.h \
 /usr/include/c++/13/x86_64-redhat-linux/bits/cpu_defines.h \
 /usr/include/c++/13/pstl/pstl_config.h /usr/include/stdlib.h \
 /usr/include/bits/libc-header-start.h \
 /usr/lib/gcc/x86_64-redhat-linux/13/include/stddef.h \
 /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h \
 /usr/include/bits/floatn.h /usr/include/bits/floatn-common.h \
 /usr/include/bits/types/locale_t.h /usr/include/bits/types/__locale_t.h \
 /usr/include/sys/types.h /usr/include/bits/types.h \
 /usr/include/bits/typesizes.h /usr/include/bits/time64.h \
 /usr/include/bits/types/clock_t.h /usr/include/bits/types/clockid_t.h \
 /usr/include/bits/types/time_t.h /usr/include/bits/types/timer_t.h \
 /usr/include/bits/stdint-intn.h /usr/include/endian.h \
 /usr/include/bits/endian.h /usr/include/bits/endianness.h \
 /usr/include/bits/byteswap.h /usr/include/bits/uintn-identity.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/types/sigset_t.h /usr/include/bits/types/__sigset_t.h \
 /usr/include/bits/types/struct_timeval.h \
 /usr/include/bits/types/struct_timespec.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/thread-shared-types.h \
 /usr/include/bits/pthreadtypes-arch.h \
 /usr/include/bits/atomic_wide_counter.h /usr/include/bits/struct_mutex.h \
 /usr/include/bits/struct_rwlock.h /usr/include/alloca.h \
 /usr/include/bits/stdlib-float.h /usr/include/c++/13/bits/std_abs.h \
 /usr/include/stdio.h \
 /usr/lib/gcc/x86_64-redhat-linux/13/include/stdarg.h \
 /usr/include/bits/types/__fpos_t.h /usr/include/bits/types/__mbstate_t.h \
 /usr/include/bits/types/__fpos64_t.h /usr/include/bits/types/__FILE.h \
 /usr/include/bits/types/FILE.h /usr/include/bits/types/struct_FILE.h \
 /usr/include/bits/types/cookie_io_functions_t.h \
 /usr/include/bits/stdio_lim.h /usr/include/string.h \
 /usr/include/strings.h ../threads/list.h
interrupt.o: ../machine/interrupt.cc /usr/include/stdc-predef.h \
 ../threads/copyright.h ../machine/interrupt.h ../threads/list.h \
 ../threads/copyright.h ../threads/utility.h ../machine/sysdep.h \
 /usr/include/c++/13/stdlib.h /usr/include/c++/13/cstdlib \
 /usr/include/c++/13/x86_64-redhat-linux/bits/c++config.h \
 /usr/include/bits/wordsize.h \
 /usr/include/c++/13/x86_64-redhat-linux/bits/os_defines.h \
 /usr/include/features.h /usr/include/features-time64.h \
 /usr/include/bits/timesize.h /usr/include/sys/cdefs.h \
 /usr/include/bits/long-double.h /usr/include/gnu/stubs.h \
 /usr/include/gnu/stubs-64.h \
 /usr/include/c++/13/x86_64-redhat-linux/bits/cpu_defines.h \
 /usr/include/c++/13/pstl/pstl_config.h /usr/include/stdlib.h \
 /usr/include/bits/libc-header-start.h \
 /usr/lib/gcc/x86_64-redhat-linux/13/include/stddef.h \
 /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h \
 /usr/include/bits/floatn.h /usr/include/bits/floatn-common.h \
 /usr/include/bits/types/locale_t.h /usr/include/bits/types/__locale_t.h \
 /usr/include/sys/types.h /usr/include/bits/types.h \
 /usr/include/bits/typesizes.h /usr/include/bits/time64.h \
 /usr/include/bits/types/clock_t.h /usr/include/bits/types/clockid_t.h \
 /usr/include/bits/types/time_t.h /usr/include/bits/types/timer_t.h \
 /usr/include/bits/stdint-intn.h /usr/include/endian.h \
 /usr/include/bits/endian.h /usr/include/bits/endianness.h \
 /usr/include/bits/byteswap.h /usr/include/bits/uintn-identity.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/types/sigset_t.h /usr/include/bits/types/__sigset_t.h \
 /usr/include/bits/types/struct_timeval.h \
 /usr/include/bits/types/struct_timespec.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/thread-shared-types.h \
 /usr/include/bits/pthreadtypes-arch.h \
 /usr/include/bits/atomic_wide_counter.h /usr/include/bits/struct_mutex.h \
 /usr/include/bits/struct_rwlock.h /usr/include/alloca.h \
 /usr/include/bits/stdlib-float.h /usr/include/c++/13/bits/std_abs.h \
 /usr/include/stdio.h \
 /usr/lib/gcc/x86_64-redhat-linux/13/include/stdarg.h \
 /usr/include/bits/types/__fpos_t.h /usr/include/bits/types/__mbstate_t.h \
 /usr/include/bits/types/__fpos64_t.h /usr/include/bits/types/__FILE.h \
 /usr/include/bits/types/FILE.h /usr/include/bits/types/struct_FILE.h \
 /usr/include/bits/types/cookie_io_functions_t.h \
 /usr/include/bits/stdio_lim.h /usr/include/string.h \
 /usr/include/strings.h ../threads/system.h ../machine/interrupt.h \
 ../threads/scheduler.h ../threads/list.h ../threads/thread.h \
 ../machine/stats.h ../machine/timer.h ../threads/utility.h
sysdep.o: ../machine/sysdep.cc /usr/include/stdc-predef.h \
 ../threads/copyright.h /usr/include/stdio.h \
 /usr/include/bits/libc-header-start.h /usr/include/features.h \
 /usr/include/features-time64.h /usr/include/bits/wordsize.h \
 /usr/include/bits/timesize.h /usr/include/sys/cdefs.h \
 /usr/include/bits/long-double.h /usr/include/gnu/stubs.h \
 /usr/include/gnu/stubs-64.h \
 /usr/lib/gcc/x86_64-redhat-linux/13/include/stddef.h \
 /usr/lib/gcc/x86_64-redhat-linux/13/include/stdarg.h \
 /usr/include/bits/types.h /usr/include/bits/typesizes.h \
 /usr/include/bits/time64.h /usr/include/bits/types/__fpos_t.h \
 /usr/include/bits/types/__mbstate_t.h \
 /usr/include/bits/types/__fpos64_t.h /usr/include/bits/types/__FILE.h \
 /usr/include/bits/types/FILE.h /usr/include/bits/types/struct_FILE.h \
 /usr/include/bits/types/cookie_io_functions_t.h \
 /usr/include/bits/stdio_lim.h /usr/include/bits/floatn.h \
 /usr/include/bits/floatn-common.h /usr/include/string.h \
 /usr/include/bits/types/locale_t.h /usr/include/bits/types/__locale_t.h \
 /usr/include/strings.h /usr/include/signal.h \
 /usr/include/bits/signum-generic.h /usr/include/bits/signum-arch.h \
 /usr/include/bits/types/sig_atomic_t.h \
 /usr/include/bits/types/sigset_t.h /usr/include/bits/types/__sigset_t.h \
 /usr/include/bits/types/struct_timespec.h /usr/include/bits/endian.h \
 /usr/include/bits/endianness.h /usr/include/bits/types/time_t.h \
 /usr/include/bits/types/siginfo_t.h /usr/include/bits/types/__sigval_t.h \
 /usr/include/bits/siginfo-arch.h /usr/include/bits/siginfo-consts.h \
 /usr/include/bits/siginfo-consts-arch.h \
 /usr/include/bits/types/sigval_t.h /usr/include/bits/types/sigevent_t.h \
 /usr/include/bits/sigevent-consts.h /usr/include/bits/sigaction.h \
 /usr/include/bits/sigcontext.h /usr/include/bits/types/stack_t.h \
 /usr/include/sys/ucontext.h /usr/include/bits/sigstack.h \
 /usr/include/bits/sigstksz.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/environments.h \
 /usr/include/bits/confname.h /usr/include/bits/getopt_posix.h \
 /usr/include/bits/getopt_core.h /usr/include/bits/unistd_ext.h \
 /usr/include/linux/close_range.h /usr/include/bits/ss_flags.h \
 /usr/include/bits/types/struct_sigstack.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/thread-shared-types.h \
 /usr/include/bits/pthreadtypes-arch.h \
 /usr/include/bits/atomic_wide_counter.h /usr/include/bits/struct_mutex.h \
 /usr/include/bits/struct_rwlock.h /usr/include/bits/sigthread.h \
 /usr/include/bits/signal_ext.h /usr/include/sys/types.h \
 /usr/include/bits/types/clock_t.h /usr/include/bits/types/clockid_t.h \
 /usr/include/bits/types/timer_t.h /usr/include/bits/stdint-intn.h \
 /usr/include/endian.h /usr/include/bits/byteswap.h \
 /usr/include/bits/uintn-identity.h /usr/include/sys/select.h \
 /usr/include/bits/select.h /usr/include/bits/types/struct_timeval.h \
 /usr/include/sys/socket.h /usr/include/bits/types/struct_iovec.h \
 /usr/include/bits/socket.h /usr/include/bits/socket_type.h \
 /usr/include/bits/sockaddr.h /usr/include/asm/socket.h \
 /usr/include/asm-generic/socket.h /usr/include/linux/posix_types.h \
 /usr/include/linux/stddef.h /usr/include/asm/posix_types.h \
 /usr/include/asm/posix_types_64.h /usr/include/asm-generic/posix_types.h \
 /usr/include/asm/bitsperlong.h /usr/include/asm-generic/bitsperlong.h \
 /usr/include/asm/sockios.h /usr/include/asm-generic/sockios.h \
 /usr/include/bits/types/struct_osockaddr.h /usr/include/sys/file.h \
 /usr/include/fcntl.h /usr/include/bits/fcntl.h \
 /usr/include/bits/fcntl-linux.h /usr/include/linux/falloc.h \
 /usr/include/bits/stat.h /usr/include/bits/struct_stat.h \
 /usr/include/sys/un.h /usr/include/sys/mman.h /usr/include/bits/mman.h \
 /usr/include/bits/mman-map-flags-generic.h \
 /usr/include/bits/mman-linux.h /usr/include/bits/mman-shared.h \
 /usr/include/bits/mman_ext.h /usr/include/sys/syscall.h \
 /usr/include/asm/unistd.h /usr/include/asm/unistd_64.h \
 /usr/include/bits/syscall.h /usr/include/c++/13/stdlib.h \
 /usr/include/c++/13/cstdlib \
 /usr/include/c++/13/x86_64-redhat-linux/bits/c++config.h \
 /usr/include/c++/13/x86_64-redhat-linux/bits/os_defines.h \
 /usr/include/c++/13/x86_64-redhat-linux/bits/cpu_defines.h \
 /usr/include/c++/13/pstl/pstl_config.h /usr/include/stdlib.h \
 /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h \
 /usr/include/alloca.h /usr/include/bits/stdlib-float.h \
 /usr/include/c++/13/bits/std_abs.h ../machine/interrupt.h \
 ../threads/list.h ../threads/copyright.h ../threads/utility.h \
 ../machine/sysdep.h ../threads/system.h ../machine/interrupt.h \
 ../threads/scheduler.h ../threads/list.h ../threads/thread.h \
 ../machine/stats.h ../machine/timer.h ../threads/utility.h
stats.o: ../machine/stats.cc /usr/include/stdc-predef.h \
 ../threads/copyright.h ../threads/utility.h ../threads/copyright.h \
 ../machine/sysdep.h /usr/include/c++/13/stdlib.h \
 /usr/include/c++/13/cstdlib \
 /usr/include/c++/13/x86_64-redhat-linux/bits/c++config.h \
 /usr/include/bits/wordsize.h \
 /usr/include/c++/13/x86_64-redhat-linux/bits/os_defines.h \
 /usr/include/features.h /usr/include/features-time64.h \
 /usr/include/bits/timesize.h /usr/include/sys/cdefs.h \
 /usr/include/bits/long-double.h /usr/include/gnu/stubs.h \
 /usr/include/gnu/stubs-64.h \
 /usr/include/c++/13/x86_64-redhat-linux/bits/cpu_defines.h \
 /usr/include/c++/13/pstl/pstl_config.h /usr/include/stdlib.h \
 /usr/include/bits/libc-header-start.h \
 /usr/lib/gcc/x86_64-redhat-linux/13/include/stddef.h \
 /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h \
 /usr/include/bits/floatn.h /usr/include/bits/floatn-common.h \
 /usr/include/bits/types/locale_t.h /usr/include/bits/types/__locale_t.h \
 /usr/include/sys/types.h /usr/include/bits/types.h \
 /usr/include/bits/typesizes.h /usr/include/bits/time64.h \
 /usr/include/bits/types/clock_t.h /usr/include/bits/types/clockid_t.h \
 /usr/include/bits/types/time_t.h /usr/include/bits/types/timer_t.h \
 /usr/include/bits/stdint-intn.h /usr/include/endian.h \
 /usr/include/bits/endian.h /usr/include/bits/endianness.h \
 /usr/include/bits/byteswap.h /usr/include/bits/uintn-identity.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/types/sigset_t.h /usr/include/bits/types/__sigset_t.h \
 /usr/include/bits/types/struct_timeval.h \
 /usr/include/bits/types/struct_timespec.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/thread-shared-types.h \
 /usr/include/bits/pthreadtypes-arch.h \
 /usr/include/bits/atomic_wide_counter.h /usr/include/bits/struct_mutex.h \
 /usr/include/bits/struct_rwlock.h /usr/include/alloca.h \
 /usr/include/bits/stdlib-float.h /usr/include/c++/13/bits/std_abs.h \
 /usr/include/stdio.h \
 /usr/lib/gcc/x86_64-redhat-linux/13/include/stdarg.h \
 /usr/include/bits/types/__fpos_t.h /usr/include/bits/types/__mbstate_t.h \
 /usr/include/bits/types/__fpos64_t.h /usr/include/bits/types/__FILE.h \
 /usr/include/bits/types/FILE.h /usr/include/bits/types/struct_FILE.h \
 /usr/include/bits/types/cookie_io_functions_t.h \
 /usr/include/bits/stdio_lim.h /usr/include/string.h \
 /usr/include/strings.h ../machine/stats.h
timer.o: ../machine/timer.cc /usr/include/stdc-predef.h \
 ../threads/copyright.h ../machine/timer.h ../threads/utility.h \
 ../threads/copyright.h ../machine/sysdep.h /usr/include/c++/13/stdlib.h \
 /usr/include/c++/13/cstdlib \
 /usr/include/c++/13/x86_64-redhat-linux/bits/c++config.h \
 /usr/include/bits/wordsize.h \
 /usr/include/c++/13/x86_64-redhat-linux/bits/os_defines.h \
 /usr/include/features.h /usr/include/features-time64.h \
 /usr/include/bits/timesize.h /usr/include/sys/cdefs.h \
 /usr/include/bits/long-double.h /usr/include/gnu/stubs.h \
 /usr/include/gnu/stubs-64.h \
 /usr/include/c++/13/x86_64-redhat-linux/bits/cpu_defines.h \
 /usr/include/c++/13/pstl/pstl_config.h /usr/include/stdlib.h \
 /usr/include/bits/libc-header-start.h \
 /usr/lib/gcc/x86_64-redhat-linux/13/include/stddef.h \
 /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h \
 /usr/include/bits/floatn.h /usr/include/bits/floatn-common.h \
 /usr/include/bits/types/locale_t.h /usr/include/bits/types/__locale_t.h \
 /usr/include/sys/types.h /usr/include/bits/types.h \
 /usr/include/bits/typesizes.h /usr/include/bits/time64.h \
 /usr/include/bits/types/clock_t.h /usr/include/bits/types/clockid_t.h \
 /usr/include/bits/types/time_t.h /usr/include/bits/types/timer_t.h \
 /usr/include/bits/stdint-intn.h /usr/include/endian.h \
 /usr/include/bits/endian.h /usr/include/bits/endianness.h \
 /usr/include/bits/byteswap.h /usr/include/bits/uintn-identity.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/types/sigset_t.h /usr/include/bits/types/__sigset_t.h \
 /usr/include/bits/types/struct_timeval.h \
 /usr/include/bits/types/struct_timespec.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/thread-shared-types.h \
 /usr/include/bits/pthreadtypes-arch.h \
 /usr/include/bits/atomic_wide_counter.h /usr/include/bits/struct_mutex.h \
 /usr/include/bits/struct_rwlock.h /usr/include/alloca.h \
 /usr/include/bits/stdlib-float.h /usr/include/c++/13/bits/std_abs.h \
 /usr/include/stdio.h \
 /usr/lib/gcc/x86_64-redhat-linux/13/include/stdarg.h \
 /usr/include/bits/types/__fpos_t.h /usr/include/bits/types/__mbstate_t.h \
 /usr/include/bits/types/__fpos64_t.h /usr/include/bits/types/__FILE.h \
 /usr/include/bits/types/FILE.h /usr/include/bits/types/struct_FILE.h \
 /usr/include/bits/types/cookie_io_functions_t.h \
 /usr/include/bits/stdio_lim.h /usr/include/string.h \
 /usr/include/strings.h ../threads/system.h ../machine/interrupt.h \
 ../threads/list.h ../threads/utility.h ../threads/scheduler.h \
 ../threads/list.h ../threads/thread.h ../machine/stats.h \
 ../machine/timer.h
preemptive.o: ../threads/preemptive.cc /usr/include/stdc-predef.h \
 ../threads/preemptive.h ../threads/system.h ../threads/copyright.h \
 ../machine/interrupt.h ../threads/copyright.h ../threads/list.h \
 ../threads/utility.h ../machine/sysdep.h /usr/include/c++/13/stdlib.h \
 /usr/include/c++/13/cstdlib \
 /usr/include/c++/13/x86_64-redhat-linux/bits/c++config.h \
 /usr/include/bits/wordsize.h \
 /usr/include/c++/13/x86_64-redhat-linux/bits/os_defines.h \
 /usr/include/features.h /usr/include/features-time64.h \
 /usr/include/bits/timesize.h /usr/include/sys/cdefs.h \
 /usr/include/bits/long-double.h /usr/include/gnu/stubs.h \
 /usr/include/gnu/stubs-64.h \
 /usr/include/c++/13/x86_64-redhat-linux/bits/cpu_defines.h \
 /usr/include/c++/13/pstl/pstl_config.h /usr/include/stdlib.h \
 /usr/include/bits/libc-header-start.h \
 /usr/lib/gcc/x86_64-redhat-linux/13/include/stddef.h \
 /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h \
 /usr/include/bits/floatn.h /usr/include/bits/floatn-common.h \
 /usr/include/bits/types/locale_t.h /usr/include/bits/types/__locale_t.h \
 /usr/include/sys/types.h /usr/include/bits/types.h \
 /usr/include/bits/typesizes.h /usr/include/bits/time64.h \
 /usr/include/bits/types/clock_t.h /usr/include/bits/types/clockid_t.h \
 /usr/include/bits/types/time_t.h /usr/include/bits/types/timer_t.h \
 /usr/include/bits/stdint-intn.h /usr/include/endian.h \
 /usr/include/bits/endian.h /usr/include/bits/endianness.h \
 /usr/include/bits/byteswap.h /usr/include/bits/uintn-identity.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/types/sigset_t.h /usr/include/bits/types/__sigset_t.h \
 /usr/include/bits/types/struct_timeval.h \
 /usr/include/bits/types/struct_timespec.h \
 /usr/include/bits/pthreadtypes.h /usr/include/bits/thread-shared-types.h \
 /usr/include/bits/pthreadtypes-arch.h \
 /usr/include/bits/atomic_wide_counter.h /usr/include/bits/struct_mutex.h \
 /usr/include/bits/struct_rwlock.h /usr/include/alloca.h \
 /usr/include/bits/stdlib-float.h /usr/include/c++/13/bits/std_abs.h \
 /usr/include/stdio.h \
 /usr/lib/gcc/x86_64-redhat-linux/13/include/stdarg.h \
 /usr/include/bits/types/__fpos_t.h /usr/include/bits/types/__mbstate_t.h \
 /usr/include/bits/types/__fpos64_t.h /usr/include/bits/types/__FILE.h \
 /usr/include/bits/types/FILE.h /usr/include/bits/types/struct_FILE.h \
 /usr/include/bits/types/cookie_io_functions_t.h \
 /usr/include/bits/stdio_lim.h /usr/include/string.h \
 /usr/include/strings.h ../threads/scheduler.h ../threads/list.h \
 ../threads/thread.h ../machine/stats.h ../machine/timer.h \
 ../threads/utility.h /usr/include/unistd.h /usr/include/bits/posix_opt.h \
 /usr/include/bits/environments.h /usr/include/bits/confname.h \
 /usr/include/bits/getopt_posix.h /usr/include/bits/getopt_core.h \
 /usr/include/bits/unistd_ext.h /usr/include/linux/close_range.h \
 /usr/include/sys/ptrace.h /usr/include/bits/ptrace-shared.h \
 /usr/include/sys/wait.h /usr/include/signal.h \
 /usr/include/bits/signum-generic.h /usr/include/bits/signum-arch.h \
 /usr/include/bits/types/sig_atomic_t.h \
 /usr/include/bits/types/siginfo_t.h /usr/include/bits/types/__sigval_t.h \
 /usr/include/bits/siginfo-arch.h /usr/include/bits/siginfo-consts.h \
 /usr/include/bits/siginfo-consts-arch.h \
 /usr/include/bits/types/sigval_t.h /usr/include/bits/types/sigevent_t.h \
 /usr/include/bits/sigevent-consts.h /usr/include/bits/sigaction.h \
 /usr/include/bits/sigcontext.h /usr/include/bits/types/stack_t.h \
 /usr/include/sys/ucontext.h /usr/include/bits/sigstack.h \
 /usr/include/bits/sigstksz.h /usr/include/bits/ss_flags.h \
 /usr/include/bits/types/struct_sigstack.h /usr/include/bits/sigthread.h \
 /usr/include/bits/signal_ext.h /usr/include/bits/types/idtype_t.h \
 /usr/include/sys/user.h
# DEPENDENCIES MUST END AT END OF FILE
# IF YOU PUT STUFF HERE IT WILL GO AWAY
# see make depend above
