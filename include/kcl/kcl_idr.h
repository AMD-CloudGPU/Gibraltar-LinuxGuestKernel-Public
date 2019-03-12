#ifndef AMDKCL_IDR_H
#define AMDKCL_IDR_H

#include <linux/idr.h>

#if LINUX_VERSION_CODE < KERNEL_VERSION(4, 5, 0)
#define idr_for_each_entry_continue(idr, entry, id)			\
	for ((entry) = idr_get_next((idr), &(id));			\
	     entry;							\
	     ++id, (entry) = idr_get_next((idr), &(id)))
#endif

#endif /* AMDKCL_IDR_H */
