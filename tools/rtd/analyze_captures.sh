#!/bin/bash
# analyze_captures.sh DIR_WITH_RGP_FILES [WORKDIR] : decode every .rgp, identify kernels, print per-kernel wave time.
set -e; T="$(cd "$(dirname "$0")" && pwd)"; D=$1; W=${2:-/tmp/openrgp-an}; mkdir -p "$W"
[ -x "$T/rtd_summary" ] || "$T/build.sh"
i=0; for f in $(ls "$D"/*.rgp | sort -V); do
  python3 "$T/mkisa.py" "$f" "$W/isa$i"; RTD_ALARM=300 RTD_DUMP="$W/w$i.txt" "$T/rtd_summary" "$f" "$W/isa$i" >/dev/null 2>&1 || true; i=$((i+1)); done
python3 "$T/analyze.py" "$W" $(seq 0 $((i-1)))
