/*
 * Version information for Yorl Executive Tools (yolex)
 */
#ifndef VERSION_H
#define VERSION_H

#define YORL_VERSION_MAJOR 1
#define YORL_VERSION_MINOR 0
#define YORL_VERSION_PATCH 0
#define YORL_VERSION_BUILD 2437

#define YORL_VERSION_STRING "1.0.0-2437"

/* Function declarations */
const char* get_yorl_version(void);
const char* get_build_date(void);
const char* get_compiler_info(void);

#endif /* VERSION_H */
/* Additional function declarations for yorl.y compatibility */
const char* get_yorl_full_version(void);
const char* get_version_info(void);