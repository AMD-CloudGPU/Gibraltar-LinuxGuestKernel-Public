dnl #
dnl # commit v5.0-rc1-342-gfcd70cd36b9b
dnl # drm: Split out drm_probe_helper.h
dnl #
AC_DEFUN([AC_AMDGPU_DRM_PROBE_HELPER_H],
	[AC_MSG_CHECKING([whether drm/drm_probe_helper.h is available])
	AC_KERNEL_TEST_HEADER_FILE_EXIST([drm/drm_probe_helper.h], [
		AC_MSG_RESULT(yes)
		AC_DEFINE(HAVE_DRM_PROBE_HELPER_H, 1, [drm/drm_probe_helper.h is available])
	],[
		AC_MSG_RESULT(no)
	])
])
