#include <contacts.h>
#include <stdlib.h>

#include "utc-contacts-service-tc-utils.h"
#include "utc-contacts-service-record-name.h"
#include "utc-contacts-service-record-image.h"
#include "utc-contacts-service-record-company.h"
#include "utc-contacts-service-record-note.h"
#include "utc-contacts-service-record-number.h"
#include "utc-contacts-service-record-email.h"
#include "utc-contacts-service-record-event.h"
#include "utc-contacts-service-record-messenger.h"
#include "utc-contacts-service-record-address.h"
#include "utc-contacts-service-record-url.h"
#include "utc-contacts-service-record-nickname.h"
#include "utc-contacts-service-record-profile.h"
#include "utc-contacts-service-record-relationship.h"
#include "utc-contacts-service-record-extension.h"
#include "utc-contacts-service-record-contact.h"
#include "utc-contacts-service-record-sip.h"

// _contacts_my_profile
#define CTSVC_MY_PROFILE_UID_C1 "UID_C"
#define CTSVC_MY_PROFILE_UID_U1 "UID_U"
#define CTSVC_MY_PROFILE_UID_C2 "UID_C2"
#define CTSVC_MY_PROFILE_UID_U2 "UID_U2"

ctsvc_view_s _view_my_profile;
bool _view_my_profile_load = false;

static void _ctsvc_tc_load_view_my_profile()
{
	_view_my_profile_load = true;
	// _contacts_my_profile
	ctsvc_property_s my_profile_create1[] = {
		ctsvc_tc_util_create_str_property(_contacts_my_profile.uid, CTSVC_MY_PROFILE_UID_C1),
	};
	ctsvc_property_s my_profile_update1[] = {
		ctsvc_tc_util_create_str_property(_contacts_my_profile.uid, CTSVC_MY_PROFILE_UID_U1),
	};
	ctsvc_property_s my_profile_create2[] = {
		ctsvc_tc_util_create_str_property(_contacts_my_profile.uid, CTSVC_MY_PROFILE_UID_C2),
	};
	ctsvc_property_s my_profile_update2[] = {
		ctsvc_tc_util_create_str_property(_contacts_my_profile.uid, CTSVC_MY_PROFILE_UID_U2),
	};

	_view_my_profile.create1_count = sizeof(my_profile_create1)/sizeof(ctsvc_property_s);
	_view_my_profile.create2_count = sizeof(my_profile_create2)/sizeof(ctsvc_property_s);
	_view_my_profile.update1_count = sizeof(my_profile_update1)/sizeof(ctsvc_property_s);
	_view_my_profile.update2_count = sizeof(my_profile_update2)/sizeof(ctsvc_property_s);

	_view_my_profile.create1 = calloc(_view_my_profile.create1_count, sizeof(ctsvc_property_s));
	_view_my_profile.create2 = calloc(_view_my_profile.create2_count, sizeof(ctsvc_property_s));
	_view_my_profile.update1 = calloc(_view_my_profile.update1_count, sizeof(ctsvc_property_s));
	_view_my_profile.update2 = calloc(_view_my_profile.update2_count, sizeof(ctsvc_property_s));

	int i;
	for (i=0;i<_view_my_profile.create1_count;i++)
		_view_my_profile.create1[i] = my_profile_create1[i];
	for (i=0;i<_view_my_profile.create2_count;i++)
		_view_my_profile.create2[i] = my_profile_create2[i];
	for (i=0;i<_view_my_profile.update1_count;i++)
		_view_my_profile.update1[i] = my_profile_update1[i];
	for (i=0;i<_view_my_profile.update2_count;i++)
		_view_my_profile.update2[i] = my_profile_update2[i];
}

