#include <string>
#include <unistd.h>
#include <dlfcn.h>

#include "symbolhook.h"

static void *handle;

static void funA() {
    printf("!WARNING!, SYMBOL HOOK CALLED BEFORE RELOCATION INSTALLED\n");
}
extern "C" __attribute__((used)) void *p_k5_base64_decode = (void *) funA;
extern "C" void k5_base64_decode() {
    SYMBOL_HOOK( p_k5_base64_decode);
}
extern "C" __attribute__((used)) void *p_k5_base64_encode = (void *) funA;
extern "C" void k5_base64_encode() {
    SYMBOL_HOOK( p_k5_base64_encode);
}
extern "C" __attribute__((used)) void *p_k5_bcmp = (void *) funA;
extern "C" void k5_bcmp() {
    SYMBOL_HOOK( p_k5_bcmp);
}
extern "C" __attribute__((used)) void *p_k5_buf_add = (void *) funA;
extern "C" void k5_buf_add() {
    SYMBOL_HOOK( p_k5_buf_add);
}
extern "C" __attribute__((used)) void *p_k5_buf_add_fmt = (void *) funA;
extern "C" void k5_buf_add_fmt() {
    SYMBOL_HOOK( p_k5_buf_add_fmt);
}
extern "C" __attribute__((used)) void *p_k5_buf_add_len = (void *) funA;
extern "C" void k5_buf_add_len() {
    SYMBOL_HOOK( p_k5_buf_add_len);
}
extern "C" __attribute__((used)) void *p_k5_buf_free = (void *) funA;
extern "C" void k5_buf_free() {
    SYMBOL_HOOK( p_k5_buf_free);
}
extern "C" __attribute__((used)) void *p_k5_buf_get_space = (void *) funA;
extern "C" void k5_buf_get_space() {
    SYMBOL_HOOK( p_k5_buf_get_space);
}
extern "C" __attribute__((used)) void *p_k5_buf_init_dynamic = (void *) funA;
extern "C" void k5_buf_init_dynamic() {
    SYMBOL_HOOK( p_k5_buf_init_dynamic);
}
extern "C" __attribute__((used)) void *p_k5_buf_init_fixed = (void *) funA;
extern "C" void k5_buf_init_fixed() {
    SYMBOL_HOOK( p_k5_buf_init_fixed);
}
extern "C" __attribute__((used)) void *p_k5_buf_status = (void *) funA;
extern "C" void k5_buf_status() {
    SYMBOL_HOOK( p_k5_buf_status);
}
extern "C" __attribute__((used)) void *p_k5_buf_truncate = (void *) funA;
extern "C" void k5_buf_truncate() {
    SYMBOL_HOOK( p_k5_buf_truncate);
}
extern "C" __attribute__((used)) void *p_k5_clear_error = (void *) funA;
extern "C" void k5_clear_error() {
    SYMBOL_HOOK( p_k5_clear_error);
}
extern "C" __attribute__((used)) void *p_k5_free_error = (void *) funA;
extern "C" void k5_free_error() {
    SYMBOL_HOOK( p_k5_free_error);
}
extern "C" __attribute__((used)) void *p_k5_get_error = (void *) funA;
extern "C" void k5_get_error() {
    SYMBOL_HOOK( p_k5_get_error);
}
extern "C" __attribute__((used)) void *p_k5_json_array_add = (void *) funA;
extern "C" void k5_json_array_add() {
    SYMBOL_HOOK( p_k5_json_array_add);
}
extern "C" __attribute__((used)) void *p_k5_json_array_create = (void *) funA;
extern "C" void k5_json_array_create() {
    SYMBOL_HOOK( p_k5_json_array_create);
}
extern "C" __attribute__((used)) void *p_k5_json_array_fmt = (void *) funA;
extern "C" void k5_json_array_fmt() {
    SYMBOL_HOOK( p_k5_json_array_fmt);
}
extern "C" __attribute__((used)) void *p_k5_json_array_get = (void *) funA;
extern "C" void k5_json_array_get() {
    SYMBOL_HOOK( p_k5_json_array_get);
}
extern "C" __attribute__((used)) void *p_k5_json_array_length = (void *) funA;
extern "C" void k5_json_array_length() {
    SYMBOL_HOOK( p_k5_json_array_length);
}
extern "C" __attribute__((used)) void *p_k5_json_array_set = (void *) funA;
extern "C" void k5_json_array_set() {
    SYMBOL_HOOK( p_k5_json_array_set);
}
extern "C" __attribute__((used)) void *p_k5_json_bool_create = (void *) funA;
extern "C" void k5_json_bool_create() {
    SYMBOL_HOOK( p_k5_json_bool_create);
}
extern "C" __attribute__((used)) void *p_k5_json_bool_value = (void *) funA;
extern "C" void k5_json_bool_value() {
    SYMBOL_HOOK( p_k5_json_bool_value);
}
extern "C" __attribute__((used)) void *p_k5_json_decode = (void *) funA;
extern "C" void k5_json_decode() {
    SYMBOL_HOOK( p_k5_json_decode);
}
extern "C" __attribute__((used)) void *p_k5_json_encode = (void *) funA;
extern "C" void k5_json_encode() {
    SYMBOL_HOOK( p_k5_json_encode);
}
extern "C" __attribute__((used)) void *p_k5_json_get_tid = (void *) funA;
extern "C" void k5_json_get_tid() {
    SYMBOL_HOOK( p_k5_json_get_tid);
}
extern "C" __attribute__((used)) void *p_k5_json_null_create = (void *) funA;
extern "C" void k5_json_null_create() {
    SYMBOL_HOOK( p_k5_json_null_create);
}
extern "C" __attribute__((used)) void *p_k5_json_null_create_val = (void *) funA;
extern "C" void k5_json_null_create_val() {
    SYMBOL_HOOK( p_k5_json_null_create_val);
}
extern "C" __attribute__((used)) void *p_k5_json_number_create = (void *) funA;
extern "C" void k5_json_number_create() {
    SYMBOL_HOOK( p_k5_json_number_create);
}
extern "C" __attribute__((used)) void *p_k5_json_number_value = (void *) funA;
extern "C" void k5_json_number_value() {
    SYMBOL_HOOK( p_k5_json_number_value);
}
extern "C" __attribute__((used)) void *p_k5_json_object_count = (void *) funA;
extern "C" void k5_json_object_count() {
    SYMBOL_HOOK( p_k5_json_object_count);
}
extern "C" __attribute__((used)) void *p_k5_json_object_create = (void *) funA;
extern "C" void k5_json_object_create() {
    SYMBOL_HOOK( p_k5_json_object_create);
}
extern "C" __attribute__((used)) void *p_k5_json_object_get = (void *) funA;
extern "C" void k5_json_object_get() {
    SYMBOL_HOOK( p_k5_json_object_get);
}
extern "C" __attribute__((used)) void *p_k5_json_object_iterate = (void *) funA;
extern "C" void k5_json_object_iterate() {
    SYMBOL_HOOK( p_k5_json_object_iterate);
}
extern "C" __attribute__((used)) void *p_k5_json_object_set = (void *) funA;
extern "C" void k5_json_object_set() {
    SYMBOL_HOOK( p_k5_json_object_set);
}
extern "C" __attribute__((used)) void *p_k5_json_release = (void *) funA;
extern "C" void k5_json_release() {
    SYMBOL_HOOK( p_k5_json_release);
}
extern "C" __attribute__((used)) void *p_k5_json_retain = (void *) funA;
extern "C" void k5_json_retain() {
    SYMBOL_HOOK( p_k5_json_retain);
}
extern "C" __attribute__((used)) void *p_k5_json_string_create = (void *) funA;
extern "C" void k5_json_string_create() {
    SYMBOL_HOOK( p_k5_json_string_create);
}
extern "C" __attribute__((used)) void *p_k5_json_string_create_base64 = (void *) funA;
extern "C" void k5_json_string_create_base64() {
    SYMBOL_HOOK( p_k5_json_string_create_base64);
}
extern "C" __attribute__((used)) void *p_k5_json_string_create_len = (void *) funA;
extern "C" void k5_json_string_create_len() {
    SYMBOL_HOOK( p_k5_json_string_create_len);
}
extern "C" __attribute__((used)) void *p_k5_json_string_unbase64 = (void *) funA;
extern "C" void k5_json_string_unbase64() {
    SYMBOL_HOOK( p_k5_json_string_unbase64);
}
extern "C" __attribute__((used)) void *p_k5_json_string_utf8 = (void *) funA;
extern "C" void k5_json_string_utf8() {
    SYMBOL_HOOK( p_k5_json_string_utf8);
}
extern "C" __attribute__((used)) void *p_k5_once = (void *) funA;
extern "C" void k5_once() {
    SYMBOL_HOOK( p_k5_once);
}
extern "C" __attribute__((used)) void *p_k5_os_mutex_destroy = (void *) funA;
extern "C" void k5_os_mutex_destroy() {
    SYMBOL_HOOK( p_k5_os_mutex_destroy);
}
extern "C" __attribute__((used)) void *p_k5_os_mutex_init = (void *) funA;
extern "C" void k5_os_mutex_init() {
    SYMBOL_HOOK( p_k5_os_mutex_init);
}
extern "C" __attribute__((used)) void *p_k5_os_mutex_lock = (void *) funA;
extern "C" void k5_os_mutex_lock() {
    SYMBOL_HOOK( p_k5_os_mutex_lock);
}
extern "C" __attribute__((used)) void *p_k5_os_mutex_unlock = (void *) funA;
extern "C" void k5_os_mutex_unlock() {
    SYMBOL_HOOK( p_k5_os_mutex_unlock);
}
extern "C" __attribute__((used)) void *p_k5_path_isabs = (void *) funA;
extern "C" void k5_path_isabs() {
    SYMBOL_HOOK( p_k5_path_isabs);
}
extern "C" __attribute__((used)) void *p_k5_path_join = (void *) funA;
extern "C" void k5_path_join() {
    SYMBOL_HOOK( p_k5_path_join);
}
extern "C" __attribute__((used)) void *p_k5_path_split = (void *) funA;
extern "C" void k5_path_split() {
    SYMBOL_HOOK( p_k5_path_split);
}
extern "C" __attribute__((used)) void *p_k5_set_error = (void *) funA;
extern "C" void k5_set_error() {
    SYMBOL_HOOK( p_k5_set_error);
}
extern "C" __attribute__((used)) void *p_k5_set_error_info_callout_fn = (void *) funA;
extern "C" void k5_set_error_info_callout_fn() {
    SYMBOL_HOOK( p_k5_set_error_info_callout_fn);
}
extern "C" __attribute__((used)) void *p_k5_strerror_r = (void *) funA;
extern "C" void k5_strerror_r() {
    SYMBOL_HOOK( p_k5_strerror_r);
}
extern "C" __attribute__((used)) void *p_k5_utf16le_to_utf8 = (void *) funA;
extern "C" void k5_utf16le_to_utf8() {
    SYMBOL_HOOK( p_k5_utf16le_to_utf8);
}
extern "C" __attribute__((used)) void *p_k5_utf8_to_utf16le = (void *) funA;
extern "C" void k5_utf8_to_utf16le() {
    SYMBOL_HOOK( p_k5_utf8_to_utf16le);
}
extern "C" __attribute__((used)) void *p_k5_vset_error = (void *) funA;
extern "C" void k5_vset_error() {
    SYMBOL_HOOK( p_k5_vset_error);
}
extern "C" __attribute__((used)) void *p_krb5int_close_plugin = (void *) funA;
extern "C" void krb5int_close_plugin() {
    SYMBOL_HOOK( p_krb5int_close_plugin);
}
extern "C" __attribute__((used)) void *p_krb5int_close_plugin_dirs = (void *) funA;
extern "C" void krb5int_close_plugin_dirs() {
    SYMBOL_HOOK( p_krb5int_close_plugin_dirs);
}
extern "C" __attribute__((used)) void *p_krb5int_free_plugin_dir_data = (void *) funA;
extern "C" void krb5int_free_plugin_dir_data() {
    SYMBOL_HOOK( p_krb5int_free_plugin_dir_data);
}
extern "C" __attribute__((used)) void *p_krb5int_free_plugin_dir_func = (void *) funA;
extern "C" void krb5int_free_plugin_dir_func() {
    SYMBOL_HOOK( p_krb5int_free_plugin_dir_func);
}
extern "C" __attribute__((used)) void *p_krb5int_freeaddrinfo = (void *) funA;
extern "C" void krb5int_freeaddrinfo() {
    SYMBOL_HOOK( p_krb5int_freeaddrinfo);
}
extern "C" __attribute__((used)) void *p_krb5int_gai_strerror = (void *) funA;
extern "C" void krb5int_gai_strerror() {
    SYMBOL_HOOK( p_krb5int_gai_strerror);
}
extern "C" __attribute__((used)) void *p_krb5int_get_plugin_data = (void *) funA;
extern "C" void krb5int_get_plugin_data() {
    SYMBOL_HOOK( p_krb5int_get_plugin_data);
}
extern "C" __attribute__((used)) void *p_krb5int_get_plugin_dir_data = (void *) funA;
extern "C" void krb5int_get_plugin_dir_data() {
    SYMBOL_HOOK( p_krb5int_get_plugin_dir_data);
}
extern "C" __attribute__((used)) void *p_krb5int_get_plugin_dir_func = (void *) funA;
extern "C" void krb5int_get_plugin_dir_func() {
    SYMBOL_HOOK( p_krb5int_get_plugin_dir_func);
}
extern "C" __attribute__((used)) void *p_krb5int_get_plugin_func = (void *) funA;
extern "C" void krb5int_get_plugin_func() {
    SYMBOL_HOOK( p_krb5int_get_plugin_func);
}
extern "C" __attribute__((used)) void *p_krb5int_getaddrinfo = (void *) funA;
extern "C" void krb5int_getaddrinfo() {
    SYMBOL_HOOK( p_krb5int_getaddrinfo);
}
extern "C" __attribute__((used)) void *p_krb5int_getnameinfo = (void *) funA;
extern "C" void krb5int_getnameinfo() {
    SYMBOL_HOOK( p_krb5int_getnameinfo);
}
extern "C" __attribute__((used)) void *p_krb5int_getspecific = (void *) funA;
extern "C" void krb5int_getspecific() {
    SYMBOL_HOOK( p_krb5int_getspecific);
}
extern "C" __attribute__((used)) void *p_krb5int_gmt_mktime = (void *) funA;
extern "C" void krb5int_gmt_mktime() {
    SYMBOL_HOOK( p_krb5int_gmt_mktime);
}
extern "C" __attribute__((used)) void *p_krb5int_key_delete = (void *) funA;
extern "C" void krb5int_key_delete() {
    SYMBOL_HOOK( p_krb5int_key_delete);
}
extern "C" __attribute__((used)) void *p_krb5int_key_register = (void *) funA;
extern "C" void krb5int_key_register() {
    SYMBOL_HOOK( p_krb5int_key_register);
}
extern "C" __attribute__((used)) void *p_krb5int_mutex_alloc = (void *) funA;
extern "C" void krb5int_mutex_alloc() {
    SYMBOL_HOOK( p_krb5int_mutex_alloc);
}
extern "C" __attribute__((used)) void *p_krb5int_mutex_free = (void *) funA;
extern "C" void krb5int_mutex_free() {
    SYMBOL_HOOK( p_krb5int_mutex_free);
}
extern "C" __attribute__((used)) void *p_krb5int_mutex_lock = (void *) funA;
extern "C" void krb5int_mutex_lock() {
    SYMBOL_HOOK( p_krb5int_mutex_lock);
}
extern "C" __attribute__((used)) void *p_krb5int_mutex_unlock = (void *) funA;
extern "C" void krb5int_mutex_unlock() {
    SYMBOL_HOOK( p_krb5int_mutex_unlock);
}
extern "C" __attribute__((used)) void *p_krb5int_open_plugin = (void *) funA;
extern "C" void krb5int_open_plugin() {
    SYMBOL_HOOK( p_krb5int_open_plugin);
}
extern "C" __attribute__((used)) void *p_krb5int_open_plugin_dirs = (void *) funA;
extern "C" void krb5int_open_plugin_dirs() {
    SYMBOL_HOOK( p_krb5int_open_plugin_dirs);
}
extern "C" __attribute__((used)) void *p_krb5int_pthread_loaded = (void *) funA;
extern "C" void krb5int_pthread_loaded() {
    SYMBOL_HOOK( p_krb5int_pthread_loaded);
}
extern "C" __attribute__((used)) void *p_krb5int_setspecific = (void *) funA;
extern "C" void krb5int_setspecific() {
    SYMBOL_HOOK( p_krb5int_setspecific);
}
extern "C" __attribute__((used)) void *p_krb5int_strlcat = (void *) funA;
extern "C" void krb5int_strlcat() {
    SYMBOL_HOOK( p_krb5int_strlcat);
}
extern "C" __attribute__((used)) void *p_krb5int_strlcpy = (void *) funA;
extern "C" void krb5int_strlcpy() {
    SYMBOL_HOOK( p_krb5int_strlcpy);
}
extern "C" __attribute__((used)) void *p_krb5int_ucs4_to_utf8 = (void *) funA;
extern "C" void krb5int_ucs4_to_utf8() {
    SYMBOL_HOOK( p_krb5int_ucs4_to_utf8);
}
extern "C" __attribute__((used)) void *p_krb5int_utf8_next = (void *) funA;
extern "C" void krb5int_utf8_next() {
    SYMBOL_HOOK( p_krb5int_utf8_next);
}
extern "C" __attribute__((used)) void *p_krb5int_utf8_to_ucs4 = (void *) funA;
extern "C" void krb5int_utf8_to_ucs4() {
    SYMBOL_HOOK( p_krb5int_utf8_to_ucs4);
}
extern "C" __attribute__((used)) void *p_krb5int_zap = (void *) funA;
extern "C" void krb5int_zap() {
    SYMBOL_HOOK( p_krb5int_zap);
}
static void __attribute__  ((constructor (103))) hookInit() {
handle = dlopen("libkrb5support.so.0", RTLD_LAZY);
p_k5_base64_decode = dlsym(handle, "k5_base64_decode");
p_k5_base64_encode = dlsym(handle, "k5_base64_encode");
p_k5_bcmp = dlsym(handle, "k5_bcmp");
p_k5_buf_add = dlsym(handle, "k5_buf_add");
p_k5_buf_add_fmt = dlsym(handle, "k5_buf_add_fmt");
p_k5_buf_add_len = dlsym(handle, "k5_buf_add_len");
p_k5_buf_free = dlsym(handle, "k5_buf_free");
p_k5_buf_get_space = dlsym(handle, "k5_buf_get_space");
p_k5_buf_init_dynamic = dlsym(handle, "k5_buf_init_dynamic");
p_k5_buf_init_fixed = dlsym(handle, "k5_buf_init_fixed");
p_k5_buf_status = dlsym(handle, "k5_buf_status");
p_k5_buf_truncate = dlsym(handle, "k5_buf_truncate");
p_k5_clear_error = dlsym(handle, "k5_clear_error");
p_k5_free_error = dlsym(handle, "k5_free_error");
p_k5_get_error = dlsym(handle, "k5_get_error");
p_k5_json_array_add = dlsym(handle, "k5_json_array_add");
p_k5_json_array_create = dlsym(handle, "k5_json_array_create");
p_k5_json_array_fmt = dlsym(handle, "k5_json_array_fmt");
p_k5_json_array_get = dlsym(handle, "k5_json_array_get");
p_k5_json_array_length = dlsym(handle, "k5_json_array_length");
p_k5_json_array_set = dlsym(handle, "k5_json_array_set");
p_k5_json_bool_create = dlsym(handle, "k5_json_bool_create");
p_k5_json_bool_value = dlsym(handle, "k5_json_bool_value");
p_k5_json_decode = dlsym(handle, "k5_json_decode");
p_k5_json_encode = dlsym(handle, "k5_json_encode");
p_k5_json_get_tid = dlsym(handle, "k5_json_get_tid");
p_k5_json_null_create = dlsym(handle, "k5_json_null_create");
p_k5_json_null_create_val = dlsym(handle, "k5_json_null_create_val");
p_k5_json_number_create = dlsym(handle, "k5_json_number_create");
p_k5_json_number_value = dlsym(handle, "k5_json_number_value");
p_k5_json_object_count = dlsym(handle, "k5_json_object_count");
p_k5_json_object_create = dlsym(handle, "k5_json_object_create");
p_k5_json_object_get = dlsym(handle, "k5_json_object_get");
p_k5_json_object_iterate = dlsym(handle, "k5_json_object_iterate");
p_k5_json_object_set = dlsym(handle, "k5_json_object_set");
p_k5_json_release = dlsym(handle, "k5_json_release");
p_k5_json_retain = dlsym(handle, "k5_json_retain");
p_k5_json_string_create = dlsym(handle, "k5_json_string_create");
p_k5_json_string_create_base64 = dlsym(handle, "k5_json_string_create_base64");
p_k5_json_string_create_len = dlsym(handle, "k5_json_string_create_len");
p_k5_json_string_unbase64 = dlsym(handle, "k5_json_string_unbase64");
p_k5_json_string_utf8 = dlsym(handle, "k5_json_string_utf8");
p_k5_once = dlsym(handle, "k5_once");
p_k5_os_mutex_destroy = dlsym(handle, "k5_os_mutex_destroy");
p_k5_os_mutex_init = dlsym(handle, "k5_os_mutex_init");
p_k5_os_mutex_lock = dlsym(handle, "k5_os_mutex_lock");
p_k5_os_mutex_unlock = dlsym(handle, "k5_os_mutex_unlock");
p_k5_path_isabs = dlsym(handle, "k5_path_isabs");
p_k5_path_join = dlsym(handle, "k5_path_join");
p_k5_path_split = dlsym(handle, "k5_path_split");
p_k5_set_error = dlsym(handle, "k5_set_error");
p_k5_set_error_info_callout_fn = dlsym(handle, "k5_set_error_info_callout_fn");
p_k5_strerror_r = dlsym(handle, "k5_strerror_r");
p_k5_utf16le_to_utf8 = dlsym(handle, "k5_utf16le_to_utf8");
p_k5_utf8_to_utf16le = dlsym(handle, "k5_utf8_to_utf16le");
p_k5_vset_error = dlsym(handle, "k5_vset_error");
p_krb5int_close_plugin = dlsym(handle, "krb5int_close_plugin");
p_krb5int_close_plugin_dirs = dlsym(handle, "krb5int_close_plugin_dirs");
p_krb5int_free_plugin_dir_data = dlsym(handle, "krb5int_free_plugin_dir_data");
p_krb5int_free_plugin_dir_func = dlsym(handle, "krb5int_free_plugin_dir_func");
p_krb5int_freeaddrinfo = dlsym(handle, "krb5int_freeaddrinfo");
p_krb5int_gai_strerror = dlsym(handle, "krb5int_gai_strerror");
p_krb5int_get_plugin_data = dlsym(handle, "krb5int_get_plugin_data");
p_krb5int_get_plugin_dir_data = dlsym(handle, "krb5int_get_plugin_dir_data");
p_krb5int_get_plugin_dir_func = dlsym(handle, "krb5int_get_plugin_dir_func");
p_krb5int_get_plugin_func = dlsym(handle, "krb5int_get_plugin_func");
p_krb5int_getaddrinfo = dlsym(handle, "krb5int_getaddrinfo");
p_krb5int_getnameinfo = dlsym(handle, "krb5int_getnameinfo");
p_krb5int_getspecific = dlsym(handle, "krb5int_getspecific");
p_krb5int_gmt_mktime = dlsym(handle, "krb5int_gmt_mktime");
p_krb5int_key_delete = dlsym(handle, "krb5int_key_delete");
p_krb5int_key_register = dlsym(handle, "krb5int_key_register");
p_krb5int_mutex_alloc = dlsym(handle, "krb5int_mutex_alloc");
p_krb5int_mutex_free = dlsym(handle, "krb5int_mutex_free");
p_krb5int_mutex_lock = dlsym(handle, "krb5int_mutex_lock");
p_krb5int_mutex_unlock = dlsym(handle, "krb5int_mutex_unlock");
p_krb5int_open_plugin = dlsym(handle, "krb5int_open_plugin");
p_krb5int_open_plugin_dirs = dlsym(handle, "krb5int_open_plugin_dirs");
p_krb5int_pthread_loaded = dlsym(handle, "krb5int_pthread_loaded");
p_krb5int_setspecific = dlsym(handle, "krb5int_setspecific");
p_krb5int_strlcat = dlsym(handle, "krb5int_strlcat");
p_krb5int_strlcpy = dlsym(handle, "krb5int_strlcpy");
p_krb5int_ucs4_to_utf8 = dlsym(handle, "krb5int_ucs4_to_utf8");
p_krb5int_utf8_next = dlsym(handle, "krb5int_utf8_next");
p_krb5int_utf8_to_ucs4 = dlsym(handle, "krb5int_utf8_to_ucs4");
p_krb5int_zap = dlsym(handle, "krb5int_zap");

}