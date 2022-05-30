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
#include "utc-contacts-service-record-group-relation.h"
#include "utc-contacts-service-record-extension.h"
#include "utc-contacts-service-record-contact.h"
#include "utc-contacts-service-record-sip.h"

// _contacts_strchild
#define CTSVC_CONTACT_STR_FIRST "first"
#define CTSVC_CONTACT_STR_LABEL "label"
#define CTSVC_CONTACT_STR_NOTE "note"
#define CTSVC_CONTACT_STR_NAME "name"
#define CTSVC_CONTACT_STR_TEXT "text"
#define CTSVC_CONTACT_STR_DATA2 "data2"

// _contacts_contact
#define CTSVC_CONTACT_RINGTONE_PATH_C1 CTSVC_RINGTONE_PATH_C1
#define CTSVC_CONTACT_RINGTONE_PATH_U1 CTSVC_RINGTONE_PATH_U1
#define CTSVC_CONTACT_IS_FAVORITE_C1 true
#define CTSVC_CONTACT_IS_FAVORITE_U1 false
#define CTSVC_CONTACT_UID_C1 "UID_C"
#define CTSVC_CONTACT_UID_U1 "UID_U"
#define CTSVC_CONTACT_VIBRATION_C1 CTSVC_VIBRATION_C1
#define CTSVC_CONTACT_VIBRATION_U1 CTSVC_VIBRATION_U1
#define CTSVC_CONTACT_LINK_MODE_C1 CONTACTS_CONTACT_LINK_MODE_NONE
#define CTSVC_CONTACT_LINK_MODE_U1 CONTACTS_CONTACT_LINK_MODE_IGNORE_ONCE
#define CTSVC_CONTACT_MESSAGE_ALERT_C1 CTSVC_MESSAGE_ALERT_C1
#define CTSVC_CONTACT_MESSAGE_ALERT_U1 CTSVC_MESSAGE_ALERT_U1
#define CTSVC_CONTACT_RINGTONE_PATH_C2 CTSVC_RINGTONE_PATH_C2
#define CTSVC_CONTACT_RINGTONE_PATH_U2 CTSVC_RINGTONE_PATH_U2
#define CTSVC_CONTACT_IS_FAVORITE_C2 true
#define CTSVC_CONTACT_IS_FAVORITE_U2 false
#define CTSVC_CONTACT_UID_C2 "UID_C2"
#define CTSVC_CONTACT_UID_U2 "UID_U2"
#define CTSVC_CONTACT_VIBRATION_C2 CTSVC_VIBRATION_C2
#define CTSVC_CONTACT_VIBRATION_U2 CTSVC_VIBRATION_U2
#define CTSVC_CONTACT_LINK_MODE_C2 CONTACTS_CONTACT_LINK_MODE_NONE
#define CTSVC_CONTACT_LINK_MODE_U2 CONTACTS_CONTACT_LINK_MODE_IGNORE_ONCE
#define CTSVC_CONTACT_MESSAGE_ALERT_C2 CTSVC_MESSAGE_ALERT_C2
#define CTSVC_CONTACT_MESSAGE_ALERT_U2 CTSVC_MESSAGE_ALERT_U2


ctsvc_view_s _view_contact;
bool _view_contact_load = false;

static void _ctsvc_tc_load_view_contact()
{
	_view_contact_load = true;
	// _contacts_contact
	ctsvc_property_s contact_create1[] = {
		ctsvc_tc_util_create_str_property(_contacts_contact.ringtone_path, CTSVC_CONTACT_RINGTONE_PATH_C1),
		ctsvc_tc_util_create_bool_property(_contacts_contact.is_favorite,	CTSVC_CONTACT_IS_FAVORITE_C1),
		ctsvc_tc_util_create_str_property(_contacts_contact.uid, CTSVC_CONTACT_UID_C1),
		ctsvc_tc_util_create_str_property(_contacts_contact.vibration, CTSVC_CONTACT_VIBRATION_C1),
		ctsvc_tc_util_create_int_property(_contacts_contact.link_mode, CTSVC_CONTACT_LINK_MODE_C1),
		ctsvc_tc_util_create_str_property(_contacts_contact.message_alert, CTSVC_CONTACT_MESSAGE_ALERT_C1),
	};
	ctsvc_property_s contact_update1[] = {
		ctsvc_tc_util_create_str_property(_contacts_contact.ringtone_path, CTSVC_CONTACT_RINGTONE_PATH_U1),
		//ctsvc_tc_util_create_bool_property(_contacts_contact.is_favorite, CTSVC_CONTACT_IS_FAVORITE_U1),
		ctsvc_tc_util_create_str_property(_contacts_contact.uid, CTSVC_CONTACT_UID_U1),
		ctsvc_tc_util_create_str_property(_contacts_contact.vibration, CTSVC_CONTACT_VIBRATION_U1),
		ctsvc_tc_util_create_str_property(_contacts_contact.message_alert, CTSVC_CONTACT_MESSAGE_ALERT_U1),
	};
	ctsvc_property_s contact_create2[] = {
		ctsvc_tc_util_create_str_property(_contacts_contact.ringtone_path, CTSVC_CONTACT_RINGTONE_PATH_C2),
		ctsvc_tc_util_create_bool_property(_contacts_contact.is_favorite,	CTSVC_CONTACT_IS_FAVORITE_C2),
		ctsvc_tc_util_create_str_property(_contacts_contact.uid, CTSVC_CONTACT_UID_C2),
		ctsvc_tc_util_create_str_property(_contacts_contact.vibration, CTSVC_CONTACT_VIBRATION_C2),
		ctsvc_tc_util_create_int_property(_contacts_contact.link_mode, CTSVC_CONTACT_LINK_MODE_C2),
		ctsvc_tc_util_create_str_property(_contacts_contact.message_alert, CTSVC_CONTACT_MESSAGE_ALERT_C2),
	};
	ctsvc_property_s contact_update2[] = {
		ctsvc_tc_util_create_str_property(_contacts_contact.ringtone_path, CTSVC_CONTACT_RINGTONE_PATH_U2),
		//ctsvc_tc_util_create_bool_property(_contacts_contact.is_favorite,	CTSVC_CONTACT_IS_FAVORITE_U2),
		ctsvc_tc_util_create_str_property(_contacts_contact.uid, CTSVC_CONTACT_UID_U2),
		ctsvc_tc_util_create_str_property(_contacts_contact.vibration, CTSVC_CONTACT_VIBRATION_U2),
		ctsvc_tc_util_create_str_property(_contacts_contact.message_alert, CTSVC_CONTACT_MESSAGE_ALERT_U2),
	};


	_view_contact.create1_count = sizeof(contact_create1)/sizeof(ctsvc_property_s);
	_view_contact.create2_count = sizeof(contact_create2)/sizeof(ctsvc_property_s);
	_view_contact.update1_count = sizeof(contact_update1)/sizeof(ctsvc_property_s);
	_view_contact.update2_count = sizeof(contact_update2)/sizeof(ctsvc_property_s);

	_view_contact.create1 = calloc(_view_contact.create1_count, sizeof(ctsvc_property_s));
	_view_contact.create2 = calloc(_view_contact.create2_count, sizeof(ctsvc_property_s));
	_view_contact.update1 = calloc(_view_contact.update1_count, sizeof(ctsvc_property_s));
	_view_contact.update2 = calloc(_view_contact.update2_count, sizeof(ctsvc_property_s));

	int i;
	for (i=0;i<_view_contact.create1_count;i++)
		_view_contact.create1[i] = contact_create1[i];
	for (i=0;i<_view_contact.create2_count;i++)
		_view_contact.create2[i] = contact_create2[i];
	for (i=0;i<_view_contact.update1_count;i++)
		_view_contact.update1[i] = contact_update1[i];
	for (i=0;i<_view_contact.update2_count;i++)
		_view_contact.update2[i] = contact_update2[i];
}

