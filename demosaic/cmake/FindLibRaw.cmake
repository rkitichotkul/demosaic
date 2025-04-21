find_path(LIBRAW_INCLUDE_DIR libraw/libraw.h)
find_library(LIBRAW_LIBRARY NAMES raw)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LibRaw DEFAULT_MSG LIBRAW_LIBRARY LIBRAW_INCLUDE_DIR)

if(LIBRAW_FOUND)
  set(LIBRAW_LIBRARIES ${LIBRAW_LIBRARY})
  set(LIBRAW_INCLUDE_DIRS ${LIBRAW_INCLUDE_DIR})
endif()
