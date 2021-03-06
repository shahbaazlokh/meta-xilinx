# MicroBlaze architecture tune feature configuration

# Architecture feature and override
TUNEVALID[microblaze] = "MicroBlaze"
MACHINEOVERRIDES =. "${@bb.utils.contains("TUNE_FEATURES", "microblaze", "microblaze:", "" ,d)}"

# Endian
TUNEVALID[big-endian] = "Use Microblaze Big Endian."
TUNECONFLICTS[big-endian] = "little-endian"
TUNEVALID[little-endian] = "Use Microblaze Little Endian."
TUNECONFLICTS[little-endian] = "big-endian"

MBPKGARCH_ENDIAN = "${@bb.utils.contains("TUNE_FEATURES", "little-endian", "el", "eb" ,d)}"

TUNE_CCARGS += "${@bb.utils.contains("TUNE_FEATURES", "big-endian", "-mbig-endian", "" ,d)}"
TUNE_CCARGS += "${@bb.utils.contains("TUNE_FEATURES", "little-endian", "-mlittle-endian", "" ,d)}"

# General features
TUNEVALID[barrel-shift] = "Enable Hardware Barrel Shifter"
TUNEVALID[pattern-compare] = "Enable Pattern Compare Instructions"
TUNEVALID[reorder] = "Enable Reorder Instructions"

# General feature compiler args
TUNE_CCARGS += "${@bb.utils.contains("TUNE_FEATURES", "barrel-shift", "-mxl-barrel-shift", "-mno-xl-barrel-shift" ,d)}"
TUNE_CCARGS += "${@bb.utils.contains("TUNE_FEATURES", "pattern-compare", "-mxl-pattern-compare", "-mno-xl-pattern-compare" ,d)}"
TUNE_CCARGS += "${@bb.utils.contains("TUNE_FEATURES", "reorder", "-mxl-reorder", "-mno-xl-reorder" ,d)}"

# General feature package architecture formatting
MBPKGARCH_TUNE = ""
MBPKGARCH_TUNE .= "${@bb.utils.contains("TUNE_FEATURES", "barrel-shift", "-bs", "" ,d)}"
MBPKGARCH_TUNE .= "${@bb.utils.contains("TUNE_FEATURES", "pattern-compare", "-cmp", "" ,d)}"
MBPKGARCH_TUNE .= "${@bb.utils.contains("TUNE_FEATURES", "reorder", "-re", "" ,d)}"

# Additional features
require conf/machine/include/microblaze/feature-microblaze-versions.inc
require conf/machine/include/microblaze/feature-microblaze-math.inc

# Architecture name, either 'microblazeeb' or 'microblazeel' depending on endianess
TUNE_ARCH = "microblaze${@bb.utils.contains("TUNE_FEATURES", "little-endian", "el", "eb" ,d)}"

# Package Architecture formatting
TUNE_PKGARCH = "microblaze${MBPKGARCH_ENDIAN}${MBPKGARCH_VERSION}${MBPKGARCH_TUNE}${MBPKGARCH_MATH}"

