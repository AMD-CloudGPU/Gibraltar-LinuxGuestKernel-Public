#ifndef AMDGPU_BACKPORT_H
#define AMDGPU_BACKPORT_H

#include <kcl/kcl_kref.h>
#include <kcl/kcl_fence.h>
#include <kcl/kcl_drm.h>
#include <kcl/kcl_reservation.h>
#include <kcl/kcl_amdgpu.h>
#include <kcl/kcl_mm.h>
#include <kcl/kcl_vga_switcheroo.h>
#include <kcl/kcl_fence_array.h>
#include <kcl/kcl_kthread.h>
#include <kcl/kcl_io.h>
#if LINUX_VERSION_CODE < KERNEL_VERSION(3, 7, 0)
#include <kcl/kcl_interval_tree_generic.h>
#endif

#endif /* AMDGPU_BACKPORT_H */
