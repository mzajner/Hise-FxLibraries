#!/usr/bin/env python3
import re
from pathlib import Path

THIRDPARTY_DIR = Path(__file__).resolve().parent.parent
PTP_DIR = THIRDPARTY_DIR / "src" / "PointToPoint"

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

CLASS_RE = re.compile(r"\b(class|struct)\s+([A-Za-z_][A-Za-z0-9_]*)\b")

# Capture param number: Potentiometer { maxValue, paramNumber, ... }
POT_RE   = re.compile(r"\bPotentiometer\s+\w+\s*\{\s*[^,]+,\s*(\d+)\s*,")
VR_RE    = re.compile(r"\bVariableResistor\s+\w+\s*\{\s*[^,]+,\s*(\d+)\s*,")
# Also handle inline constructions: Potentiometer( maxValue, paramNumber, ... )
POT_RE2  = re.compile(r"\bPotentiometer\s*\(\s*[^,]+,\s*(\d+)\s*,")
VR_RE2   = re.compile(r"\bVariableResistor\s*\(\s*[^,]+,\s*(\d+)\s*,")

COMMENT_RE = re.compile(r"^\s*//\s*(.+?)\s*$")

# Prefer comments containing these words
KEYWORDS = (
    "bass","mid","treble","tone","gain","level","drive","bias","presence",
    "notch","hpf","lpf","bpf","hp","lp","freq","frequency","q","res","resonance","mix"
)

# Preserve these acronyms exactly in the final labels
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
    # Ptp + class name with underscores removed
    return "Ptp" + "".join(re.split(r"[_\s]+", cls))

def sanitize_label(s: str) -> str:
    """
    Output contains ONLY letters/numbers/spaces.
    Spaces are collapsed. Title case applied, with acronym preservation.
    """
    s = (s or "").strip()

    # remove common noise words
    s = re.sub(r"\b(Pot|Potentiometer)\b", "", s, flags=re.IGNORECASE).strip()
    s = re.sub(r"[:\-]+$", "", s).strip()

    # allow only letters, numbers, spaces
    s = re.sub(r"[^A-Za-z0-9 ]+", " ", s)
    s = re.sub(r"\s+", " ", s).strip()
    if not s:
        return ""

    # Title case words, then restore acronyms
    words = [w.capitalize() for w in s.split(" ")]
    words = [ACRONYMS.get(w, w) for w in words]
    return " ".join(words).strip()

def infer_label_nearby(lines, hit_idx, default_label):
    """
    Look back up to 6 lines for a // comment.
    Prefer a comment containing KEYWORDS. Otherwise use the closest comment.
    """
    best = ""
    best_is_keyword = False

    for back in range(1, 7):
        j = hit_idx - back
        if j < 0:
            break
        m = COMMENT_RE.match(lines[j])
        if not m:
            continue

        txt = m.group(1).strip()
        txt_l = txt.lower()

        if any(k in txt_l for k in KEYWORDS):
            best = txt
            best_is_keyword = True
            break

        if not best:
            best = txt

    label = sanitize_label(best)
    if label:
        return label

    # fallback: sanitize default (should already be safe)
    return sanitize_label(default_label) or default_label

def extract_class_blocks(text: str):
    matches = list(CLASS_RE.finditer(text))
    for i, m in enumerate(matches):
        cls = m.group(2)
        start = m.start()
        end = matches[i+1].start() if i+1 < len(matches) else len(text)
        yield cls, text[start:end]

def main():
    print("# header\tclass\tnode\tparamCount\tlabelsCSV")

    for hdr in HEADERS:
        p = PTP_DIR / hdr
        if not p.exists():
            continue

        text = p.read_text(encoding="utf-8", errors="ignore")

        for cls, block in extract_class_blocks(text):
            lines = block.splitlines()

            param_to_label = {}  # 1-based -> label
            nums = []

            for i, line in enumerate(lines):
                for rx in (POT_RE, VR_RE, POT_RE2, VR_RE2):
                    for m in rx.finditer(line):
                        n = int(m.group(1))
                        nums.append(n)

                        if n not in param_to_label:
                            param_to_label[n] = infer_label_nearby(lines, i, f"P{n}")

            if not nums:
                continue

            param_count = max(nums)
            labels = []
            for n in range(1, param_count + 1):
                lab = param_to_label.get(n, f"P{n}")
                lab = sanitize_label(lab) or f"P{n}"
                labels.append(lab)

            labels_csv = ",".join(labels)
            node = node_name_from_class(cls)

            print(f"{hdr}\t{cls}\t{node}\t{param_count}\t{labels_csv}")

if __name__ == "__main__":
    main()
