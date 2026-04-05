#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
GEN="${SCRIPT_DIR}/gen_ptp_node.sh"
MANIFEST="${SCRIPT_DIR}/ptp_manifest_params.tsv"

while IFS=$'\t' read -r HEADER CLASS NODE PARAMCOUNT LABELS; do
  [[ -z "${HEADER:-}" ]] && continue
  [[ "${HEADER}" == \#* ]] && continue
  HEADER="${HEADER%$'\r'}"
  CLASS="${CLASS%$'\r'}"
  NODE="${NODE%$'\r'}"
  PARAMCOUNT="${PARAMCOUNT%$'\r'}"
  LABELS="${LABELS%$'\r'}"

  "${GEN}" --force "${CLASS}" "${HEADER}" "${NODE}" "${PARAMCOUNT}" "${LABELS}"
done < "${MANIFEST}"
