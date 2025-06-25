#!/usr/bin/env python3
import re, sys, os

def extract_prototypes(lines):
    protos = []

    # 1) Your simple style:  word<TAB>*?name(arg_type arg_name)
    simple_re = re.compile(
        r'^\s*'
        r'(?P<ret>\w+)'        # return type: a single word
        r'\t'                  # a literal tab
        r'(?P<name>\*?\w+)'    # optional * then name
        r'\('
        r'(?P<args>\w+\s+\w+)' # exactly two words: type + name
        r'\)\s*$'
    )

    # 2) Single-line with brace:  ret name(args) {
    single_re = re.compile(
        r'^\s*'
        r'(?P<ret>[A-Za-z_][\w\s\*\:<>]*?)'
        r'\s+'
        r'(?P<name>[A-Za-z_]\w*)'
        r'\s*\('
        r'(?P<args>[^)]*)'
        r'\)\s*\{'
    )

    # 3) Signature-only then brace-on-next-line:
    sig_re = re.compile(
        r'^\s*'
        r'(?P<ret>[A-Za-z_][\w\s\*\:<>]*?)'
        r'\s+'
        r'(?P<name>[A-Za-z_]\w*)'
        r'\s*\('
        r'(?P<args>[^)]*)'
        r'\)\s*$'
    )

    i = 0
    while i < len(lines):
        line = lines[i].rstrip()

        # simple style match
        m0 = simple_re.match(line)
        if m0:
            ret, name, args = m0.group('ret'), m0.group('name'), m0.group('args')
            protos.append(f"{ret} {name}({args});")
            i += 1
            continue

        # single-line with {
        m1 = single_re.match(line)
        if m1:
            ret = m1.group('ret').strip()
            name = m1.group('name')
            args = m1.group('args').strip() or 'void'
            protos.append(f"{ret} {name}({args});")
            i += 1
            continue

        # signature-only then next line is {
        m2 = sig_re.match(line)
        if m2 and i+1 < len(lines) and lines[i+1].strip() == '{':
            ret = m2.group('ret').strip()
            name = m2.group('name')
            args = m2.group('args').strip() or 'void'
            protos.append(f"{ret} {name}({args});")
            i += 2
            continue

        i += 1

    return protos


def main():
    if len(sys.argv) != 2:
        print(f"Usage: {sys.argv[0]} path/to/source.c")
        sys.exit(1)

    src = sys.argv[1]
    if not src.endswith('.c') or not os.path.isfile(src):
        print("❌ Must point to an existing .c file")
        sys.exit(1)

    base = os.path.splitext(os.path.basename(src))[0]
    hdr = base + '2.h'

    with open(src) as f:
        lines = f.readlines()

    protos = extract_prototypes(lines)
    if not protos:
        print("⚠️  No prototypes found. Double‑check your style.")
        sys.exit(0)

    guard = base.upper() + "_H"
    with open(hdr, 'w') as f:
        f.write(f"#ifndef {guard}\n#define {guard}\n\n")
        for p in protos:
            f.write(p + "\n")
        f.write(f"\n#endif /* {guard} */\n")

    print(f"✅ Wrote {len(protos)} prototypes to {hdr}")


if __name__ == "__main__":
    main()
