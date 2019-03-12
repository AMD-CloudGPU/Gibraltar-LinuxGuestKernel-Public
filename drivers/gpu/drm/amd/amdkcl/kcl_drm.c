#include <kcl/kcl_drm.h>
#include "kcl_common.h"

#if DRM_VERSION_CODE < DRM_VERSION(4, 5, 0) && !(defined(OS_NAME_UBUNTU) || defined(OS_NAME_SLE))
int drm_pcie_get_max_link_width(struct drm_device *dev, u32 *mlw)
{
	struct pci_dev *root;
	u32 lnkcap;

	*mlw = 0;
	if (!dev->pdev)
		return -EINVAL;

	root = dev->pdev->bus->self;
	if (!root)
		return -EINVAL;

	pcie_capability_read_dword(root, PCI_EXP_LNKCAP, &lnkcap);

	*mlw = (lnkcap & PCI_EXP_LNKCAP_MLW) >> 4;

	DRM_INFO("probing mlw for device %x:%x = %x\n", root->vendor, root->device, lnkcap);
	return 0;
}
EXPORT_SYMBOL(drm_pcie_get_max_link_width);
#endif

void (*_kcl_drm_fb_helper_cfb_fillrect)(struct fb_info *info,
				const struct fb_fillrect *rect);
EXPORT_SYMBOL(_kcl_drm_fb_helper_cfb_fillrect);

void (*_kcl_drm_fb_helper_cfb_copyarea)(struct fb_info *info,
				const struct fb_copyarea *area);
EXPORT_SYMBOL(_kcl_drm_fb_helper_cfb_copyarea);

void (*_kcl_drm_fb_helper_cfb_imageblit)(struct fb_info *info,
				 const struct fb_image *image);
EXPORT_SYMBOL(_kcl_drm_fb_helper_cfb_imageblit);

void (*_kcl_drm_fb_helper_unregister_fbi)(struct drm_fb_helper *fb_helper);
EXPORT_SYMBOL(_kcl_drm_fb_helper_unregister_fbi);

struct fb_info *(*_kcl_drm_fb_helper_alloc_fbi)(struct drm_fb_helper *fb_helper);
EXPORT_SYMBOL(_kcl_drm_fb_helper_alloc_fbi);

void (*_kcl_drm_fb_helper_release_fbi)(struct drm_fb_helper *fb_helper);
EXPORT_SYMBOL(_kcl_drm_fb_helper_release_fbi);

void (*_kcl_drm_fb_helper_set_suspend)(struct drm_fb_helper *fb_helper, int state);
EXPORT_SYMBOL(_kcl_drm_fb_helper_set_suspend);

void
(*_kcl_drm_atomic_helper_update_legacy_modeset_state)(struct drm_device *dev,
				struct drm_atomic_state *old_state);
EXPORT_SYMBOL(_kcl_drm_atomic_helper_update_legacy_modeset_state);

/**
 * _kcl_drm_fb_helper_cfb_fillrect_stub - wrapper around cfb_fillrect
 * @info: fbdev registered by the helper
 * @rect: info about rectangle to fill
 *
 * A wrapper around cfb_imageblit implemented by fbdev core
 */
void _kcl_drm_fb_helper_cfb_fillrect_stub(struct fb_info *info,
				const struct fb_fillrect *rect)
{
	cfb_fillrect(info, rect);
}

/**
 * _kcl_drm_fb_helper_cfb_copyarea_stub - wrapper around cfb_copyarea
 * @info: fbdev registered by the helper
 * @area: info about area to copy
 *
 * A wrapper around cfb_copyarea implemented by fbdev core
 */
void _kcl_drm_fb_helper_cfb_copyarea_stub(struct fb_info *info,
				const struct fb_copyarea *area)
{
	cfb_copyarea(info, area);
}

/**
 * _kcl_drm_fb_helper_cfb_imageblit_stub - wrapper around cfb_imageblit
 * @info: fbdev registered by the helper
 * @image: info about image to blit
 *
 * A wrapper around cfb_imageblit implemented by fbdev core
 */
