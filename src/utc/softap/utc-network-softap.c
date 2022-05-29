#include "assert.h"
#include "utc-network-softap-utils.h"

#include <softap.h>
#include <glib.h>
#include <time.h>
#include <unistd.h>
#include <system_info.h>

static softap_h handle;
static bool softap_supported = true;

#define PASSPHRASE_MAX 10

static void __client_connection_state_changed_cb(softap_client_h client, bool opened, void *user_data)
{
	return;
}

static void __security_type_changed_cb(softap_security_type_e changed_type, void *user_data)
{
	return;
}

static void __ssid_visibility_changed_cb(bool changed_visible, void *user_data)
{
	return;
}

static void __passphrase_changed_cb(void *user_data)
{
	return;
}

static void __settings_reloaded_cb(softap_error_e result, void *user_data)
{
	return;
}

static void __enabled_cb(softap_error_e error, bool is_requested, void *data)
{
	return;
}

static void __disabled_cb(softap_error_e error, softap_disabled_cause_e code, void *data)
{
	return;
}

static bool connected_client_cb(softap_client_h client, void *user_data)
{
	return true;
}

void utc_softap_startup(void)
{
	/* start of TC */
	system_info_get_platform_bool("http://tizen.org/feature/network.wifi.softap", &softap_supported);

	if (!handle)
		softap_create(&handle);

	return;
}

void utc_softap_cleanup(void)
{
	/* end of TC */
	softap_destroy(handle);
	handle = NULL;

	return;
}

/**
 * @brief Negative test case of softap_create()
 */
int utc_softap_create_n(void)
{
	int ret = 0;

	ret = softap_create(NULL);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @brief Positive test case of softap_create()
 */
int utc_softap_create_p(void)
{
	int ret = 0;

	softap_destroy(handle);
	handle = NULL;

	ret = softap_create(&handle);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_NONE);
	return 0;

}

int utc_softap_destroy_n(void)
{
	int ret = 0;

	ret = softap_destroy(NULL);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @brief Positive test case of softap_create()
 */
int utc_softap_destroy_p(void)
{
	int ret = 0;

	ret = softap_destroy(handle);
	handle = NULL;

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_NONE);
	handle = NULL;

	return 0;
}

int utc_softap_is_enabled_n(void)
{
	int ret = 0;
	bool enable = false;

	ret = softap_is_enabled(NULL, &enable);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);
	ret = softap_is_enabled(handle, NULL);
	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);
	ret = softap_is_enabled(NULL, NULL);
	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);

	return 0;
}

int utc_softap_is_enabled_p(void)
{
	int ret = 0;
	bool enable = false;

	ret = softap_is_enabled(handle, &enable);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_NONE);

	return 0;
}

int utc_softap_get_mac_address_n(void)
{
	int ret = 0;
	char *mac = NULL;

	ret = softap_get_mac_address(NULL, NULL);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);
	ret = softap_get_mac_address(handle, NULL);
	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);
	ret = softap_get_mac_address(NULL, &mac);
	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);

	return 0;
}

/* precondition: softap should be enabled.
int utc_softap_get_mac_address_p(void)
{
	int ret = 0;
	char *mac = NULL;

	ret = softap_get_mac_address(handle, &mac);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_NONE);

	return 0;
}
*/

int utc_softap_get_network_interface_name_n(void)
{
	int ret = 0;
	char *iface = NULL;

	ret = softap_get_network_interface_name(handle, NULL);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);
	ret = softap_get_network_interface_name(NULL, &iface);
	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);
	ret = softap_get_network_interface_name(NULL, NULL);
	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);

	return 0;
}

/* precondition: softap should be enabled.
int utc_softap_get_network_interface_name_p(void)
{
	int ret = 0;
	char *iface = NULL;

	ret = softap_get_network_interface_name(handle, &iface);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	if (NULL != iface)
		free(iface);
	assert_eq(ret, SOFTAP_ERROR_NONE);
	return 0;
}
*/

