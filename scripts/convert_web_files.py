import os

Import("env")

SRC_DIR = os.path.join(env["PROJECT_DIR"], "res")
DST_DIR = os.path.join(env["PROJECT_DIR"], "include/pre_builded_headers")

def process_file(path):
    with open(path, "r", encoding="utf-8") as f:
        data = f.read()

    data = data.replace("\n", "")
    data = data.replace("    ", "")
    data = data.replace('"', '\\"')
    return data

def generate(var_name, data):
    return (
        "#pragma once\n"
        "#include <pgmspace.h>\n\n"
        f'const char {var_name}[] PROGMEM = "{data}";\n'
    )

def convert():
    for file in os.listdir(SRC_DIR):
        if not (file.endswith(".html") or file.endswith(".css")):
            continue

        in_path = os.path.join(SRC_DIR, file)
        var_name = file.replace(".", "_")
        out_path = os.path.join(DST_DIR, var_name + ".h")

        data = process_file(in_path)
        content = generate(var_name, data)

        with open(out_path, "w", encoding="utf-8") as f:
            f.write(content)

convert()