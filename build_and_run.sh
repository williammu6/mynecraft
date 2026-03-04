#!/usr/bin/env bash

set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="${ROOT_DIR}/build"
BIN_PATH="${BUILD_DIR}/Mynecraft"
SEED="${1:-$RANDOM}"

cmake -S "${ROOT_DIR}" -B "${BUILD_DIR}" -DCMAKE_POLICY_VERSION_MINIMUM=3.5
cmake --build "${BUILD_DIR}"
"${BIN_PATH}" "${SEED}"
