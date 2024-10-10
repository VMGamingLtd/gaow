# Notes:
#
# To debug find_library():
# cmake -DCMAKE_FIND_DEBUG_MODE=ON ../gaow

cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
  set(vcpkg_install_path /w1/vcpkg/installed/x64-windows)
  set(cpackages_install_path /w1/cpackages)
  set(mariadb_connector_install_path "/Program Files/MariaDB/MariaDB C++ Connector 64-bit")
elseif(UNIX)
  set(cpackages_install_path $ENV{MY_PATH}/w1/cpackages)
else()
  message(FATAL_ERROR "unsupported platform")
endif()

add_library(libuv STATIC IMPORTED)
if(WIN32)
  set_target_properties(libuv PROPERTIES
    IMPORTED_LOCATION ${vcpkg_install_path}/lib/uv.lib 
  )
  target_include_directories(libuv 
    INTERFACE ${vcpkg_install_path}/include
  )
elseif(UNIX)
  find_library(UV_LIBRARY NAMES uv 
    PATHS /usr/lib
    PATH_SUFFIXES x86_64-linux-gnu
    REQUIRED
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()

add_library(libz STATIC IMPORTED)
if(WIN32)
  set_target_properties(libz PROPERTIES
    IMPORTED_LOCATION ${vcpkg_install_path}/lib/zlib.lib 
  )
  target_include_directories(libz 
    INTERFACE ${vcpkg_install_path}/include
  )
elseif(UNIX)
  find_library(ZLIB_LIBRARY NAMES z 
    PATHS /usr/lib
    PATH_SUFFIXES x86_64-linux-gnu
    REQUIRED
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()

add_library(libprotobuf STATIC IMPORTED)
if(WIN32)
  set_target_properties(libprotobuf PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libprotobufd.lib 
  )
  target_include_directories(libprotobuf 
    INTERFACE ${cpackages_install_path}/include
  )
elseif(UNIX)
  set_target_properties(libprotobuf PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libprotobuf.a
  )
  target_include_directories(libprotobuf 
    INTERFACE ${cpackages_install_path}/include
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()

add_library(libprotoc STATIC IMPORTED)
if(WIN32)
  set_target_properties(libprotoc PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libprotocd.lib 
  )
  target_include_directories(libprotoc 
    INTERFACE ${cpackages_install_path}/include
  )
elseif(UNIX)
  set_target_properties(libprotoc PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libprotoc.a
  )
  target_include_directories(libprotoc 
    INTERFACE ${cpackages_install_path}/include
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()




# abseil begin
add_library(libabsl_atomic_hook_test_helper STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_atomic_hook_test_helper PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_atomic_hook_test_helper.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_atomic_hook_test_helper PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_atomic_hook_test_helper.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_bad_any_cast_impl STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_bad_any_cast_impl PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_bad_any_cast_impl.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_bad_any_cast_impl PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_bad_any_cast_impl.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_bad_optional_access STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_bad_optional_access PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_bad_optional_access.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_bad_optional_access PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_bad_optional_access.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_bad_variant_access STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_bad_variant_access PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_bad_variant_access.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_bad_variant_access PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_bad_variant_access.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_base STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_base PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_base.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_base PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_base.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_city STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_city PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_city.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_city PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_city.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_civil_time STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_civil_time PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_civil_time.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_civil_time PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_civil_time.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_cord STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_cord PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_cord.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_cord PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_cord.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_cord_internal STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_cord_internal PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_cord_internal.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_cord_internal PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_cord_internal.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_cordz_functions STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_cordz_functions PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_cordz_functions.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_cordz_functions PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_cordz_functions.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_cordz_handle STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_cordz_handle PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_cordz_handle.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_cordz_handle PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_cordz_handle.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_cordz_info STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_cordz_info PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_cordz_info.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_cordz_info PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_cordz_info.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_cordz_sample_token STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_cordz_sample_token PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_cordz_sample_token.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_cordz_sample_token PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_cordz_sample_token.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_crc32c STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_crc32c PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_crc32c.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_crc32c PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_crc32c.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_crc_cord_state STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_crc_cord_state PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_crc_cord_state.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_crc_cord_state PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_crc_cord_state.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_crc_cpu_detect STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_crc_cpu_detect PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_crc_cpu_detect.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_crc_cpu_detect PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_crc_cpu_detect.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_crc_internal STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_crc_internal PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_crc_internal.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_crc_internal PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_crc_internal.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_debugging_internal STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_debugging_internal PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_debugging_internal.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_debugging_internal PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_debugging_internal.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_demangle_internal STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_demangle_internal PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_demangle_internal.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_demangle_internal PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_demangle_internal.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_die_if_null STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_die_if_null PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_die_if_null.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_die_if_null PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_die_if_null.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_examine_stack STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_examine_stack PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_examine_stack.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_examine_stack PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_examine_stack.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_exception_safety_testing STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_exception_safety_testing PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_exception_safety_testing.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_exception_safety_testing PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_exception_safety_testing.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_exponential_biased STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_exponential_biased PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_exponential_biased.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_exponential_biased PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_exponential_biased.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_failure_signal_handler STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_failure_signal_handler PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_failure_signal_handler.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_failure_signal_handler PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_failure_signal_handler.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_flags_commandlineflag STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_flags_commandlineflag PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_flags_commandlineflag.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_flags_commandlineflag PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_flags_commandlineflag.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_flags_commandlineflag_internal STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_flags_commandlineflag_internal PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_flags_commandlineflag_internal.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_flags_commandlineflag_internal PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_flags_commandlineflag_internal.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_flags_config STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_flags_config PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_flags_config.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_flags_config PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_flags_config.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_flags_internal STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_flags_internal PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_flags_internal.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_flags_internal PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_flags_internal.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_flags_marshalling STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_flags_marshalling PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_flags_marshalling.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_flags_marshalling PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_flags_marshalling.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_flags_parse STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_flags_parse PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_flags_parse.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_flags_parse PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_flags_parse.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_flags_private_handle_accessor STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_flags_private_handle_accessor PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_flags_private_handle_accessor.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_flags_private_handle_accessor PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_flags_private_handle_accessor.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_flags_program_name STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_flags_program_name PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_flags_program_name.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_flags_program_name PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_flags_program_name.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_flags_reflection STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_flags_reflection PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_flags_reflection.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_flags_reflection PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_flags_reflection.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_flags_usage STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_flags_usage PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_flags_usage.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_flags_usage PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_flags_usage.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_flags_usage_internal STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_flags_usage_internal PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_flags_usage_internal.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_flags_usage_internal PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_flags_usage_internal.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_graphcycles_internal STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_graphcycles_internal PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_graphcycles_internal.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_graphcycles_internal PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_graphcycles_internal.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_hash STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_hash PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_hash.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_hash PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_hash.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_hash_generator_testing STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_hash_generator_testing PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_hash_generator_testing.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_hash_generator_testing PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_hash_generator_testing.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_hashtablez_sampler STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_hashtablez_sampler PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_hashtablez_sampler.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_hashtablez_sampler PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_hashtablez_sampler.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_int128 STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_int128 PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_int128.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_int128 PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_int128.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_kernel_timeout_internal STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_kernel_timeout_internal PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_kernel_timeout_internal.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_kernel_timeout_internal PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_kernel_timeout_internal.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_leak_check STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_leak_check PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_leak_check.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_leak_check PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_leak_check.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_log_entry STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_log_entry PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_log_entry.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_log_entry PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_log_entry.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_log_flags STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_log_flags PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_log_flags.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_log_flags PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_log_flags.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_log_globals STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_log_globals PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_log_globals.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_log_globals PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_log_globals.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_log_initialize STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_log_initialize PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_log_initialize.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_log_initialize PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_log_initialize.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_log_internal_check_op STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_log_internal_check_op PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_log_internal_check_op.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_log_internal_check_op PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_log_internal_check_op.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_log_internal_conditions STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_log_internal_conditions PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_log_internal_conditions.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_log_internal_conditions PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_log_internal_conditions.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_log_internal_fnmatch STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_log_internal_fnmatch PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_log_internal_fnmatch.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_log_internal_fnmatch PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_log_internal_fnmatch.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_log_internal_format STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_log_internal_format PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_log_internal_format.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_log_internal_format PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_log_internal_format.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_log_internal_globals STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_log_internal_globals PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_log_internal_globals.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_log_internal_globals PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_log_internal_globals.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_log_internal_log_sink_set STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_log_internal_log_sink_set PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_log_internal_log_sink_set.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_log_internal_log_sink_set PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_log_internal_log_sink_set.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_log_internal_message STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_log_internal_message PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_log_internal_message.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_log_internal_message PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_log_internal_message.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_log_internal_nullguard STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_log_internal_nullguard PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_log_internal_nullguard.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_log_internal_nullguard PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_log_internal_nullguard.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_log_internal_proto STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_log_internal_proto PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_log_internal_proto.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_log_internal_proto PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_log_internal_proto.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_log_internal_test_actions STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_log_internal_test_actions PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_log_internal_test_actions.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_log_internal_test_actions PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_log_internal_test_actions.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_log_internal_test_helpers STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_log_internal_test_helpers PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_log_internal_test_helpers.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_log_internal_test_helpers PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_log_internal_test_helpers.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_log_internal_test_matchers STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_log_internal_test_matchers PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_log_internal_test_matchers.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_log_internal_test_matchers PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_log_internal_test_matchers.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_log_severity STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_log_severity PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_log_severity.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_log_severity PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_log_severity.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_log_sink STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_log_sink PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_log_sink.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_log_sink PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_log_sink.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_low_level_hash STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_low_level_hash PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_low_level_hash.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_low_level_hash PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_low_level_hash.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_malloc_internal STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_malloc_internal PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_malloc_internal.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_malloc_internal PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_malloc_internal.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_per_thread_sem_test_common STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_per_thread_sem_test_common PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_per_thread_sem_test_common.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_per_thread_sem_test_common PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_per_thread_sem_test_common.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_periodic_sampler STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_periodic_sampler PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_periodic_sampler.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_periodic_sampler PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_periodic_sampler.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_pow10_helper STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_pow10_helper PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_pow10_helper.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_pow10_helper PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_pow10_helper.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_random_distributions STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_random_distributions PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_random_distributions.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_random_distributions PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_random_distributions.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_random_internal_distribution_test_util STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_random_internal_distribution_test_util PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_random_internal_distribution_test_util.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_random_internal_distribution_test_util PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_random_internal_distribution_test_util.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_random_internal_platform STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_random_internal_platform PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_random_internal_platform.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_random_internal_platform PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_random_internal_platform.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_random_internal_pool_urbg STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_random_internal_pool_urbg PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_random_internal_pool_urbg.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_random_internal_pool_urbg PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_random_internal_pool_urbg.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_random_internal_randen STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_random_internal_randen PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_random_internal_randen.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_random_internal_randen PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_random_internal_randen.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_random_internal_randen_hwaes STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_random_internal_randen_hwaes PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_random_internal_randen_hwaes.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_random_internal_randen_hwaes PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_random_internal_randen_hwaes.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_random_internal_randen_hwaes_impl STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_random_internal_randen_hwaes_impl PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_random_internal_randen_hwaes_impl.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_random_internal_randen_hwaes_impl PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_random_internal_randen_hwaes_impl.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_random_internal_randen_slow STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_random_internal_randen_slow PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_random_internal_randen_slow.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_random_internal_randen_slow PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_random_internal_randen_slow.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_random_internal_seed_material STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_random_internal_seed_material PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_random_internal_seed_material.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_random_internal_seed_material PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_random_internal_seed_material.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_random_seed_gen_exception STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_random_seed_gen_exception PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_random_seed_gen_exception.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_random_seed_gen_exception PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_random_seed_gen_exception.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_random_seed_sequences STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_random_seed_sequences PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_random_seed_sequences.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_random_seed_sequences PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_random_seed_sequences.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_raw_hash_set STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_raw_hash_set PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_raw_hash_set.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_raw_hash_set PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_raw_hash_set.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_raw_logging_internal STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_raw_logging_internal PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_raw_logging_internal.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_raw_logging_internal PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_raw_logging_internal.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_scoped_mock_log STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_scoped_mock_log PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_scoped_mock_log.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_scoped_mock_log PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_scoped_mock_log.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_scoped_set_env STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_scoped_set_env PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_scoped_set_env.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_scoped_set_env PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_scoped_set_env.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_spinlock_test_common STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_spinlock_test_common PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_spinlock_test_common.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_spinlock_test_common PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_spinlock_test_common.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_spinlock_wait STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_spinlock_wait PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_spinlock_wait.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_spinlock_wait PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_spinlock_wait.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_stack_consumption STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_stack_consumption PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_stack_consumption.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_stack_consumption PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_stack_consumption.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_stacktrace STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_stacktrace PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_stacktrace.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_stacktrace PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_stacktrace.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_status STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_status PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_status.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_status PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_status.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_statusor STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_statusor PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_statusor.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_statusor PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_statusor.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_str_format_internal STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_str_format_internal PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_str_format_internal.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_str_format_internal PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_str_format_internal.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_strerror STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_strerror PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_strerror.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_strerror PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_strerror.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_string_view STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_string_view PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_string_view.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_string_view PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_string_view.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_strings STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_strings PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_strings.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_strings PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_strings.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_strings_internal STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_strings_internal PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_strings_internal.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_strings_internal PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_strings_internal.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_symbolize STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_symbolize PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_symbolize.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_symbolize PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_symbolize.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_synchronization STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_synchronization PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_synchronization.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_synchronization PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_synchronization.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_test_instance_tracker STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_test_instance_tracker PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_test_instance_tracker.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_test_instance_tracker PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_test_instance_tracker.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_throw_delegate STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_throw_delegate PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_throw_delegate.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_throw_delegate PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_throw_delegate.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_time STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_time PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_time.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_time PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_time.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_time_internal_test_util STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_time_internal_test_util PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_time_internal_test_util.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_time_internal_test_util PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_time_internal_test_util.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_time_zone STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_time_zone PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_time_zone.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_time_zone PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_time_zone.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libabsl_vlog_config_internal STATIC IMPORTED)
if(WIN32)
  set_target_properties(libabsl_vlog_config_internal PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/absl_vlog_config_internal.lib
  )
elseif(UNIX)
  set_target_properties(libabsl_vlog_config_internal PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libabsl_vlog_config_internal.a
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
# abseil end

# protobuf_other_libs begin
add_library(lib_gmock STATIC IMPORTED)
if(WIN32)
  set_target_properties(lib_gmock PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/gmock.lib
  )
elseif(UNIX)
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libprotobufd STATIC IMPORTED)
if(WIN32)
  set_target_properties(libprotobufd PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libprotobufd.lib
  )
elseif(UNIX)
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libprotocd STATIC IMPORTED)
if(WIN32)
  set_target_properties(libprotocd PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libprotocd.lib
  )
elseif(UNIX)
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(libupbd STATIC IMPORTED)
if(WIN32)
  set_target_properties(libupbd PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libupbd.lib
  )
elseif(UNIX)
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(utf8_range STATIC IMPORTED)
if(WIN32)
  set_target_properties(utf8_range PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/utf8_range.lib
  )
elseif(UNIX)
else()
  message(FATAL_ERROR "unsupported platform")
endif()
add_library(utf8_validity STATIC IMPORTED)
if(WIN32)
  set_target_properties(utf8_validity PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/utf8_validity.lib
  )
elseif(UNIX)
else()
  message(FATAL_ERROR "unsupported platform")
endif()
# protobuf_other_libs end

# Note: jwt-cpp is header only library
add_library(jwt-cpp STATIC IMPORTED)
if(WIN32)
  target_include_directories(jwt-cpp 
    INTERFACE ${vcpkg_install_path}/include
  )
elseif(UNIX)
  target_include_directories(jwt-cpp 
    INTERFACE ${cpackages_install_path}/include
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()

add_library(libssl STATIC IMPORTED)
if(WIN32)
  set_target_properties(libssl PROPERTIES
    IMPORTED_LOCATION ${vcpkg_install_path}/lib/libssl.lib 
  )
  target_include_directories(libssl 
    INTERFACE ${vcpkg_install_path}/include
  )
elseif(UNIX)
  find_library(SSL_LIBRARY NAMES ssl 
    PATHS /usr/lib
    PATH_SUFFIXES x86_64-linux-gnu
    REQUIRED
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()

add_library(libcrypto STATIC IMPORTED)
if(WIN32)
  set_target_properties(libcrypto PROPERTIES
    IMPORTED_LOCATION ${vcpkg_install_path}/lib/libcrypto.lib 
  )
  target_include_directories(libcrypto 
    INTERFACE ${vcpkg_install_path}/include
  )
elseif(UNIX)
  find_library(CRYPTO_LIBRARY NAMES crypto
    PATHS /usr/lib
    PATH_SUFFIXES x86_64-linux-gnu
    REQUIRED
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()

add_library(libmariadbcpp STATIC IMPORTED)
if(WIN32)
  set_target_properties(libmariadbcpp PROPERTIES
    IMPORTED_LOCATION ${mariadb_connector_install_path}/mariadbcpp.lib
  )
  target_include_directories(libmariadbcpp 
    INTERFACE ${mariadb_connector_install_path}/include
  )
elseif(UNIX)
  find_library(MARIADB_CPP_LIBRARY NAMES mariadbcpp 
    PATHS /usr/lib
    PATH_SUFFIXES x86_64-linux-gnu
    REQUIRED
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()



add_library(uWebSocketsLib OBJECT IMPORTED)
file(GLOB uWebSocketsLib_obj_files "${CMAKE_SOURCE_DIR}/uWebSockets/uSockets/*.o")
set(uWebSocketsLib_includes 
  "${CMAKE_SOURCE_DIR}/uWebSockets/uSockets/src" 
  "${CMAKE_SOURCE_DIR}/uWebSockets/src"
)
set_property(TARGET uWebSocketsLib PROPERTY
  IMPORTED_OBJECTS ${uWebSocketsLib_obj_files}
)

if(WIN32)
	#target_include_directories(uWebSocketsLib 
	#  INTERFACE ${vcpkg_install_path}/include
	#)
endif()


project(WebsocketServer)

file(GLOB protobuf_source_files 
	"${CMAKE_SOURCE_DIR}/wsrv/protobuf/*.pb.cc"  
	"${CMAKE_SOURCE_DIR}/wsrv/protobuf/*.pb.h"
	"${CMAKE_SOURCE_DIR}/wsrv/protobuf/gaos/*.pb.cc"  
	"${CMAKE_SOURCE_DIR}/wsrv/protobuf/gaos/*.pb.h"
)

add_executable(wsrv 
  wsrv/main.cpp
  wsrv/WsConnection.cpp
  wsrv/WsConnection.h
  wsrv/WsSocketContext.cpp
  wsrv/WsSocketContext.h
  wsrv/uuid.cpp
  wsrv/uuid.h
  wsrv/Utils.cpp
  wsrv/Utils.h
  wsrv/message/Dispatcher.cpp
  wsrv/message/Dispatcher.h
  wsrv/message/websocket/PingPong.cpp
  wsrv/message/websocket/PingPong.h
  wsrv/message/websocket/Authenticate.cpp
  wsrv/message/websocket/Authenticate.h
  wsrv/message/unity_browser_channel/UnityBrowserChannel.cpp
  wsrv/message/unity_browser_channel/UnityBrowserChannel.h
  wsrv/message/group/GroupBroadcast.cpp
  wsrv/message/group/GroupBroadcast.h
  wsrv/message/gaos/GaosBroadcast.cpp
  wsrv/message/gaos/GaosBroadcast.h
  wsrv/groups/Groups.cpp
  wsrv/groups/Groups.h
  wsrv/caching/ExpiringCache.cpp
  wsrv/caching/ExpiringCache.h
  wsrv/caching/GroupUsersCache.cpp
  wsrv/caching/GroupUsersCache.h
  wsrv/DbConnection.cpp
  wsrv/DbConnection.h
  wsrv/config.h
  wsrv/gaos/gaos.cpp
  wsrv/gaos/gaos.h
  ${protobuf_source_files}
)

# Create source groups to maintain directory structure in Visual Studio
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}")

# Set the runtime library to /MTd for debug builds
if (MSVC)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} /MTd")
endif()

if(WIN32)
  target_link_libraries(wsrv 
    uWebSocketsLib 
    libuv
    libz
	libprotobuf
	libprotoc
# abseil beign
libabsl_atomic_hook_test_helper
libabsl_bad_any_cast_impl
libabsl_bad_optional_access
libabsl_bad_variant_access
libabsl_base
libabsl_city
libabsl_civil_time
libabsl_cord
libabsl_cord_internal
libabsl_cordz_functions
libabsl_cordz_handle
libabsl_cordz_info
libabsl_cordz_sample_token
libabsl_crc32c
libabsl_crc_cord_state
libabsl_crc_cpu_detect
libabsl_crc_internal
libabsl_debugging_internal
libabsl_demangle_internal
libabsl_die_if_null
libabsl_examine_stack
libabsl_exception_safety_testing
libabsl_exponential_biased
libabsl_failure_signal_handler
libabsl_flags_commandlineflag
libabsl_flags_commandlineflag_internal
libabsl_flags_config
libabsl_flags_internal
libabsl_flags_marshalling
libabsl_flags_parse
libabsl_flags_private_handle_accessor
libabsl_flags_program_name
libabsl_flags_reflection
libabsl_flags_usage
libabsl_flags_usage_internal
libabsl_graphcycles_internal
libabsl_hash
libabsl_hash_generator_testing
libabsl_hashtablez_sampler
libabsl_int128
libabsl_kernel_timeout_internal
libabsl_leak_check
libabsl_log_entry
libabsl_log_flags
libabsl_log_globals
libabsl_log_initialize
libabsl_log_internal_check_op
libabsl_log_internal_conditions
libabsl_log_internal_fnmatch
libabsl_log_internal_format
libabsl_log_internal_globals
libabsl_log_internal_log_sink_set
libabsl_log_internal_message
libabsl_log_internal_nullguard
libabsl_log_internal_proto
libabsl_log_internal_test_actions
libabsl_log_internal_test_helpers
libabsl_log_internal_test_matchers
libabsl_log_severity
libabsl_log_sink
libabsl_low_level_hash
libabsl_malloc_internal
libabsl_per_thread_sem_test_common
libabsl_periodic_sampler
libabsl_pow10_helper
libabsl_random_distributions
libabsl_random_internal_distribution_test_util
libabsl_random_internal_platform
libabsl_random_internal_pool_urbg
libabsl_random_internal_randen
libabsl_random_internal_randen_hwaes
libabsl_random_internal_randen_hwaes_impl
libabsl_random_internal_randen_slow
libabsl_random_internal_seed_material
libabsl_random_seed_gen_exception
libabsl_random_seed_sequences
libabsl_raw_hash_set
libabsl_raw_logging_internal
libabsl_scoped_mock_log
libabsl_scoped_set_env
libabsl_spinlock_test_common
libabsl_spinlock_wait
libabsl_stack_consumption
libabsl_stacktrace
libabsl_status
libabsl_statusor
libabsl_str_format_internal
libabsl_strerror
libabsl_string_view
libabsl_strings
libabsl_strings_internal
libabsl_symbolize
libabsl_synchronization
libabsl_test_instance_tracker
libabsl_throw_delegate
libabsl_time
libabsl_time_internal_test_util
libabsl_time_zone
libabsl_vlog_config_internal
# abseil end
# protobuf_other_libs begin
lib_gmock
libprotobufd
libprotocd
libupbd
utf8_range
utf8_validity
# protobuf_other_libs end
	libssl
	libcrypto
	libmariadbcpp
  )
elseif(UNIX)
  target_link_libraries(wsrv 
    uWebSocketsLib 
    ${UV_LIBRARY}
    ${ZLIB_LIBRARY}
    libprotobuf
    libprotoc
# abseil beign
libabsl_atomic_hook_test_helper
libabsl_bad_any_cast_impl
libabsl_bad_optional_access
libabsl_bad_variant_access
libabsl_base
libabsl_city
libabsl_civil_time
libabsl_cord
libabsl_cord_internal
libabsl_cordz_functions
libabsl_cordz_handle
libabsl_cordz_info
libabsl_cordz_sample_token
libabsl_crc32c
libabsl_crc_cord_state
libabsl_crc_cpu_detect
libabsl_crc_internal
libabsl_debugging_internal
libabsl_demangle_internal
libabsl_die_if_null
libabsl_examine_stack
libabsl_exception_safety_testing
libabsl_exponential_biased
libabsl_failure_signal_handler
libabsl_flags_commandlineflag
libabsl_flags_commandlineflag_internal
libabsl_flags_config
libabsl_flags_internal
libabsl_flags_marshalling
libabsl_flags_parse
libabsl_flags_private_handle_accessor
libabsl_flags_program_name
libabsl_flags_reflection
libabsl_flags_usage
libabsl_flags_usage_internal
libabsl_graphcycles_internal
libabsl_hash
libabsl_hash_generator_testing
libabsl_hashtablez_sampler
libabsl_int128
libabsl_kernel_timeout_internal
libabsl_leak_check
libabsl_log_entry
libabsl_log_flags
libabsl_log_globals
libabsl_log_initialize
libabsl_log_internal_check_op
libabsl_log_internal_conditions
libabsl_log_internal_fnmatch
libabsl_log_internal_format
libabsl_log_internal_globals
libabsl_log_internal_log_sink_set
libabsl_log_internal_message
libabsl_log_internal_nullguard
libabsl_log_internal_proto
libabsl_log_internal_test_actions
libabsl_log_internal_test_helpers
libabsl_log_internal_test_matchers
libabsl_log_severity
libabsl_log_sink
libabsl_low_level_hash
libabsl_malloc_internal
libabsl_per_thread_sem_test_common
libabsl_periodic_sampler
libabsl_pow10_helper
libabsl_random_distributions
libabsl_random_internal_distribution_test_util
libabsl_random_internal_platform
libabsl_random_internal_pool_urbg
libabsl_random_internal_randen
libabsl_random_internal_randen_hwaes
libabsl_random_internal_randen_hwaes_impl
libabsl_random_internal_randen_slow
libabsl_random_internal_seed_material
libabsl_random_seed_gen_exception
libabsl_random_seed_sequences
libabsl_raw_hash_set
libabsl_raw_logging_internal
libabsl_scoped_mock_log
libabsl_scoped_set_env
libabsl_spinlock_test_common
libabsl_spinlock_wait
libabsl_stack_consumption
libabsl_stacktrace
libabsl_status
libabsl_statusor
libabsl_str_format_internal
libabsl_strerror
libabsl_string_view
libabsl_strings
libabsl_strings_internal
libabsl_symbolize
libabsl_synchronization
libabsl_test_instance_tracker
libabsl_throw_delegate
libabsl_time
libabsl_time_internal_test_util
libabsl_time_zone
libabsl_vlog_config_internal
# abseil end
    ${SSL_LIBRARY}
    ${CRYPTO_LIBRARY}
	${MARIADB_CPP_LIBRARY}
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()

if(WIN32)
  # Note: allways keep cpackages_install_path include before vcpkg_install_path include, 
  #       we want manualy compiled package overide vcpkg installed package provided same include can be found  in both locations, 
  target_include_directories(wsrv PRIVATE 
    ${uWebSocketsLib_includes}
    ${cpackages_install_path}/include
    ${vcpkg_install_path}/include
	${CMAKE_SOURCE_DIR}/wsrv/protobuf
  )
elseif(UNIX)
  target_include_directories(wsrv PRIVATE 
    ${uWebSocketsLib_includes}
    ${cpackages_install_path}/include
	${CMAKE_SOURCE_DIR}/wsrv/protobuf
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