static int _ctsvc_tc_record_free_property_contact()
{
	int i;

	if (false == _view_contact_load)
		return -1;

	_view_contact_load = false;

	for (i=0;i<_view_contact.create1_count;i++) {
		if ( _contacts_contact.ringtone_path == _view_contact.create1[i].property_id
			|| _contacts_contact.vibration == _view_contact.create1[i].property_id
			|| _contacts_contact.message_alert == _view_contact.create1[i].property_id )
			free(_view_contact.create1[i].val.str_val);
	}
	for (i=0;i<_view_contact.create2_count;i++) {
		if ( _contacts_contact.ringtone_path == _view_contact.create2[i].property_id
			|| _contacts_contact.vibration == _view_contact.create2[i].property_id
			|| _contacts_contact.message_alert == _view_contact.create2[i].property_id )
			free(_view_contact.create2[i].val.str_val);
	}
	for (i=0;i<_view_contact.update1_count;i++) {
		if ( _contacts_contact.ringtone_path == _view_contact.update1[i].property_id
			|| _contacts_contact.vibration == _view_contact.update1[i].property_id
			|| _contacts_contact.message_alert == _view_contact.update1[i].property_id )
			free(_view_contact.update1[i].val.str_val);
	}
	for (i=0;i<_view_contact.update2_count;i++) {
		if ( _contacts_contact.ringtone_path == _view_contact.update2[i].property_id
			|| _contacts_contact.vibration == _view_contact.update2[i].property_id
			|| _contacts_contact.message_alert == _view_contact.update2[i].property_id )
			free(_view_contact.update2[i].val.str_val);
	}

	free(_view_contact.create1);
	free(_view_contact.create2);
	free(_view_contact.update1);
	free(_view_contact.update2);

	return 0;
}


int ctsvc_tc_record_get_property_contact(ctsvc_property_type_e type, ctsvc_property_s **p_properties, int *p_property_count)
{
	if (false == _view_contact_load)
		_ctsvc_tc_load_view_contact();

	switch (type) {
	case PROPERTY_TYPE_CREATE1:
		*p_properties = _view_contact.create1;
		*p_property_count = _view_contact.create1_count;
		break;
	case PROPERTY_TYPE_CREATE2:
		*p_properties = _view_contact.create2;
		*p_property_count = _view_contact.create2_count;
		break;
	case PROPERTY_TYPE_UPDATE1:
		*p_properties = _view_contact.update1;
		*p_property_count = _view_contact.update1_count;
		break;
	case PROPERTY_TYPE_UPDATE2:
		*p_properties = _view_contact.update2;
		*p_property_count = _view_contact.update2_count;
		break;
	default :
		break;
	}
	return 0;
}

