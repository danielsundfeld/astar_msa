#!/bin/bash
VERSION_FILE="./src/version.h"

#head -c 32 to allow up to 32 chars in a version
cat <<EOT > $VERSION_FILE
#ifndef _VERSION_H
#define _VERSION_H

const std::string astar_version = "$(git describe --always || head -c 32)";
#endif
EOT