static int _ctsvc_tc_record_free_property_my_profile()
{
	if (false == _view_my_profile_load)
		return -1;

	_view_my_profile_load = false;

	_view_my_profile.create1 = calloc(_view_my_profile.create1_count, sizeof(ctsvc_property_s));
	_view_my_profile.create2 = calloc(_view_my_profile.create2_count, sizeof(ctsvc_property_s));
	_view_my_profile.update1 = calloc(_view_my_profile.update1_count, sizeof(ctsvc_property_s));
	_view_my_profile.update2 = calloc(_view_my_profile.update2_count, sizeof(ctsvc_property_s));

	return 0;
}

int ctsvc_tc_record_get_property_my_profile(ctsvc_property_type_e type, ctsvc_property_s **p_properties, int *p_property_count)
{
	if (false == _view_my_profile_load)
		_ctsvc_tc_load_view_my_profile();

	switch (type) {
	case PROPERTY_TYPE_CREATE1:
		*p_properties = _view_my_profile.create1;
		*p_property_count = _view_my_profile.create1_count;
		break;
	case PROPERTY_TYPE_CREATE2:
		*p_properties = _view_my_profile.create2;
		*p_property_count = _view_my_profile.create2_count;
		break;
	case PROPERTY_TYPE_UPDATE1:
		*p_properties = _view_my_profile.update1;
		*p_property_count = _view_my_profile.update1_count;
		break;
	case PROPERTY_TYPE_UPDATE2:
		*p_properties = _view_my_profile.update2;
		*p_property_count = _view_my_profile.update2_count;
		break;
	default :
		break;
	}
	return 0;
}

int ctsvc_tc_record_compare_my_profile(contacts_record_h record, ctsvc_property_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *properties = NULL;
	do {
		if (0 != (ret = ctsvc_tc_record_get_property_my_profile(type, &properties, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_record_compare(record, properties, property_count))) break;
		return 0;
	} while (0);
	return ret;
}

int ctsvc_tc_filter_set_my_profile(contacts_filter_h filter, ctsvc_property_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *properties = NULL;
	do {
		if (0 != (ret = ctsvc_tc_record_get_property_my_profile(type, &properties, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_filter_set(filter, properties, property_count))) break;
		return 0;
	} while (0);
	return ret;
}


int ctsvc_tc_record_update_my_profile(contacts_record_h record, ctsvc_property_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *property_list = NULL;
	do {
		if (0 != (ret = ctsvc_tc_record_get_property_my_profile(type, &property_list, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_record_set_property(record, property_list, property_count))) break;
		return 0;
	} while (0);
	return ret;
}

int ctsvc_tc_record_create_my_profile(int address_book_id, ctsvc_property_type_e type, contacts_record_h *p_record)
{
	int ret = 0;
	contacts_record_h record = NULL;
	int property_count = 0;
	ctsvc_property_s *property_list = NULL;

	contacts_record_h name = NULL;
	contacts_record_h image = NULL;
	contacts_record_h company = NULL;
	contacts_record_h note = NULL;
	contacts_record_h number = NULL;
	contacts_record_h email = NULL;
	contacts_record_h event = NULL;
	contacts_record_h messenger = NULL;
	contacts_record_h address = NULL;
	contacts_record_h url = NULL;
	contacts_record_h nickname = NULL;
	contacts_record_h profile = NULL;
	contacts_record_h relationship = NULL;
	contacts_record_h extension = NULL;
	contacts_record_h sip = NULL;

	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_my_profile._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_set_int(record, _contacts_my_profile.address_book_id, address_book_id))) break;
		if (0 != (ret = ctsvc_tc_record_get_property_my_profile(type, &property_list, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_record_set_property(record, property_list, property_count))) break;
		if (0 != (ret = ctsvc_tc_record_create_name(0, type, &name))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_add_child_record(record, _contacts_my_profile.name, name))) break;
		if (0 != (ret = ctsvc_tc_record_create_image(0, type, &image))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_add_child_record(record, _contacts_my_profile.image, image))) break;
		if (0 != (ret = ctsvc_tc_record_create_company(0, type, &company))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_add_child_record(record, _contacts_my_profile.company, company))) break;
		if (0 != (ret = ctsvc_tc_record_create_note(0, type, &note))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_add_child_record(record, _contacts_my_profile.note, note))) break;
		if (0 != (ret = ctsvc_tc_record_create_number(0, type, &number))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_add_child_record(record, _contacts_my_profile.number, number))) break;
		if (0 != (ret = ctsvc_tc_record_create_email(0, type, &email))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_add_child_record(record, _contacts_my_profile.email, email))) break;
		if (0 != (ret = ctsvc_tc_record_create_event(0, type, &event))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_add_child_record(record, _contacts_my_profile.event, event))) break;
		if (0 != (ret = ctsvc_tc_record_create_messenger(0, type, &messenger))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_add_child_record(record, _contacts_my_profile.messenger, messenger))) break;
		if (0 != (ret = ctsvc_tc_record_create_address(0, type, &address))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_add_child_record(record, _contacts_my_profile.address, address))) break;
		if (0 != (ret = ctsvc_tc_record_create_url(0, type, &url))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_add_child_record(record, _contacts_my_profile.url, url))) break;
		if (0 != (ret = ctsvc_tc_record_create_nickname(0, type, &nickname))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_add_child_record(record, _contacts_my_profile.nickname, nickname))) break;
		if (0 != (ret = ctsvc_tc_record_create_profile(0, type, &profile))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_add_child_record(record, _contacts_my_profile.profile, profile))) break;
		if (0 != (ret = ctsvc_tc_record_create_relationship(0, type, &relationship))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_add_child_record(record, _contacts_my_profile.relationship, relationship))) break;
		if (0 != (ret = ctsvc_tc_record_create_extension(0, type, &extension))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_add_child_record(record, _contacts_my_profile.extension, extension))) break;
		if (0 != (ret = ctsvc_tc_record_create_sip(0, type, &sip))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_add_child_record(record, _contacts_my_profile.sip, sip))) break;
	} while (0);
	*p_record = record;
	return ret;
}

