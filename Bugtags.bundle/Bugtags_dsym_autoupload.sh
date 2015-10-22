# Copyright 2015 Bugtags. All rights reserved.
#
# Usage:
#   * In the project editor, select your target.
#   * Click "Build Phases" at the top of the project editor.
#   * Click "+" button in the top left corner.
#   * Choose "New Run Script Build Phase."
#   * Uncomment and paste the following script.
#
# --- INVOCATION SCRIPT BEGIN ---
# # SKIP_SIMULATOR_BUILDS=1
# APP_KEY="" #Fill your own App Key
# APP_SECRET="" #Fill your own App Secret
# SCRIPT_SRC=$(find "$PROJECT_DIR" -name 'Bugtags_dsym_autoupload.sh' | head -1)
# if [ ! "${SCRIPT_SRC}" ]; then
#   echo "Bugtags: err: script not found. Make sure that you're including Bugtags.bundle in your project directory"
#   exit 1
# fi
# source "${SCRIPT_SRC}"
# --- INVOCATION SCRIPT END ---

echo "Bugtags: Started uploading dSYM"

if [ ! "${APP_KEY}" ] || [ ! "${APP_SECRET}" ]; then
	echo "Bugtags error: APP_KEY or APP_SECRET is invalid"
	exit 0
fi

APP_VERSION=$(/usr/libexec/PlistBuddy -c "Print CFBundleShortVersionString" "${PROJECT_DIR}/${INFOPLIST_FILE}")
APP_BUILD=$(/usr/libexec/PlistBuddy -c "Print CFBundleVersion" "${PROJECT_DIR}/${INFOPLIST_FILE}")

# Check for simulator builds
if [ "$EFFECTIVE_PLATFORM_NAME" == "-iphonesimulator" ]; then
if [ "${SKIP_SIMULATOR_BUILDS}" ] && [ "${SKIP_SIMULATOR_BUILDS}" -eq 1 ]; then
echo "Bugtags: Skipping simulator build"
exit 0
fi
fi

# Check internet connection
if [ ! "`ping -c 1 bugtags.com`" ]; then
exit 0
fi

# Create temp directory if not exists
CURRENT_USER=$(whoami | tr -dc '[:alnum:]\n\r' | tr '[:upper:]' '[:lower:]')
TEMP_ROOT="/tmp/Bugtags-${CURRENT_USER}"
if [ ! -d "${TEMP_ROOT}" ]; then
mkdir "${TEMP_ROOT}"
fi
TEMP_DIRECTORY="${TEMP_ROOT}/$EXECUTABLE_NAME"
if [ ! -d "${TEMP_DIRECTORY}" ]; then
mkdir "${TEMP_DIRECTORY}"
fi

# Check dSYM file
DSYM_PATH=${DWARF_DSYM_FOLDER_PATH}/${DWARF_DSYM_FILE_NAME}
DSYM_UUIDs=$(dwarfdump --uuid "${DSYM_PATH}" | cut -d' ' -f2)

# Check if UUIDs exists
DSYM_UUIDs_PATH="${TEMP_DIRECTORY}/UUIDs.dat"
if [ -f "${DSYM_UUIDs_PATH}" ]; then
if grep -Fxq "${DSYM_UUIDs}" "${DSYM_UUIDs_PATH}"; then
exit 0
fi
fi

# Create dSYM .zip file
DSYM_PATH_ZIP="${TEMP_DIRECTORY}/$DWARF_DSYM_FILE_NAME.zip"
if [ ! -d "$DSYM_PATH" ]; then
echo "Bugtags error: dSYM not found: ${DSYM_PATH}"
exit 0
fi
echo "Bugtags: Compressing dSYM file..."
(/usr/bin/zip --recurse-paths -j -x *.plist --quiet "${DSYM_PATH_ZIP}" "${DSYM_PATH}") || exit 0

# Upload dSYM
echo "Bugtags: Uploading dSYM file..."
ENDPOINT="https://bugtags.com/api/apps/symbols/upload"
STATUS=$(curl "${ENDPOINT}" --write-out %{http_code} --silent --output /dev/null -F "file=@${DSYM_PATH_ZIP};type=application/octet-stream" -F "app_key=${APP_KEY}" -F "secret_key=${APP_SECRET}" -F "version_name=${APP_VERSION}" -F "version_code=${APP_BUILD}")
if [ $STATUS -ne 200 ]; then
echo "Bugtags error: dSYM archive not succesfully uploaded."
echo "Bugtags: deleting temporary dSYM archive..."
/bin/rm -f "${DSYM_PATH_ZIP}"
exit 0
fi

# Remove temp dSYM archive
echo "Bugtags: deleting temporary dSYM archive..."
/bin/rm -f "${DSYM_PATH_ZIP}"

# Save UUIDs
echo "${DSYM_UUIDs}" >> "${DSYM_UUIDs_PATH}"

# Finalize
echo "Bugtags: dSYM upload complete."
if [ "$?" -ne 0 ]; then
echo "Bugtags error: an error was encountered uploading dSYM"
exit 0
fi