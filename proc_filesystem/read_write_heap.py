#!/usr/bin/python3

"""
This module finds a string in the heap of a running process, and replaces it.
"""

import sys
import os
import re
import struct

def main():
    """
    finds a string in the heap of a running process, and replaces it.
    """
    if len(sys.argv) != 4:
        print("argument error")
        sys.exit(1)

    try:
        pid = int(sys.argv[1])
        search_string = sys.argv[2]
        replace_string = sys.argv[3]
    except ValueError:
        print("argument error")
        sys.exit(1)

    if not os.path.exists(f"/proc/{pid}"):
        print(f"error: process {pid} does not exist")
        sys.exit(1)
    
    maps_file = f"/proc/{pid}/maps"

    start_address = None
    end_address = None

    with open(maps_file, "r") as file:
        for line in file:
            if "[heap]" in line:
                print("{line}\n")
                match = re.match(r"([0-9a-f]+)-([0-9a-f]+) r[w-]p .* \[heap\]", line)
                if match:
                    start_address = int(match.group(1), 16)
                    end_address = int(match.group(2), 16)
                    break
    
    if start_address is None or end_address is None:
        print("error: could not find heap")
        sys.exit(1)

    mem_file = f"/proc/{pid}/mem"

    with open (mem_file, "r+b") as mem:
        mem.seek(start_address)

        heap = mem.read(end_address - start_address)

        search_bytes = search_string.encode("ascii")
        replace_bytes = replace_string.encode("ascii")

        pos = heap.find(search_bytes)

        if pos == -1:
            print(f"'{search_string}' not found in heap")
            sys.exit(1)
        
        mem.seek(start_address + pos)

        mem.write(replace_bytes)
        print(f"Replaced '{search_string}' with '{replace_string}' in heap at address {hex(start_address + pos)}.")

if __name__ == "__main__":
    main()

