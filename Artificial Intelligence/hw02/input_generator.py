import random

def generate_input_file(file_name, board_size, cancer_ratio):
    with open(file_name, "w") as file:
        board = [1 if random.random() < cancer_ratio else 0 for _ in range(board_size)]
        file.write(" ".join(map(str, board)) + "\n")

def main():
    for i in range(1, 6):
        generate_input_file(f"input{i}.txt", random.randint(1, 10), random.uniform(0.3, 0.7))

if __name__ == "__main__":
    main()

