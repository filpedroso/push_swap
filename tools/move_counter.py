import sys

def main():
    # Read from stdin
    moves = sys.stdin.read().strip().splitlines()
    
    # Filter out empty lines (just in case)
    moves = [line for line in moves if line.strip()]
    
    print(len(moves))

if __name__ == "__main__":
    main()