int ctsvc_tc_record_compare_contact(contacts_record_h record, ctsvc_property_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *properties = NULL;
	do {
		if (0 != (ret = ctsvc_tc_record_get_property_contact(type, &properties, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_record_compare(record, properties, property_count))) break;
		return 0;
	} while (0);
	return ret;
}

int ctsvc_tc_filter_set_contact(contacts_filter_h filter, ctsvc_property_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *properties = NULL;
	do {
		if (0 != (ret = ctsvc_tc_record_get_property_contact(type, &properties, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_filter_set(filter, properties, property_count))) break;
		return 0;
	} while (0);
	return ret;
}


int ctsvc_tc_record_update_contact(contacts_record_h record, ctsvc_property_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *property_list = NULL;
	do {
		if (0 != (ret = ctsvc_tc_record_get_property_contact(type, &property_list, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_record_set_property(record, property_list, property_count))) break;
		return 0;
	} while (0);
	return ret;
}

int ctsvc_tc_record_create_contact(int address_book_id, int group_id, ctsvc_property_type_e type, contacts_record_h *p_record)
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
	contacts_record_h group_relation = NULL;
	contacts_record_h extension = NULL;
	contacts_record_h sip = NULL;

	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_contact._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_set_int(record, _contacts_contact.address_book_id, address_book_id))) break;
		if (0 != (ret = ctsvc_tc_record_get_property_contact(type, &property_list, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_record_set_property(record, property_list, property_count))) break;
		if (0 != (ret = ctsvc_tc_record_create_name(0, type, &name))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_add_child_record(record, _contacts_contact.name, name))) break;
		if (0 != (ret = ctsvc_tc_record_create_image(0, type, &image))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_add_child_record(record, _contacts_contact.image, image))) break;
		if (0 != (ret = ctsvc_tc_record_create_company(0, type, &company))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_add_child_record(record, _contacts_contact.company, company))) break;
		if (0 != (ret = ctsvc_tc_record_create_note(0, type, &note))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_add_child_record(record, _contacts_contact.note, note))) break;
		if (0 != (ret = ctsvc_tc_record_create_number(0, type, &number))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_add_child_record(record, _contacts_contact.number, number))) break;
		if (0 != (ret = ctsvc_tc_record_create_email(0, type, &email))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_add_child_record(record, _contacts_contact.email, email))) break;
		if (0 != (ret = ctsvc_tc_record_create_event(0, type, &event))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_add_child_record(record, _contacts_contact.event, event))) break;
		if (0 != (ret = ctsvc_tc_record_create_messenger(0, type, &messenger))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_add_child_record(record, _contacts_contact.messenger, messenger))) break;
		if (0 != (ret = ctsvc_tc_record_create_address(0, type, &address))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_add_child_record(record, _contacts_contact.address, address))) break;
		if (0 != (ret = ctsvc_tc_record_create_url(0, type, &url))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_add_child_record(record, _contacts_contact.url, url))) break;
		if (0 != (ret = ctsvc_tc_record_create_nickname(0, type, &nickname))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_add_child_record(record, _contacts_contact.nickname, nickname))) break;
		if (0 != (ret = ctsvc_tc_record_create_profile(0, type, &profile))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_add_child_record(record, _contacts_contact.profile, profile))) break;
		if (0 != (ret = ctsvc_tc_record_create_relationship(0, type, &relationship))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_add_child_record(record, _contacts_contact.relationship, relationship))) break;
		if (0 != (ret = ctsvc_tc_record_create_sip(0, type, &sip))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_add_child_record(record, _contacts_contact.sip, sip))) break;
		if (group_id) {
			if (0 != (ret = ctsvc_tc_record_create_group_relation(0, group_id, type, &group_relation))) break;
			if (CONTACTS_ERROR_NONE != (ret = contacts_record_add_child_record(record, _contacts_contact.group_relation, group_relation))) break;
		}
		if (0 != (ret = ctsvc_tc_record_create_extension(0, type, &extension))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_add_child_record(record, _contacts_contact.extension, extension))) break;
	} while (0);
	*p_record = record;
	return ret;
}

