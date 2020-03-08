#!/usr/bin/python3
"""Finds & overwrites a string in a process' mem file"""

from sys import argv

USAGE = "USAGE: read_write_heap.py pid search_string replace_string"


def parse_maps_file(pid):
    """parses /proc/PID/maps file for heap info"""
    heap_start = heap_stop = None
    try:
        with open("/proc/{:d}/maps".format(pid), "r") as file:
            for line in file:
                if line.endswith("[heap]\n"):
                    heap_start, heap_stop = \
                        [int(x, 16) for x in line.split(" ")[0].split("-")]
    except Exception as e:
        print(e) or exit(1)
    if not heap_start or not heap_stop:
        print("[ERROR] Heap address not found.") or exit(1)
    print("[*] Heap starts at {:02X}".format(heap_start))
    return heap_start, heap_stop


def update_mem_file(pid, search_string, replace_string, heap_start, heap_stop):
    """finds search_string in /proc/PID/mem and writes replace_string"""
    try:
        with open("/proc/{:d}/mem".format(pid), "r+b") as f:
            f.seek(heap_start)
            data = f.read(heap_stop - heap_start)
            print("[*] Read {:d} bytes".format(heap_stop - heap_start))
            string_offset = data.find(search_string.encode())
            if string_offset > -1:
                print("[*] String found at {:02X}"
                      .format(heap_start + string_offset))
                f.seek(heap_start + string_offset)
                written = f.write(replace_string.encode() + b'\x00')
                print("[*] {:d} bytes written!".format(written))
            else:
                print(
                    "[ERROR] String '{:s}' not found in heap."
                    .format(search_string))
                exit(1)
    except Exception as e:
        print(e) or exit(1)

if __name__ == "__main__":
    if len(argv) < 4 or len(argv[2]) < len(argv[3]):
        print(USAGE) or exit(1)
    heap_start, heap_stop = parse_maps_file(int(argv[1]))
    update_mem_file(int(argv[1]), argv[2], argv[3], heap_start, heap_stop)
