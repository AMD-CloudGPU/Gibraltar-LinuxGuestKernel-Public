/*
 * Copyright © 2008 Keith Packard
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that copyright
 * notice and this permission notice appear in supporting documentation, and
 * that the name of the copyright holders not be used in advertising or
 * publicity pertaining to distribution of the software without specific,
 * written prior permission.  The copyright holders make no representations
 * about the suitability of this software for any purpose.  It is provided "as
 * is" without express or implied warranty.
 *
 * THE COPYRIGHT HOLDERS DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THIS SOFTWARE.
 */

#ifndef _KCL_DRM_DP_HELPER_H_
#define _KCL_DRM_DP_HELPER_H_

#include <linux/types.h>
#include <linux/i2c.h>
#include <linux/delay.h>

#if DRM_VERSION_CODE >= DRM_VERSION(4, 19, 0)
#include <drm/drm_dp_helper.h>
#endif

#if DRM_VERSION_CODE < DRM_VERSION(4, 11, 0)
#define DP_DPRX_FEATURE_ENUMERATION_LIST    0x2210  /* DP 1.3 */
#endif

static inline void kcl_drm_dp_cec_irq(struct drm_dp_aux *aux)
{
#if DRM_VERSION_CODE >= DRM_VERSION(4, 19, 0)
	drm_dp_cec_irq(aux);
#endif
}

static inline void kcl_drm_dp_cec_register_connector(struct drm_dp_aux *aux,
						 const char *name,
						 struct device *parent)
{
#if DRM_VERSION_CODE >= DRM_VERSION(4, 19, 0)
	drm_dp_cec_register_connector(aux, name, parent);
#endif
}

static inline void kcl_drm_dp_cec_unregister_connector(struct drm_dp_aux *aux)
{
#if DRM_VERSION_CODE >= DRM_VERSION(4, 19, 0)
	drm_dp_cec_unregister_connector(aux);
#endif
}

static inline void kcl_drm_dp_cec_set_edid(struct drm_dp_aux *aux,
				       const struct edid *edid)
{
#if DRM_VERSION_CODE >= DRM_VERSION(4, 19, 0)
	drm_dp_cec_set_edid(aux, edid);
#endif
}

static inline void kcl_drm_dp_cec_unset_edid(struct drm_dp_aux *aux)
{
#if DRM_VERSION_CODE >= DRM_VERSION(4, 19, 0)
	drm_dp_cec_unset_edid(aux);
#endif
}

#endif /* _KCL_DRM_DP_HELPER_H_ */