void _kcl_drm_fb_helper_cfb_imageblit_stub(struct fb_info *info,
				 const struct fb_image *image)
{
	cfb_imageblit(info, image);
}

/**
 * _kcl_drm_fb_helper_alloc_fbi_stub - allocate fb_info and some of its members
 * @fb_helper: driver-allocated fbdev helper
 *
 * A helper to alloc fb_info and the members cmap and apertures. Called
 * by the driver within the fb_probe fb_helper callback function.
 *
 * RETURNS:
 * fb_info pointer if things went okay, pointer containing error code
 * otherwise
 */
struct fb_info *_kcl_drm_fb_helper_alloc_fbi_stub(struct drm_fb_helper *fb_helper)
{
	struct device *dev = fb_helper->dev->dev;
	struct fb_info *info;
	int ret;

	info = framebuffer_alloc(0, dev);
	if (!info)
		return ERR_PTR(-ENOMEM);

	ret = fb_alloc_cmap(&info->cmap, 256, 0);
	if (ret)
		goto err_release;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 35)
	info->apertures = alloc_apertures(1);
	if (!info->apertures) {
		ret = -ENOMEM;
		goto err_free_cmap;
	}
#endif

	fb_helper->fbdev = info;

	return info;

err_free_cmap:
	fb_dealloc_cmap(&info->cmap);
err_release:
	framebuffer_release(info);
	return ERR_PTR(ret);
}

/**
 * _kcl_drm_fb_helper_unregister_fbi_stub - unregister fb_info framebuffer device
 * @fb_helper: driver-allocated fbdev helper
 *
 * A wrapper around unregister_framebuffer, to release the fb_info
 * framebuffer device
 */
void _kcl_drm_fb_helper_unregister_fbi_stub(struct drm_fb_helper *fb_helper)
{
	if (fb_helper && fb_helper->fbdev)
		unregister_framebuffer(fb_helper->fbdev);
}

/**
 * _kcl_drm_fb_helper_release_fbi_stub - dealloc fb_info and its members
 * @fb_helper: driver-allocated fbdev helper
 *
 * A helper to free memory taken by fb_info and the members cmap and
 * apertures
 */
void _kcl_drm_fb_helper_release_fbi_stub(struct drm_fb_helper *fb_helper)
{
	if (fb_helper) {
		struct fb_info *info = fb_helper->fbdev;

		if (info) {
			if (info->cmap.len)
				fb_dealloc_cmap(&info->cmap);
			framebuffer_release(info);
		}

		fb_helper->fbdev = NULL;
	}
}

/**
 * _kcl_drm_fb_helper_set_suspend_stub - wrapper around fb_set_suspend
 * @fb_helper: driver-allocated fbdev helper
 * @state: desired state, zero to resume, non-zero to suspend
 *
 * A wrapper around fb_set_suspend implemented by fbdev core
 */
void _kcl_drm_fb_helper_set_suspend_stub(struct drm_fb_helper *fb_helper, int state)
{
	if (fb_helper && fb_helper->fbdev)
		fb_set_suspend(fb_helper->fbdev, state);
}

static inline bool
_kcl_drm_atomic_crtc_needs_modeset(struct drm_crtc_state *state)
{
    return state->mode_changed || state->active_changed ;
}

static inline struct drm_plane_state *
_kcl_drm_atomic_get_existing_plane_state(struct drm_atomic_state *state,
                    struct drm_plane *plane)
{
#if DRM_VERSION_CODE < DRM_VERSION(4, 8, 0)
	return state->plane_states[drm_plane_index(plane)];
#else
	return state->planes[drm_plane_index(plane)].state;
#endif
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(4, 15, 0)

#define for_each_connector_in_state(__state, connector, connector_state, __i) \
	for ((__i) = 0;							\
	     (__i) < (__state)->num_connector &&				\
	     ((connector) = (__state)->connectors[__i].ptr,			\
	     (connector_state) = (__state)->connectors[__i].state, 1); 	\
	     (__i)++)							\
		for_each_if (connector)

#define for_each_crtc_in_state(__state, crtc, crtc_state, __i)	\
	for ((__i) = 0;						\
	     (__i) < (__state)->dev->mode_config.num_crtc &&	\
	     ((crtc) = (__state)->crtcs[__i].ptr,			\
	     (crtc_state) = (__state)->crtcs[__i].state, 1);	\
	     (__i)++)						\
		for_each_if (crtc_state)

#endif

void
_kcl_drm_atomic_helper_update_legacy_modeset_state_stub(struct drm_device *dev,
					      struct drm_atomic_state *old_state)
{
	struct drm_connector *connector;
	struct drm_connector_state *old_conn_state;
	struct drm_crtc *crtc;
	struct drm_crtc_state *old_crtc_state;
	int i;