static int _ctsvc_tc_record_clone_contact(void)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *property_list = NULL;
	contacts_record_h record = NULL;
	contacts_record_h record_clone = NULL;

	do {
		if (CONTACTS_ERROR_NONE != (ret = ctsvc_tc_record_create_contact(LOCAL_DB_ID, LOCAL_DB_ID, PROPERTY_TYPE_CREATE1, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_clone(record, &record_clone))) break;
		if (CONTACTS_ERROR_NONE != (ret = ctsvc_tc_record_get_property_contact(PROPERTY_TYPE_CREATE1, &property_list, &property_count))) break;
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

static int _ctsvc_tc_record_create_contact(void)
{
	int ret = 0;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_contact._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while(0);
	contacts_record_destroy(record, true);
	return ret;
}

static int _ctsvc_tc_record_destroy_contact(void)
{
	int ret = 0;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_contact._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while(0);
	contacts_record_destroy(record, true);
	return ret;
}

static int _ctsvc_tc_record_get_uri_p_contact(void)
{
	int ret = 0;
	const char *uri = NULL;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_contact._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_get_uri_p(record, &uri))) break;
		if (NULL == uri || STRING_EQUAL != strcmp(uri, _contacts_contact._uri)) {
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

static int _ctsvc_tc_record_add_child_record_contact(void)
{
	int ret = 0;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_contact._uri, &record))) break;
		if (0 != (ret = _ctsvc_tc_record_add_child_record(record, _contacts_contact.name, _contacts_name._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_add_child_record(record, _contacts_contact.image, _contacts_image._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_add_child_record(record, _contacts_contact.company, _contacts_company._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_add_child_record(record, _contacts_contact.note, _contacts_note._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_add_child_record(record, _contacts_contact.number, _contacts_number._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_add_child_record(record, _contacts_contact.email, _contacts_email._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_add_child_record(record, _contacts_contact.event, _contacts_event._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_add_child_record(record, _contacts_contact.messenger, _contacts_messenger._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_add_child_record(record, _contacts_contact.address, _contacts_address._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_add_child_record(record, _contacts_contact.url, _contacts_url._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_add_child_record(record, _contacts_contact.nickname, _contacts_nickname._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_add_child_record(record, _contacts_contact.profile, _contacts_profile._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_add_child_record(record, _contacts_contact.relationship, _contacts_relationship._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_add_child_record(record, _contacts_contact.extension, _contacts_extension._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_add_child_record(record, _contacts_contact.sip, _contacts_sip._uri))) break;
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
		/* add value */
		if (0 == strcmp(view_uri, _contacts_name._uri)) {
			contacts_record_set_str(child, _contacts_name.first, CTSVC_CONTACT_STR_FIRST);
		} else if (0 == strcmp(view_uri, _contacts_image._uri)) {
			contacts_record_set_str(child, _contacts_image.label, CTSVC_CONTACT_STR_LABEL);
		} else if (0 == strcmp(view_uri, _contacts_company._uri)) {
			contacts_record_set_str(child, _contacts_company.label, CTSVC_CONTACT_STR_LABEL);
		} else if (0 == strcmp(view_uri, _contacts_note._uri)) {
			contacts_record_set_str(child, _contacts_note.note, CTSVC_CONTACT_STR_NOTE);
		} else if (0 == strcmp(view_uri, _contacts_number._uri)) {
			contacts_record_set_str(child, _contacts_number.label, CTSVC_CONTACT_STR_LABEL);
		} else if (0 == strcmp(view_uri, _contacts_email._uri)) {
			contacts_record_set_str(child, _contacts_email.label, CTSVC_CONTACT_STR_LABEL);
		} else if (0 == strcmp(view_uri, _contacts_event._uri)) {
			contacts_record_set_str(child, _contacts_event.label, CTSVC_CONTACT_STR_LABEL);
		} else if (0 == strcmp(view_uri, _contacts_messenger._uri)) {
			contacts_record_set_str(child, _contacts_messenger.label, CTSVC_CONTACT_STR_LABEL);
		} else if (0 == strcmp(view_uri, _contacts_address._uri)) {
			contacts_record_set_str(child, _contacts_address.label, CTSVC_CONTACT_STR_LABEL);
		} else if (0 == strcmp(view_uri, _contacts_url._uri)) {
			contacts_record_set_str(child, _contacts_url.label, CTSVC_CONTACT_STR_LABEL);
		} else if (0 == strcmp(view_uri, _contacts_nickname._uri)) {
			contacts_record_set_str(child, _contacts_nickname.name, CTSVC_CONTACT_STR_NAME);
		} else if (0 == strcmp(view_uri, _contacts_profile._uri)) {
			contacts_record_set_str(child, _contacts_profile.text, CTSVC_CONTACT_STR_TEXT);
		} else if (0 == strcmp(view_uri, _contacts_relationship._uri)) {
			contacts_record_set_str(child, _contacts_relationship.label, CTSVC_CONTACT_STR_LABEL);
		} else if (0 == strcmp(view_uri, _contacts_extension._uri)) {
			contacts_record_set_str(child, _contacts_extension.data2, CTSVC_CONTACT_STR_DATA2);
		} else if (0 == strcmp(view_uri, _contacts_sip._uri)) {
			contacts_record_set_str(child, _contacts_sip.label, CTSVC_CONTACT_STR_LABEL);
		} else {
		}
		/* add value */
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


static int _ctsvc_tc_record_clone_child_record_list_contact(void)
{
	int ret = 0;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_contact._uri, &record))) break;
		if (0 != (ret = _ctsvc_tc_record_clone_child_record(record, _contacts_contact.name, _contacts_name._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_clone_child_record(record, _contacts_contact.image, _contacts_image._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_clone_child_record(record, _contacts_contact.company, _contacts_company._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_clone_child_record(record, _contacts_contact.note, _contacts_note._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_clone_child_record(record, _contacts_contact.number, _contacts_number._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_clone_child_record(record, _contacts_contact.email, _contacts_email._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_clone_child_record(record, _contacts_contact.event, _contacts_event._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_clone_child_record(record, _contacts_contact.messenger, _contacts_messenger._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_clone_child_record(record, _contacts_contact.address, _contacts_address._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_clone_child_record(record, _contacts_contact.url, _contacts_url._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_clone_child_record(record, _contacts_contact.nickname, _contacts_nickname._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_clone_child_record(record, _contacts_contact.profile, _contacts_profile._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_clone_child_record(record, _contacts_contact.relationship, _contacts_relationship._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_clone_child_record(record, _contacts_contact.extension, _contacts_extension._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_clone_child_record(record, _contacts_contact.sip, _contacts_sip._uri))) break;

		/* start result check */
		char *p = NULL;
		contacts_record_h child = NULL;
		contacts_record_get_child_record_at_p(record, _contacts_contact.name, 0, &child);
		contacts_record_get_str_p(child, _contacts_name.first, &p);
		ret = strcmp(p, CTSVC_CONTACT_STR_FIRST);
		if (0 != ret)
			break;
		contacts_record_get_child_record_at_p(record, _contacts_contact.image, 0, &child);
		contacts_record_get_str_p(child, _contacts_image.label, &p);
		ret = strcmp(p, CTSVC_CONTACT_STR_LABEL);
		if (0 != ret)
			break;
		contacts_record_get_child_record_at_p(record, _contacts_contact.company, 0, &child);
		contacts_record_get_str_p(child, _contacts_company.label, &p);
		ret = strcmp(p, CTSVC_CONTACT_STR_LABEL);
		if (0 != ret)
			break;
		contacts_record_get_child_record_at_p(record, _contacts_contact.note, 0, &child);
		contacts_record_get_str_p(child, _contacts_note.note, &p);
		ret = strcmp(p, CTSVC_CONTACT_STR_NOTE);
		if (0 != ret)
			break;
		contacts_record_get_child_record_at_p(record, _contacts_contact.number, 0, &child);
		contacts_record_get_str_p(child, _contacts_number.label, &p);
		ret = strcmp(p, CTSVC_CONTACT_STR_LABEL);
		if (0 != ret)
			break;
		contacts_record_get_child_record_at_p(record, _contacts_contact.email, 0, &child);
		contacts_record_get_str_p(child, _contacts_email.label, &p);
		ret = strcmp(p, CTSVC_CONTACT_STR_LABEL);
		if (0 != ret)
			break;
		contacts_record_get_child_record_at_p(record, _contacts_contact.event, 0, &child);
		contacts_record_get_str_p(child, _contacts_event.label, &p);
		ret = strcmp(p, CTSVC_CONTACT_STR_LABEL);
		if (0 != ret)
			break;
		contacts_record_get_child_record_at_p(record, _contacts_contact.messenger, 0, &child);
		contacts_record_get_str_p(child, _contacts_messenger.label, &p);
		ret = strcmp(p, CTSVC_CONTACT_STR_LABEL);
		if (0 != ret)
			break;
		contacts_record_get_child_record_at_p(record, _contacts_contact.address, 0, &child);
		contacts_record_get_str_p(child, _contacts_address.label, &p);
		ret = strcmp(p, CTSVC_CONTACT_STR_LABEL);
		if (0 != ret)
			break;
		contacts_record_get_child_record_at_p(record, _contacts_contact.url, 0, &child);
		contacts_record_get_str_p(child, _contacts_url.label, &p);
		ret = strcmp(p, CTSVC_CONTACT_STR_LABEL);
		if (0 != ret)
			break;
		contacts_record_get_child_record_at_p(record, _contacts_contact.nickname, 0, &child);
		contacts_record_get_str_p(child, _contacts_nickname.name, &p);
		ret = strcmp(p, CTSVC_CONTACT_STR_NAME);
		if (0 != ret)
			break;
		contacts_record_get_child_record_at_p(record, _contacts_contact.profile, 0, &child);
		contacts_record_get_str_p(child, _contacts_profile.text, &p);
		ret = strcmp(p, CTSVC_CONTACT_STR_TEXT);
		if (0 != ret)
			break;
		contacts_record_get_child_record_at_p(record, _contacts_contact.relationship, 0, &child);
		contacts_record_get_str_p(child, _contacts_relationship.label, &p);
		ret = strcmp(p, CTSVC_CONTACT_STR_LABEL);
		if (0 != ret)
			break;
		contacts_record_get_child_record_at_p(record, _contacts_contact.extension, 0, &child);
		contacts_record_get_str_p(child, _contacts_extension.data2, &p);
		ret = strcmp(p, CTSVC_CONTACT_STR_DATA2);
		if (0 != ret)
			break;
		contacts_record_get_child_record_at_p(record, _contacts_contact.sip, 0, &child);
		contacts_record_get_str_p(child, _contacts_sip.label, &p);
		ret = strcmp(p, CTSVC_CONTACT_STR_LABEL);
		if (0 != ret)
			break;
		/* end result check */

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

static int _ctsvc_tc_record_remove_child_record_contact(void)
{
	int ret = 0;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_contact._uri, &record))) break;
		if (0 != (ret = _ctsvc_tc_record_remove_child_record(record, _contacts_contact.name, _contacts_name._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_remove_child_record(record, _contacts_contact.image, _contacts_image._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_remove_child_record(record, _contacts_contact.company, _contacts_company._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_remove_child_record(record, _contacts_contact.note, _contacts_note._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_remove_child_record(record, _contacts_contact.number, _contacts_number._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_remove_child_record(record, _contacts_contact.email, _contacts_email._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_remove_child_record(record, _contacts_contact.event, _contacts_event._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_remove_child_record(record, _contacts_contact.messenger, _contacts_messenger._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_remove_child_record(record, _contacts_contact.address, _contacts_address._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_remove_child_record(record, _contacts_contact.url, _contacts_url._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_remove_child_record(record, _contacts_contact.nickname, _contacts_nickname._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_remove_child_record(record, _contacts_contact.profile, _contacts_profile._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_remove_child_record(record, _contacts_contact.relationship, _contacts_relationship._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_remove_child_record(record, _contacts_contact.extension, _contacts_extension._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_remove_child_record(record, _contacts_contact.sip, _contacts_sip._uri))) break;

		/* start result check */
		contacts_record_h child = NULL;
		ret = contacts_record_get_child_record_at_p(record, _contacts_contact.name, 0, &child);
		if (CONTACTS_ERROR_NO_DATA != ret)
			break;
		ret = contacts_record_get_child_record_at_p(record, _contacts_contact.image, 0, &child);
		if (CONTACTS_ERROR_NO_DATA != ret)
			break;
		ret = contacts_record_get_child_record_at_p(record, _contacts_contact.company, 0, &child);
		if (CONTACTS_ERROR_NO_DATA != ret)
			break;
		ret = contacts_record_get_child_record_at_p(record, _contacts_contact.note, 0, &child);
		if (CONTACTS_ERROR_NO_DATA != ret)
			break;
		ret = contacts_record_get_child_record_at_p(record, _contacts_contact.number, 0, &child);
		if (CONTACTS_ERROR_NO_DATA != ret)
			break;
		ret = contacts_record_get_child_record_at_p(record, _contacts_contact.email, 0, &child);
		if (CONTACTS_ERROR_NO_DATA != ret)
			break;
		ret = contacts_record_get_child_record_at_p(record, _contacts_contact.event, 0, &child);
		if (CONTACTS_ERROR_NO_DATA != ret)
			break;
		ret = contacts_record_get_child_record_at_p(record, _contacts_contact.messenger, 0, &child);
		if (CONTACTS_ERROR_NO_DATA != ret)
			break;
		ret = contacts_record_get_child_record_at_p(record, _contacts_contact.address, 0, &child);
		if (CONTACTS_ERROR_NO_DATA != ret)
			break;
		ret = contacts_record_get_child_record_at_p(record, _contacts_contact.url, 0, &child);
		if (CONTACTS_ERROR_NO_DATA != ret)
			break;
		ret = contacts_record_get_child_record_at_p(record, _contacts_contact.nickname, 0, &child);
		if (CONTACTS_ERROR_NO_DATA != ret)
			break;
		ret = contacts_record_get_child_record_at_p(record, _contacts_contact.profile, 0, &child);
		if (CONTACTS_ERROR_NO_DATA != ret)
			break;
		ret = contacts_record_get_child_record_at_p(record, _contacts_contact.relationship, 0, &child);
		if (CONTACTS_ERROR_NO_DATA != ret)
			break;
		ret = contacts_record_get_child_record_at_p(record, _contacts_contact.extension, 0, &child);
		if (CONTACTS_ERROR_NO_DATA != ret)
			break;
		ret = contacts_record_get_child_record_at_p(record, _contacts_contact.sip, 0, &child);
		if (CONTACTS_ERROR_NO_DATA != ret)
			break;
		ret = contacts_record_get_child_record_at_p(record, _contacts_contact.messenger, 0, &child);
		/* end result check */

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
		/* add value */
		if (0 == strcmp(view_uri, _contacts_name._uri)) {
			contacts_record_set_str(child, _contacts_name.first, CTSVC_CONTACT_STR_FIRST);
		} else if (0 == strcmp(view_uri, _contacts_image._uri)) {
			contacts_record_set_str(child, _contacts_image.label, CTSVC_CONTACT_STR_LABEL);
		} else if (0 == strcmp(view_uri, _contacts_company._uri)) {
			contacts_record_set_str(child, _contacts_company.label, CTSVC_CONTACT_STR_LABEL);
		} else if (0 == strcmp(view_uri, _contacts_note._uri)) {
			contacts_record_set_str(child, _contacts_note.note, CTSVC_CONTACT_STR_NOTE);
		} else if (0 == strcmp(view_uri, _contacts_number._uri)) {
			contacts_record_set_str(child, _contacts_number.label, CTSVC_CONTACT_STR_LABEL);
		} else if (0 == strcmp(view_uri, _contacts_email._uri)) {
			contacts_record_set_str(child, _contacts_email.label, CTSVC_CONTACT_STR_LABEL);
		} else if (0 == strcmp(view_uri, _contacts_event._uri)) {
			contacts_record_set_str(child, _contacts_event.label, CTSVC_CONTACT_STR_LABEL);
		} else if (0 == strcmp(view_uri, _contacts_messenger._uri)) {
			contacts_record_set_str(child, _contacts_messenger.label, CTSVC_CONTACT_STR_LABEL);
		} else if (0 == strcmp(view_uri, _contacts_address._uri)) {
			contacts_record_set_str(child, _contacts_address.label, CTSVC_CONTACT_STR_LABEL);
		} else if (0 == strcmp(view_uri, _contacts_url._uri)) {
			contacts_record_set_str(child, _contacts_url.label, CTSVC_CONTACT_STR_LABEL);
		} else if (0 == strcmp(view_uri, _contacts_nickname._uri)) {
			contacts_record_set_str(child, _contacts_nickname.name, CTSVC_CONTACT_STR_NAME);
		} else if (0 == strcmp(view_uri, _contacts_profile._uri)) {
			contacts_record_set_str(child, _contacts_profile.text, CTSVC_CONTACT_STR_TEXT);
		} else if (0 == strcmp(view_uri, _contacts_relationship._uri)) {
			contacts_record_set_str(child, _contacts_relationship.label, CTSVC_CONTACT_STR_LABEL);
		} else if (0 == strcmp(view_uri, _contacts_extension._uri)) {
			contacts_record_set_str(child, _contacts_extension.data2, CTSVC_CONTACT_STR_DATA2);
		} else if (0 == strcmp(view_uri, _contacts_sip._uri)) {
			contacts_record_set_str(child, _contacts_sip.label, CTSVC_CONTACT_STR_LABEL);
		} else {
		}
		/* add value */
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

static int _ctsvc_tc_record_get_child_record_at_p_contact(void)
{
	int ret = 0;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_contact._uri, &record))) break;
		if (0 != (ret = _ctsvc_tc_record_get_child_record_at_p(record, _contacts_contact.name, _contacts_name._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_get_child_record_at_p(record, _contacts_contact.image, _contacts_image._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_get_child_record_at_p(record, _contacts_contact.company, _contacts_company._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_get_child_record_at_p(record, _contacts_contact.note, _contacts_note._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_get_child_record_at_p(record, _contacts_contact.number, _contacts_number._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_get_child_record_at_p(record, _contacts_contact.email, _contacts_email._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_get_child_record_at_p(record, _contacts_contact.event, _contacts_event._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_get_child_record_at_p(record, _contacts_contact.messenger, _contacts_messenger._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_get_child_record_at_p(record, _contacts_contact.address, _contacts_address._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_get_child_record_at_p(record, _contacts_contact.url, _contacts_url._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_get_child_record_at_p(record, _contacts_contact.nickname, _contacts_nickname._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_get_child_record_at_p(record, _contacts_contact.profile, _contacts_profile._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_get_child_record_at_p(record, _contacts_contact.relationship, _contacts_relationship._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_get_child_record_at_p(record, _contacts_contact.extension, _contacts_extension._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_get_child_record_at_p(record, _contacts_contact.sip, _contacts_sip._uri))) break;

		/* start result check */
		char *p = NULL;
		contacts_record_h child = NULL;
		contacts_record_get_child_record_at_p(record, _contacts_contact.name, 0, &child);
		contacts_record_get_str_p(child, _contacts_name.first, &p);
		ret = strcmp(p, CTSVC_CONTACT_STR_FIRST);
		if (0 != ret)
			break;
		contacts_record_get_child_record_at_p(record, _contacts_contact.image, 0, &child);
		contacts_record_get_str_p(child, _contacts_image.label, &p);
		ret = strcmp(p, CTSVC_CONTACT_STR_LABEL);
		if (0 != ret)
			break;
		contacts_record_get_child_record_at_p(record, _contacts_contact.company, 0, &child);
		contacts_record_get_str_p(child, _contacts_company.label, &p);
		ret = strcmp(p, CTSVC_CONTACT_STR_LABEL);
		if (0 != ret)
			break;
		contacts_record_get_child_record_at_p(record, _contacts_contact.note, 0, &child);
		contacts_record_get_str_p(child, _contacts_note.note, &p);
		ret = strcmp(p, CTSVC_CONTACT_STR_NOTE);
		if (0 != ret)
			break;
		contacts_record_get_child_record_at_p(record, _contacts_contact.number, 0, &child);
		contacts_record_get_str_p(child, _contacts_number.label, &p);
		ret = strcmp(p, CTSVC_CONTACT_STR_LABEL);
		if (0 != ret)
			break;
		contacts_record_get_child_record_at_p(record, _contacts_contact.email, 0, &child);
		contacts_record_get_str_p(child, _contacts_email.label, &p);
		ret = strcmp(p, CTSVC_CONTACT_STR_LABEL);
		if (0 != ret)
			break;
		contacts_record_get_child_record_at_p(record, _contacts_contact.event, 0, &child);
		contacts_record_get_str_p(child, _contacts_event.label, &p);
		ret = strcmp(p, CTSVC_CONTACT_STR_LABEL);
		if (0 != ret)
			break;
		contacts_record_get_child_record_at_p(record, _contacts_contact.messenger, 0, &child);
		contacts_record_get_str_p(child, _contacts_messenger.label, &p);
		ret = strcmp(p, CTSVC_CONTACT_STR_LABEL);
		if (0 != ret)
			break;
		contacts_record_get_child_record_at_p(record, _contacts_contact.address, 0, &child);
		contacts_record_get_str_p(child, _contacts_address.label, &p);
		ret = strcmp(p, CTSVC_CONTACT_STR_LABEL);
		if (0 != ret)
			break;
		contacts_record_get_child_record_at_p(record, _contacts_contact.url, 0, &child);
		contacts_record_get_str_p(child, _contacts_url.label, &p);
		ret = strcmp(p, CTSVC_CONTACT_STR_LABEL);
		if (0 != ret)
			break;
		contacts_record_get_child_record_at_p(record, _contacts_contact.nickname, 0, &child);
		contacts_record_get_str_p(child, _contacts_nickname.name, &p);
		ret = strcmp(p, CTSVC_CONTACT_STR_NAME);
		if (0 != ret)
			break;
		contacts_record_get_child_record_at_p(record, _contacts_contact.profile, 0, &child);
		contacts_record_get_str_p(child, _contacts_profile.text, &p);
		ret = strcmp(p, CTSVC_CONTACT_STR_TEXT);
		if (0 != ret)
			break;
		contacts_record_get_child_record_at_p(record, _contacts_contact.relationship, 0, &child);
		contacts_record_get_str_p(child, _contacts_relationship.label, &p);
		ret = strcmp(p, CTSVC_CONTACT_STR_LABEL);
		if (0 != ret)
			break;
		contacts_record_get_child_record_at_p(record, _contacts_contact.extension, 0, &child);
		contacts_record_get_str_p(child, _contacts_extension.data2, &p);
		ret = strcmp(p, CTSVC_CONTACT_STR_DATA2);
		if (0 != ret)
			break;
		contacts_record_get_child_record_at_p(record, _contacts_contact.sip, 0, &child);
		contacts_record_get_str_p(child, _contacts_sip.label, &p);
		ret = strcmp(p, CTSVC_CONTACT_STR_LABEL);
		if (0 != ret)
			break;
		/* end result check */

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


static int _ctsvc_tc_record_get_child_record_count_contact(void)
{
	int ret = 0;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_contact._uri, &record))) break;
		if (0 != (ret = _ctsvc_tc_record_get_child_record_count(record, _contacts_contact.name, _contacts_name._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_get_child_record_count(record, _contacts_contact.image, _contacts_image._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_get_child_record_count(record, _contacts_contact.company, _contacts_company._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_get_child_record_count(record, _contacts_contact.note, _contacts_note._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_get_child_record_count(record, _contacts_contact.number, _contacts_number._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_get_child_record_count(record, _contacts_contact.email, _contacts_email._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_get_child_record_count(record, _contacts_contact.event, _contacts_event._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_get_child_record_count(record, _contacts_contact.messenger, _contacts_messenger._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_get_child_record_count(record, _contacts_contact.address, _contacts_address._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_get_child_record_count(record, _contacts_contact.url, _contacts_url._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_get_child_record_count(record, _contacts_contact.nickname, _contacts_nickname._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_get_child_record_count(record, _contacts_contact.profile, _contacts_profile._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_get_child_record_count(record, _contacts_contact.relationship, _contacts_relationship._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_get_child_record_count(record, _contacts_contact.extension, _contacts_extension._uri))) break;
		if (0 != (ret = _ctsvc_tc_record_get_child_record_count(record, _contacts_contact.sip, _contacts_sip._uri))) break;

		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while(0);
	contacts_record_destroy(record, true);
	return ret;

}

static int _ctsvc_tc_record_compare_type_contact(ctsvc_data_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *property_list = NULL;
	contacts_record_h record = NULL;

	do {
		if (0 != (ret = ctsvc_tc_record_create_contact(LOCAL_DB_ID, LOCAL_DB_ID, PROPERTY_TYPE_CREATE1, &record))) break;
		if (0 != (ret = ctsvc_tc_record_get_property_contact(PROPERTY_TYPE_CREATE1, &property_list, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_record_compare_type(record, type, property_list, property_count))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while (0);
	contacts_record_destroy(record, true);
	return ret;
}

static int _ctsvc_tc_record_get_bool_contact(void)
{
	return _ctsvc_tc_record_compare_type_contact(PROPERTY_BOOL);
}

static int _ctsvc_tc_record_get_double_contact(void)
{
	return _ctsvc_tc_record_compare_type_contact(PROPERTY_DOUBLE);
}

static int _ctsvc_tc_record_get_int_contact(void)
{
	return _ctsvc_tc_record_compare_type_contact(PROPERTY_INT);
}

static int _ctsvc_tc_record_get_lli_contact(void)
{
	return _ctsvc_tc_record_compare_type_contact(PROPERTY_LLI);
}

static int _ctsvc_tc_record_get_str_contact(void)
{
	return _ctsvc_tc_record_compare_type_contact(PROPERTY_STR);
}

static int _ctsvc_tc_record_get_str_p_contact(void)
{
	return _ctsvc_tc_record_compare_type_contact(PROPERTY_STR);
}

static int _ctsvc_tc_record_set_bool_contact(void)
{
	return _ctsvc_tc_record_compare_type_contact(PROPERTY_BOOL);
}

static int _ctsvc_tc_record_set_double_contact(void)
{
	return _ctsvc_tc_record_compare_type_contact(PROPERTY_DOUBLE);
}

static int _ctsvc_tc_record_set_int_contact(void)
{
	return _ctsvc_tc_record_compare_type_contact(PROPERTY_INT);
}

static int _ctsvc_tc_record_set_lli_contact(void)
{
	return _ctsvc_tc_record_compare_type_contact(PROPERTY_LLI);
}

static int _ctsvc_tc_record_set_str_contact(void)
{
	return _ctsvc_tc_record_compare_type_contact(PROPERTY_STR);
}


ctsvc_tc_record_plugin_s _tc_record_contact = {
	.clone = _ctsvc_tc_record_clone_contact,
	.create = _ctsvc_tc_record_create_contact,
	.destroy = _ctsvc_tc_record_destroy_contact,
	.get_uri_p = _ctsvc_tc_record_get_uri_p_contact,
	.add_child_record = _ctsvc_tc_record_add_child_record_contact,
	.clone_child_record_list = _ctsvc_tc_record_clone_child_record_list_contact,
	.remove_child_record = _ctsvc_tc_record_remove_child_record_contact,
	.get_child_record_at_p = _ctsvc_tc_record_get_child_record_at_p_contact,
	.get_child_record_count = _ctsvc_tc_record_get_child_record_count_contact,
	.get_bool = _ctsvc_tc_record_get_bool_contact,
	.get_double = _ctsvc_tc_record_get_double_contact,
	.get_int = _ctsvc_tc_record_get_int_contact,
	.get_lli = _ctsvc_tc_record_get_lli_contact,
	.get_str = _ctsvc_tc_record_get_str_contact,
	.get_str_p = _ctsvc_tc_record_get_str_p_contact,
	.set_bool = _ctsvc_tc_record_set_bool_contact,
	.set_double = _ctsvc_tc_record_set_double_contact,
	.set_int = _ctsvc_tc_record_set_int_contact,
	.set_lli = _ctsvc_tc_record_set_lli_contact,
	.set_str = _ctsvc_tc_record_set_str_contact,
	.free_properties = _ctsvc_tc_record_free_property_contact,
};



static int _ctsvc_tc_record_clone_simple_contact(void)
{
	int ret = 0;
	contacts_record_h record = NULL;
	contacts_record_h record_clone = NULL;

	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_simple_contact._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_clone(record, &record_clone))) break;
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

static int _ctsvc_tc_record_create_simple_contact(void)
{
	int ret = 0;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_simple_contact._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while(0);
	contacts_record_destroy(record, true);
	return ret;
}

static int _ctsvc_tc_record_destroy_simple_contact(void)
{
	int ret = 0;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_simple_contact._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while(0);
	contacts_record_destroy(record, true);
	return ret;
}

static int _ctsvc_tc_record_get_uri_p_simple_contact(void)
{
	int ret = 0;
	const char *uri = NULL;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_simple_contact._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_get_uri_p(record, &uri))) break;
		if (NULL == uri || STRING_EQUAL != strcmp(uri, _contacts_simple_contact._uri)) {
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

static int _ctsvc_tc_record_compare_type_simple_contact(ctsvc_data_type_e type)
{
	int ret = 0;
	contacts_record_h record = NULL;

	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_simple_contact._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while (0);
	contacts_record_destroy(record, true);
	return ret;
}

static int _ctsvc_tc_record_get_bool_simple_contact(void)
{
	return _ctsvc_tc_record_compare_type_simple_contact(PROPERTY_BOOL);
}

static int _ctsvc_tc_record_get_double_simple_contact(void)
{
	return _ctsvc_tc_record_compare_type_simple_contact(PROPERTY_DOUBLE);
}

static int _ctsvc_tc_record_get_int_simple_contact(void)
{
	return _ctsvc_tc_record_compare_type_simple_contact(PROPERTY_INT);
}

static int _ctsvc_tc_record_get_lli_simple_contact(void)
{
	return _ctsvc_tc_record_compare_type_simple_contact(PROPERTY_LLI);
}

static int _ctsvc_tc_record_get_str_simple_contact(void)
{
	return _ctsvc_tc_record_compare_type_simple_contact(PROPERTY_STR);
}

static int _ctsvc_tc_record_get_str_p_simple_contact(void)
{
	return _ctsvc_tc_record_compare_type_simple_contact(PROPERTY_STR);
}

static int _ctsvc_tc_record_set_bool_simple_contact(void)
{
	return _ctsvc_tc_record_compare_type_simple_contact(PROPERTY_BOOL);
}

static int _ctsvc_tc_record_set_double_simple_contact(void)
{
	return _ctsvc_tc_record_compare_type_simple_contact(PROPERTY_DOUBLE);
}

static int _ctsvc_tc_record_set_int_simple_contact(void)
{
	return _ctsvc_tc_record_compare_type_simple_contact(PROPERTY_INT);
}

static int _ctsvc_tc_record_set_lli_simple_contact(void)
{
	return _ctsvc_tc_record_compare_type_simple_contact(PROPERTY_LLI);
}

static int _ctsvc_tc_record_set_str_simple_contact(void)
{
	return _ctsvc_tc_record_compare_type_simple_contact(PROPERTY_STR);
}


ctsvc_tc_record_plugin_s _tc_record_simple_contact = {
	.clone = _ctsvc_tc_record_clone_simple_contact,
	.create = _ctsvc_tc_record_create_simple_contact,
	.destroy = _ctsvc_tc_record_destroy_simple_contact,
	.get_uri_p = _ctsvc_tc_record_get_uri_p_simple_contact,
	.add_child_record = NULL,
	.clone_child_record_list = NULL,
	.remove_child_record = NULL,
	.get_child_record_at_p = NULL,
	.get_child_record_count = NULL,
	.get_bool = _ctsvc_tc_record_get_bool_simple_contact,
	.get_double = _ctsvc_tc_record_get_double_simple_contact,
	.get_int = _ctsvc_tc_record_get_int_simple_contact,
	.get_lli = _ctsvc_tc_record_get_lli_simple_contact,
	.get_str = _ctsvc_tc_record_get_str_simple_contact,
	.get_str_p = _ctsvc_tc_record_get_str_p_simple_contact,
	.set_bool = _ctsvc_tc_record_set_bool_simple_contact,
	.set_double = _ctsvc_tc_record_set_double_simple_contact,
	.set_int = _ctsvc_tc_record_set_int_simple_contact,
	.set_lli = _ctsvc_tc_record_set_lli_simple_contact,
	.set_str = _ctsvc_tc_record_set_str_simple_contact,
	.free_properties = NULL,
};

static int _ctsvc_tc_filter_add_type_contact(ctsvc_data_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *property_list = NULL;
	contacts_filter_h filter = NULL;

	do {
		if (0 != (ret = contacts_filter_create(_contacts_contact._uri, &filter))) break;
		if (0 != (ret = ctsvc_tc_record_get_property_contact(PROPERTY_TYPE_CREATE1, &property_list, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_filter_add_type(filter, type, property_list, property_count))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_filter_destroy(filter))) break;
		filter = NULL;
		return 0;
	} while (0);
	contacts_filter_destroy(filter);
	return ret;
}

static int _ctsvc_tc_filter_add_bool_contact(void)
{
	return _ctsvc_tc_filter_add_type_contact(PROPERTY_BOOL);
}

static int _ctsvc_tc_filter_add_int_contact(void)
{
	return _ctsvc_tc_filter_add_type_contact(PROPERTY_INT);
}

static int _ctsvc_tc_filter_add_double_contact(void)
{
	return _ctsvc_tc_filter_add_type_contact(PROPERTY_DOUBLE);
}

static int _ctsvc_tc_filter_add_lli_contact(void)
{
	return _ctsvc_tc_filter_add_type_contact(PROPERTY_LLI);
}

static int _ctsvc_tc_filter_add_str_contact(void)
{
	return _ctsvc_tc_filter_add_type_contact(PROPERTY_STR);
}

ctsvc_tc_filter_plugin_s _tc_filter_contact = {
	.add_bool = _ctsvc_tc_filter_add_bool_contact,
	.add_double = _ctsvc_tc_filter_add_double_contact,
	.add_int = _ctsvc_tc_filter_add_int_contact,
	.add_lli = _ctsvc_tc_filter_add_lli_contact,
	.add_str = _ctsvc_tc_filter_add_str_contact,
};
