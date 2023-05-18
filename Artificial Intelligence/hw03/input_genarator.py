import random

def generate_test_file(n=random.randint(2, 8), m=random.randint(1, 8), filename='input.txt'):
    with open(filename, 'w') as file:
        file.write(f'{n} {m}\n')
        for _ in range(n):
            file.write(' '.join(str(random.randint(0, 1)) for _ in range(m)) + '\n')

generate_test_file()