int utc_softap_set_ip_address_n(void)
{
	int ret = 0;
	char *ip = "192.168.0.1";

	ret = softap_set_ip_address(handle, SOFTAP_ADDRESS_FAMILY_IPV4, NULL);
	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);
	ret = softap_set_ip_address(NULL, SOFTAP_ADDRESS_FAMILY_IPV4, ip);
	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);
	ret = softap_set_ip_address(NULL, SOFTAP_ADDRESS_FAMILY_IPV4, NULL);
	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);

	return 0;
}

int utc_softap_set_ip_address_p(void)
{
	int ret = 0;
	char *ip = "192.168.0.1";

	ret = softap_set_ip_address(handle, SOFTAP_ADDRESS_FAMILY_IPV4, ip);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_NONE);
	return 0;
}

int utc_softap_get_ip_address_n(void)
{
	int ret = 0;
	char *ip = NULL;

	ret = softap_get_ip_address(handle, SOFTAP_ADDRESS_FAMILY_IPV4, NULL);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);
	ret = softap_get_ip_address(NULL, SOFTAP_ADDRESS_FAMILY_IPV4, &ip);
	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);
	ret = softap_get_ip_address(NULL, SOFTAP_ADDRESS_FAMILY_IPV4, NULL);
	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);

	return 0;
}

/* precondition: softap should be enabled.
int utc_softap_get_ip_address_p(void)
{
	int ret = 0;
	char *ip = NULL;

	ret = softap_get_ip_address(handle, 0, &ip);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_NONE);
	return 0;
}
*/

int utc_softap_get_gateway_address_n(void)
{
	int ret = 0;
	char *gwaddress = NULL;

	ret = softap_get_gateway_address(handle, 0, NULL);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);
	ret = softap_get_gateway_address(NULL, 0, &gwaddress);
	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);
	ret = softap_get_gateway_address(NULL, 0, NULL);
	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);

	return 0;
}

/* precondition: softap should be enabled.
int utc_softap_get_gateway_address_p(void)
{
	int ret = 0;
	char *gwaddress = NULL;

	ret = softap_get_gateway_address(handle, 0, &gwaddress);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_NONE);
	return 0;
}
*/

int utc_softap_get_subnet_mask_n(void)
{
	int ret = 0;
	char *subnetmask = NULL;

	ret = softap_get_subnet_mask(NULL, 0, NULL);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);
	ret = softap_get_subnet_mask(handle, 0, NULL);
	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);
	ret = softap_get_subnet_mask(NULL, 0, &subnetmask);
	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);

	return 0;
}

/* precondition: softap should be enabled.
int utc_softap_get_subnet_mask_p(void)
{
	int ret = 0;
	char *subnetmask = NULL;

	ret = softap_get_subnet_mask(handle, SOFTAP_ADDRESS_FAMILY_IPV4, &subnetmask);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_NONE);
	return 0;
}
*/

int utc_softap_foreach_connected_clients_n(void)
{
	int ret = 0;

	ret = softap_foreach_connected_clients(handle, NULL, NULL);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);
	ret = softap_foreach_connected_clients(NULL, connected_client_cb, NULL);
	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);
	ret = softap_foreach_connected_clients(NULL, NULL, NULL);
	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);

	return 0;
}

int utc_softap_foreach_connected_clients_p(void)
{
	int ret = 0;

	ret = softap_foreach_connected_clients(handle, connected_client_cb, NULL);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_NONE);
	return 0;
}

int utc_softap_set_enabled_cb_n(void)
{
	int ret = 0;

	ret = softap_set_enabled_cb(handle, NULL, NULL);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);
	ret = softap_set_enabled_cb(NULL, __enabled_cb, NULL);
	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);
	ret = softap_set_enabled_cb(NULL, NULL, NULL);
	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);

	return 0;
}

