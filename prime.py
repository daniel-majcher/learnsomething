import timeit

def disasterCode():
    knownPrimes = []
    for i in range (2,1000):
        uniquePrimes = []
        isPrime = True
        for prime in knownPrimes:
            if i%prime==0:
                isPrime = False
                uniquePrimes.append(prime)
        if isPrime:
            knownPrimes.append(i)

# Benchmark the code
if __name__ == "__main__":
    benchmark_code = "disasterCode()"
    setup_code = "from __main__ import disasterCode"

    # Measure the execution time of disasterCode function
    times = []
    for i in range(0,5):
        times.append(timeit.timeit(benchmark_code, setup=setup_code, number=1))

    res = sum(times)/5

    print(f"Average execution time after 5 runs: {res:.6f} seconds")