	/* clear out existing links and update dpms */
	for_each_connector_in_state(old_state, connector, old_conn_state, i) {
		if (connector->encoder) {
			WARN_ON(!connector->encoder->crtc);

			connector->encoder->crtc = NULL;
			connector->encoder = NULL;
		}

		crtc = connector->state->crtc;
		if ((!crtc && old_conn_state->crtc) ||
		    (crtc && _kcl_drm_atomic_crtc_needs_modeset(crtc->state))) {
			struct drm_property *dpms_prop =
				dev->mode_config.dpms_property;
			int mode = DRM_MODE_DPMS_OFF;

			if (crtc && crtc->state->active)
				mode = DRM_MODE_DPMS_ON;

			connector->dpms = mode;
			drm_object_property_set_value(&connector->base,
						      dpms_prop, mode);
		}
	}

	/* set new links */
	for_each_connector_in_state(old_state, connector, old_conn_state, i) {
		if (!connector->state->crtc)
			continue;

		if (WARN_ON(!connector->state->best_encoder))
			continue;

		connector->encoder = connector->state->best_encoder;
		connector->encoder->crtc = connector->state->crtc;
	}

	/* set legacy state in the crtc structure */
	for_each_crtc_in_state(old_state, crtc, old_crtc_state, i) {
		struct drm_plane *primary = crtc->primary;

		crtc->mode = crtc->state->mode;
		crtc->enabled = crtc->state->enable;

		if (_kcl_drm_atomic_get_existing_plane_state(old_state, primary) &&
		    primary->state->crtc == crtc) {
			crtc->x = primary->state->src_x >> 16;
			crtc->y = primary->state->src_y >> 16;
		}

		if (crtc->state->enable)
			drm_calc_timestamping_constants(crtc,
							&crtc->state->adjusted_mode);
	}
}

void amdkcl_drm_init(void)
{
	_kcl_drm_fb_helper_cfb_fillrect = amdkcl_fp_setup("drm_fb_helper_cfb_fillrect",
					_kcl_drm_fb_helper_cfb_fillrect_stub);
	_kcl_drm_fb_helper_cfb_copyarea = amdkcl_fp_setup("drm_fb_helper_cfb_copyarea",
					_kcl_drm_fb_helper_cfb_copyarea_stub);
	_kcl_drm_fb_helper_cfb_imageblit = amdkcl_fp_setup("drm_fb_helper_cfb_imageblit",
					_kcl_drm_fb_helper_cfb_imageblit_stub);
	_kcl_drm_fb_helper_alloc_fbi = amdkcl_fp_setup("drm_fb_helper_alloc_fbi",
					_kcl_drm_fb_helper_alloc_fbi_stub);
	_kcl_drm_fb_helper_unregister_fbi = amdkcl_fp_setup("drm_fb_helper_unregister_fbi",
					_kcl_drm_fb_helper_unregister_fbi_stub);
	_kcl_drm_fb_helper_release_fbi = amdkcl_fp_setup("drm_fb_helper_release_fbi",
					_kcl_drm_fb_helper_release_fbi_stub);
	_kcl_drm_fb_helper_set_suspend = amdkcl_fp_setup("drm_fb_helper_set_suspend",
					_kcl_drm_fb_helper_set_suspend_stub);
	_kcl_drm_atomic_helper_update_legacy_modeset_state = amdkcl_fp_setup(
					"drm_atomic_helper_update_legacy_modeset_state",
					_kcl_drm_atomic_helper_update_legacy_modeset_state_stub);
}