int utc_softap_set_enabled_cb_p(void)
{
	int ret = 0;

	ret = softap_set_enabled_cb(handle, __enabled_cb, NULL);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_NONE);
	return 0;
}

int utc_softap_unset_enabled_cb_n(void)
{
	int ret = 0;

	ret = softap_unset_enabled_cb(NULL);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);
	return 0;
}

int utc_softap_unset_enabled_cb_p(void)
{
	int ret = 0;

	ret = softap_unset_enabled_cb(handle);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_NONE);
	return 0;
}

int utc_softap_set_disabled_cb_n(void)
{
	int ret = 0;

	ret = softap_set_disabled_cb(handle, NULL, NULL);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);
	ret = softap_set_disabled_cb(NULL, __disabled_cb, NULL);
	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);
	ret = softap_set_disabled_cb(NULL, NULL, NULL);
	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);

	return 0;
}

int utc_softap_set_disabled_cb_p(void)
{
	int ret = 0;

	ret = softap_set_disabled_cb(handle, __disabled_cb, NULL);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_NONE);
	return 0;
}

int utc_softap_unset_disabled_cb_n(void)
{
	int ret = 0;

	ret = softap_unset_disabled_cb(NULL);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);
	return 0;
}

int utc_softap_unset_disabled_cb_p(void)
{
	int ret = 0;

	ret = softap_unset_disabled_cb(handle);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_NONE);
	return 0;
}

int utc_softap_set_client_connection_state_changed_cb_n(void)
{
	int ret;

	ret = softap_set_client_connection_state_changed_cb(handle, NULL, NULL);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);
	ret = softap_set_client_connection_state_changed_cb(NULL, __client_connection_state_changed_cb, NULL);
	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);
	ret = softap_set_client_connection_state_changed_cb(NULL, NULL, NULL);
	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);

	return 0;
}

int utc_softap_set_client_connection_state_changed_cb_p(void)
{
	int ret;

	ret = softap_set_client_connection_state_changed_cb(handle,
			__client_connection_state_changed_cb, NULL);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_NONE);
	return 0;
}

int utc_softap_unset_client_connection_state_changed_cb_n(void)
{
	int ret;

	ret = softap_unset_client_connection_state_changed_cb(NULL);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);
	return 0;
}

int utc_softap_unset_client_connection_state_changed_cb_p(void)
{
	int ret;

	ret = softap_unset_client_connection_state_changed_cb(handle);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_NONE);
	return 0;
}

int utc_softap_set_security_type_changed_cb_n(void)
{
	int ret;

	ret = softap_set_security_type_changed_cb(handle, NULL, NULL);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);
	ret = softap_set_security_type_changed_cb(NULL, __security_type_changed_cb, NULL);
	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);
	ret = softap_set_security_type_changed_cb(NULL, NULL, NULL);
	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);

	return 0;
}

int utc_softap_set_security_type_changed_cb_p(void)
{
	int ret;

	ret = softap_set_security_type_changed_cb(handle, __security_type_changed_cb, NULL);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_NONE);
	return 0;
}

int utc_softap_unset_security_type_changed_cb_n(void)
{
	int ret;

	ret = softap_unset_security_type_changed_cb(NULL);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);
	return 0;
}

int utc_softap_unset_security_type_changed_cb_p(void)
{
	int ret;

	ret = softap_unset_security_type_changed_cb(handle);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_NONE);
	return 0;
}

int utc_softap_set_ssid_visibility_changed_cb_n(void)
{
	int ret;

	ret = softap_set_ssid_visibility_changed_cb(handle, NULL, NULL);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);
	ret = softap_set_ssid_visibility_changed_cb(NULL,
			__ssid_visibility_changed_cb, NULL);
	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);
	ret = softap_set_ssid_visibility_changed_cb(NULL, NULL, NULL);
	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);

	return 0;
}

int utc_softap_set_ssid_visibility_changed_cb_p(void)
{
	int ret;

	ret = softap_set_ssid_visibility_changed_cb(handle,
			__ssid_visibility_changed_cb, NULL);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_NONE);
	return 0;
}

