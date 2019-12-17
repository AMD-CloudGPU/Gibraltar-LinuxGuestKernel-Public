dnl #
dnl # commit 649027d73a630
dnl # workqueue: implement high priority workqueue
dnl #
AC_DEFUN([AC_AMDGPU_WQ_HIGHPRI], [
	AC_MSG_CHECKING([whether WQ_HIGHPRI is available])
	AC_KERNEL_TRY_COMPILE([
		#include <linux/workqueue.h>
	], [
		unsigned int flags = WQ_HIGHPRI;
	], [
		AC_MSG_RESULT(yes)
		AC_DEFINE(HAVE_WQ_HIGHPRI, 1, [WQ_HIGHPRI is available])
	], [
		AC_MSG_RESULT(no)
	])
])
