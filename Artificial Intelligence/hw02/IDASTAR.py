import sys
import time
import os

sys.setrecursionlimit(10000)

def read_input(file_path):
    with open(file_path, 'r') as f:
        return list(map(int, f.read().strip().split()))

def write_output(file_path, run_time, moves=None):
    with open(file_path, 'a') as f:
        f.write(f'Total run time = {run_time:.6f} seconds\n')
        if moves is not None:
            f.write(f'An optimal solution has {len(moves)} moves:\n')
            f.write(' '.join(str(move) for move in moves))
        else:
            f.write('There is no solution.')
        f.write('\n')

def spread_cancer(board):
    new_board = [0] * len(board)
    for i in range(len(board)):
        if board[i] == 1:
            if i - 1 >= 0:
                new_board[i - 1] = 1
            if i + 1 < len(board):
                new_board[i + 1] = 1
    return new_board

def heuristic(board):
    return sum(board)

def ida_star_search(board, depth, moves, bound, visited_states):
    h = heuristic(board)
    if h == 0:
        return moves

    if h + depth > bound:
        return None

    state_tuple = tuple(board)
    if state_tuple in visited_states:
        return None
    visited_states.add(state_tuple)

    for i in range(len(board)):
        if board[i] == 1:
            new_board = board.copy()
            new_board[i] = 0
            new_board = spread_cancer(new_board)
            new_state_tuple = tuple(new_board)
            if new_state_tuple in visited_states:
                continue
            result = ida_star_search(new_board, depth + 1, moves + [i + 1], bound, visited_states.copy())
            if result is not None:
                return result
    return None

def ida_star(board):
    bound = heuristic(board)
    while True:
        result = ida_star_search(board, 0, [], bound, set())
        if result is not None:
            return result
        bound += 1

def main():
    input_files = ['input1.txt', 'input2.txt', 'input3.txt', 'input4.txt', 'input5.txt']
    output_path = 'output-IDASTAR.txt'

    if os.path.exists(output_path):
        os.remove(output_path)

    for i, input_file in enumerate(input_files, start=1):
        print(f"Running input{i}.txt... ")
        start_time = time.time()
        board = read_input(input_file)

        solution, execution_time = None, None
        for _ in range(6000):
            solution = ida_star(board)
            execution_time = time.time() - start_time
            if solution is not None:
                break
            time.sleep(1)

        if execution_time >= 6000:
            print("Time exceed 600 seconds")
            with open(output_path, 'a') as output_file:
                output_file.write(f'----- {input_file} -----\n')
            write_output(output_path, execution_time, None)
            continue

        print(f"Done. time: {execution_time:.6f} seconds")
        with open(output_path, 'a') as output_file:
            output_file.write(f'----- {input_file} -----\n')
        write_output(output_path, execution_time, solution if solution != "NO_SOLUTION" else None)

if __name__ == '__main__':
    main()

