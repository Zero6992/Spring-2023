import os
import time
import numpy as np

def alpha_beta(board, depth, alpha, beta, maximizing_player, score):
    if depth == 0 or np.sum(board) == 0:
        return score, None

    if maximizing_player:
        max_eval = float('-inf')
        max_move = None
        for move in get_moves(board):
            new_board = apply_move(board, move)
            move_score = get_move_score(board, move)
            eval, _ = alpha_beta(new_board, depth-1, alpha, beta, False, score + move_score)
            if eval > max_eval:
                max_eval = eval
                max_move = move
            alpha = max(alpha, eval)
            if beta <= alpha:
                break
        return max_eval, max_move
    else:
        min_eval = float('inf')
        min_move = None
        for move in get_moves(board):
            new_board = apply_move(board, move)
            move_score = get_move_score(board, move)
            eval, _ = alpha_beta(new_board, depth-1, alpha, beta, True, score - move_score)
            if eval < min_eval:
                min_eval = eval
                min_move = move
            beta = min(beta, eval)
            if beta <= alpha:
                break
        return min_eval, min_move
    
def get_move_score(board, move):
    if move[0] == 'Row':
        return np.sum(board[move[1]-1, :])
    else:
        return np.sum(board[:, move[1]-1])

def get_moves(board):
    moves = []
    for i in range(board.shape[0]):
        if np.sum(board[i, :]) > 0:
            moves.append(('Row', i+1))
    for j in range(board.shape[1]):
        if np.sum(board[:, j]) > 0:
            moves.append(('Column', j+1))
    return moves

def apply_move(board, move):
    new_board = board.copy()
    if move[0] == 'Row':
        new_board[move[1]-1, :] = 0
    else:
        new_board[:, move[1]-1] = 0
    return new_board

def read_input(file_name):
    with open(file_name, 'r') as file:
        n, m = map(int, file.readline().split())
        board = np.zeros((n, m))
        for i in range(n):
            board[i, :] = list(map(int, file.readline().split()))
    return board

def write_output(file_name, move, points, run_time):
    with open(file_name, 'a') as file:
        file.write(f'{move[0]}#: {move[1]}\n')
        file.write(f'{points} points\n')
        file.write(f'Total run time = {run_time} seconds.\n')
        file.write('------\n')

def main():
    if os.path.exists('output.txt'):
        with open('output.txt', 'r+') as file:
            file.truncate(0)
    for i in range(1, 6):
        start_time = time.time()
        board = read_input(f'input{i}.txt')
        points, move = alpha_beta(board, 5, float('-inf'), float('inf'), True, 0)
        run_time = round(time.time() - start_time, 4)
        write_output('output.txt', move, points, run_time)

if __name__ == "__main__":
    main()
