#!/usr/bin/env python3
import argparse
import re
from pathlib import Path

# ----------------------------
# Config
# ----------------------------
HEADERS = [
    "PedalCircuits.h",
    "ClippingCircuits.h",
    "FilterCircuits.h",
    "EQCircuits.h",
    "AmpTonestacks.h",
    "AmpClippers.h",
    "ExampleChains.h",
    "Lite.h",
]

CLASS_RE = re.compile(r"\bclass\s+([A-Za-z_][A-Za-z0-9_]*)\s*:\s*public\s+Circuit\b")
COMMENT_RE = re.compile(r"^\s*//\s*(.+?)\s*$")

# Param number extraction (1-based in PTP)
POT_RE  = re.compile(r"\bPotentiometer\s+\w+\s*\{\s*[^,]+,\s*(\d+)\s*,")
VR_RE   = re.compile(r"\bVariableResistor\s+\w+\s*\{\s*[^,]+,\s*(\d+)\s*,")
POT_RE2 = re.compile(r"\bPotentiometer\s*\(\s*[^,]+,\s*(\d+)\s*,")
VR_RE2  = re.compile(r"\bVariableResistor\s*\(\s*[^,]+,\s*(\d+)\s*,")

KEYWORDS = (
    "bass","mid","treble","tone","gain","level","drive","bias","presence",
    "notch","hpf","lpf","bpf","hp","lp","freq","frequency","q","res","resonance","mix"
)

ACRONYMS = {
    "Hpf": "HPF",
    "Lpf": "LPF",
    "Eq":  "EQ",
    "Bpf": "BPF",
    "Hp":  "HP",
    "Lp":  "LP",
    "Q":   "Q",
}

def node_name_from_class(cls: str) -> str:
    # CamelCase: remove underscores from class name, prefix with Ptp
    return "Ptp" + "".join(re.split(r"[_\s]+", cls))

def sanitize_label(s: str) -> str:
    """
    Output contains ONLY letters/numbers/spaces.
    Spaces collapsed. Title-cased, with acronym preservation.
    """
    s = (s or "").strip()
    s = re.sub(r"\b(Pot|Potentiometer)\b", "", s, flags=re.IGNORECASE).strip()
    s = re.sub(r"[:\-]+$", "", s).strip()

    # keep only letters/numbers/spaces
    s = re.sub(r"[^A-Za-z0-9 ]+", " ", s)
    s = re.sub(r"\s+", " ", s).strip()
    if not s:
        return ""

    words = [w.capitalize() for w in s.split(" ")]
    words = [ACRONYMS.get(w, w) for w in words]
    return " ".join(words).strip()

def infer_label_nearby(lines, hit_idx, default_label):
    best = ""
    for back in range(1, 7):
        j = hit_idx - back
        if j < 0:
            break
        m = COMMENT_RE.match(lines[j])
        if not m:
            continue
        txt = m.group(1).strip()
        if any(k in txt.lower() for k in KEYWORDS):
            best = txt
            break
        if not best:
            best = txt

    label = sanitize_label(best)
    if label:
        return label
    return sanitize_label(default_label) or default_label

def extract_class_blocks(text: str):
    matches = list(CLASS_RE.finditer(text))
    for i, m in enumerate(matches):
        cls = m.group(1)
        start = m.start()
        end = matches[i+1].start() if i+1 < len(matches) else len(text)
        yield cls, text[start:end]

def analyze_params(block: str):
    lines = block.splitlines()
    nums = []
    labels = {}  # 1-based -> inferred label

    for i, line in enumerate(lines):
        for rx in (POT_RE, VR_RE, POT_RE2, VR_RE2):
            for mm in rx.finditer(line):
                n = int(mm.group(1))
                nums.append(n)
                if n not in labels:
                    labels[n] = infer_label_nearby(lines, i, f"P{n}")

    if not nums:
        return 0, []

    count = max(nums)
    out_labels = []
    for n in range(1, count + 1):
        lab = labels.get(n, f"P{n}")
        lab = sanitize_label(lab) or f"P{n}"
        out_labels.append(lab)
    return count, out_labels

def load_overrides(path: Path):
    """
    Optional TSV format:
      nodeName<TAB>labelsCSV
    labelsCSV example: Bass,Mid,Treble
    """
    overrides = {}
    if not path or not path.exists():
        return overrides

    for raw in path.read_text(encoding="utf-8", errors="ignore").splitlines():
        if not raw.strip() or raw.lstrip().startswith("#"):
            continue
        parts = raw.split("\t")
        if len(parts) < 2:
            continue
        node = parts[0].strip()
        labels_csv = parts[1].strip()
        # sanitize each label hard
        labs = [sanitize_label(x) for x in labels_csv.split(",")]
        labs = [x for x in labs if x]
        if node and labs:
            overrides[node] = labs
    return overrides

