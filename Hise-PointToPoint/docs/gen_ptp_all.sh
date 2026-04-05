#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
GEN="${SCRIPT_DIR}/gen_ptp_node.sh"
MANIFEST="${SCRIPT_DIR}/ptp_manifest.tsv"

while IFS=$'\t' read -r HEADER CLASS NODE || [[ -n "${HEADER:-}" ]]; do
  # skip blanks and comments
  [[ -z "${HEADER//[[:space:]]/}" ]] && continue
  [[ "${HEADER}" == \#* ]] && continue

  # trim CR if file has Windows line endings
  HEADER="${HEADER%$'\r'}"
  CLASS="${CLASS%$'\r'}"
  NODE="${NODE%$'\r'}"

  # fail fast if malformed line
  [[ -n "${CLASS:-}" && -n "${NODE:-}" ]] || exit 1

"${GEN}" --force "${CLASS}" "${HEADER}" "${NODE}"
done < "${MANIFEST}"
