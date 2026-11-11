import re
import sys
from pathlib import Path

# 符合:# <center> 內容 </center>(# 數量不限)
PATTERN = re.compile(r"^(#+)\s*<center>\s*(.*?)\s*</center>\s*$", re.IGNORECASE)


def fix_file(path: Path, apply: bool) -> bool:
    # newline="" 保留原本的換行符號(CRLF 或 LF),不會被改掉
    with open(path, "r", encoding="utf-8", newline="") as f:
        lines = f.read().splitlines(keepends=True)

    for i, line in enumerate(lines):
        if not line.startswith("#"):
            continue  # 找第一個標題行
        body = line.rstrip("\r\n")
        ending = line[len(body):]
        new_body = PATTERN.sub(r"\1 \2", body)
        if new_body == body:
            return False  # 第一個標題沒有 <center>,不處理
        print(f"{path}\n  - {body}\n  + {new_body}")
        if apply:
            lines[i] = new_body + ending
            with open(path, "w", encoding="utf-8", newline="") as f:
                f.write("".join(lines))
        return True  # 只處理第一個標題,處理完就結束
    return False


def main() -> None:
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    apply = "--apply" in sys.argv
    root = Path(args[0]) if args else Path(".")

    count = sum(fix_file(p, apply) for p in root.rglob("*.md"))
    mode = "已修改" if apply else "預覽(未修改,加 --apply 才會寫入)"
    print(f"\n{mode}:共 {count} 個檔案")


if __name__ == "__main__":
    main()