int utc_softap_unset_ssid_visibility_changed_cb_n(void)
{
	int ret;

	ret = softap_unset_ssid_visibility_changed_cb(NULL);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);
	return 0;
}

int utc_softap_unset_ssid_visibility_changed_cb_p(void)
{
	int ret;

	ret = softap_unset_ssid_visibility_changed_cb(handle);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_NONE);
	return 0;
}

int utc_softap_set_passphrase_changed_cb_n(void)
{
	int ret;

	ret = softap_set_passphrase_changed_cb(handle, NULL, NULL);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);
	ret = softap_set_passphrase_changed_cb(NULL,
			__passphrase_changed_cb, NULL);
	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);
	ret = softap_set_passphrase_changed_cb(NULL, NULL, NULL);
	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);

	return 0;
}

int utc_softap_set_passphrase_changed_cb_p(void)
{
	int ret;

	ret = softap_set_passphrase_changed_cb(handle,
			__passphrase_changed_cb, NULL);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_NONE);
	return 0;
}

int utc_softap_unset_passphrase_changed_cb_n(void)
{
	int ret;

	ret = softap_unset_passphrase_changed_cb(NULL);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);
	return 0;
}

int utc_softap_unset_passphrase_changed_cb_p(void)
{
	int ret;

	ret = softap_unset_passphrase_changed_cb(handle);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_NONE);
	return 0;
}

int utc_softap_set_security_type_n(void)
{
	int ret;

	ret = softap_set_security_type(NULL,
			SOFTAP_SECURITY_TYPE_WPA2_PSK);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);

	ret = softap_set_security_type(handle, 4);
	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);
	return 0;
}

int utc_softap_set_security_type_p(void)
{
	int ret;

	ret = softap_set_security_type(handle,
			SOFTAP_SECURITY_TYPE_NONE);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_NONE);
	ret = softap_set_security_type(handle,
			SOFTAP_SECURITY_TYPE_WPA2_PSK);
	assert_eq(ret, SOFTAP_ERROR_NONE);
	return 0;
}

int utc_softap_get_security_type_n(void)
{
	int ret;

	ret = softap_get_security_type(handle, NULL);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);
	ret = softap_get_security_type(NULL, NULL);
	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);

	return 0;
}

int utc_softap_get_security_type_p(void)
{
	int ret;
	softap_security_type_e type;

	ret = softap_get_security_type(handle, &type);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_NONE);
	return 0;
}

int utc_softap_set_ssid_n(void)
{
	int ret;

	ret = softap_set_ssid(handle, NULL);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);
	ret = softap_set_ssid(NULL, "ABCDEFGH");
	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);
	ret = softap_set_ssid(NULL, NULL);
	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);

	return 0;
}

int utc_softap_set_ssid_p(void)
{
	int ret;

	ret = softap_set_ssid(handle, "ABCDEFGH");

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_NONE);
	return 0;
}

int utc_softap_get_ssid_n(void)
{
	int ret;
	char *ssid = NULL;

	ret = softap_get_ssid(handle, NULL);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);
	ret = softap_get_ssid(NULL, &ssid);
	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);
	ret = softap_get_ssid(NULL, NULL);
	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);

	return 0;
}

int utc_softap_get_ssid_p(void)
{
	int ret;
	char *ssid = NULL;

	ret = softap_get_ssid(handle, &ssid);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_NONE);

	if (ssid)
		free(ssid);
	return 0;
}

int utc_softap_set_ssid_visibility_n(void)
{
	int ret;

	ret = softap_set_ssid_visibility(NULL, 0);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);
	return 0;
}

int utc_softap_set_ssid_visibility_p(void)
{
	int ret;

	ret = softap_set_ssid_visibility(handle, 0);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_NONE);
	ret = softap_set_ssid_visibility(handle, 1);
	assert_eq(ret, SOFTAP_ERROR_NONE);
	return 0;
}

