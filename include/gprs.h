/*
 *
 *  oFono - Open Source Telephony
 *
 *  Copyright (C) 2008-2009  Intel Corporation. All rights reserved.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 2 as
 *  published by the Free Software Foundation.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#ifndef __OFONO_GPRS_H
#define __OFONO_GPRS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <ofono/types.h>

struct ofono_gprs;

struct ofono_gprs_primary_context {
	unsigned id;
	int type;
	int direction;
	int active;
	char *apn;
	char *username;
	char *password;
};

typedef void (*ofono_gprs_status_cb_t)(const struct ofono_error *error,
						int status, int lac, int ci,
						int tech, void *data);

typedef void (*ofono_gprs_cb_t)(const struct ofono_error *error, void *data);

typedef void (*ofono_gprs_alloc_cb_t)(const struct ofono_error *error,
					struct ofono_gprs_primary_context *ctx,
					void *data);

struct ofono_gprs_driver {
	const char *name;
	int (*probe)(struct ofono_gprs *gprs, unsigned int vendor,
			void *data);
	void (*remove)(struct ofono_gprs *gprs);
	void (*set_attached)(struct ofono_gprs *gprs, int attached,
				ofono_gprs_cb_t cb, void *data);
	void (*set_active)(struct ofono_gprs *gprs, unsigned id,
				int active, ofono_gprs_cb_t cb,
				void *data);
	void (*set_active_all)(struct ofono_gprs *gprs,
				int active, ofono_gprs_cb_t cb,
				void *data);
	void (*create_context)(struct ofono_gprs *gprs,
				ofono_gprs_alloc_cb_t cb,
				void *data);
	void (*remove_context)(struct ofono_gprs *gprs, unsigned id,
				ofono_gprs_cb_t cb, void *data);
	void (*registration_status)(struct ofono_gprs *gprs,
					ofono_gprs_status_cb_t cb, void *data);
};

void ofono_gprs_status_notify(struct ofono_gprs *gprs,
				int status, int lac, int ci, int tech);

void ofono_gprs_notify(struct ofono_gprs *gprs,
					struct ofono_gprs_primary_context *ctx);
void ofono_gprs_deactivated(struct ofono_gprs *gprs,
					unsigned id);
void ofono_gprs_detached(struct ofono_gprs *gprs);

int ofono_gprs_driver_register(const struct ofono_gprs_driver *d);
void ofono_gprs_driver_unregister(const struct ofono_gprs_driver *d);

struct ofono_gprs *ofono_gprs_create(struct ofono_modem *modem,
					unsigned int vendor, const char *driver,
					void *data);
void ofono_gprs_register(struct ofono_gprs *gprs);
void ofono_gprs_remove(struct ofono_gprs *gprs);

void ofono_gprs_set_data(struct ofono_gprs *gprs, void *data);
void *ofono_gprs_get_data(struct ofono_gprs *gprs);

#ifdef __cplusplus
}
#endif

#endif /* __OFONO_GPRS_H */
