import time
import numpy as np

# Function to load board from file
def load_board(filename):
    with open(filename, 'r') as file:
        n, m = map(int, file.readline().split())
        board = [list(map(int, line.split())) for line in file]
    return np.array(board), n, m

# Function to calculate score for given state
def calc_score(state):
    print(np.sum(state))
    return np.sum(state)

# Function to get all possible moves
def get_possible_moves(state, n, m):
    moves = []
    for i in range(n):
        if np.sum(state[i, :]) > 0:
            moves.append(("Row", i+1))
    for i in range(m):
        if np.sum(state[:, i]) > 0:
            moves.append(("Column", i+1))
    return moves

# Function to apply a move
def apply_move(state, move):
    new_state = state.copy()
    if move[0] == "Row":
        new_state[move[1]-1, :] = 0
    else:
        new_state[:, move[1]-1] = 0
    return new_state

# Function to check if game has ended
def is_game_over(state):
    return np.sum(state) == 0

# Alpha-beta pruning function
def alpha_beta(state, depth, alpha, beta, maximizing_player, n, m):
    if depth == 0 or is_game_over(state):
        return calc_score(state), None

    possible_moves = get_possible_moves(state, n, m)

    if maximizing_player:
        max_eval = float('-inf')
        best_move = None
        for move in possible_moves:
            new_state = apply_move(state, move)
            new_score = calc_score(state) - calc_score(new_state)
            eval, _ = alpha_beta(new_state, depth - 1, alpha, beta, False, n, m)
            eval = new_score - eval
            if eval > max_eval:
                max_eval = eval
                best_move = move
            alpha = max(alpha, eval)
            if beta <= alpha:
                break
        return max_eval, best_move
    else:
        min_eval = float('inf')
        best_move = None
        for move in possible_moves:
            new_state = apply_move(state, move)
            eval, _ = alpha_beta(new_state, depth - 1, alpha, beta, True, n, m)
            if eval < min_eval:
                min_eval = eval
                best_move = move
            beta = min(beta, eval)
            if beta <= alpha:
                break
        return min_eval, best_move

# Function to execute game
def execute_game(input_file, output_file):
    start_time = time.time()
    board, n, m = load_board(input_file)
    _, best_move = alpha_beta(board, n*m, float('-inf'), float('inf'), True, n, m)
    final_state = apply_move(board, best_move)
    final_score = calc_score(board) - calc_score(final_state)
    execution_time = time.time() - start_time

    with open(output_file, 'w') as file:
        file.write(f'{best_move[0]}#: {best_move[1]}\n')
        file.write(f'{final_score} points\n')
        file.write(f'Total run time = {execution_time:.2f} seconds.\n')

# Execute game
execute_game('input.txt', 'output.txt')
