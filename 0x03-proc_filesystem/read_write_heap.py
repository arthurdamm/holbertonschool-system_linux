#!/usr/bin/python3
"""Finds & overwrites a string in a process' mem file"""

from sys import argv, stdout

USAGE = "USAGE: read_write_heap.py pid search_string replace_string\n"

if __name__ == "__main__":
    if len(argv) < 4:
        stdout.write(USAGE)
        exit(1)
    if not len(argv[2]) or not len(argv[3]) or len(argv[2]) < len(argv[3]):
        stdout.write(USAGE)
        exit(1)
    heap_start = None
    try:
        with open("/proc/{:d}/maps".format(int(argv[1])), "r") as file:
            for line in file:
                if line.endswith("[heap]\n"):
                    heap_start, heap_stop = \
                        [int(x, 16) for x in line.split(" ")[0].split("-")]
    except Exception as e:
        stdout.write(str(e) + "\n")
        exit(1)
    if not heap_start or not heap_stop:
        stdout.write("[ERROR] Heap address not found.\n")
        exit(1)
    print("[*] Heap starts at {:02X}".format(heap_start))
    try:
        with open("/proc/{:d}/mem".format(int(argv[1])), "rb") as f:
            f.seek(heap_start)
            data = f.read(heap_stop - heap_start)
            print("[*] Read {:d} bytes".format(heap_stop - heap_start))
            string_offset = data.find(argv[2].encode())
        if string_offset > -1:
            print("[*] String found at {:02X}"
                  .format(heap_start + string_offset))
            with open("/proc/{:d}/mem".format(int(argv[1])), "wb") as f:
                f.seek(heap_start + string_offset)
                written = f.write(argv[3].encode() + b'\x00')
                print("[*] {:d} bytes written!".format(written))
        else:
            stdout.write(
                "[ERROR] String '{:s}' not found in heap.\n".format(argv[2]))
            exit(1)
    except Exception as e:
        stdout.write(str(e) + "\n")
        exit(1)
