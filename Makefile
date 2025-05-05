# Add to existing Makefile

TEST_OBJS = tests/unit/test_preprocessing.o tests/unit/test_kmeans.o \
            tests/unit/test_elbow.o tests/integration/test_integration.o \
            tests/performance/benchmark.o tests/test_utils.o

test_preprocessing: tests/unit/test_preprocessing.o tests/test_utils.o src/preprocessing.o src/riscv_utils.o
	$(CC) $(LDFLAGS) -o $@ $^

test_kmeans: tests/unit/test_kmeans.o tests/test_utils.o src/kmeans.o src/preprocessing.o src/riscv_utils.o
	$(CC) $(LDFLAGS) -o $@ $^

test_integration: tests/integration/test_integration.o tests/test_utils.o \
                 src/kmeans.o src/elbow.o src/preprocessing.o src/riscv_utils.o
	$(CC) $(LDFLAGS) -o $@ $^

benchmark: tests/performance/benchmark.o tests/test_utils.o \
           src/kmeans.o src/elbow.o src/preprocessing.o src/riscv_utils.o
	$(CC) $(LDFLAGS) -o $@ $^

test_all: test_preprocessing test_kmeans test_integration
	spike pk test_preprocessing
	spike pk test_kmeans
	spike pk test_integration

clean:
	rm -f $(OBJS) $(TEST_OBJS) clustering.elf test_preprocessing test_kmeans test_integration benchmark