static int _ctsvc_tc_record_clone_my_profile(void)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *property_list = NULL;
	contacts_record_h record = NULL;
	contacts_record_h record_clone = NULL;

	do {
		if (CONTACTS_ERROR_NONE != (ret = ctsvc_tc_record_create_my_profile(0, PROPERTY_TYPE_CREATE1, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_clone(record, &record_clone))) break;
		if (CONTACTS_ERROR_NONE != (ret = ctsvc_tc_record_get_property_my_profile(PROPERTY_TYPE_CREATE1, &property_list, &property_count))) break;
		if (CONTACTS_ERROR_NONE != (ret = ctsvc_tc_util_record_compare(record_clone, property_list, property_count))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record_clone, true))) break;
		record_clone = NULL;
		return 0;
	} while(0);
	contacts_record_destroy(record, true);
	contacts_record_destroy(record_clone, true);
	return ret;
}

static int _ctsvc_tc_record_create_my_profile(void)
{
	int ret = 0;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_my_profile._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while(0);
	contacts_record_destroy(record, true);
	return ret;
}

static int _ctsvc_tc_record_destroy_my_profile(void)
{
	int ret = 0;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_my_profile._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while(0);
	contacts_record_destroy(record, true);
	return ret;
}

static int _ctsvc_tc_record_get_uri_p_my_profile(void)
{
	int ret = 0;
	const char *uri = NULL;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_my_profile._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_get_uri_p(record, &uri))) break;
		if (NULL == uri || STRING_EQUAL != strcmp(uri, _contacts_my_profile._uri)) {
			ret = -1;
			break;
		}
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while(0);
	contacts_record_destroy(record, true);
	return ret;
}

static int _ctsvc_tc_record_add_child_record(contacts_record_h record, unsigned int property_id, const char *view_uri)
{
	int ret;
	contacts_record_h child = NULL;

	ret = contacts_record_create(view_uri, &child);
	if (CONTACTS_ERROR_NONE != ret)
		return ret;

	ret = contacts_record_add_child_record(record, property_id, child);
	if (CONTACTS_ERROR_NONE != ret)
		contacts_record_destroy(child, true);

	return ret;
}

