#ifndef AMDKCL_DRM_H
#define AMDKCL_DRM_H

#include <linux/version.h>
#include <drm/drmP.h>
#include <drm/drm_fb_helper.h>
#include <drm/drm_atomic.h>
#include <drm/drm_gem.h>
#include <drm/drm_atomic_helper.h>

extern void (*_kcl_drm_fb_helper_cfb_fillrect)(struct fb_info *info,
				const struct fb_fillrect *rect);
extern void (*_kcl_drm_fb_helper_cfb_copyarea)(struct fb_info *info,
				const struct fb_copyarea *area);
extern void (*_kcl_drm_fb_helper_cfb_imageblit)(struct fb_info *info,
				 const struct fb_image *image);
extern void (*_kcl_drm_fb_helper_unregister_fbi)(struct drm_fb_helper *fb_helper);
extern struct fb_info *(*_kcl_drm_fb_helper_alloc_fbi)(struct drm_fb_helper *fb_helper);
extern void (*_kcl_drm_fb_helper_release_fbi)(struct drm_fb_helper *fb_helper);
extern void (*_kcl_drm_fb_helper_set_suspend)(struct drm_fb_helper *fb_helper, int state);
extern void
(*_kcl_drm_atomic_helper_update_legacy_modeset_state)(struct drm_device *dev,
					      struct drm_atomic_state *old_state);

#if DRM_VERSION_CODE < DRM_VERSION(4, 5, 0)  && \
	!defined(OS_NAME_UBUNTU)
extern int drm_pcie_get_max_link_width(struct drm_device *dev, u32 *mlw);
#endif

static inline void kcl_drm_fb_helper_cfb_fillrect(struct fb_info *info,
				const struct fb_fillrect *rect)
{
#ifdef BUILD_AS_DKMS
	_kcl_drm_fb_helper_cfb_fillrect(info, rect);
#else
	drm_fb_helper_cfb_fillrect(info, rect);
#endif
}

static inline void kcl_drm_fb_helper_cfb_copyarea(struct fb_info *info,
				const struct fb_copyarea *area)
{
#ifdef BUILD_AS_DKMS
	_kcl_drm_fb_helper_cfb_copyarea(info, area);
#else
	drm_fb_helper_cfb_copyarea(info, area);
#endif
}

static inline void kcl_drm_fb_helper_cfb_imageblit(struct fb_info *info,
				 const struct fb_image *image)
{
#ifdef BUILD_AS_DKMS
	_kcl_drm_fb_helper_cfb_imageblit(info, image);
#else
	drm_fb_helper_cfb_imageblit(info, image);
#endif
}

static inline struct fb_info *kcl_drm_fb_helper_alloc_fbi(struct drm_fb_helper *fb_helper)
{
#ifdef BUILD_AS_DKMS
	return _kcl_drm_fb_helper_alloc_fbi(fb_helper);
#else
	return drm_fb_helper_alloc_fbi(fb_helper);
#endif
}

static inline void kcl_drm_fb_helper_release_fbi(struct drm_fb_helper *fb_helper)
{
#ifdef BUILD_AS_DKMS
	_kcl_drm_fb_helper_release_fbi(fb_helper);
#else
	drm_fb_helper_release_fbi(fb_helper);
#endif
}

static inline void kcl_drm_fb_helper_unregister_fbi(struct drm_fb_helper *fb_helper)
{
#ifdef BUILD_AS_DKMS
	_kcl_drm_fb_helper_unregister_fbi(fb_helper);
#else
	drm_fb_helper_unregister_fbi(fb_helper);
#endif
}

static inline void kcl_drm_fb_helper_set_suspend(struct drm_fb_helper *fb_helper, int state)
{
#ifdef BUILD_AS_DKMS
	_kcl_drm_fb_helper_set_suspend(fb_helper, state);
#else
	drm_fb_helper_set_suspend(fb_helper, state);
#endif
}

static inline void
kcl_drm_atomic_helper_update_legacy_modeset_state(struct drm_device *dev,
					      struct drm_atomic_state *old_state)
{
#ifdef BUILD_AS_DKMS
	_kcl_drm_atomic_helper_update_legacy_modeset_state(dev, old_state);
#else
	drm_atomic_helper_update_legacy_modeset_state(dev, old_state);
#endif
}

#ifndef DRM_DEBUG_VBL
#define DRM_UT_VBL		0x20
#define DRM_DEBUG_VBL(fmt, args...)					\
	do {								\
		if (unlikely(drm_debug & DRM_UT_VBL))			\
			drm_ut_debug_printk(__func__, fmt, ##args);	\
	} while (0)
#endif

static inline bool kcl_drm_arch_can_wc_memory(void)
{
#if defined(CONFIG_PPC) && !defined(CONFIG_NOT_COHERENT_CACHE)
	return false;
#elif defined(CONFIG_MIPS) && defined(CONFIG_CPU_LOONGSON3)
	return false;
#else
	return true;
#endif
}

static inline int kcl_drm_encoder_init(struct drm_device *dev,
		      struct drm_encoder *encoder,
		      const struct drm_encoder_funcs *funcs,
		      int encoder_type, const char *name, ...)
{
#if DRM_VERSION_CODE >= DRM_VERSION(4, 5, 0)
	return drm_encoder_init(dev, encoder, funcs,
			 encoder_type, name);
#else
	return drm_encoder_init(dev, encoder, funcs,
			 encoder_type);
#endif
}

static inline int kcl_drm_crtc_init_with_planes(struct drm_device *dev, struct drm_crtc *crtc,
			      struct drm_plane *primary,
			      struct drm_plane *cursor,
			      const struct drm_crtc_funcs *funcs,
			      const char *name, ...)
{
#if DRM_VERSION_CODE >= DRM_VERSION(4, 5, 0)
		return drm_crtc_init_with_planes(dev, crtc, primary,
				 cursor, funcs, name);
#else
		return drm_crtc_init_with_planes(dev, crtc, primary,
				 cursor, funcs);
#endif
}

static inline int kcl_drm_universal_plane_init(struct drm_device *dev, struct drm_plane *plane,
			     unsigned long possible_crtcs,
			     const struct drm_plane_funcs *funcs,
			     const uint32_t *formats, unsigned int format_count,
			     enum drm_plane_type type,
			     const char *name, ...)
{
#if DRM_VERSION_CODE >= DRM_VERSION(4, 5, 0)
		return drm_universal_plane_init(dev, plane, possible_crtcs, funcs,
				 formats, format_count, type, name);
#else
		return drm_universal_plane_init(dev, plane, possible_crtcs, funcs,
				 formats, format_count, type);
#endif
}

static inline int
kcl_drm_calc_vbltimestamp_from_scanoutpos(struct drm_device *dev,
					  unsigned int pipe,
					  int *max_error,
					  struct timeval *vblank_time,
					  unsigned flags,
					  const struct drm_crtc *refcrtc,
					  const struct drm_display_mode *mode)
{
#if DRM_VERSION_CODE < DRM_VERSION(4, 4, 0)
	return drm_calc_vbltimestamp_from_scanoutpos(dev, pipe, max_error, vblank_time,
						     flags, refcrtc, mode);
#else
	return drm_calc_vbltimestamp_from_scanoutpos(dev, pipe, max_error, vblank_time,
						     flags, mode);
#endif
}

#endif /* AMDKCL_DRM_H */