int utc_softap_get_ssid_visibility_n(void)
{
	int ret;

	ret = softap_get_ssid_visibility(handle, NULL);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);
	ret = softap_get_ssid_visibility(NULL, NULL);
	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);

	return 0;
}

int utc_softap_get_ssid_visibility_p(void)
{
	int ret;
	bool visible = false;

	ret = softap_get_ssid_visibility(handle, &visible);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_NONE);
	return 0;
}

int utc_softap_set_passphrase_n(void)
{
	int ret;

	ret = softap_set_passphrase(handle, NULL);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);
	ret = softap_set_passphrase(NULL, "zxcefddd");
	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);
	ret = softap_set_passphrase(NULL, NULL);
	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);
	ret = softap_set_passphrase(handle, "1234");
	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);
	return 0;
}

int utc_softap_set_passphrase_p(void)
{
	int ret;
	int i;
	char passphrase[PASSPHRASE_MAX + 1] = {0, };

	srand(time(NULL));

	for (i = 0; i < PASSPHRASE_MAX ; i++)
		passphrase[i] = (char) (rand()%26) + 97;

	ret = softap_set_passphrase(handle, passphrase);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_NONE);
	return 0;
}

int utc_softap_get_passphrase_n(void)
{
	int ret;
	char *pass = NULL;

	ret = softap_get_passphrase(handle, NULL);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);
	ret = softap_get_passphrase(NULL, &pass);
	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);
	ret = softap_get_passphrase(NULL, NULL);
	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);

	return 0;
}

int utc_softap_get_passphrase_p(void)
{
	int ret;
	char *pass = NULL;

	ret = softap_get_passphrase(handle, &pass);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_NONE);

	if (pass)
		free(pass);
	return 0;
}

int utc_softap_push_wps_button_n(void)
{
	int ret = softap_push_wps_button(handle);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	if (softap_utils_check_profile(MOBILE_PROFILE))
		assert_eq(ret, SOFTAP_ERROR_OPERATION_FAILED);
	else
		assert_eq(ret, SOFTAP_ERROR_NOT_PERMITTED);

	ret = softap_push_wps_button(NULL);
	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);

	return 0;
}

int utc_softap_set_wps_pin_n(void)
{
	int ret;
	char *pin = "1234567890";

	ret = softap_set_wps_pin(handle, pin);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	if (softap_utils_check_profile(MOBILE_PROFILE))
		assert_eq(ret, SOFTAP_ERROR_OPERATION_FAILED);
	else
		assert_eq(ret, SOFTAP_ERROR_NOT_PERMITTED);

	ret = softap_set_wps_pin(NULL, pin);
	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);
	ret = softap_set_wps_pin(handle, NULL);
	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);
	ret = softap_set_wps_pin(NULL, NULL);
	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);

	return 0;
}

int utc_softap_set_vendor_element_n(void)
{
	int ret;
	char *vendor = "DD050016328000";

	ret = softap_set_vendor_element(handle, NULL);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);
	ret = softap_set_vendor_element(NULL, vendor);
	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);
	ret = softap_set_vendor_element(NULL, NULL);
	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);

	return 0;
}

int utc_softap_set_vendor_element_p(void)
{
	int ret;
	char *vendor = "DD050016328000";

	ret = softap_set_vendor_element(handle, vendor);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_NONE);
	return 0;
}

int utc_softap_get_vendor_element_n(void)
{
	int ret;
	char *vendor = NULL;

	ret = softap_get_vendor_element(handle, NULL);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);
	ret = softap_get_vendor_element(NULL, &vendor);
	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);
	ret = softap_get_vendor_element(NULL, NULL);
	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);

	return 0;
}

int utc_softap_get_vendor_element_p(void)
{
	int ret;
	char *vendor = NULL;

	ret = softap_get_vendor_element(handle, &vendor);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_NONE);
	return 0;
}

