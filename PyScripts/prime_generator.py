from sys import argv

def is_prime(number: int) -> bool:
    if number % 2 == 0:
        return False

    for i in range(3, int(number ** 0.5) + 1, 2):
        if number % i == 0:
            return False
    return True

def get_prime(at_least: int) -> int:
    n = at_least
    n += 1 - (n % 2)

    while not is_prime(n):
        n += 2
    return n


def main():
    print(get_prime(int(argv[1])))

if __name__ == '__main__':
    main()