def write_wrapper(out_file: Path, ptp_header: str, circuit_class: str, node_name: str,
                  param_count: int, param_labels: list[str], force: bool):
    if out_file.exists() and not force:
        return

    include_path = f'src/PointToPoint/{ptp_header}'

    # Build params initializer
    params_init = ""
    if param_count > 0:
        params_init = "    std::vector<double> params { " + ", ".join(["0.5"] * param_count) + " };\n\n"

    # setParameter template
    set_param = ""
    create_params = "    void createParameters(ParameterDataList&) {}\n"
    if param_count > 0:
        lines = []
        lines.append("    template <int P> void setParameter(double v)")
        lines.append("    {")
        for i in range(param_count):
            if i == 0:
                lines.append(f"        if      (P == {i}) params[{i}] = v;")
            else:
                lines.append(f"        else if (P == {i}) params[{i}] = v;")
        lines.append("    }")
        lines.append("")
        lines.append("    void createParameters(ParameterDataList& data)")
        lines.append("    {")
        for i, lab in enumerate(param_labels):
            lines.append("        {")
            lines.append(f'            parameter::data p("{lab}", {{ 0.0, 1.0 }});')
            lines.append(f"            registerCallback<{i}>(p);")
            lines.append("            p.setDefaultValue(0.5);")
            lines.append("            data.add(std::move(p));")
            lines.append("        }")
        lines.append("    }")
        create_params = "\n".join(lines) + "\n"

        set_param = ""  # already included in create_params

    # process() param push
    param_push = ""
    if param_count > 0:
        param_push = "        effect.setParametersWithSmoothing(params);\n\n"

    content = f"""#pragma once
#include <JuceHeader.h>
#include "{include_path}"

namespace project
{{
using namespace juce;
using namespace hise;
using namespace scriptnode;

template <int NV>
struct {node_name} : public data::base
{{
    SNEX_NODE({node_name});

    struct MetadataClass {{ SN_NODE_ID("{node_name}"); }};

    static constexpr bool isModNode()            {{ return false; }}
    static constexpr bool isPolyphonic()         {{ return NV > 1; }}
    static constexpr bool hasTail()              {{ return false; }}
    static constexpr bool isSuspendedOnSilence() {{ return true; }}
    static constexpr int  getFixChannelAmount()  {{ return 2; }}

    static constexpr int NumTables         = 0;
    static constexpr int NumSliderPacks    = 0;
    static constexpr int NumAudioFiles     = 0;
    static constexpr int NumFilters        = 0;
    static constexpr int NumDisplayBuffers = 0;

    PointToPoint::{circuit_class} effect;

    double sampleRate = 44100.0;
    int    blockSize  = 512;

{params_init}    void prepare(PrepareSpecs specs)
    {{
        sampleRate = specs.sampleRate;
        blockSize  = specs.blockSize;
        effect.prepare(sampleRate, blockSize);
        effect.setParameterUpdateIntervalInSamples(64);
        effect.setSmoothResponseTimeMilliseconds(5.0f);
    }}

    void reset()
    {{
        effect.prepare(sampleRate, blockSize);
    }}

    template <typename ProcessDataType>
    void process(ProcessDataType& data)
    {{
{param_push}        auto& fix = data.template as<ProcessData<2>>();
        auto  blk = fix.toAudioBlock();

        float* L = blk.getChannelPointer(0);
        float* R = blk.getChannelPointer(1);
        int    n = data.getNumSamples();

        effect.processInPlace(L, 0, n);
        effect.processInPlace(R, 1, n);
    }}

    SN_EMPTY_PROCESS_FRAME;
    SN_EMPTY_HANDLE_EVENT;

{create_params}
    void setExternalData(const ExternalData&, int) {{}}
    int  handleModulation(double&) {{ return 0; }}
}};

}} // namespace project
"""

    out_file.write_text(content, encoding="utf-8")

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--force", action="store_true", help="overwrite existing wrapper headers")
    ap.add_argument("--base-only", action="store_true", help="generate without exposing parameters")
    ap.add_argument("--overrides", type=str, default="", help="optional TSV: nodeName<TAB>labelsCSV")
    args = ap.parse_args()

    thirdparty_dir = Path(__file__).resolve().parent.parent
    ptp_dir = thirdparty_dir / "src" / "PointToPoint"

    overrides = load_overrides(Path(args.overrides)) if args.overrides else {}

    for hdr in HEADERS:
        header_path = ptp_dir / hdr
        if not header_path.exists():
            continue

        text = header_path.read_text(encoding="utf-8", errors="ignore")

        for cls, block in extract_class_blocks(text):
            node = node_name_from_class(cls)
            out_file = thirdparty_dir / f"{node}.h"

            if args.base_only:
                param_count, labels = 0, []
            else:
                param_count, labels = analyze_params(block)
                if node in overrides:
                    labels = overrides[node]
                    param_count = len(labels)

            if param_count > 0 and not labels:
                labels = [f"P{i}" for i in range(1, param_count + 1)]

            write_wrapper(
                out_file=out_file,
                ptp_header=hdr,
                circuit_class=cls,
                node_name=node,
                param_count=param_count,
                param_labels=labels,
                force=args.force
            )

if __name__ == "__main__":
    main()