int utc_softap_set_channel_n(void)
{
	int ret;
	int channel = 10;

	ret = softap_set_channel(NULL, channel);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);
	return 0;
}

int utc_softap_set_channel_p(void)
{
	int ret;
	int channel = 10;

	ret = softap_set_channel(handle, channel);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_NONE);
	return 0;
}

int utc_softap_get_channel_n(void)
{
	int ret;
	int channel;

	ret = softap_get_channel(NULL, &channel);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);
	ret = softap_get_channel(handle, NULL);
	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);
	ret = softap_get_channel(NULL, NULL);
	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);

	return 0;
}

int utc_softap_get_channel_p(void)
{
	int ret;
	int channel;

	ret = softap_get_channel(handle, &channel);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_NONE);
	return 0;
}

int utc_softap_enable_dhcp_n(void)
{
	int ret;

	ret = softap_enable_dhcp(NULL);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);
	return 0;
}

int utc_softap_enable_dhcp_p(void)
{
	int ret;

	ret = softap_enable_dhcp(handle);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(ret, SOFTAP_ERROR_NONE);

	softap_disable_dhcp(handle); // postcondition

	return 0;
}

int utc_softap_disable_dhcp_n(void)
{
	int ret;

	ret = softap_disable_dhcp(NULL);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);
	return 0;
}

int utc_softap_disable_dhcp_p(void)
{
	int ret;

	softap_enable_dhcp(handle); // precondition

	ret = softap_disable_dhcp(handle);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_NONE);
	return 0;
}

int utc_softap_is_dhcp_enabled_n(void)
{
	int ret = 0;
	bool enable = false;

	ret = softap_is_dhcp_enabled(NULL, &enable);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);
	ret = softap_is_dhcp_enabled(handle, NULL);
	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);
	ret = softap_is_dhcp_enabled(NULL, NULL);
	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);

	return 0;
}

int utc_softap_is_dhcp_enabled_p(void)
{
	int ret = 0;
	bool enable = false;

	ret = softap_is_dhcp_enabled(handle, &enable);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_NONE);
	return 0;
}

int utc_softap_enable_dhcp_with_range_n(void)
{
	int ret;
	char *str = "192.168.1.3";
	char *end = "192.168.1.200";

	ret = softap_enable_dhcp_with_range(NULL, str, end);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);
	ret = softap_enable_dhcp_with_range(handle, NULL, end);
	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);
	ret = softap_enable_dhcp_with_range(handle, str, NULL);
	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);
	ret = softap_enable_dhcp_with_range(NULL, NULL, NULL);
	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);

	return 0;
}

int utc_softap_enable_dhcp_with_range_p(void)
{
	int ret;
	char *str = "192.168.1.3";
	char *end = "192.168.1.200";

	ret = softap_enable_dhcp_with_range(handle, str, end);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(ret, SOFTAP_ERROR_NONE);

	softap_disable_dhcp(handle); // postcondition

	return 0;
}

int utc_softap_set_mode_n(void)
{
	int ret;

	ret = softap_set_mode(NULL,
			SOFTAP_WIRELESS_MODE_B);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);

	ret = softap_set_security_type(handle, 4);
	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);
	return 0;
}

int utc_softap_set_mode_p(void)
{
	int ret;

	ret = softap_set_mode(handle,
			SOFTAP_WIRELESS_MODE_B);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_NONE);
	return 0;
}

int utc_softap_get_mode_n(void)
{
	int ret;

	ret = softap_get_mode(handle, NULL);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);
	ret = softap_get_mode(NULL, NULL);
	assert_eq(ret, SOFTAP_ERROR_INVALID_PARAMETER);

	return 0;
}

int utc_softap_get_mode_p(void)
{
	int ret;
	softap_wireless_mode_e mode;

	ret = softap_get_mode(handle, &mode);

	if (!softap_supported) {
		assert_eq(ret, SOFTAP_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(ret, SOFTAP_ERROR_NONE);
	return 0;
}