static int _ctsvc_tc_record_add_child_record_my_profile(void)
{
	int ret = 0;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_my_profile._uri, &record))) break;
		if (0 != (ret = _ctsvc_tc_record_add_child_record(record, _contacts_my_profile.name, _contacts_name._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_add_child_record(record, _contacts_my_profile.image, _contacts_image._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_add_child_record(record, _contacts_my_profile.company, _contacts_company._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_add_child_record(record, _contacts_my_profile.note, _contacts_note._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_add_child_record(record, _contacts_my_profile.number, _contacts_number._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_add_child_record(record, _contacts_my_profile.email, _contacts_email._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_add_child_record(record, _contacts_my_profile.event, _contacts_event._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_add_child_record(record, _contacts_my_profile.messenger, _contacts_messenger._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_add_child_record(record, _contacts_my_profile.address, _contacts_address._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_add_child_record(record, _contacts_my_profile.url, _contacts_url._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_add_child_record(record, _contacts_my_profile.nickname, _contacts_nickname._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_add_child_record(record, _contacts_my_profile.profile, _contacts_profile._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_add_child_record(record, _contacts_my_profile.relationship, _contacts_relationship._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_add_child_record(record, _contacts_my_profile.extension, _contacts_extension._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_add_child_record(record, _contacts_my_profile.sip, _contacts_sip._uri))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while(0);
	contacts_record_destroy(record, true);
	return ret;
}

static int _ctsvc_tc_record_clone_child_record(contacts_record_h record, unsigned int property_id, const char *view_uri)
{
	int ret;
	int count = 0;
	contacts_record_h child = NULL;
	contacts_list_h list = NULL;

	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(view_uri, &child))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_add_child_record(record, property_id, child))) break;
		child = NULL;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_clone_child_record_list(record, property_id, &list))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_list_get_count(list, &count))) break;
		if (count < 1) {
			ret = -1;
			break;
		}
		if (CONTACTS_ERROR_NONE != (ret = contacts_list_destroy(list, true))) break;
		return 0;
	} while (0);
	contacts_record_destroy(child, true);
	contacts_list_destroy(list, true);
	return ret;
}


static int _ctsvc_tc_record_clone_child_record_list_my_profile(void)
{
	int ret = 0;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_my_profile._uri, &record))) break;
		if (0 != (ret = _ctsvc_tc_record_clone_child_record(record, _contacts_my_profile.name, _contacts_name._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_clone_child_record(record, _contacts_my_profile.image, _contacts_image._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_clone_child_record(record, _contacts_my_profile.company, _contacts_company._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_clone_child_record(record, _contacts_my_profile.note, _contacts_note._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_clone_child_record(record, _contacts_my_profile.number, _contacts_number._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_clone_child_record(record, _contacts_my_profile.email, _contacts_email._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_clone_child_record(record, _contacts_my_profile.event, _contacts_event._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_clone_child_record(record, _contacts_my_profile.messenger, _contacts_messenger._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_clone_child_record(record, _contacts_my_profile.address, _contacts_address._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_clone_child_record(record, _contacts_my_profile.url, _contacts_url._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_clone_child_record(record, _contacts_my_profile.nickname, _contacts_nickname._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_clone_child_record(record, _contacts_my_profile.profile, _contacts_profile._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_clone_child_record(record, _contacts_my_profile.relationship, _contacts_relationship._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_clone_child_record(record, _contacts_my_profile.extension, _contacts_extension._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_clone_child_record(record, _contacts_my_profile.sip, _contacts_sip._uri))) break;

		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while(0);
	contacts_record_destroy(record, true);
	return ret;
}

static int _ctsvc_tc_record_remove_child_record(contacts_record_h record, unsigned int property_id, const char *view_uri)
{
	int ret;
	int count = 0;
	int count2 = 0;
	contacts_record_h child = NULL;

	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(view_uri, &child))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_add_child_record(record, property_id, child))) break;
		child = NULL;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_get_child_record_count(record, property_id, &count))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_get_child_record_at_p(record, property_id, 0, &child))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_remove_child_record(record, property_id, child))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(child, true))) break;
		child = NULL;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_get_child_record_count(record, property_id, &count2))) break;
		if (count == count2) {
			ret = -1;
			break;
		}
		return 0;
	} while (0);
	contacts_record_destroy(child, true);
	return ret;
}

static int _ctsvc_tc_record_remove_child_record_my_profile(void)
{
	int ret = 0;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_my_profile._uri, &record))) break;
		if (0 != (ret = _ctsvc_tc_record_remove_child_record(record, _contacts_my_profile.name, _contacts_name._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_remove_child_record(record, _contacts_my_profile.image, _contacts_image._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_remove_child_record(record, _contacts_my_profile.company, _contacts_company._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_remove_child_record(record, _contacts_my_profile.note, _contacts_note._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_remove_child_record(record, _contacts_my_profile.number, _contacts_number._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_remove_child_record(record, _contacts_my_profile.email, _contacts_email._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_remove_child_record(record, _contacts_my_profile.event, _contacts_event._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_remove_child_record(record, _contacts_my_profile.messenger, _contacts_messenger._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_remove_child_record(record, _contacts_my_profile.address, _contacts_address._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_remove_child_record(record, _contacts_my_profile.url, _contacts_url._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_remove_child_record(record, _contacts_my_profile.nickname, _contacts_nickname._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_remove_child_record(record, _contacts_my_profile.profile, _contacts_profile._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_remove_child_record(record, _contacts_my_profile.relationship, _contacts_relationship._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_remove_child_record(record, _contacts_my_profile.extension, _contacts_extension._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_remove_child_record(record, _contacts_my_profile.sip, _contacts_sip._uri))) break;

		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while(0);
	contacts_record_destroy(record, true);
	return ret;
}

static int _ctsvc_tc_record_get_child_record_at_p(contacts_record_h record, unsigned int property_id, const char *view_uri)
{
	int ret;
	contacts_record_h child = NULL;

	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(view_uri, &child))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_add_child_record(record, property_id, child))) break;
		child = NULL;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_get_child_record_at_p(record, property_id, 0, &child))) break;
		if (NULL == child) {
			ret = -1;
			break;
		}
		return 0;
	} while (0);
	contacts_record_destroy(child, true);
	return ret;
}

static int _ctsvc_tc_record_get_child_record_at_p_my_profile(void)
{
	int ret = 0;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_my_profile._uri, &record))) break;
		if (0 != (ret = _ctsvc_tc_record_get_child_record_at_p(record, _contacts_my_profile.name, _contacts_name._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_get_child_record_at_p(record, _contacts_my_profile.image, _contacts_image._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_get_child_record_at_p(record, _contacts_my_profile.company, _contacts_company._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_get_child_record_at_p(record, _contacts_my_profile.note, _contacts_note._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_get_child_record_at_p(record, _contacts_my_profile.number, _contacts_number._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_get_child_record_at_p(record, _contacts_my_profile.email, _contacts_email._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_get_child_record_at_p(record, _contacts_my_profile.event, _contacts_event._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_get_child_record_at_p(record, _contacts_my_profile.messenger, _contacts_messenger._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_get_child_record_at_p(record, _contacts_my_profile.address, _contacts_address._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_get_child_record_at_p(record, _contacts_my_profile.url, _contacts_url._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_get_child_record_at_p(record, _contacts_my_profile.nickname, _contacts_nickname._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_get_child_record_at_p(record, _contacts_my_profile.profile, _contacts_profile._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_get_child_record_at_p(record, _contacts_my_profile.relationship, _contacts_relationship._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_get_child_record_at_p(record, _contacts_my_profile.extension, _contacts_extension._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_get_child_record_at_p(record, _contacts_my_profile.sip, _contacts_sip._uri))) break;

		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while(0);
	contacts_record_destroy(record, true);
	return ret;
}

static int _ctsvc_tc_record_get_child_record_count(contacts_record_h record, unsigned int property_id, const char *view_uri)
{
	int ret;
	int count = 0;
	contacts_record_h child = NULL;

	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(view_uri, &child))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_add_child_record(record, property_id, child))) break;
		child = NULL;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_get_child_record_count(record, property_id, &count))) break;
		if (count < 1) {
			ret = -1;
			break;
		}
		return 0;
	} while (0);
	contacts_record_destroy(child, true);
	return ret;
}


static int _ctsvc_tc_record_get_child_record_count_my_profile(void)
{
	int ret = 0;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_my_profile._uri, &record))) break;
		if (0 != (ret = _ctsvc_tc_record_get_child_record_count(record, _contacts_my_profile.name, _contacts_name._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_get_child_record_count(record, _contacts_my_profile.image, _contacts_image._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_get_child_record_count(record, _contacts_my_profile.company, _contacts_company._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_get_child_record_count(record, _contacts_my_profile.note, _contacts_note._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_get_child_record_count(record, _contacts_my_profile.number, _contacts_number._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_get_child_record_count(record, _contacts_my_profile.email, _contacts_email._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_get_child_record_count(record, _contacts_my_profile.event, _contacts_event._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_get_child_record_count(record, _contacts_my_profile.messenger, _contacts_messenger._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_get_child_record_count(record, _contacts_my_profile.address, _contacts_address._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_get_child_record_count(record, _contacts_my_profile.url, _contacts_url._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_get_child_record_count(record, _contacts_my_profile.nickname, _contacts_nickname._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_get_child_record_count(record, _contacts_my_profile.profile, _contacts_profile._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_get_child_record_count(record, _contacts_my_profile.relationship, _contacts_relationship._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_get_child_record_count(record, _contacts_my_profile.extension, _contacts_extension._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_get_child_record_count(record, _contacts_my_profile.sip, _contacts_sip._uri))) break;

		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while(0);
	contacts_record_destroy(record, true);
	return ret;

}

static int _ctsvc_tc_record_compare_type_my_profile(ctsvc_data_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *property_list = NULL;
	contacts_record_h record = NULL;

	do {
		if (0 != (ret = ctsvc_tc_record_create_my_profile(0, PROPERTY_TYPE_CREATE1, &record))) break;
		if (0 != (ret = ctsvc_tc_record_get_property_my_profile(PROPERTY_TYPE_CREATE1, &property_list, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_record_compare_type(record, type, property_list, property_count))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while (0);
	contacts_record_destroy(record, true);
	return ret;
}

static int _ctsvc_tc_record_get_bool_my_profile(void)
{
	return _ctsvc_tc_record_compare_type_my_profile(PROPERTY_BOOL);
}

static int _ctsvc_tc_record_get_double_my_profile(void)
{
	return _ctsvc_tc_record_compare_type_my_profile(PROPERTY_DOUBLE);
}

static int _ctsvc_tc_record_get_int_my_profile(void)
{
	return _ctsvc_tc_record_compare_type_my_profile(PROPERTY_INT);
}

static int _ctsvc_tc_record_get_lli_my_profile(void)
{
	return _ctsvc_tc_record_compare_type_my_profile(PROPERTY_LLI);
}

static int _ctsvc_tc_record_get_str_my_profile(void)
{
	return _ctsvc_tc_record_compare_type_my_profile(PROPERTY_STR);
}

static int _ctsvc_tc_record_get_str_p_my_profile(void)
{
	return _ctsvc_tc_record_compare_type_my_profile(PROPERTY_STR);
}

static int _ctsvc_tc_record_set_bool_my_profile(void)
{
	return _ctsvc_tc_record_compare_type_my_profile(PROPERTY_BOOL);
}

static int _ctsvc_tc_record_set_double_my_profile(void)
{
	return _ctsvc_tc_record_compare_type_my_profile(PROPERTY_DOUBLE);
}

static int _ctsvc_tc_record_set_int_my_profile(void)
{
	return _ctsvc_tc_record_compare_type_my_profile(PROPERTY_INT);
}

static int _ctsvc_tc_record_set_lli_my_profile(void)
{
	return _ctsvc_tc_record_compare_type_my_profile(PROPERTY_LLI);
}

static int _ctsvc_tc_record_set_str_my_profile(void)
{
	return _ctsvc_tc_record_compare_type_my_profile(PROPERTY_STR);
}


ctsvc_tc_record_plugin_s _tc_record_my_profile = {
	.clone = _ctsvc_tc_record_clone_my_profile,
	.create = _ctsvc_tc_record_create_my_profile,
	.destroy = _ctsvc_tc_record_destroy_my_profile,
	.get_uri_p = _ctsvc_tc_record_get_uri_p_my_profile,
	.add_child_record = _ctsvc_tc_record_add_child_record_my_profile,
	.clone_child_record_list = _ctsvc_tc_record_clone_child_record_list_my_profile,
	.remove_child_record = _ctsvc_tc_record_remove_child_record_my_profile,
	.get_child_record_at_p = _ctsvc_tc_record_get_child_record_at_p_my_profile,
	.get_child_record_count = _ctsvc_tc_record_get_child_record_count_my_profile,
	.get_bool = _ctsvc_tc_record_get_bool_my_profile,
	.get_double = _ctsvc_tc_record_get_double_my_profile,
	.get_int = _ctsvc_tc_record_get_int_my_profile,
	.get_lli = _ctsvc_tc_record_get_lli_my_profile,
	.get_str = _ctsvc_tc_record_get_str_my_profile,
	.get_str_p = _ctsvc_tc_record_get_str_p_my_profile,
	.set_bool = _ctsvc_tc_record_set_bool_my_profile,
	.set_double = _ctsvc_tc_record_set_double_my_profile,
	.set_int = _ctsvc_tc_record_set_int_my_profile,
	.set_lli = _ctsvc_tc_record_set_lli_my_profile,
	.set_str = _ctsvc_tc_record_set_str_my_profile,
	.free_properties = _ctsvc_tc_record_free_property_my_profile,
};


static int _ctsvc_tc_filter_add_type_my_profile(ctsvc_data_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *property_list = NULL;
	contacts_filter_h filter = NULL;

	do {
		if (0 != (ret = contacts_filter_create(_contacts_my_profile._uri, &filter))) break;
		if (0 != (ret = ctsvc_tc_record_get_property_my_profile(PROPERTY_TYPE_CREATE1, &property_list, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_filter_add_type(filter, type, property_list, property_count))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_filter_destroy(filter))) break;
		filter = NULL;
		return 0;
	} while (0);
	contacts_filter_destroy(filter);
	return ret;
}

static int _ctsvc_tc_filter_add_bool_my_profile(void)
{
	return _ctsvc_tc_filter_add_type_my_profile(PROPERTY_BOOL);
}

static int _ctsvc_tc_filter_add_int_my_profile(void)
{
	return _ctsvc_tc_filter_add_type_my_profile(PROPERTY_INT);
}

static int _ctsvc_tc_filter_add_double_my_profile(void)
{
	return _ctsvc_tc_filter_add_type_my_profile(PROPERTY_DOUBLE);
}

static int _ctsvc_tc_filter_add_lli_my_profile(void)
{
	return _ctsvc_tc_filter_add_type_my_profile(PROPERTY_LLI);
}

static int _ctsvc_tc_filter_add_str_my_profile(void)
{
	return _ctsvc_tc_filter_add_type_my_profile(PROPERTY_STR);
}

ctsvc_tc_filter_plugin_s _tc_filter_my_profile = {
	.add_bool = _ctsvc_tc_filter_add_bool_my_profile,
	.add_double = _ctsvc_tc_filter_add_double_my_profile,
	.add_int = _ctsvc_tc_filter_add_int_my_profile,
	.add_lli = _ctsvc_tc_filter_add_lli_my_profile,
	.add_str = _ctsvc_tc_filter_add_str_my_profile,
};
